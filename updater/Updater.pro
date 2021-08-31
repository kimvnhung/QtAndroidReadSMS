QT -= gui

QT += core androidextras xml network

TEMPLATE = lib
DEFINES += UPDATER_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


#LIBS += -L$$PWD/libs/armeabi-v7a -lchilkatAndroid
#INCLUDEPATH += $$PWD/include
#DEPENDPATH += $PWD/include

SOURCES += \
    com_hungkv_autolikeapp_communication_WeakUpLibrary.cpp \
    webapirequest.cpp \
    qtandroidservice.cpp

HEADERS += \
    com_hungkv_autolikeapp_communication_WeakUpLibrary.h \
    webapirequest.h \
    constants.h \
    qtandroidservice.h

include($$PWD/android_openssl/openssl.pri)
