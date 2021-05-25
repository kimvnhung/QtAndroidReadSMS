QT += quick androidextras

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        comunication/utility.cpp \
        database/databasereader.cpp \
        main.cpp \
        comunication/qtandroidservice.cpp

HEADERS += \
        comunication/qtandroidservice.h \
        comunication/references.h \
        comunication/utility.h \
        database/databasereader.h

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

android{
    DISTFILES += \
        android/src/com/hungkv/autolikeapp/comunication/ActivityUtils.java \
        android/src/com/hungkv/autolikeapp/comunication/QtAndroidService.java \
        android/AndroidManifest.xml \
        android/src/com/hungkv/autolikeapp/listener/SmsReceiver.java

    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
}

DISTFILES += \
    android/src/com/hungkv/autolikeapp/database/DatabaseHandler.java \
    android/src/com/hungkv/autolikeapp/database/Transaction.java
