#ifndef _AUTOTOUCHEVENTCONTROLLER_H
#define _AUTOTOUCHEVENTCONTROLLER_H

#include <QDebug>
#include <QObject>

#include "autotestfunctionalcontroller.h"

class TouchEventController : public QObject
{
    Q_OBJECT
    public:
        static TouchEventController* getInstance(AutoTestFunctionalController* controller = nullptr) {
            if (m_instance == nullptr) {
                m_instance = new TouchEventController(controller);
            }
            return m_instance;
        }

        virtual ~TouchEventController();

        void setup();
        void startTest();
        void stopTest();
        void runningTest();
        void sendTouch(int x, int y);
        bool getTestMode();
        void setConfirmTouchTestMode(bool confirm);
        bool getConfirmTouchTestMode();

    signals:
        void confirmTouchChanged();
        void confirmSendTouch();

    private slots:
        void nextDevice(int x, int y);
        void showConfirmTouch();
        void receivedTouch();

    protected:
        TouchEventController(AutoTestFunctionalController* controller);

        bool _sendSinglePressTouchEvent(int x, int y);
        bool _sendSingleReleaseTouchEvent(int x, int y);
        void _sendTouchEvent(int x, int y);

        void _generateTouchEventWithTracking(int x, int y);
        void _writeEvent(int type, int code, int value);
        void _flushbuffer();

    protected:
        void _severalTouchEventsTest();


    private:
        static TouchEventController* m_instance;
        AutoTestFunctionalController* m_controller;
        std::string m_buffer;
        std::string m_device;
        int index = 0;
        int m_fd;
        bool m_initial = false;
        bool m_confirmTouch = false;
        bool m_isTest = false;
        bool m_testMode = false;
        int testcase = 0;
};

#endif // _AUTOTOUCHEVENTCONTROLLER_H