#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QObject>

namespace Constants {
    namespace Action {
        const QString OPEN_QT_ACTIVITY_ACTION = "com.hungkv.autolikeapp.action.openqtactivity";
        const QString START_BACKGROUND_SERVICE_ACTION = "com.hungkv.autolikeapp.action.startbackground";
        const QString START_FOREGROUND_ACTION = "com.hungkv.autolikeapp.action.startforeground";
        const QString STOPFOREGROUND_ACTION = "com.hungkv.autolikeapp.action.stopforeground";
        const QString LOG_ACTION = "com.hungkv.autolikeapp.action.log";
        const QString ACTIVITY_STOPPED_ACTION = "com.hungkv.autolike.activitystopped";
        const QString UPDATE_TRANSACTION_ACTION = "com.hungkv.autolike.updatetransaction";
        const QString UPDATE_TRANSACTION_STATUS_ACTION = "com.hungkv.autolike.updatetransactionstatus";
        const QString UPDATE_TO_SERVER = "com.hungkv.autolike.updatetoserver";
        const QString NOTIFY_CONNECTION_ACTION = "com.hungkv.autolike.notifyconnection";
        const QString REVENUE_REQUEST_ACTION = "com.hungkv.autolike.revenuedatarequest";
        const QString REPORTS_REQUEST_ACTION = "com.hungkv.autolike.reportdatarequest";
        const QString HISTORY_REQUEST_ACTION = "com.hungkv.autolike.historydatarequest";
        const QString SERVICE_CLOCK_ACTION = "com.hungkv.autolike.serviceclock";
        const QString REFRESH_UI_ACTION = "com.hungkv.autolikeapp.refreshui";
        const QString DELETE_SMS_ACTION = "com.hungkv.autolikeapp.deletesms";
    }

    namespace TransactionField{
        const QString ID = "id";
        const QString PHONE = "phone";
        const QString CODE = "code";
        const QString VALUE = "value";
        const QString TIME = "time";
        const QString UPDATE_TIME = "update_time";
        const QString STATUS = "status";
        const QString SMS_CONTENT = "sms_content";
    }

    namespace Info {
        const QString DATABASE_DECLARE_INFO = "com.hungkv.autolikeapp.info.databasedeclaration";
        const QString UPDATE_DATA_INFO = "com.hungkv.autolikeapp.info.updatedata";
        const QString INTERNET_CONNECTED = "com.hungkv.autolikeapp.internetconnected";
    }

    namespace ToastDuration {
        const int LONG = 1;
        const int SHORT = 0;
    }

}

#endif // CONSTANTS_H
