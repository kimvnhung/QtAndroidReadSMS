#include "appmain.h"

#include <QQmlContext>

AppMain::AppMain(QQmlApplicationEngine *engine, QObject *parent) :
    QObject(parent),
    m_engine(engine)
{
    masterController = new MasterController(this);
    masterController->startService();
    serviceCommunicator = new ServiceCommunicator(this);
    connect(masterController, &MasterController::databaseAvailable, serviceCommunicator, &ServiceCommunicator::onDatabaseAvailable);
    connect(masterController, &MasterController::sendMessage, serviceCommunicator, &ServiceCommunicator::sendToService);
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
    connect(serviceCommunicator, &ServiceCommunicator::messageFromService, masterController, &MasterController::onReceiveMessageFromService);

}
