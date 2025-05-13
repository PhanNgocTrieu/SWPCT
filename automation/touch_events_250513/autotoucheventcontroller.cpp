#include "autotoucheventcontroller.h"
#include <random>
#include <fcntl.h>
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <dirent.h>
#include <linux/uinput.h>
#include <linux/input.h>
#include <sys/time.h>
#include <vector>
#include <thread>

#ifdef UINPUT_TEST
static const char* DEV_FILE = "/dev/uinput/event1";
#else
static const char* DEV_FILE = "/dev/input/";
#endif

static const char* DEV_NAME = "VirtualTouch";
char g_deviceName[64] = {0};

#define MT_TRACKING_DOWN    0   // press
#define MT_TRACKING_UP      -1 // release
#define MAX_INPUT_DEVICES   32
#define TOUCH_DOWN          1
#define TOUCH_UP            0
#define MAX_TESTCASES       30
#define DELAY_TIMER         5000 // 5 seconds
#define BREAK_POINT         0

TouchEventController* TouchEventController::m_instance = nullptr;

TouchEventController::TouchEventController(AutoTestFunctionalController* controller)
    : m_controller(controller), m_buffer(""), m_device(""), m_fd(0)  {
        qInfo() << "[Trieu.phan] TouchEventController constructor called";

    QObject::connect(this, &TouchEventController::confirmTouchChanged, this, &TouchEventController::showConfirmTouch);
    QObject::connect(this, &TouchEventController::confirmSendTouch, this, [this](){
        _severalTouchEventsTest();
    });
    if (m_controller) {
        QObject::connect(m_controller, &AutoTestFunctionalController::nextDevice, this, &TouchEventController::nextDevice);
        QObject::connect(m_controller, &AutoTestFunctionalController::receivedTouch, this, &TouchEventController::receivedTouch);
    }
}

TouchEventController::~TouchEventController() {
    if (m_fd) {
        close(m_fd);
        m_fd = 0;
    }
}

void TouchEventController::nextDevice(int x, int y) {
    _sendTouchEvent(x, y);
}

void TouchEventController::receivedTouch() {
    std::this_thread::sleep_for(std::chrono::milliseconds(DELAY_TIMER));
    // sleep(5);
    _severalTouchEventsTest();
}

void TouchEventController::setup() {
    if (m_initial && m_testMode) {
        qWarning() << "[Trieu.phan] TouchEventController::setup() already initialized";
        return;
    }

    m_initial = true;
    m_testMode = true;
    qInfo() << "initializing with testcase of touch(100,100)";
    this->sendTouch(100,100);
}

void TouchEventController::startTest() {
    m_isTest = true;
    qInfo() << "[Trieu.phan] testing started";
    runningTest();
}

void TouchEventController::setConfirmTouchTestMode(bool confirm) {
    if (m_confirmTouch != confirm) {
        m_confirmTouch = confirm;
        emit confirmTouchChanged();
    }
}

void TouchEventController::showConfirmTouch() {
    qInfo() << "[Trieu.phan] confirmTouch: " << (m_confirmTouch ? "true" : "false");
}

void TouchEventController::stopTest() {
    m_isTest = false;
    m_testMode = false;
    qInfo() << "[Trieu.phan] testing stopped";
}

void TouchEventController::runningTest() {
    if (m_isTest) {
        if (m_confirmTouch) {
            this->_severalTouchEventsTest();
        }
    }
}

void TouchEventController::sendTouch(int x, int y) {
    _sendTouchEvent(x,y);
}

void TouchEventController::_sendTouchEvent(int x, int y) {
    std::thread touchThread([this, x, y]() {
        do {
            if (index >= MAX_INPUT_DEVICES) {
                qWarning() << "[Trieu.phan] No more input devices available for upper index: " << index;
                index = 0;
                break;
            }

            if (m_confirmTouch) {
                qWarning() << "[Trieu.phan] Touch event already confirmed ! ready to test with : " << g_deviceName << " - fd: " << m_fd;
                break;
            }

            bool isFailed = false;
            if (m_fd) {
                close(m_fd);
                m_fd = 0;
            }

            do {
                char dev[64];
                snprintf(dev, sizeof(dev), "%sevent%d", DEV_FILE, index);
                snprintf(g_deviceName, sizeof(g_deviceName), "%s", dev);
                // qInfo() << "[Trieu.phan] Opening input device: " << dev;
                m_fd = open(dev, O_WRONLY | O_NONBLOCK);
                if (0 > m_fd) {
                    isFailed = true;
                    break;
                }
                _generateTouchEventWithTracking(x, y);
            } while (0);

            index++;

            if (isFailed) {
                break;
            }
            // making space
            std::this_thread::sleep_for(std::chrono::milliseconds(DELAY_TIMER));
            emit m_controller->nextDevice(x, y);

        } while (BREAK_POINT);
    });

    touchThread.detach();
}

