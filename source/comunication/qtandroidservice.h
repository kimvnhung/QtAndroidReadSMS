#ifndef QTANDROIDSERVICE_H
#define QTANDROIDSERVICE_H

#include <QObject>
#include <QtAndroid>
#include <QAndroidIntent>

class QtAndroidService : public QObject
{
    Q_OBJECT

public:
    QtAndroidService(QObject *parent = nullptr);

    static QtAndroidService *instance() { return m_instance; }
    Q_INVOKABLE void sendToService(const QString &name);

signals:
    void messageFromService(const QString &message);

private:
    static QtAndroidService *m_instance;
};

#endif // QTANDROIDSERVICE_H
