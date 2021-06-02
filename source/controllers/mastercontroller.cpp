#include "mastercontroller.h"

MasterController::MasterController(QGuiApplication *parent) :
    QObject(parent)
{
//    JniMessenger *initialer = new JniMessenger(parent);
//    Q_UNUSED(initialer)
    connect(parent,&QGuiApplication::applicationStateChanged,[=](Qt::ApplicationState state){
        switch (state) {
        case Qt::ApplicationHidden:
            QtAndroidService::instance()->log("Application Hidden");
            break;
        case Qt::ApplicationActive:
            QtAndroidService::instance()->log("Application Active");

            this->m_revenueController->updateList();
            break;
        case Qt::ApplicationInactive:
            QtAndroidService::instance()->log("Application Inactive");

            break;
        case Qt::ApplicationSuspended:
            QtAndroidService::instance()->log("Application Suspended");

        }
    });


    this->m_revenueController = new RevenueController(this);

    QtAndroidService *initialier = new QtAndroidService(parent);
    connect(initialier, &QtAndroidService::messageFromService,this, &MasterController::onReceiveMessageFromService);
    initialier->startBackgroundService();


}


//publics
QtAndroidService* MasterController::qtAndroidService()
{
    return QtAndroidService::instance();
}

JniMessenger* MasterController::jniMessenger()
{
    return JniMessenger::instance();
}

RevenueController* MasterController::revenueController()
{
    return this->m_revenueController;
}




//slots
void MasterController::onReceiveMessageFromService(const QString &message)
{
    if(message.startsWith(Constants::Info::DATABASE_DECLARE_INFO)){
        onDatabaseAvailable(message.mid(Constants::Info::DATABASE_DECLARE_INFO.length()));
    }

    if(message == Constants::Info::UPDATE_DATA_INFO){
        this->m_revenueController->updateList();
    }

    if(message.contains("on")){
        log(message);
    }
}

//private
void MasterController::onDatabaseAvailable(QString path)
{
    //Declare database
    DatabaseHandler *handler = new DatabaseHandler(this,path);
    Q_UNUSED(handler)

    this->m_revenueController->updateList();

}

void MasterController::log(QString message)
{
    QtAndroidService::instance()->log(message);
}
