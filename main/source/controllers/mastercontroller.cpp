#include "mastercontroller.h"

#include <QAndroidIntent>
#include <QAndroidJniEnvironment>
#include "utility.h"

MasterController* MasterController::mInstance = nullptr;

MasterController::MasterController(QObject *parent) :
    QObject(parent)
{
    mInstance = this;

    this->m_revenueController = new RevenueController(this);
    this->m_settingController = new SettingController(this);
    connect(m_settingController->getAboutUsProperty(), &PropertyAction::clicked,[=](){
        //about index = 5

    });
    this->m_reportController = new ReportController(this);
    connect(m_reportController, &ReportController::requestData,[this](QDate date){
        emit requestBackground(Constants::Action::REPORTS_REQUEST_ACTION,date.toString("dd/MM/yy"));
    });
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

bool MasterController::isLoading()
{
    return this->m_isLoading;
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


void MasterController::onTabSelected()
{
    LOGD("");
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
        onIsLoadingChanged(true);
        emit requestBackground(Constants::Action::REVENUE_REQUEST_ACTION);
        break;
    case 1:
        mReportsTab->setSelected(true);
        onIsLoadingChanged(true);
        emit requestBackground(Constants::Action::REPORTS_REQUEST_ACTION,this->m_reportController->getSelected_Date().toString("dd/MM/yy"));
        break;
    case 2:
        mHistoryTab->setSelected(true);
        onIsLoadingChanged(true);
        emit requestBackground(Constants::Action::HISTORY_REQUEST_ACTION);
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
    LOGD("Qt - %s",message.toUtf8().data());
}

void MasterController::messageFromBackground(const QString &action, const QString &data)
{
    if(data == ""){
        handleAction(action);
    }else {
        handleActionWithData(action,data);
    }
}

//private

void MasterController::handleActionWithData(const QString &action, const QString &data)
{
    if(action == Constants::Action::REVENUE_REQUEST_ACTION){
        this->m_revenueController->updateList(Utility::fromJson(data));
        onIsLoadingChanged(false);
    }else if(action == Constants::Action::REPORTS_REQUEST_ACTION){
        onIsLoadingChanged(false);
        this->m_reportController->updateList(Utility::fromJson(data));
    }else if(action == Constants::Action::HISTORY_REQUEST_ACTION){
        onIsLoadingChanged(false);
        this->m_historyController->updateList(Utility::fromJson(data));
    }
}

void MasterController::handleAction(const QString &action)
{
    if(action.startsWith(Constants::Info::DATABASE_DECLARE_INFO)){
        onIsLoadingChanged(true);
        emit requestBackground(Constants::Action::REVENUE_REQUEST_ACTION);
        // QJsonObject obj;
        // obj.insert(Constants::TransactionField::ID,0);
        // obj.insert(Constants::TransactionField::PHONE,"0354445540");
        // obj.insert(Constants::TransactionField::CODE, "MTXMI62");
        // obj.insert(Constants::TransactionField::VALUE, 100000);
        // obj.insert(Constants::TransactionField::TIME, "");
        // obj.insert(Constants::TransactionField::UPDATE_TIME, "");
        // obj.insert(Constants::TransactionField::STATUS, Transaction::ACCEPTED);
        // updateTransaction(QJsonDocument(obj).toJson(QJsonDocument::Compact),
        //                   Constants::Action::UPDATE_TRANSACTION_STATUS_ACTION);
    }else if(action == Constants::Info::UPDATE_DATA_INFO){
        qDebug()<<"onUpdateInfo";
//        if(!DatabaseHandler::instance()->isDatabaseOpenable()){
//            //restart service to reopen database
//            //QtAndroidService::instance()->startBackgroundService();
//        }else {
//            updateAll();
//        }
    }else if(action == Constants::Action::UPDATE_TO_SERVER){
        //this->historyController()->updateTransactionToServer();
    }else if(action == Constants::Info::INTERNET_CONNECTED){
        //this->historyController()->updateTransactionToServer();
    }else if(action == Constants::Action::REFRESH_UI_ACTION){
        if(mRevenueTab->selected()){
            emit requestBackground(Constants::Action::REVENUE_REQUEST_ACTION);
        }else if(mReportsTab->selected()){
            emit requestBackground(Constants::Action::REPORTS_REQUEST_ACTION,
                                   this->m_reportController->getSelected_Date().toString("dd/MM/yy"));
        }else if (mHistoryTab->selected()) {
            emit requestBackground(Constants::Action::REPORTS_REQUEST_ACTION);
        }
    }
}

void MasterController::updateAll()
{
//    this->m_revenueController->updateList();
//    this->m_historyController->updateList();
//    this->m_reportController->updateList();
}

void MasterController::requestDatabase()
{
    QAndroidIntent serviceIntent(Constants::Action::START_BACKGROUND_SERVICE_ACTION);

    QAndroidJniObject javaClass("com/hungkv/autolikeapp/communication/QtAndroidService");
    QAndroidJniEnvironment env;
    jclass objectClass = env->GetObjectClass(javaClass.object<jobject>());
    serviceIntent.handle().callObjectMethod(
                "setClass",
                "(Landroid/content/Context;Ljava/lang/Class;)Landroid/content/Intent;",
                QtAndroid::androidActivity().object(),
                objectClass);

    QAndroidJniObject result = QtAndroid::androidActivity().callObjectMethod(
                "startService",
                "(Landroid/content/Intent;)Landroid/content/ComponentName;",
                serviceIntent.handle().object());

}

// void MasterController::updateTransaction(QString jsonTrans, QString action)
// {
//     QAndroidIntent serviceIntent(action);

//     QAndroidJniObject javaClass("com/hungkv/autolikeapp/communication/QtAndroidService");
//     QAndroidJniEnvironment env;
//     jclass objectClass = env->GetObjectClass(javaClass.object<jobject>());
//     serviceIntent.handle().callObjectMethod(
//                 "setClass",
//                 "(Landroid/content/Context;Ljava/lang/Class;)Landroid/content/Intent;",
//                 QtAndroid::androidContext().object(),
//                 objectClass);
//     serviceIntent.putExtra("Transaction", jsonTrans.toUtf8());

//     QAndroidJniObject result = QtAndroid::androidContext().callObjectMethod(
//                 "startService",
//                 "(Landroid/content/Intent;)Landroid/content/ComponentName;",
//                 serviceIntent.handle().object());

// }

void MasterController::startService()
{
    QAndroidIntent serviceIntent(QtAndroid::androidActivity().object(),
                                        "com/hungkv/autolikeapp/communication/QtAndroidService");
    QAndroidJniObject result = QtAndroid::androidActivity().callObjectMethod(
        "startService",
        "(Landroid/content/Intent;)Landroid/content/ComponentName;",
        serviceIntent.handle().object());
}


void MasterController::onIsLoadingChanged(bool isLoading)
{
    m_isLoading = isLoading;
    emit isLoadingChanged();
}
