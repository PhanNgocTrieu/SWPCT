#ifndef _TEST_FUNCTIONAL_H
#define _TEST_FUNCTIONAL_H

#include <QObject>

class TouchEventController;

class AutoTestFunctionalController : public QObject
{
    Q_OBJECT

    public:
        static AutoTestFunctionalController* instance();
        virtual ~AutoTestFunctionalController();

    signals:
        void nextDevice(int x, int y);
        void receivedTouch();

    public slots:
        void setup();
        void startTest();
        void stopTest();
        bool getTestMode();
        void setConfirmTouchTestMode(bool confirmTouch);
        bool getConfirmTouchTestMode();

    protected:
        AutoTestFunctionalController();

    private:
        static AutoTestFunctionalController* m_instance;
        TouchEventController* m_touchController = nullptr;

};

#endif // _TEST_FUNCTIONAL_H