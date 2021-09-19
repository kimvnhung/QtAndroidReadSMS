#ifndef SERVICECOMMUNICATOR_H
#define SERVICECOMMUNICATOR_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QRemoteObjectNode>
#include <QTimer>
#include <QUrl>
#include "rep_qtandroidservice_replica.h"
#include "log.h"

class ServiceCommunicator : public QObject
{
    Q_OBJECT
public:
    explicit ServiceCommunicator(QObject *parent = nullptr);


public slots:
    void onCheckReplicConnection();
    void onServiceStatusChanged(bool isConnected);
    void sendToService(const QString &message);
    void startService();
signals:
    void messageFromService(const QString &message);
    void serviceConnected();

private:
    QRemoteObjectNode repNode;
    QSharedPointer<QtAndroidServiceReplica> rep;
    bool m_isInitializedReplica;
    bool m_isServiceConnected;
    QTimer connectTimer;
};

#endif // SERVICECOMMUNICATOR_H
