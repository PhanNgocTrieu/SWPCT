// Copyright (c) 2013-2022 LG Electronics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0

#include "webossurfaceitem.h"
#include "webossurfacegroup.h"
#include "weboswindowmodel.h"
#include "webosgroupedwindowmodel.h"
#include "webossurfacemodel.h"
#include "weboscorecompositor.h"
#include "weboscompositorwindow.h"
#include "weboscompositortracer.h"
#include "webosshellsurface.h"
#include "webosinputmethod.h"
#ifdef MULTIINPUT_SUPPORT
#include "webosinputdevice.h"
#endif
#include <QDateTime>
#include <QQmlEngine>
#include <QOpenGLTexture>
#include <QWaylandQuickSurface>
#include <QDebug>

#include <qweboskeyextension.h>

#include <QtWaylandCompositor/qwaylandseat.h>
#include <QtWaylandCompositor/private/qwaylandkeyboard_p.h>
#include <QtWaylandCompositor/qwaylandbufferref.h>

#include "weboscompositortracer.h"
#include "weboskeyboard.h"

WebOSSurfaceItem::WebOSSurfaceItem(WebOSCoreCompositor* compositor, QWaylandQuickSurface* surface)
        : QWaylandQuickItem()
        , m_compositor(compositor)
        , m_fullscreen(false)
        , m_lastFullscreenTick(0)
        , m_groupedWindowModel(0)
        , m_cardSnapShotFilePath()
        , m_customImageFilePath(QLatin1String("none"))
        , m_backgroundImageFilePath()
        , m_backgroundColor("")
        , m_shellSurface(0)
        , m_itemState(ItemStateNormal)
        , m_itemStateReason(QString())
        , m_notifyPositionToClient(true)
        , m_displayId(-1)
        , m_displayAffinity(0)
        , m_appId("")
        , m_type("_WEBOS_WINDOW_TYPE_CARD")
        , m_windowClass(WindowClass_Normal)
        , m_title("")
        , m_subtitle("")
        , m_params("")
        , m_launchLastApp(false)
        , m_launchLastInputApp(false)
        , m_typeTransitioning(false)
        , m_orientation(Qt::LandscapeOrientation)
        , m_containsMouse(false)
        , m_hovered(false)
        , m_processId()
        , m_exposed(false)
        , m_launchRequired(false)
        , m_hasKeyboardFocus(false)
        , m_grabKeyboardFocusOnClick(true)
        , m_surfaceGroup(0)
        , m_closePolicy(QVariantMap())
        , m_coverState(CoverStateNormal)
        , m_activeRegion(QRect(0,0,0,0))
        , m_fullscreenMode(false)
{
    setSurface(surface);

    if (surface) {
        connect(surface, SIGNAL(damaged(const QRegion &)), this, SLOT(onSurfaceDamaged(const QRegion &)));
    }

    connect(this, &QQuickItem::xChanged, this, &WebOSSurfaceItem::updateScreenPosition);
    connect(this, &QQuickItem::yChanged, this, &WebOSSurfaceItem::updateScreenPosition);
    // Send position_changed whenever the surface resizes
    // so that the client gets notified that the resize is done
    connect(this, &QQuickItem::widthChanged, this, &WebOSSurfaceItem::updateScreenPosition);
    connect(this, &QQuickItem::heightChanged, this, &WebOSSurfaceItem::updateScreenPosition);
    // Set the ownership as CppOwnership explicitly to prevent from garbage collecting by JS engine
    QQmlEngine::setObjectOwnership((QObject*)this, QQmlEngine::CppOwnership);

    //In Qt5.2, All MouseAreas have default cursor as default value. So all surfaceitems should have default cursor as a initial value so that
    //it can restore the cursor from the system ui's cursor. See QQuickWindowPrivate::updateCursor()
    setCursor(Qt::ArrowCursor);

    if (!qgetenv("WEBOS_DISABLE_TOUCH").isEmpty())
        setTouchEventsEnabled(false);
    else
        setTouchEventsEnabled(true);

    if (m_compositor->webOS2DGraphicDeviceExtension()) {
        Compositor2DGraphicDevice *gdev = m_compositor->webOS2DGraphicDeviceExtension()->graphicDevice2D();
        if (gdev) {
            connect(gdev, &Compositor2DGraphicDevice::sceneGraphPaintNodeTypeChanged,
                    this, &WebOSSurfaceItem::onSceneGraphPaintNodeTypeChanged);
            onSceneGraphPaintNodeTypeChanged(gdev->sceneGraphPaintNodeType());
        }
    }

    connect(this, &QQuickItem::windowChanged, this, &WebOSSurfaceItem::handleWindowChanged);
    connect(surface, &QWaylandSurface::contentOrientationChanged, this, &WebOSSurfaceItem::contentOrientationChanged);

    connect(m_compositor, SIGNAL(cursorVisibleChanged()), this, SLOT(updateContainsMouse()));
    setObjectName(QStringLiteral("surfaceItem_default"));
    if (surface)
        surface->setObjectName(QStringLiteral("surface_default"));
}

WebOSSurfaceItem::~WebOSSurfaceItem()
{
    emit surfaceAboutToBeDestroyed();

    sendCloseToGroupItems();
    if (isSurfaceGroupRoot())
        m_surfaceGroup->setRootItem(NULL);
    m_surfaceGroup = NULL;
    deleteCardSnapshot();
    delete m_shellSurface;
}

void WebOSSurfaceItem::setDisplayId(int id)
{
    if (m_displayId != id) {
        m_displayId = id;
        emit displayIdChanged();
    }
}

void WebOSSurfaceItem::setDisplayAffinity(int affinity)
{
    if (m_displayAffinity != affinity) {
        qInfo() << "setting display affinity" << affinity << "for" << this;
        m_displayAffinity = affinity;
        emit displayAffinityChanged();
        emit dataChanged();
    }
}

void WebOSSurfaceItem::handleWindowChanged()
{
    qInfo() << this << "moved to window" << window();
    setDisplayId(window() ? static_cast<WebOSCompositorWindow *>(window())->displayId() : -1);
    if (!window()) {
        m_hovered = false;
        updateContainsMouse();
    }
}

void WebOSSurfaceItem::requestMinimize()
{
    PMTRACE_FUNCTION;
    emit m_compositor->minimizeRequested(this);
}

bool WebOSSurfaceItem::requestFullscreen()
{
    PMTRACE_FUNCTION;
    emit m_compositor->fullscreenRequested(this);
    // TODO remove return types
    return true;
}

bool WebOSSurfaceItem::fullscreen() const
{
    return m_fullscreen;
}

