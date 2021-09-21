#ifndef QTANDROIDSERVICE_H
#define QTANDROIDSERVICE_H

#include <QObject>
#include <QtAndroid>
#include <QAndroidIntent>
#include <QTimer>

#include "constants.h"
#include "rep_qtandroidservice_source.h"
#include "log.h"
#include "webapirequest.h"
#include "databasehandler.h"
#include "transaction.h"

class QtAndroidService : public QObject
{
    Q_OBJECT

public:
    QtAndroidService(QObject *parent = nullptr);
    ~QtAndroidService();

    static QtAndroidService *instance();
    Q_INVOKABLE void startBackgroundService();
    Q_INVOKABLE void startForegroundService();
    Q_INVOKABLE void log(const QString &message);
    Q_INVOKABLE void updateTransaction(QString jsonTrans);
    void registerNative();

    void passingObject(QAndroidJniObject javaObject);
    QAndroidJniObject* jniObject(){return m_javaServiceInstance;}

signals:
    void sendToUi(const QString &message);
public slots:
    void handleAction(const QString &action);
    void handleActionWithData(const QString &action, const QString &data);
    void onInternetConnectionChanged(bool isConnected);
    void handleAsynTask();

private:
    static QtAndroidService *m_instance;
    QTimer *timer = nullptr;
    QTimer *delayForUpdate = nullptr;
    WebAPIRequest *webAPI = nullptr;
    QAndroidJniObject *m_javaServiceInstance = nullptr;
    static QString DatabasePath;
    QList<QString> needToUpdate;

    void updateToServer(QList<Transaction*> listTrans);
    void pushOnGoogleSheet(QList<Transaction*> listTrans);

    void updateInfo();
    //async void
    void updateTransactionStatus();

private slots:
    void onNetworkResponse(QString response);


};

#endif // QTANDROIDSERVICE_H
