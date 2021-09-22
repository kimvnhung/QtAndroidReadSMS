#include "appcommunication.h"

#include "databasehandler.h"
#include "qtandroidservice.h"
#include "utility.h"

AppCommunication::AppCommunication(QObject *parent) : QtAndroidServiceSource(parent)
{
    QtAndroidService::instance();
    connect(QtAndroidService::instance(), &QtAndroidService::requestUI, this, &AppCommunication::sendToUI);
    internetCheckingTimer = new QTimer(this);
    internetCheckingTimer->setInterval(3000);
    isConnectedInternet = Utility::isNetworkConnected(900);
    connect(internetCheckingTimer,&QTimer::timeout,[this]{
       if(Utility::isNetworkConnected() != isConnectedInternet){
            isConnectedInternet = Utility::isNetworkConnected(900);
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

void AppCommunication::requestBackground(const QString &action, const QString &data)
{
    LOGD("");
    if(data == ""){
        QtAndroidService::instance()->handleAction(action);
    }else {
        QtAndroidService::instance()->handleActionWithData(action,data);
    }
}