void WebOSSurfaceItem::setFullscreen(bool enabled)
{
    PMTRACE_FUNCTION;
    // Currently this should not be called directly from qml or from other
    // place. To make a surface full screen use "requestFullscreen()" method
    if (m_fullscreen != enabled) {
        m_fullscreen = enabled;
        emit fullscreenChanged(m_fullscreen);
        if (enabled) {
            setExposed(true);
        } else {
            // Update the tick when the item goes into recents
            // Otherwise, a Card which is just launched will be sorted during animation.
            m_lastFullscreenTick = m_compositor->getFullscreenTick();
            emit lastFullscreenTickChanged();
        }

        emit dataChanged();
    }
}

QList<QTouchEvent::TouchPoint> WebOSSurfaceItem::mapToTarget(const QList<QTouchEvent::TouchPoint>& points) const
{
    QList<QTouchEvent::TouchPoint> result;
    foreach (QTouchEvent::TouchPoint point, points) {
        point.setPos(mapToSurface(point.pos()));
        result.append(point);
    }
    return result;
}

void WebOSSurfaceItem::takeWlKeyboardFocus() const
{
    if (!isSurfaced()) {
        qWarning("null surface(), not setting focus");
        return;
    }
    /* set keyboard focus for all devices */
    foreach (QWaylandSeat *dev, m_compositor->inputDevices()) {
        if (dev)
            dev->setKeyboardFocus(surface());
    }
}

bool WebOSSurfaceItem::isWlKeyboardFocusTaken() const
{
    bool bIsWlKeyboardFocusTaken = true;
    foreach (QWaylandSeat *dev, m_compositor->inputDevices()) {
        if (dev)
            bIsWlKeyboardFocusTaken = bIsWlKeyboardFocusTaken && (surface() == dev->keyboardFocus());
    }
    return bIsWlKeyboardFocusTaken;
}

bool WebOSSurfaceItem::contains(const QPointF& point) const
{
    return inputRegionContains(point);
}

bool WebOSSurfaceItem::isMapped()
{
    return m_compositor && m_compositor->isMapped(this);
}

void WebOSSurfaceItem::hoverMoveEvent(QHoverEvent *event)
{
    if (acceptHoverEvents()) {
        QMouseEvent e(QEvent::MouseMove, event->pos(), Qt::NoButton, Qt::NoButton, event->modifiers());
        mouseMoveEvent(&e);
    }
}

void WebOSSurfaceItem::mouseMoveEvent(QMouseEvent * event)
{
    // Make sure client to receive the latest position before the mouse event
    updateScreenPosition();

    QMouseEvent e(event->type(), event->pos(),
                  event->button(), event->buttons(), event->modifiers());
    QWaylandQuickItem::mouseMoveEvent(&e);
}

void WebOSSurfaceItem::mousePressEvent(QMouseEvent *event)
{
    if (surface()) {
       QMouseEvent e(event->type(), event->localPos().toPoint(),
           event->button(), event->buttons(), event->modifiers());

        QWaylandSeat *inputDevice = getInputDevice(&e);

        if (inputDevice) {
            if (inputDevice->mouseFocus() != view())
                inputDevice->setMouseFocus(view());

            if (inputDevice->mouseFocus()
                    && inputDevice->mouseFocus()->surface() != inputDevice->keyboardFocus()
                    && m_grabKeyboardFocusOnClick) {
                takeWlKeyboardFocus();
                m_hasKeyboardFocus = true;
                emit hasKeyboardFocusChanged();
            }
        }

        // Send extra mouse move event as otherwise the client
        // will handle the button event in the incorrect coordinate
        // in case the surface size is changed.
        mouseMoveEvent(&e);
        qInfo() << "[MOUSE:PressEvent] appId:" << appId();
        inputDevice->sendMousePressEvent(e.button());
    }
}

void WebOSSurfaceItem::mouseReleaseEvent(QMouseEvent *event)
{
    if (surface()) {
        QMouseEvent e(event->type(), event->localPos().toPoint(),
                      event->button(), event->buttons(), event->modifiers());
        // Send extra mouse move event as otherwise the client
        // will handle the button event in the incorrect coordinate
        // in case the surface size is changed.
        mouseMoveEvent(&e);
        qInfo() << "[MOUSE:ReleaseEvent] appId:" << appId();
        QWaylandQuickItem::mouseReleaseEvent(&e);
    }
}

void WebOSSurfaceItem::wheelEvent(QWheelEvent *event)
{
    QWheelEvent e(event->pos(), event->globalPos(), event->pixelDelta(),
                  event->angleDelta(), event->delta(), Qt::Vertical, event->buttons(), event->modifiers());

#ifdef MULTIINPUT_SUPPORT
    QWaylandSeat *inputDevice = getInputDevice(&e);
    if (inputDevice && inputDevice->mouseFocus() != view())
        inputDevice->setMouseFocus(view());
#else
    m_compositor->defaultSeat()->setMouseFocus(surface());
#endif

    if (surface()) {
        // Send extra mouse move event as otherwise the client
        // will handle the wheel event in the incorrect coordinate
        // in case the surface size is changed.
        QMouseEvent ee(QEvent::MouseMove, event->pos(), Qt::NoButton, Qt::NoButton, event->modifiers());
        mouseMoveEvent(&ee);
    }

    QWaylandQuickItem::wheelEvent(&e);
}

void WebOSSurfaceItem::touchEvent(QTouchEvent *event)
{
    QTouchEvent e(event->type(), event->device(), event->modifiers(),
                  event->touchPointStates(), mapToTarget(event->touchPoints()));
    e.setWindow(event->window());

    // This may not be needed with QtWayland 5.12
    // Currently, this is due to QWaylandSurfaceItem::mouseUngrabEvent
    // which sends the Cancel without window().
    if (!event->window())
        e.setWindow(window());

    if (surface() && inputEventsEnabled() && touchEventsEnabled()) {
        WebOSCompositorWindow *w = static_cast<WebOSCompositorWindow *>(window());
        QWaylandSeat *seat = nullptr;

#ifdef MULTIINPUT_SUPPORT
        seat = getInputDevice(&e);
#else
        if (w)
            seat = w->inputDevice();
#endif
        if (seat == nullptr) {
            qWarning("no input device for this event");
            event->ignore();
            return;
        }

        QPoint pointPos;
        const QList<QTouchEvent::TouchPoint> &points = e.touchPoints();
        if (!points.isEmpty())
            pointPos = points.at(0).pos().toPoint();

        if (e.type() == QEvent::TouchBegin && !surface()->inputRegionContains(pointPos)) {
            event->ignore();
            return;
        }

        event->accept();
        if (seat->mouseFocus() != view())
            seat->sendMouseMoveEvent(view(), pointPos, mapToScene(pointPos));

        if (e.type() == QEvent::TouchBegin) {
            if (seat->mouseFocus() &&
                seat->mouseFocus()->surface() != seat->keyboardFocus() &&
                m_grabKeyboardFocusOnClick) {
                /* set keyboard focus for all devices */
                takeWlKeyboardFocus();
                m_hasKeyboardFocus = true;
                emit hasKeyboardFocusChanged();
            }
        }

        if (e.touchPointStates() & Qt::TouchPointPressed)
            qInfo() << "[TOUCH:TouchPointPressed] appId:" << appId();
        else if (e.touchPointStates() & Qt::TouchPointReleased)
            qInfo() << "[TOUCH:TouchPointReleased] appId:" << appId();
        seat->sendFullTouchEvent(surface(), &e);

        if (m_compositor->getTestMode()) {
            m_compositor->setConfirmTouchTestMode(true);
        }
        else {
            m_compositor->setConfirmTouchTestMode(false);
        }
    } else {
        QWaylandQuickItem::touchEvent(event);
    }
}

