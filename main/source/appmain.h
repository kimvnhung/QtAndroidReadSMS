#ifndef APPMAIN_H
#define APPMAIN_H

#include <QObject>
#include "communication/servicecommunicator.h"

#include "controllers/mastercontroller.h"

class AppMain : public QObject
{
    Q_OBJECT
public:
    explicit AppMain(QObject *parent = nullptr);

    explicit AppMain(QQmlApplicationEngine* engine, QObject *parent = nullptr);
    ~AppMain();
    void initAplication();

private:
    void connectSignalSlots();

private:
    QQmlApplicationEngine* m_engine;
    ServiceCommunicator *serviceCommunicator = nullptr;
    MasterController *masterController = nullptr;
};

#endif // APPMAIN_H
