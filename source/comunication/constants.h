#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QObject>

class Constants{
public:
    class Action{
    public :
        static QString OPEN_QT_ACTIVITY_ACTION;
        static QString START_BACKGROUND_SERVICE_ACTION;
        static QString START_FOREGROUND_ACTION;
        static QString STOPFOREGROUND_ACTION;
        static QString LOG_ACTION;
    };

    class Info{
    public:
        static QString DATABASE_DECLARE_INFO;
        static QString UPDATE_DATA_INFO;
    };

    class ToastDuration{
    public:
        static int LONG;
        static int SHORT;
    };
};


#endif // CONSTANTS_H