void WebOSSurfaceItem::hoverEnterEvent(QHoverEvent *event)
{
    Q_UNUSED(event);
    if (acceptHoverEvents() && surface()) {
#ifdef MULTIINPUT_SUPPORT
        if (m_compositor->seatFor(event))
            m_compositor->seatFor(event)->setMouseFocus(view());
#else
        if (m_compositor->defaultSeat())
            m_compositor->defaultSeat()->setMouseFocus(view());
#endif
        if (!m_hovered) {
            m_hovered = true;
            updateContainsMouse();
        }
    }

    m_compositor->notifyPointerEnteredSurface(this->surface());
    QWaylandQuickItem::hoverEnterEvent(event);
}

void WebOSSurfaceItem::hoverLeaveEvent(QHoverEvent *event)
{
    Q_UNUSED(event);
    if (acceptHoverEvents() && surface()) {
        QPointF curPosition = static_cast<QPointF>(QCursor::pos());
#ifdef MULTIINPUT_SUPPORT
        m_compositor->resetMouseFocus(surface());
#else
        if (m_compositor->defaultSeat())
            m_compositor->defaultSeat()->setMouseFocus(NULL, curPosition, curPosition);
#endif
        if (m_hovered) {
            m_hovered = false;
            updateContainsMouse();
        }
    }

    m_compositor->notifyPointerLeavedSurface(this->surface());
    QWaylandQuickItem::hoverLeaveEvent(event);
}

void WebOSSurfaceItem::updateContainsMouse()
{
    if (m_hovered)
        m_containsMouse = m_compositor->cursorVisible();
    else
        m_containsMouse = false;
    emit containsMouseChanged();
}

QWaylandSeat* WebOSSurfaceItem::getInputDevice(QInputEvent *event) const
{
#ifdef MULTIINPUT_SUPPORT
    return m_compositor->seatFor(event);
#else
    Q_UNUSED(event);
    if (!isSurfaced()) {
        qWarning("no surface, returning compositor->defaultSeat.");
        return m_compositor->defaultSeat();
    }
    return surface()->compositor()->defaultSeat();
#endif
}

void WebOSSurfaceItem::mouseUngrabEvent()
{
#ifdef MULTIINPUT_SUPPORT
    if (surface()) {
        QTouchEvent e(QEvent::TouchCancel);
        for (int i = 1; i < m_compositor->inputDevices().size(); i++) {
            QWaylandSeat *dev = m_compositor->inputDevices().at(i);
            if (!surface()->views().isEmpty() && dev && dev->mouseFocus() == surface()->views().first()) {
                if(dynamic_cast<WebOSInputDevice*>(dev))
                    e = QTouchEvent(QEvent::TouchCancel, Q_NULLPTR, (Qt::KeyboardModifiers)(static_cast<WebOSInputDevice*>(dev)->id()));
                break;
            }
        }
        QWaylandQuickItem::touchEvent(&e);
    }
#else
    QWaylandQuickItem::mouseUngrabEvent();
#endif
}

void WebOSSurfaceItem::keyPressEvent(QKeyEvent *event)
{
    PMTRACE_FUNCTION;

    QWaylandSeat *inputDevice = getInputDevice(event);
    if (!inputDevice) {
        qWarning() << "no input device for this event";
        return;
    }
    auto keyboard = static_cast<WebOSKeyboard*>(inputDevice->keyboard());

    if (surface()) {
        if ((isPartOfGroup() || isSurfaceGroupRoot()) &&
            //If keyboard is grabbed, do not propagate key events between
            //window-group to avoid unintended keyboard focus change.
            !keyboard->currentGrab()) {
            if (acceptsKeyEvent(event)) {
                if (!isWlKeyboardFocusTaken()) {
                    takeWlKeyboardFocus();
                    qInfo() << "Take keyboard focus: " << this << event->key();
                } else {
                    qInfo() << "Already keyboard focused: " << this << event->key();
                }
                inputDevice->sendFullKeyEvent(event);
            } else {
                if (m_surfaceGroup) {
                    WebOSSurfaceItem *nextItem = NULL;
                    if (m_surfaceGroup->allowLayerKeyOrder()) {
                        nextItem = m_surfaceGroup->nextKeyOrderedSurfaceGroupItem(this);
                        qInfo() << this << "investigates next key ordered item: " << nextItem << event->key();
                    }
                    else {
                        nextItem = m_surfaceGroup->nextZOrderedSurfaceGroupItem(this);
                        qInfo() << this << "investigates next z ordered item: " << nextItem << event->key();
                    }
                    if (nextItem) {
                        nextItem->keyPressEvent(event);
                    } else {
                        qInfo() << this << "got no next ordered item: " << event->key() << m_surfaceGroup->allowLayerKeyOrder();
                    }
                }
            }
        } else {
            if (hasFocus()) {
                qInfo() << "Focused surface is not a group member and not a current keyboard grab: " << this << event->key();
                QString bannerwebappId("com.webos.app.bannerwebapp");
                if(appId() == bannerwebappId && inputDevice->keyboardFocus() != surface()) {
                        qInfo() << "Surface is not focused, change focus and send " << this << event->key();
                        QWaylandSurface* currentActiveSurface = inputDevice->keyboardFocus();
                        inputDevice->setKeyboardFocus(surface());
                        inputDevice->sendFullKeyEvent(event);
                        inputDevice->setKeyboardFocus(currentActiveSurface);
                }
                else {
                    inputDevice->sendFullKeyEvent(event);
                }
            } else {
                qInfo() << "Surface is not focused and not a current keyboard grab. Do not send key: " << this << event->key();
            }
        }
    } else {
        qInfo() << "Not surfaced: " << this << event->key();
    }
}

