QT += qml quick androidextras sql svg xml network

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = $$PWD

INCLUDEPATH += source/

SOURCES += \
        source/comunication/jnimessenger.cpp \
        source/comunication/qtandroidservice.cpp \
        source/comunication/utility.cpp \
        source/comunication/webapirequest.cpp \
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
        source/comunication/constants.h \
        source/comunication/jnimessenger.h \
        source/comunication/qtandroidservice.h \
        source/comunication/utility.h \
        source/comunication/webapirequest.h \
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
        source/android/src/com/hungkv/autolikeapp/comunication/JniMessenger.java \
        source/android/src/com/hungkv/autolikeapp/comunication/QtAndroidService.java \
        source/android/src/com/hungkv/autolikeapp/database/DatabaseHandler.java \
        source/android/src/com/hungkv/autolikeapp/database/Transaction.java \
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

DISTFILES += \
    source/android/src/com/hungkv/autolikeapp/comunication/NetworkChangeReceiver.java \
    source/android/src/com/hungkv/autolikeapp/comunication/NetworkUtil.java




