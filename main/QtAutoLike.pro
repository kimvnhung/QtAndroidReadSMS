QT += qml quick androidextras sql svg xml network remoteobjects

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = $$PWD

REPC_REPLICA += ../common/qtandroidservice.rep


INCLUDEPATH += source/

SOURCES += \
        source/communication/jnimessenger.cpp \
        source/communication/qtandroidservice.cpp \
        source/communication/utility.cpp \
        source/communication/webapirequest.cpp \
        source/controllers/historycontroller.cpp \
        source/controllers/mastercontroller.cpp \
        source/controllers/reportcontroller.cpp \
        source/controllers/revenuecontroller.cpp \
        source/controllers/settingcontroller.cpp \
        source/database/databasehandler.cpp \
        main.cpp \
        source/model/account.cpp \
        source/model/propertyAction.cpp \
        source/model/tabaction.cpp \
        source/model/transaction.cpp

HEADERS += \
        source/communication/constants.h \
        source/communication/jnimessenger.h \
        source/communication/qtandroidservice.h \
        source/communication/utility.h \
        source/communication/webapirequest.h \
        source/controllers/historycontroller.h \
        source/controllers/mastercontroller.h \
        source/controllers/reportcontroller.h \
        source/controllers/revenuecontroller.h \
        source/controllers/settingcontroller.h \
        source/database/databasehandler.h \
        source/model/account.h \
        source/model/propertyaction.h \
        source/model/tabaction.h \
        source/model/transaction.h

RESOURCES += views.qrc \
    components.qrc \
    values.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

android{
    DISTFILES += \
        source/android/res/drawable/ic_launcher.png \
        source/android/src/com/hungkv/autolikeapp/MainActivity.java \
        source/android/src/com/hungkv/autolikeapp/Constants.java \
        source/android/src/com/hungkv/autolikeapp/communication/JniMessenger.java \
        source/android/src/com/hungkv/autolikeapp/communication/QtAndroidService.java \
        source/android/src/com/hungkv/autolikeapp/database/DatabaseHandler.java \
        source/android/src/com/hungkv/autolikeapp/database/Transaction.java \
        source/android/src/com/hungkv/autolikeapp/communication/NetworkChangeReceiver.java \
        source/android/src/com/hungkv/autolikeapp/communication/NetworkUtil.java \
        source/android/AndroidManifest.xml \
        source/android/src/com/hungkv/autolikeapp/listener/SmsReceiver.java

    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/source/android
    include($$PWD/android_openssl/openssl.pri)

    deployment.files += AutoLikeAgency.db
    deployment.path = /assets
    INSTALLS += deployment

    certificates.path = /assets
    certificates.files += \
        $$PWD/certs/approval-api.pfx \
        $$PWD/certs/approval.pfx \
        $$PWD/certs/approval-mt.pfx
    INSTALLS += certificates
}