void WebOSSurfaceItem::keyReleaseEvent(QKeyEvent *event)
{
    PMTRACE_FUNCTION;

    QWaylandSeat *inputDevice = getInputDevice(event);
    if (!inputDevice) {
        qWarning() << "no input device for this event";
        return;
    }
    auto keyboard = static_cast<WebOSKeyboard*>(inputDevice->keyboard());

    if (surface()) {
        if ((isPartOfGroup() || isSurfaceGroupRoot()) &&
            //If keyboard is grabbed, do not propagate key events between
            //window-group to avoid unintended keyboard focus change.
            !keyboard->currentGrab()) {
            if (acceptsKeyEvent(event)) {
                if (!isWlKeyboardFocusTaken()) {
                    takeWlKeyboardFocus();
                }
                inputDevice->sendFullKeyEvent(event);
            } else {
                if (m_surfaceGroup) {
                    WebOSSurfaceItem *nextItem = NULL;
                    if (m_surfaceGroup->allowLayerKeyOrder())
                        nextItem = m_surfaceGroup->nextKeyOrderedSurfaceGroupItem(this);
                    else
                        nextItem = m_surfaceGroup->nextZOrderedSurfaceGroupItem(this);
                    if (nextItem) {
                        nextItem->keyReleaseEvent(event);
                    }
                }
            }
        } else {
            if (hasFocus()) {
                QString bannerwebappId("com.webos.app.bannerwebapp");
                if(appId() == bannerwebappId && inputDevice->keyboardFocus() != surface()) {
                        qInfo() << "Surface is not focused, change focus and send " << this << event->key();
                        QWaylandSurface* currentActiveSurface = inputDevice->keyboardFocus();
                        inputDevice->setKeyboardFocus(surface());
                        inputDevice->sendFullKeyEvent(event);
                        inputDevice->setKeyboardFocus(currentActiveSurface);
                }
                else {
                    inputDevice->sendFullKeyEvent(event);
                }
            }
        }
    }
}

void WebOSSurfaceItem::focusInEvent(QFocusEvent *event)
{
    takeWlKeyboardFocus();
    QQuickItem::focusInEvent(event);
}

void WebOSSurfaceItem::focusOutEvent(QFocusEvent *event)
{
#ifdef MULTIINPUT_SUPPORT
    //Reset Keybaord/Pointer focus
    foreach (QWaylandSeat *dev, m_compositor->inputDevices()) {
	if (dev) {
            if (dev->keyboardFocus() == surface())
                dev->setKeyboardFocus(0);
            if (surface() && !surface()->views().isEmpty()
                && dev->mouseFocus() == surface()->views().first())
                dev->setMouseFocus(nullptr);
	}
    }
#else
    QWaylandSeat *inputDevice = m_compositor->defaultSeat();
    if (inputDevice) {
        if (inputDevice && inputDevice->keyboardFocus() == surface())
            inputDevice->setKeyboardFocus(0);
        if (surface() && inputDevice && inputDevice->mouseFocus() == surface()->views().first())
            inputDevice->setMouseFocus(nullptr);
    }
#endif

    m_compositor->setMouseEventEnabled(true);

    QQuickItem::focusOutEvent(event);
}

QVariantMap WebOSSurfaceItem::windowProperties()
{
    if (m_shellSurface) {
        return m_shellSurface->properties();
    }
    qWarning() << this << "m_shellSurface not available, use surface() instead";
    if (!isSurfaced()) {
        qWarning("null surface(), returning empty property map");
        return QVariantMap();
    }

    QVariantMap res;
    for (auto name: surface()->dynamicPropertyNames())
        res[name] = surface()->property(name.constData());

    return res;
}

void WebOSSurfaceItem::setWindowProperty(const QString& key, const QVariant& value)
{
    if (m_shellSurface) {
        m_shellSurface->setProperty(key, value, false);
    } else {
        qWarning() << this << "m_shellSurface not available, use surface() instead";
        if (!isSurfaced()) {
            qWarning("null surface(), setting property is NOOP");
            return;
        }
        surface()->setProperty(key.toLatin1().constData(), value);
    }
}

void WebOSSurfaceItem::updateProperties(const QVariantMap &properties, const QString &name, const QVariant &value)
{
    if (!surface()) {
        qWarning() << "ignoring property for an unsurfaced item" << this << name;
        return;
    }

    if (name == QLatin1String("appId")) {
        setAppId(value.toString());
    } else if (name == QLatin1String("_WEBOS_WINDOW_TYPE")) {
        setType(value.toString());
    } else if (name == QLatin1String("_WEBOS_WINDOW_CLASS")) {
        setWindowClass(WebOSSurfaceItem::WindowClass(value.toInt()), false);
    } else if (name == QLatin1String("title")) {
        setTitle(value.toString(), false);
    } else if (name == QLatin1String("subtitle")) {
        setSubtitle(value.toString(), false);
    } else if (name == QLatin1String("params")) {
        setParams(value.toString());
    } else if (name == QLatin1String("_WEBOS_LAUNCH_PREV_APP_AFTER_CLOSING")) {
        setLaunchLastApp(value.toBool());
    } else if (name == QLatin1String("_WEBOS_LAUNCH_LAST_INPUT_APP_AFTER_CLOSING")) {
        setLaunchLastInputApp(value.toBool());
    } else if (name == QLatin1String("displayAffinity")) {
        setDisplayAffinity(value.toInt());
    } else if (name == QLatin1String("windowPosition")) {
        setWindowPosition(value.toString());
    } else if (name == QLatin1String("type_transitioning")) {
        setTypeTransitioning(value.toBool());
    }

    emit windowPropertiesChanged(properties);
}

void WebOSSurfaceItem::setAppId(const QString& appId, bool updateProperty)
{
    PMTRACE_FUNCTION;
    if (m_appId != appId) {
        m_appId = appId;
        setObjectName(QString("surfaceItem_%1%2").arg(m_appId).arg(type()));
        if (surface())
            surface()->setObjectName(QString("surface_%1%2").arg(m_appId).arg(type()));
        emit appIdChanged();
        if (updateProperty)
            setWindowProperty(QLatin1String("appId"), m_appId);
        qInfo() << "appIdChanged:" << surface() << this;
    }
}

void WebOSSurfaceItem::setType(const QString& type, bool updateProperty)
{
    PMTRACE_FUNCTION;
    if (m_type != type) {
        m_type = type;
        setObjectName(QString("surfaceItem_%1%2").arg(appId()).arg(m_type));
        if (surface())
            surface()->setObjectName(QString("surface_%1%2").arg(appId()).arg(m_type));
        emit typeChanged();
        if (updateProperty)
            setWindowProperty(QLatin1String("_WEBOS_WINDOW_TYPE"), m_type);
        qInfo() << "typeChanged:" << surface() << this;
    }
}

