#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>

#include "comunication/qtandroidservice.h"
#include "comunication/jnimessenger.h"
#include "revenuecontroller.h"

#include "comunication/references.h"


class MasterController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QtAndroidService* ui_qtAndroidService READ qtAndroidService CONSTANT)
    Q_PROPERTY(JniMessenger* ui_jniMessenger READ jniMessenger CONSTANT)
    Q_PROPERTY(RevenueController* ui_revenueController READ revenueController NOTIFY revenueControllerChanged)
public:
    explicit MasterController(QObject *parent = nullptr);

    QtAndroidService* qtAndroidService();
    JniMessenger* jniMessenger();
    RevenueController* revenueController();
signals:
    void revenueControllerChanged();
    void databaseChanged();
public slots:

    void onReceiveMessageFromService(const QString &message);
private:
    RevenueController* m_revenueController = nullptr;
    void onDatabaseAvailable(QString path);
};

#endif // MAINCONTROLLER_H
