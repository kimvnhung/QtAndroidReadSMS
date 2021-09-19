#include "mastercontroller.h"

MasterController::MasterController(QObject *parent) :
    QObject(parent)
{


    this->m_revenueController = new RevenueController(this);
    this->m_settingController = new SettingController(this);
    connect(m_settingController->getAboutUsProperty(), &PropertyAction::clicked,[=](){
        //about index = 5

    });
    this->m_reportController = new ReportController(this);
    this->m_historyController = new HistoryController(this);


    mAccount = new Account(this, "Username","pass","HungKV");

    //declare action
    mRevenueTab = new TabAction(this,"qrc:/images/revenue_tab_ic.png","qrc:/images/revenue_untab_ic.png","Revenue",true);
    mReportsTab = new TabAction(this,"qrc:/images/reports_tab_ic.png","qrc:/images/reports_untab_ic.png","Reports");
    mHistoryTab = new TabAction(this,"qrc:/images/history_tab_ic.png","qrc:/images/history_untab_ic.png","Trans. history");
    mOffersTab = new TabAction(this,"qrc:/images/offers_tab_ic.png","qrc:/images/offers_untab_ic.png","Special offers");
    mSettingTab = new TabAction(this,"qrc:/images/setting_tab_ic.png","qrc:/images/setting_untab_ic.png","Settings");

    connect(mRevenueTab, &TabAction::clicked, this, &MasterController::onTabSelected);
    connect(mReportsTab, &TabAction::clicked, this, &MasterController::onTabSelected);
    connect(mHistoryTab, &TabAction::clicked, this, &MasterController::onTabSelected);
    connect(mOffersTab, &TabAction::clicked, this, &MasterController::onTabSelected);
    connect(mSettingTab, &TabAction::clicked, this, &MasterController::onTabSelected);

}


//publics
QtAndroidService* MasterController::qtAndroidService()
{
    return QtAndroidService::instance();
}

RevenueController* MasterController::revenueController()
{
    return this->m_revenueController;
}

SettingController* MasterController::settingController()
{
    return this->m_settingController;
}

ReportController* MasterController::reportController()
{
    return this->m_reportController;
}

HistoryController* MasterController::historyController()
{
    return this->m_historyController;
}

Account* MasterController::account()
{
    return this->mAccount;
}

TabAction* MasterController::revenueTab()
{
    return this->mRevenueTab;
}

TabAction* MasterController::reportsTab()
{
    return this->mReportsTab;
}

TabAction* MasterController::historyTab()
{
    return this->mHistoryTab;
}

TabAction* MasterController::offersTab()
{
    return this->mOffersTab;
}

TabAction* MasterController::settingTab()
{
    return this->mSettingTab;
}


//slots
void MasterController::onReceiveMessageFromService(const QString &message)
{
    if(message.startsWith(Constants::Info::DATABASE_DECLARE_INFO)){
        onDatabaseAvailable(message.mid(Constants::Info::DATABASE_DECLARE_INFO.length()));
    }

    if(message == Constants::Info::UPDATE_DATA_INFO){
        qDebug()<<"onUpdateInfo";
        if(!DatabaseHandler::instance()->isDatabaseOpenable()){
            //restart service to reopen database
            QtAndroidService::instance()->startBackgroundService();
        }else {
            updateAll();
        }
    }

    if(message == Constants::Action::UPDATE_TO_SERVER){
        this->historyController()->updateTransactionToServer();
    }

    if(message == Constants::Info::INTERNET_CONNECTED){
        this->historyController()->updateTransactionToServer();
    }

    if(message.contains("on")){
        log(message);
    }
}

void MasterController::onTabSelected()
{
    mRevenueTab->setSelected(false);
    mReportsTab->setSelected(false);
    mHistoryTab->setSelected(false);
    mOffersTab->setSelected(false);
    mSettingTab->setSelected(false);

    if(sender() == mReportsTab){
        emit tabChanged(1);
    }else if(sender() == mHistoryTab){
        emit tabChanged(2);
    }else if(sender() == mOffersTab){
        emit tabChanged(3);
    }else if(sender() == mSettingTab){
        emit tabChanged(4);
    }else{
        emit tabChanged(0);
    }

    ((TabAction*)sender())->setSelected(true);
}

void MasterController::swippedTo(int tabIndex)
{
    mRevenueTab->setSelected(false);
    mReportsTab->setSelected(false);
    mHistoryTab->setSelected(false);
    mOffersTab->setSelected(false);
    mSettingTab->setSelected(false);

    switch (tabIndex) {
    case 0:
        mRevenueTab->setSelected(true);
        break;
    case 1:
        mReportsTab->setSelected(true);
        break;
    case 2:
        mHistoryTab->setSelected(true);
        break;
    case 3:
        mOffersTab->setSelected(true);
        break;
    case 4:
        mSettingTab->setSelected(true);
        break;
    default:
        mRevenueTab->setSelected(true);
        break;
    }
}

void MasterController::log(QString message)
{
    LOGD("%s",message.toUtf8().data());
}

//private
void MasterController::onDatabaseAvailable(QString path)
{
    //Declare database
    DatabaseHandler *handler = new DatabaseHandler(this,path);
    Q_UNUSED(handler)

    updateAll();
}

void MasterController::updateAll()
{
    this->m_revenueController->updateList();
    this->m_historyController->updateList();
    this->m_reportController->updateList();
}


