
#include "comunication/jnimessenger.h"

#include <QAndroidService>

#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "controllers/mastercontroller.h"
#include "controllers/revenuecontroller.h"
#include "controllers/settingcontroller.h"

#if defined (Q_OS_ANDROID)
#include <QtAndroid>
#include <QtSvg>
const QVector<QString> permissions({"android.permission.RECEIVE_SMS",
                                   "android.permission.FOREGROUND_SERVICE",
                                   "android.permission.INTERNET",
                                   "android.permission.GET_TASKS"});
#endif


int main(int argc, char *argv[])
{   
    qDebug()<<"argc : "<<argc;
    if(argc==1){
        #if defined (Q_OS_ANDROID)
        //Request requiered permissions at runtime
        for(const QString &permission : permissions){
            auto result = QtAndroid::checkPermission(permission);
            if(result == QtAndroid::PermissionResult::Denied){
                auto resultHash = QtAndroid::requestPermissionsSync(QStringList({permission}));
                if(resultHash[permission] == QtAndroid::PermissionResult::Denied)
                    return 0;
            }
        }
        #endif

        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
        QGuiApplication app(argc, argv);

        //Register
        qmlRegisterType<MasterController>("SRC", 1, 0, "MasterController");
        qmlRegisterType<SettingController>("SRC", 1, 0,"SettingController");
        qmlRegisterType<RevenueController>("SRC", 1, 0,"RevenueController");
        //qmlRegisterType<JniMessenger>("SRC", 1, 0,"JniMessenger");
        qmlRegisterType<QtAndroidService>("SRC", 1, 0,"QtAndroidService");

        qmlRegisterType<Transaction>("SRC", 1, 0,"Transaction");
        qmlRegisterType<TabAction>("SRC", 1, 0,"TabAction");
        qmlRegisterType<PropertyAction>("SRC", 1, 0,"PropertyAction");




        QQmlApplicationEngine engine;
        engine.addImportPath("qrc:/");

        MasterController *masterController = new MasterController(&app);
        engine.rootContext()->setContextProperty(QLatin1String("masterController"), masterController);

        const QUrl url(QStringLiteral("qrc:/views/main.qml"));
        QObject::connect(
            &engine,
            &QQmlApplicationEngine::objectCreated,
            &app,
            [url](QObject *obj, const QUrl &objUrl) {
                if (!obj && url == objUrl)
                    QCoreApplication::exit(-1);
            },
            Qt::QueuedConnection);
        engine.load(url);

        return app.exec();
    }else if(argc > 1 && strcmp(argv[1], "-service") == 0){

        JniMessenger *messenger = new JniMessenger();
        QObject::connect(messenger, &JniMessenger::messageFromJava, [=](QString msg){
            qDebug()<<"Mess : "<<msg;
        });
        messenger->printFromJava("Hello World 123");
        return 1;
    }

    return -1;
}
