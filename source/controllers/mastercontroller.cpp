#include "mastercontroller.h"

MasterController::MasterController(QObject *parent) : QObject(parent)
{
//    JniMessenger *initialer = new JniMessenger(parent);
//    Q_UNUSED(initialer)

    this->m_revenueController = new RevenueController(this);

    QtAndroidService *initialier = new QtAndroidService(parent);
    connect(initialier, &QtAndroidService::messageFromService,this, &MasterController::onReceiveMessageFromService);
    initialier->sendToService(INITIALIZE_SERVICE);


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
    if(message.startsWith(DATABASE_PREFIX)){
        onDatabaseAvailable(message.mid(DATABASE_PREFIX.length()));
    }

    if(message == UPDATE_DATA){
        this->m_revenueController->updateList();
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