void TouchEventController::_generateTouchEventWithTracking(int x, int y) {
    static std::vector<struct input_event> eventsDown = {
        {
            .time = {0,0},
            .type = EV_ABS,
            .code = ABS_MT_TRACKING_ID,
            .value = MT_TRACKING_DOWN, // Adjust X coordinate
        },
        {
            .time = {0,0},
            .type = EV_ABS,
            .code = ABS_MT_POSITION_X,
            .value = 0, // Adjust X coordinate
        },
        {
            .time = {0,0},
            .type = EV_ABS,
            .code = ABS_MT_POSITION_Y,
            .value = 0, // Adjust Y coordinate
        },
        {
            .time = {0,0},
            .type = EV_SYN,
            .code = SYN_REPORT,
            .value = 0x00,
        }
    };

    static std::vector<struct input_event> eventsUp = {
        {
            .time = {0,0},
            .type = EV_ABS,
            .code = ABS_MT_TRACKING_ID,
            .value = MT_TRACKING_UP,
        },
        {
            .time = {0,0},
            .type = EV_SYN,
            .code = SYN_REPORT,
            .value = 0x00,
        }
    };

    for (auto& event : eventsDown) {
        if (event.code == ABS_MT_POSITION_X) {
            event.value = x;
        }
        else if (event.code == ABS_MT_POSITION_Y) {
            event.value = y;
        }
        _writeEvent(event.type, event.code, event.value);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Sleep for 200ms

    for (const auto& event : eventsUp) {
        _writeEvent(event.type, event.code, event.value);
    }
}

void TouchEventController::_writeEvent(int type, int code, int value) {
    if (!m_fd) {
        return;
    }

    struct input_event ev;
    memset(&ev, 0, sizeof(ev));

    gettimeofday(&ev.time, nullptr);
    ev.type = type;
    ev.code = code;
    ev.value = value;

    m_buffer.append(reinterpret_cast<const char*>(&ev), sizeof(ev));

    _flushbuffer();
}

void TouchEventController::_flushbuffer() {
    if (!m_fd) {
        return;
    }

    while (!m_buffer.empty()) {
        errno = 0;
        ssize_t byteswritten = write(m_fd, m_buffer.c_str(), m_buffer.size());
        if (byteswritten > 0) {
            m_buffer.erase(0, byteswritten);
        }
        else if (byteswritten == 0 || errno == EAGAIN || errno == EWOULDBLOCK) {
            break;
        }
        else  // byteswritten < 0
        {
            perror("write");
        }
    }
}

void TouchEventController::_severalTouchEventsTest() {

    std::thread sendTouchThread([this]() {
        do {
            if (!m_isTest) {
                qWarning() << "[Trieu.phan] Test is stopped";
                testcase = 0;
                break;
            }

            if (testcase > MAX_TESTCASES) {
                qWarning() << "[Trieu.phan] Ending of test case";
                testcase = 0;
                break;
            }

            testcase++;
            qInfo() << "[Trieu.phan] TouchEventController::testcase: " << testcase;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distX(0, 1980);
            std::uniform_int_distribution<> distY(80, 1080);
            int x = distX(gen);
            int y = distY(gen);
            qInfo() << "[Trieu.phan] Sent touch event at (" << x << "," << y << ")";
            _generateTouchEventWithTracking(x, y);
            std::this_thread::sleep_for(std::chrono::milliseconds(DELAY_TIMER));
            emit confirmSendTouch();

        } while(BREAK_POINT);
    });

    sendTouchThread.detach();
}


bool TouchEventController::getConfirmTouchTestMode() {
    return m_confirmTouch;
}

bool TouchEventController::getTestMode() {
    return m_testMode;
}