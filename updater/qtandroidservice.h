#ifndef QTANDROIDSERVICE_H
#define QTANDROIDSERVICE_H

#include <QObject>
#include <QtAndroid>
#include <QAndroidIntent>
#include <QTimer>

#include "constants.h"
#include "rep_qtandroidservice_source.h"
#include "log.h"

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

public slots:
    void sendToService(const QString &name) override{
        LOGD("Message : %s",name.toUtf8().data());
        emit messageFromService(name);
    }

    void requestServiceStatus() override{
        LOGD("onRequestServiceStatus");
        emit serviceStatusChanged(true);
    }

    void transferMessage();
private:
    static QtAndroidService *m_instance;
    QTimer *timer = nullptr;

};

#endif // QTANDROIDSERVICE_H
