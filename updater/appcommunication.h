#ifndef APPCOMMUNICATION_H
#define APPCOMMUNICATION_H

#include <QObject>
#include <QTimer>
#include "rep_qtandroidservice_source.h"
#include "log.h"

class AppCommunication : public QtAndroidServiceSource
{
    Q_OBJECT
public:
    explicit AppCommunication(QObject *parent = nullptr);
    ~AppCommunication();
public slots:
    void requestBackground(const QString &action, const QString &data) override;
    void requestServiceStatus() override{
        LOGD("onRequestServiceStatus");
        emit serviceStatusChanged(true);
    }

signals:
    void internetConnectionChanged(bool isConnected);
private:
    QTimer *internetCheckingTimer = nullptr;
    bool isConnectedInternet = false;
};

#endif // APPCOMMUNICATION_H