void WebOSSurfaceItem::setWindowClass(WebOSSurfaceItem::WindowClass wClass, bool updateProperty)
{
    PMTRACE_FUNCTION;
    if (m_windowClass != wClass) {
        m_windowClass = wClass;
        emit windowClassChanged();
        if (updateProperty)
            setWindowProperty(QLatin1String("_WEBOS_WINDOW_CLASS"), QVariant(m_windowClass));
    }
}

void WebOSSurfaceItem::setTitle(const QString& title, bool updateProperty)
{
    PMTRACE_FUNCTION;
    if (m_title != title) {
        qInfo() << "titleChanged from" << m_title << " to" << title;
        m_title = title;
        emit titleChanged();
        if (updateProperty)
            setWindowProperty(QLatin1String("title"), m_title);
    }
}

void WebOSSurfaceItem::setSubtitle(const QString& subtitle, bool updateProperty)
{
    PMTRACE_FUNCTION;
    if (m_subtitle != subtitle) {
        m_subtitle = subtitle;
        emit subtitleChanged();
        if (updateProperty)
            setWindowProperty(QLatin1String("subtitle"), m_subtitle);
    }
}

void WebOSSurfaceItem::setParams(const QString& params, bool updateProperty)
{
    PMTRACE_FUNCTION;
    if (m_params != params) {
        m_params = params;
        emit paramsChanged();
        if (updateProperty)
            setWindowProperty(QLatin1String("params"), m_params);
    }
}

void WebOSSurfaceItem::setLaunchLastApp(const bool& launchLastApp, bool updateProperty)
{
    PMTRACE_FUNCTION;
    if (m_launchLastApp != launchLastApp) {
        qInfo() << "setLaunchLastApp : " << launchLastApp;
        m_launchLastApp = launchLastApp;
        emit launchLastAppChanged();
        if (updateProperty)
            setWindowProperty(QLatin1String("_WEBOS_LAUNCH_PREV_APP_AFTER_CLOSING"), m_launchLastApp);
    }
}

void WebOSSurfaceItem::setLaunchLastInputApp(const bool& launchLastInputApp, bool updateProperty)
{
    PMTRACE_FUNCTION;
    if (m_launchLastInputApp != launchLastInputApp) {
        qInfo() << "setLaunchLastInputApp : " << launchLastInputApp;
        m_launchLastInputApp = launchLastInputApp;
        emit launchLastInputAppChanged();
        if (updateProperty)
            setWindowProperty(QLatin1String("_WEBOS_LAUNCH_LAST_INPUT_APP_AFTER_CLOSING"), m_launchLastInputApp);
    }
}

void WebOSSurfaceItem::setWindowPosition(const QString& windowPosition) {
     PMTRACE_FUNCTION;
    if (m_windowPosition != windowPosition) {
        qInfo() << "setWindowPosition : " << windowPosition;
        m_windowPosition = windowPosition;
        emit windowPositionChanged();
    } else {
        qInfo() << "window position is not changed";
    }
}

void WebOSSurfaceItem::setGroupedWindowModel(WebOSGroupedWindowModel* model)
{
    PMTRACE_FUNCTION;
    if (model != m_groupedWindowModel) {
        m_groupedWindowModel = model;
        emit groupedWindowModelChanged();
    }
}

void WebOSSurfaceItem::setCardSnapShotFilePath(const QString& fPath)
{
    if (m_cardSnapShotFilePath != fPath) {
        m_cardSnapShotFilePath = fPath;
        emit cardSnapShotFilePathChanged();
    }
}

void WebOSSurfaceItem::setCustomImageFilePath(QString filePath)
{
    if (m_customImageFilePath != filePath) {
        m_customImageFilePath = filePath;
        emit customImageFilePathChanged();
    }
}

void WebOSSurfaceItem::setBackgroundImageFilePath(QString filePath)
{
    QString path = filePath;
    QString filePrefix = QLatin1String("file://");
    QString pvrPrefix = QLatin1String("image://compressed");

    if (path.startsWith(filePrefix)) {
        path.remove(0, filePrefix.length());
    } else if (path.startsWith(pvrPrefix)) {
        path.remove(0, pvrPrefix.length());
    }
    if (m_backgroundImageFilePath != path) {
        m_backgroundImageFilePath = path;
        emit backgroundImageFilePathChanged();
    }
}

void WebOSSurfaceItem::setTypeTransitioning(bool typeTransitioning)
{
    qInfo() << "setTypeTransitioning (" << this << " : " << typeTransitioning << ")" ;
    if (m_typeTransitioning != typeTransitioning) {
        m_typeTransitioning = typeTransitioning;
        emit typeTransitioningChanged();
    }
}

void WebOSSurfaceItem::deleteCardSnapshot()
{
    QString filepath = getCardSnapShotFilePath();
    if (filepath == customImageFilePath() ||
        filepath == backgroundImageFilePath()) {
        return;
    }

    qInfo() << "[WebOSSurfaceItem:CARDSNAPSHOT] delete_card_snapshot_file" << ", "
            << "app_id:" << m_appId << ", "
            << "file_path:" << filepath << ", "
            << "where: deleteCardSnapshot";

    QFile oldFile(filepath);
    if (oldFile.exists()) {
        oldFile.remove();
    }
}

void WebOSSurfaceItem::prepareState(Qt::WindowState s)
{
    if (m_shellSurface)
        m_shellSurface->prepareState(s);
}

void WebOSSurfaceItem::setState(Qt::WindowState s)
{
    PMTRACE_FUNCTION;
    if (m_shellSurface) {
        m_shellSurface->setState(s);
        //If state is minimized, ignore all input events.
        setEnabled(Qt::WindowMinimized != m_shellSurface->state());
    } else {
        qWarning() << "No webos shell surface exist, cannot set state" << s;
    }
    emit stateChanged();
}

Qt::WindowState WebOSSurfaceItem::state()
{
    return m_shellSurface ? m_shellSurface->state() : Qt::WindowFullScreen;
}

void WebOSSurfaceItem::close()
{
    PMTRACE_FUNCTION;
    if (m_shellSurface) {
        sendCloseToGroupItems();
        m_shellSurface->close();
    } else {
        qWarning() << "No webos shell surface exist, cannot close";
    }
}

void WebOSSurfaceItem::sendCloseToGroupItems()
{
    PMTRACE_FUNCTION;
    if (isSurfaceGroupRoot()) {
        m_surfaceGroup->closeAttachedSurfaces();
    }
}

