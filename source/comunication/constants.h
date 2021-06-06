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
    }

    namespace Info {
        const QString DATABASE_DECLARE_INFO = "com.hungkv.autolikeapp.info.databasedeclaration";
        const QString UPDATE_DATA_INFO = "com.hungkv.autolikeapp.info.updatedata";
    }

    namespace ToastDuration {
        const int LONG = 1;
        const int SHORT = 0;
    }

}

#endif // CONSTANTS_H
