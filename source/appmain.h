#ifndef APPMAIN_H
#define APPMAIN_H

#include <QObject>
#include <QQmlApplicationEngine>
#include "communication/servicecommunicator.h"
#include "controllers/mastercontroller.h"

class AppMain : public QObject
{
    Q_OBJECT
public:
    explicit AppMain(QQmlApplicationEngine* engine, QObject *parent = nullptr);
    ~AppMain();
    void initAplication();

private:
    void connectSignalSlots();

private:
    QQmlApplicationEngine* m_engine;

    bool m_isAccessibilityAvailble;
    ServiceCommunicator* m_aslbServiceCom;
    MasterController *mastercontroller = nullptr;
};

#endif // APPMAIN_H