void WebOSSurfaceItem::setShellSurface(WebOSShellSurface* shell)
{
    PMTRACE_FUNCTION;
    if (shell && m_shellSurface != shell) {
        delete m_shellSurface;
        m_shellSurface = shell;
        connect(m_shellSurface, SIGNAL(locationHintChanged()), this, SIGNAL(locationHintChanged()));
        connect(m_shellSurface, SIGNAL(keyMaskChanged()), this, SIGNAL(keyMaskChanged()));
        connect(m_shellSurface, SIGNAL(stateChangeRequested(Qt::WindowState)), this, SLOT(requestStateChange(Qt::WindowState)));
        connect(m_shellSurface, SIGNAL(propertiesChanged(QVariantMap, QString, QVariant)),
                this, SLOT(updateProperties(QVariantMap, QString, QVariant)));
    }
}

void WebOSSurfaceItem::resetShellSurface(WebOSShellSurface *shell)
{
    PMTRACE_FUNCTION;
    if (shell && m_shellSurface == shell) {
        disconnect(m_shellSurface, SIGNAL(locationHintChanged()), this, SIGNAL(locationHintChanged()));
        disconnect(m_shellSurface, SIGNAL(keyMaskChanged()), this, SIGNAL(keyMaskChanged()));
        disconnect(m_shellSurface, SIGNAL(stateChangeRequested(Qt::WindowState)), this, SLOT(requestStateChange(Qt::WindowState)));
        disconnect(m_shellSurface, SIGNAL(propertiesChanged(QVariantMap, QString, QVariant)),
                   this, SLOT(updateProperties(QVariantMap, QString, QVariant)));
        m_shellSurface = Q_NULLPTR;
    }
}

WebOSSurfaceItem::LocationHints WebOSSurfaceItem::locationHint()
{
    return m_shellSurface ? m_shellSurface->locationHint() : LocationHintNorth  | LocationHintEast;
}

WebOSSurfaceItem::KeyMasks WebOSSurfaceItem::keyMask() const
{
    return m_shellSurface ? m_shellSurface->keyMask() : KeyMaskDefault;
}

void WebOSSurfaceItem::setItemState(ItemState state, const QString &reason)
{
    setItemStateReason(reason);

    if (m_itemState != state) {
        m_itemState = state;
        emit itemStateChanged();
        emit dataChanged();
    }
}

void WebOSSurfaceItem::setItemStateReason(const QString &reason)
{
    if (m_itemStateReason != reason) {
        m_itemStateReason = reason;

        emit itemStateReasonChanged();
    }
}

void WebOSSurfaceItem::setClosePolicy(QVariantMap &policy)
{
    if (m_closePolicy != policy) {
        m_closePolicy = policy;

        emit closePolicyChanged();
    }
}

void WebOSSurfaceItem::setCoverState(CoverState coverState)
{
    if (m_coverState != coverState) {
        m_coverState = coverState;

        emit coverStateChanged();
    }
}

void WebOSSurfaceItem::setActiveRegion(const QRect & activeRegion)
{
    if (m_activeRegion != activeRegion) {
        m_activeRegion = activeRegion;

        emit activeRegionChanged();
    }
}

void WebOSSurfaceItem::updateScreenPosition()
{
    if (m_shellSurface && m_notifyPositionToClient) {
        QPointF position = mapFromGlobal(QPoint(0,0));
        position *= -1;
        if (m_position != position) {
            qDebug() << "screen position is updated to  " << position;
            m_shellSurface->setPosition(position);
            m_position = position;
        }
    }
}

void WebOSSurfaceItem::requestStateChange(Qt::WindowState state)
{
    switch (state) {
        case Qt::WindowNoState:
        case Qt::WindowMaximized:
            qWarning() << "not yet supported to change state to" << state;
            break;
        case Qt::WindowMinimized:
            requestMinimize();
            break;
        case Qt::WindowFullScreen:
            requestFullscreen();
            break;
        default:
           qWarning() << "unknown state!";
           break;
    }
}

void WebOSSurfaceItem::onSurfaceDamaged(const QRegion &region)
{
    PMTRACE_FUNCTION;
    Q_UNUSED(region);
    PMTRACE_KEY_VALUE_LOG("appFirstFrame", (char *)appId().toStdString().c_str());

    /* Some surfaces can try to render after it is detached from scengraph.
       In that case, if compositor allows the rendering, compositor needs
       to call frameFinished. It will release previous front buffer
       of the surface. Otherwise, the surface will be stuck to wait for
       available buffer. */
    if (!window() && surface()) {
        surface()->frameStarted();
        surface()->sendFrameCallbacks();
    }
}

void WebOSSurfaceItem::setNotifyPositionToClient(bool notify)
{

    if (m_notifyPositionToClient != notify) {
        m_notifyPositionToClient = notify;
        emit notifyPositionToClientChanged();
        if (m_notifyPositionToClient)
            updateScreenPosition();
    }
}

void WebOSSurfaceItem::setExposed(bool exposed)
{
    if (m_exposed != exposed) {
        if (m_shellSurface && surface()) {
            QRegion r = exposed ? QRegion(QRect(QPoint(0, 0), surface()->size())) : QRegion();
            m_shellSurface->exposed(r);
        } else {
            qWarning("no surface or shellSurface, no one to send to.");
        }
        m_exposed = exposed;
        emit exposedChanged();
    }
}

void WebOSSurfaceItem::setLaunchRequired(bool required)
{
    if (m_launchRequired != required) {
        m_launchRequired = required;
        emit launchRequiredChanged();
    }
}

void WebOSSurfaceItem::setSurfaceGroup(WebOSSurfaceGroup* group)
{
    PMTRACE_FUNCTION;
    if (group != m_surfaceGroup) {

        m_surfaceGroup = group;

        if (!m_surfaceGroup) {
            if (m_groupedWindowModel) {
                emit m_groupedWindowModel->surfaceRemoved(this);
            }
        } else {
            connect(m_surfaceGroup, &QObject::destroyed, this, [this] { this->setSurfaceGroup(nullptr); });
        }

        emit surfaceGroupChanged();
        emit dataChanged();
    }
}

bool WebOSSurfaceItem::isPartOfGroup()
{
    // The root item of a surface is not considered to be part of a group
    return m_surfaceGroup && m_surfaceGroup->isValid() && m_surfaceGroup->rootItem() != this;
}

bool WebOSSurfaceItem::isSurfaceGroupRoot()
{
    return m_surfaceGroup && m_surfaceGroup->rootItem() == this;
}

bool WebOSSurfaceItem::acceptsKeyEvent(QKeyEvent *event) const
{
    return keyMask() & keyMaskFromQt(event->key());
}

