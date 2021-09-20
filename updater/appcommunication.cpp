#include "appcommunication.h"

#include "databasehandler.h"
#include "qtandroidservice.h"

AppCommunication::AppCommunication(QObject *parent) : QtAndroidServiceSource(parent)
{
    QtAndroidService::instance();
    connect(QtAndroidService::instance(), &QtAndroidService::sendToUi, this, &AppCommunication::messageFromService);
    internetCheckingTimer = new QTimer(this);
    internetCheckingTimer->setInterval(1000);
    isConnectedInternet = Utility::isNetworkConnected();
    connect(internetCheckingTimer,&QTimer::timeout,[this]{
       if(Utility::isNetworkConnected() != isConnectedInternet){
            isConnectedInternet = Utility::isNetworkConnected();
            LOGD("IsInternetConnected : %s",isConnectedInternet?"true":"false");
            emit internetConnectionChanged(isConnectedInternet);
       }
    });
    internetCheckingTimer->start();
    connect(this, &AppCommunication::internetConnectionChanged, QtAndroidService::instance(), &QtAndroidService::onInternetConnectionChanged);
}

AppCommunication::~AppCommunication()
{
    if(internetCheckingTimer != nullptr){
        if(internetCheckingTimer->isActive()){
            internetCheckingTimer->stop();
        }
        delete  internetCheckingTimer;
    }
}

void AppCommunication::transferDatabasePath(QString path)
{
    LOGD("");
    DatabaseHandler* databaseHandler = new DatabaseHandler(this,path);
    Q_UNUSED(databaseHandler)
}

void AppCommunication::sendToService(const QString &name)
{
    LOGD("%s",name.toUtf8().data());
    QtAndroidService::instance()->handleServiceMessage(name);
}
