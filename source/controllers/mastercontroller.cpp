#include "mastercontroller.h"

MasterController::MasterController(QGuiApplication *parent) :
    QObject(parent)
{
//    JniMessenger *initialer = new JniMessenger(parent);
//    Q_UNUSED(initialer)
    connect(parent,&QGuiApplication::applicationStateChanged,[=](Qt::ApplicationState state){
        switch (state) {
        case Qt::ApplicationHidden:
            QtAndroidService::instance()->log("Application Hidden");
            break;
        case Qt::ApplicationActive:
            QtAndroidService::instance()->log("Application Active");

            this->m_revenueController->updateList();
            break;
        case Qt::ApplicationInactive:
            QtAndroidService::instance()->log("Application Inactive");

            break;
        case Qt::ApplicationSuspended:
            QtAndroidService::instance()->log("Application Suspended");

        }
    });

//    QtAndroid::runOnAndroidThread([=]()
//    {
//        QAndroidJniObject window = QtAndroid::androidActivity().callObjectMethod("getWindow", "()Landroid/view/Window;");
//        window.callMethod<void>("addFlags", "(I)V", 0x80000000);
//        window.callMethod<void>("clearFlags", "(I)V", 0x04000000);
//        window.callMethod<void>("setStatusBarColor", "(I)V", 0xffffffff); // Desired statusbar color
//    });


    this->m_revenueController = new RevenueController(this);
    this->m_settingController = new SettingController(this);
    connect(m_settingController->getAboutUsProperty(), &PropertyAction::clicked,[=](){
        //about index = 5

    });
    this->m_reportController = new ReportController(this);
    this->m_historyController = new HistoryController(this);


    QtAndroidService *initialier = new QtAndroidService(parent);
    connect(initialier, &QtAndroidService::messageFromService,this, &MasterController::onReceiveMessageFromService);
    initialier->startBackgroundService();


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

JniMessenger* MasterController::jniMessenger()
{
    return JniMessenger::instance();
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
    QtAndroidService::instance()->log(message);
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