WebOSSurfaceItem::KeyMasks WebOSSurfaceItem::keyMaskFromQt(int key) const
{
    KeyMasks retKeyMask = KeyMaskDefault;

    switch(key) {
    case Qt::Key_Super_L:
        retKeyMask = KeyMaskHome;
    break;
    case Qt::Key_webOS_Back:
        retKeyMask = KeyMaskBack;
    break;
    case Qt::Key_webOS_Exit:
        retKeyMask = KeyMaskExit;
    break;
    case Qt::Key_Left:
        retKeyMask = KeyMaskLeft;
    break;
    case Qt::Key_webOS_LocalLeft:
        retKeyMask = KeyMaskLocalLeft;
    break;
    case Qt::Key_Up:
        retKeyMask = KeyMaskUp;
    break;
    case Qt::Key_webOS_LocalUp:
        retKeyMask = KeyMaskLocalUp;
    break;
    case Qt::Key_PageUp:
        retKeyMask = KeyMaskUp;
    break;
    case Qt::Key_Right:
        retKeyMask = KeyMaskRight;
    break;
    case Qt::Key_webOS_LocalRight:
        retKeyMask = KeyMaskLocalRight;
    break;
    case Qt::Key_Down:
        retKeyMask = KeyMaskDown;
    break;
    case Qt::Key_webOS_LocalDown:
        retKeyMask = KeyMaskLocalDown;
    break;
    case Qt::Key_PageDown:
        retKeyMask = KeyMaskDown;
    break;
    case Qt::Key_Return:
    case Qt::Key_Enter:
        retKeyMask = KeyMaskOk;
    break;
    case Qt::Key_webOS_LocalEnter:
        retKeyMask = KeyMaskLocalOk;
    break;
    case Qt::Key_0:
    case Qt::Key_1:
    case Qt::Key_2:
    case Qt::Key_3:
    case Qt::Key_4:
    case Qt::Key_5:
    case Qt::Key_6:
    case Qt::Key_7:
    case Qt::Key_8:
    case Qt::Key_9:
    case Qt::Key_webOS_BS_11:
    case Qt::Key_webOS_BS_12:
    case Qt::Key_webOS_CS1_11:
    case Qt::Key_webOS_CS1_12:
    case Qt::Key_webOS_CS2_11:
    case Qt::Key_webOS_CS2_12:
    case Qt::Key_webOS_TER_11:
    case Qt::Key_webOS_TER_12:
    case Qt::Key_webOS_4K_BS_11:
    case Qt::Key_webOS_4K_BS_12:
    case Qt::Key_webOS_4K_CS_11:
    case Qt::Key_webOS_4K_CS_12:
        retKeyMask = KeyMaskNumeric;
    break;
    case Qt::Key_Red:
        retKeyMask = KeyMaskRemoteColorRed;
    break;
    case Qt::Key_webOS_Red:
        retKeyMask = KeyMaskRemoteColorRed;
    break;
    case Qt::Key_Green:
        retKeyMask = KeyMaskRemoteColorGreen;
    break;
    case Qt::Key_webOS_Green:
        retKeyMask = KeyMaskRemoteColorGreen;
    break;
    case Qt::Key_Yellow:
        retKeyMask = KeyMaskRemoteColorYellow;
    break;
    case Qt::Key_webOS_Yellow:
        retKeyMask = KeyMaskRemoteColorYellow;
    break;
    case Qt::Key_Blue:
        retKeyMask = KeyMaskRemoteColorBlue;
    break;
    case Qt::Key_webOS_Blue:
        retKeyMask = KeyMaskRemoteColorBlue;
    break;
    case Qt::Key_webOS_ChannelUp:
    case Qt::Key_webOS_ChannelDown:
    case Qt::Key_webOS_ChannelDash:
    case Qt::Key_webOS_ChannelBack:
    case Qt::Key_webOS_InputTVRadio:
        retKeyMask = KeyMaskRemoteProgrammeGroup;
    break;
    case Qt::Key_MediaPlay:
    case Qt::Key_MediaStop:
    case Qt::Key_MediaPause:
    case Qt::Key_AudioRewind:
    case Qt::Key_AudioForward:
        retKeyMask = KeyMaskRemotePlaybackGroup | KeyMaskMinimalPlaybackGroup;
    break;
    case Qt::Key_MediaPrevious:
    case Qt::Key_MediaNext:
    case Qt::Key_MediaRecord:
    case Qt::Key_MediaTogglePlayPause:
        retKeyMask = KeyMaskRemotePlaybackGroup;
    break;
    case Qt::Key_BackForward:
        retKeyMask = KeyMaskRemotePlaybackGroup;
    break;
    case Qt::Key_AudioRepeat:
    case Qt::Key_AudioRandomPlay:
        retKeyMask = KeyMaskRemotePlaybackGroup;
    break;
    case Qt::Key_AudioCycleTrack:
        retKeyMask = KeyMaskRemotePlaybackGroup;
    break;
    case Qt::Key_webOS_Teletext:
        retKeyMask = KeyMaskRemoteTeletextGroup;
    break;
    case Qt::Key_webOS_ProgramList:
    case Qt::Key_webOS_MagnifierZoom:
    case Qt::Key_webOS_LiveZoom:
        retKeyMask = KeyMaskRemoteMagnifierGroup;
    break;
    case Qt::Key_webOS_TVGuide:
        retKeyMask = KeyMaskGuide;
    break;
    case Qt::Key_webOS_TeletextSize:
    case Qt::Key_webOS_TextMode:
    case Qt::Key_webOS_TextMix:
    case Qt::Key_webOS_TeletextReveal:
    case Qt::Key_webOS_TeletextInTime:
    case Qt::Key_webOS_TeletextHold:
    case Qt::Key_webOS_TeletextPosition:
    case Qt::Key_webOS_TeletextSubPage:
    case Qt::Key_webOS_TeletextFreeze:
    case Qt::Key_webOS_MultiPip:
        retKeyMask = KeyMaskTeletextActiveGroup;
    break;
    case Qt::Key_webOS_BMLData:
        retKeyMask = KeyMaskData;
    break;
    case Qt::Key_webOS_Info:
        retKeyMask = KeyMaskRemoteMagnifierGroup | KeyMaskInfo;
    break;
    default:
        /* If a client want to receive some special keys and the other keys have to be delivered to the parent,
             there are two approaches according to kinds of special keys.
             1) Set the key mask value with bitwise OR operation against the supported individual key masks
             2) Set the key mask value with bitwise XOR operation against the default key mask value and supported
             individual key masks.
             For above two approaches, the acceptsKeyEvent method use the bitwise AND operation against the keyMask
             of the client and retKeyMask value.
             And the retKeyMask value of default case have to be applied bitwise XOR operation against default key mask value
             and supported individual key masks for the keys without supported individual key mask. */
        retKeyMask = (KeyMasks) KeyMaskDefault
                     ^ KeyMaskLeft
                     ^ KeyMaskRight
                     ^ KeyMaskUp
                     ^ KeyMaskDown
                     ^ KeyMaskOk
                     ^ KeyMaskNumeric
                     ^ KeyMaskRemoteColorRed
                     ^ KeyMaskRemoteColorGreen
                     ^ KeyMaskRemoteColorYellow
                     ^ KeyMaskRemoteColorBlue
                     ^ KeyMaskRemoteProgrammeGroup
                     ^ KeyMaskRemotePlaybackGroup
                     ^ KeyMaskRemoteTeletextGroup
                     ^ KeyMaskLocalLeft
                     ^ KeyMaskLocalRight
                     ^ KeyMaskLocalUp
                     ^ KeyMaskLocalDown
                     ^ KeyMaskLocalOk
                     ^ KeyMaskRemoteMagnifierGroup
                     ^ KeyMaskMinimalPlaybackGroup
                     ^ KeyMaskGuide
                     ^ KeyMaskTeletextActiveGroup
                     ^ KeyMaskData
                     ^ KeyMaskInfo;
    break;
    }

    return retKeyMask;
}

