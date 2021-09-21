#include "appmain.h"

#include <QQmlContext>

AppMain::AppMain(QQmlApplicationEngine *engine, QObject *parent) :
    QObject(parent),
    m_engine(engine)
{
    masterController = new MasterController(this);
    masterController->startService();
    serviceCommunicator = new ServiceCommunicator(this);
    connect(masterController, &MasterController::requestBackground, serviceCommunicator, &ServiceCommunicator::requestBackground);
}

AppMain::~AppMain()
{

}

void AppMain::initAplication()
{
    LOGD("");

    m_engine->rootContext()->setContextProperty("masterController",masterController);
    connectSignalSlots();
}

void AppMain::connectSignalSlots()
{
    connect(serviceCommunicator, &ServiceCommunicator::serviceConnected, masterController, &MasterController::requestDatabase);
    connect(serviceCommunicator, &ServiceCommunicator::messageFromBackground, masterController, &MasterController::messageFromBackground);

}
