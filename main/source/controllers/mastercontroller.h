#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QGuiApplication>

#include <QRemoteObjectNode>
#include <QTimer>
#include <QUrl>
#include "rep_qtandroidservice_replica.h"


#include "revenuecontroller.h"
#include "settingcontroller.h"
#include "reportcontroller.h"
#include "historycontroller.h"

#include "communication/constants.h"


#include "model/tabaction.h"
#include "model/account.h"
#include "log.h"


class MasterController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(RevenueController* ui_revenueController READ revenueController NOTIFY revenueControllerChanged)
    Q_PROPERTY(SettingController* ui_settingController READ settingController NOTIFY settingControllerChanged)
    Q_PROPERTY(ReportController* ui_reportController READ reportController NOTIFY reportControllerChanged)
    Q_PROPERTY(HistoryController* ui_historyController READ historyController NOTIFY historyControllerChanged)

    Q_PROPERTY(TabAction* ui_revenueTab READ revenueTab NOTIFY revenueTabChanged)
    Q_PROPERTY(TabAction* ui_reportsTab READ reportsTab NOTIFY reportsTabChanged)
    Q_PROPERTY(TabAction* ui_historyTab READ historyTab NOTIFY historyTabChanged)
    Q_PROPERTY(TabAction* ui_offersTab READ offersTab NOTIFY offersTabChanged)
    Q_PROPERTY(TabAction* ui_settingTab READ settingTab NOTIFY settingTabChanged)

    Q_PROPERTY(Account* ui_account READ account NOTIFY accountChanged)
public:
    explicit MasterController(QObject *parent = nullptr);
    static MasterController* instace(){return mInstance;};

    RevenueController* revenueController();
    SettingController* settingController();
    ReportController* reportController();
    HistoryController* historyController();

    Account* account();

    //tab action
    TabAction* revenueTab();
    TabAction* reportsTab();
    TabAction* historyTab();
    TabAction* offersTab();
    TabAction* settingTab();

    void startService();
    void registerNative();

signals:
    void revenueControllerChanged();
    void settingControllerChanged();
    void reportControllerChanged();
    void historyControllerChanged();
    void databaseChanged();

    void revenueTabChanged();
    void reportsTabChanged();
    void historyTabChanged();
    void offersTabChanged();
    void settingTabChanged();

    void accountChanged();
    void tabChanged(int index);

    void sendMessage(const QString &message);
public slots:
    void log(QString message);
    void onReceiveMessageFromService(const QString &message);
    void onTabSelected();
    void swippedTo(int tabIndex);
    void requestDatabase();
private:
    static MasterController* mInstance;

    RevenueController* m_revenueController = nullptr;
    SettingController* m_settingController = nullptr;
    ReportController* m_reportController = nullptr;
    HistoryController* m_historyController = nullptr;

    Account* mAccount;

    //tab action
    TabAction* mRevenueTab;
    TabAction* mReportsTab;
    TabAction* mHistoryTab;
    TabAction* mOffersTab;
    TabAction* mSettingTab;

    void onDatabaseAvailable(QString path);
    void updateAll();


};

#endif // MAINCONTROLLER_H
