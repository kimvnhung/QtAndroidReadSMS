#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QGuiApplication>

#include "comunication/qtandroidservice.h"
#include "comunication/jnimessenger.h"
#include "revenuecontroller.h"


#include "comunication/constants.h"


#include "model/tabaction.h"

class MasterController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QtAndroidService* ui_qtAndroidService READ qtAndroidService CONSTANT)
    Q_PROPERTY(JniMessenger* ui_jniMessenger READ jniMessenger CONSTANT)
    Q_PROPERTY(RevenueController* ui_revenueController READ revenueController NOTIFY revenueControllerChanged)
    Q_PROPERTY(TabAction* ui_revenueTab READ revenueTab NOTIFY revenueTabChanged)
    Q_PROPERTY(TabAction* ui_reportsTab READ reportsTab NOTIFY reportsTabChanged)
    Q_PROPERTY(TabAction* ui_historyTab READ historyTab NOTIFY historyTabChanged)
    Q_PROPERTY(TabAction* ui_offersTab READ offersTab NOTIFY offersTabChanged)
    Q_PROPERTY(TabAction* ui_settingTab READ settingTab NOTIFY settingTabChanged)
public:
    explicit MasterController(QGuiApplication *parent = nullptr);

    QtAndroidService* qtAndroidService();
    JniMessenger* jniMessenger();
    RevenueController* revenueController();

    //tab action
    TabAction* revenueTab();
    TabAction* reportsTab();
    TabAction* historyTab();
    TabAction* offersTab();
    TabAction* settingTab();

signals:
    void revenueControllerChanged();
    void databaseChanged();

    void revenueTabChanged();
    void reportsTabChanged();
    void historyTabChanged();
    void offersTabChanged();
    void settingTabChanged();
public slots:
    void log(QString message);
    void onReceiveMessageFromService(const QString &message);
private:
    RevenueController* m_revenueController = nullptr;


    //tab action
    TabAction* mRevenueTab;
    TabAction* mReportsTab;
    TabAction* mHistoryTab;
    TabAction* mOffersTab;
    TabAction* mSettingTab;

    void onDatabaseAvailable(QString path);

};

#endif // MAINCONTROLLER_H
