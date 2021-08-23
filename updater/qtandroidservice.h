#ifndef QTANDROIDSERVICE_H
#define QTANDROIDSERVICE_H

#include <QObject>
#include <QtAndroid>
#include <QAndroidIntent>

#include "constants.h"

class QtAndroidService : public QObject
{
    Q_OBJECT

public:
    QtAndroidService(QObject *parent = nullptr);

    static QtAndroidService *instance() { return m_instance; }
    Q_INVOKABLE void startBackgroundService();
    Q_INVOKABLE void startForegroundService();
    Q_INVOKABLE void log(const QString &message);
    Q_INVOKABLE void updateTransaction(QString jsonTrans);

signals:
    void messageFromService(const QString &message);

private:
    static QtAndroidService *m_instance;
};

#endif // QTANDROIDSERVICE_H