void WebOSSurfaceItem::onSceneGraphPaintNodeTypeChanged(Compositor2DGraphicDevice::ScenGraphPaintNodeType type)
{
    if (type == Compositor2DGraphicDevice::GraphicDevice2D) {
        connect(this, &QQuickItem::visibleChanged, this, &QQuickItem::update);
        connect(static_cast<QQuickWindow*>(m_compositor->window()), &QQuickWindow::frameSwapped,
                m_compositor->webOS2DGraphicDeviceExtension()->graphicDevice2D(), &Compositor2DGraphicDevice::frameSwapped);

    } else {
        disconnect(this, &QQuickItem::visibleChanged, this, &QQuickItem::update);
        disconnect(static_cast<QQuickWindow*>(m_compositor->window()), &QQuickWindow::frameSwapped,
                   m_compositor->webOS2DGraphicDeviceExtension()->graphicDevice2D(), &Compositor2DGraphicDevice::frameSwapped);
    }
}

void WebOSSurfaceItem::contentOrientationChanged()
{
    qInfo() << "orientation changed: item=" << this
            << ", orientation=" << surface()->contentOrientation();

    if (m_orientation !=  surface()->contentOrientation()) {
        m_orientation = surface()->contentOrientation();
        emit orientationChanged();
    }
}

QSGNode* WebOSSurfaceItem::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *data)
{
    Compositor2DGraphicDevice *gdev = nullptr;
    if (m_compositor->webOS2DGraphicDeviceExtension())
        gdev = m_compositor->webOS2DGraphicDeviceExtension()->graphicDevice2D();

    if (!gdev || gdev->sceneGraphPaintNodeType() == Compositor2DGraphicDevice::Default) {
        return QWaylandQuickItem::updatePaintNode(oldNode, data);
    }
    if (!(surface() && surface()->hasContent()) || !textureProvider()->texture() || !paintEnabled()) {
        delete oldNode;
        oldNode = nullptr;

        return nullptr;
    }

    Compositor2DGraphicDeviceNode *node = static_cast<Compositor2DGraphicDeviceNode*>(oldNode);
    if (!node)
        node = gdev->createGraphicDeviceNode();
    Q_ASSERT(node != nullptr);

    node->setAppId(appId());
    node->setVisible(isVisible());

    return node;
}

void WebOSSurfaceItem::setCursorSurface(QWaylandSurface *surface, int hotSpotX, int hotSpotY)
{
    if (m_cursorView.surface() == surface && m_cursorHotSpotX == hotSpotX && m_cursorHotSpotY == hotSpotY) {
        qWarning() << "Cursor: attempting to set the same cursor surface, ignored" << surface << hotSpotX << hotSpotY;
    } else {
        qDebug() << "Cursor: updating cursor with surface" << surface << hotSpotX << hotSpotY;

        QCursor cursor;
        bool staticCursor = false;

        if (m_compositor->getCursor(surface, hotSpotX, hotSpotY, cursor)) {
            qDebug() << "Cursor: use the cursor designated by compositor" << cursor;
            staticCursor = true;
        } else if (!surface) {
            cursor = QCursor(Qt::BlankCursor);
            staticCursor = true;
        } else {
            staticCursor = false;
        }

        if (m_cursorView.surface()) {
            qDebug() << "Cursor: disconnect old cursor surface" << m_cursorView.surface() << "static:" << staticCursor;
            QObject::disconnect(m_cursorView.surface(), SIGNAL(redraw()), this, SLOT(updateCursor()));
        }

        /* Original source changes m_cursorView.surface(), m_cursorHotSpotX and m_cursorHotSpotY even if getCursorFromSurface
         * failes. This is not quite right, I'm afraid, but unless told otherwise, I will preserve current behaviour.
         */
        m_cursorView.setSurface(surface);
        m_cursorHotSpotX = hotSpotX;
        m_cursorHotSpotY = hotSpotY;
        if (staticCursor) {
            qDebug() << "Cursor: set a static cursor" << cursor;
            setCursor(cursor);
        } else if (surface) {
            qDebug() << "Cursor: set a live cursor with cursor surface" << surface << "static:" << staticCursor;
            connect(surface, SIGNAL(redraw()), this, SLOT(updateCursor()), Qt::UniqueConnection);
        }
    }
}

void WebOSSurfaceItem::updateCursor()
{
    m_cursorView.advance();
    QImage image = m_cursorView.currentBuffer().image();
    if (!image.isNull()) {
        if (m_cursorHotSpotX >= 0 && m_cursorHotSpotX <= image.size().width() &&
            m_cursorHotSpotY >= 0 && m_cursorHotSpotY <= image.size().height()) {
            qDebug() << "Cursor: live updating cursor with surface" << m_cursorView.surface() << m_cursorHotSpotX << m_cursorHotSpotY;
            QCursor c(QPixmap::fromImage(image), m_cursorHotSpotX, m_cursorHotSpotY);
            setCursor(c);
            return;
        }
    }
    qWarning() << "Cursor: fallback to the default cursor";
    setCursor(QCursor(Qt::ArrowCursor));
}

WebOSSurfaceItem* WebOSSurfaceItem::currentKeyFocusedItem()
{
    if (m_surfaceGroup) {
        qInfo() << "Item has surfaceGroup";
        return m_surfaceGroup->findKeyFocusedItem();
    } else {
        qInfo() << "Item does not have surfaceGroup";
        return NULL;
    }
}

void WebOSSurfaceItem::setFullscreenMode(bool fullscreenMode)
{
    m_fullscreenMode = fullscreenMode;
    emit fullscreenModeChanged();
}
