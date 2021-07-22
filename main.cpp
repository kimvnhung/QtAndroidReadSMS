
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
                                   "android.permission.GET_TASKS",
                                   "android.permission.ACCESS_NETWORK_STATE"});
#endif


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

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
    //init qtAndroidService
//    QtAndroidService *qtAndroidService = new QtAndroidService(&app);
//    Q_UNUSED(qtAndroidService)



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
}
