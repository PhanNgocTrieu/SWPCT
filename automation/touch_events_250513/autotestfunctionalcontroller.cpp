#include "autotestfunctionalcontroller.h"
#include "autotoucheventcontroller.h"
#include <QDebug>

AutoTestFunctionalController* AutoTestFunctionalController::m_instance = nullptr;

AutoTestFunctionalController* AutoTestFunctionalController::instance()
{
    if (m_instance == nullptr) {
        m_instance = new AutoTestFunctionalController();
    }
    return m_instance;
}

AutoTestFunctionalController::AutoTestFunctionalController()
: m_touchController(TouchEventController::getInstance(this))
{
    qInfo() << "[Trieu.phan] FunctionalTest constructor called";
}

AutoTestFunctionalController::~AutoTestFunctionalController() {
    qInfo() << "[Trieu.phan] FunctionalTest destructor called";
}

void AutoTestFunctionalController::startTest() {
    qInfo() << "[Trieu.phan] Starting test...";
    m_touchController->startTest();
}

void AutoTestFunctionalController::stopTest() {
    qInfo() << "[Trieu.phan] Stopping test...";
    m_touchController->stopTest();
}

bool AutoTestFunctionalController::getTestMode() {
    return m_touchController->getTestMode();
}

void AutoTestFunctionalController::setConfirmTouchTestMode(bool confirmTouch) {
    m_touchController->setConfirmTouchTestMode(confirmTouch);
}

bool AutoTestFunctionalController::getConfirmTouchTestMode() {
    return m_touchController->getConfirmTouchTestMode();
}

void AutoTestFunctionalController::setup() {
    m_touchController->setup();
}