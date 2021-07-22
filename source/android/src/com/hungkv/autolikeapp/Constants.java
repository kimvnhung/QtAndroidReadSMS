package com.hungkv.autolikeapp;

public class Constants {
    public static final String QT_LOG = "Qt : ";
    public static final String JAVA_LOG = "Java : ";
    public interface ACTION {
        public static String OPEN_QT_ACTIVITY_ACTION = "com.hungkv.autolikeapp.action.openqtactivity";
        public static String START_BACKGROUND_SERVICE_ACTION = "com.hungkv.autolikeapp.action.startbackground";
        public static String START_FOREGROUND_ACTION = "com.hungkv.autolikeapp.action.startforeground";
        public static String STOP_FOREGROUND_ACTION = "com.hungkv.autolikeapp.action.stopforeground";
        public static String LOG_ACTION = "com.hungkv.autolikeapp.action.log";
        public static String ACTIVITY_STOPPED_ACTION = "com.hungkv.autolike.activitystopped";
        public static String ACTIVITY_STARTED_ACTION = "com.hungkv.autolike.activitystarted";
        public static String UPDATE_TRANSACTION_ACTION = "com.hungkv.autolike.updatetransaction";
        public static String UPDATE_TO_SERVER = "com.hungkv.autolike.updatetoserver";
    }

    public interface INFO {
        public static String DATABASE_DECLARE_INFO = "com.hungkv.autolikeapp.info.databasedeclaration";
        public static String UPDATE_DATA_INFO = "com.hungkv.autolikeapp.info.updatedata";
    }

    public interface TRANSACTION{
        public static String ID = "id";
        public static String PHONE = "phone";
        public static String CODE = "code";
        public static String VALUE = "value";
        public static String TIME = "time";
        public static String UPDATE_TIME = "update_time";
        public static String STATUS = "status";
    }

    public interface NOTIFICATION {
        public static int FOREGROUND_SERVICE = 101;
        public static String NOTIFICATION_CHANNEL_ID = "autolikeapp_ncid";
        public static String NOTIFICATION_CHANNEL_NAME = "Auto Like Channel Name";
        public static String NOTIFICATION_DESCRIPTION = "Notification Description";
    }
}

