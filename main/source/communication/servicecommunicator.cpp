#include "servicecommunicator.h"

#include <QAndroidIntent>
#include <QtAndroid>

ServiceCommunicator::ServiceCommunicator(QObject *parent) :
    QObject(parent),
    rep(nullptr),
    m_isInitializedReplica(false),
    m_isServiceConnected(false)
{
    connectTimer.setInterval(1000);
    connect(&connectTimer, &QTimer::timeout, this , &ServiceCommunicator::onCheckReplicConnection);
    connectTimer.start();
    LOGD(" --- Created ServiceCommunicator --- ");
}

void ServiceCommunicator::onCheckReplicConnection()
{
    LOGD("");
    if(!m_isInitializedReplica) {
        repNode.connectToNode(QUrl(QStringLiteral("local:replica")));
        rep = QSharedPointer<QtAndroidServiceReplica>(repNode.acquire<QtAndroidServiceReplica>());
        m_isInitializedReplica = rep->waitForSource(3000);
        if(m_isInitializedReplica) {
            connect(rep.data(), &QtAndroidServiceReplica::serviceStatusChanged, this, &ServiceCommunicator::onServiceStatusChanged);
            connect(rep.data(), &QtAndroidServiceReplica::messageFromService, this, &ServiceCommunicator::messageFromService);

        }

    } else {
        if(m_isServiceConnected) {
            connectTimer.stop();
            emit serviceConnected();
        } else {
            rep->requestServiceStatus();
        }
    }
}

void ServiceCommunicator::onServiceStatusChanged(bool isConnected)
{
    m_isServiceConnected = isConnected;
}

void ServiceCommunicator::sendToService(const QString &msg)
{
    LOGD("");
    if(m_isServiceConnected){
        LOGD("msg : %s",msg.toUtf8().data());
        rep->sendToService(msg);
    }
}

void ServiceCommunicator::startService()
{
    QAndroidIntent serviceIntent(QtAndroid::androidActivity().object(),
                                        "com/hungkv/autolikeapp/communication/QtAndroidService");
    QAndroidJniObject result = QtAndroid::androidActivity().callObjectMethod(
        "startService",
        "(Landroid/content/Intent;)Landroid/content/ComponentName;",
        serviceIntent.handle().object());
}

void ServiceCommunicator::onDatabaseAvailable(QString path)
{
    LOGD("");
    if(m_isServiceConnected){
        LOGD("Send database path");
        rep->databaseAvailable(path);
    }
}
