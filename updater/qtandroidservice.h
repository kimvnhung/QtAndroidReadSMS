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

class QtAndroidService : public QtAndroidServiceSource
{
    Q_OBJECT

public:
    QtAndroidService(QObject *parent = nullptr);
    ~QtAndroidService();

    static QtAndroidService *instance() { return m_instance; }
    Q_INVOKABLE void startBackgroundService();
    Q_INVOKABLE void startForegroundService();
    Q_INVOKABLE void log(const QString &message);
    Q_INVOKABLE void updateTransaction(QString jsonTrans);
    void registerNative();

    static QList<QString> inbox;

    void handleServiceMessage(const QString &message);
    void passingObject(QAndroidJniObject javaObject);
    QAndroidJniObject* jniObject(){return m_javaServiceInstance;}
public slots:
    void sendToService(const QString &name) override{
        LOGD("Message : %s",name.toUtf8().data());
        emit messageFromService(name);
    }

    void requestServiceStatus() override{
        LOGD("onRequestServiceStatus");
        emit serviceStatusChanged(true);
    }

    void transferDatabasePath(QString path) override;

    void handleAsynTask();

private:
    static QtAndroidService *m_instance;
    QTimer *timer = nullptr;
    QTimer *delayForUpdate = nullptr;
    WebAPIRequest *webAPI = nullptr;
    DatabaseHandler* databaseHandler = nullptr;
    QAndroidJniObject *m_javaServiceInstance = nullptr;
    static QString DatabasePath;

    void updateToServer(QList<Transaction*> listTrans);
    void pushOnGoogleSheet(QList<Transaction*> listTrans);
private slots:
    void onNetworkResponse(QString response);
};

#endif // QTANDROIDSERVICE_H
