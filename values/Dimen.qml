pragma Singleton
import QtQuick 2.14
import QtQuick.Window 2.2

Item {
    readonly property real scrHeight: Screen.desktopAvailableHeight
    readonly property real scrWidth: Screen.desktopAvailableWidth
    readonly property real designHeight: 778
    readonly property real designWidth: 375
    readonly property real ratioH: scrHeight/designHeight
    readonly property real ratioW: scrWidth/designWidth

    readonly property real ratioSq: scrHeight>scrWidth?ratioW:ratioH

    readonly property real demo_size : 233

    //square dimen
    readonly property real tabFontSize: 10*ratioSq
    readonly property real tabButtonSize: 75*ratioSq
    readonly property real tabButtonIconSize: 15*ratioSq

    //horizontal dimen
    readonly property real windowHeight : 812*ratioH
    readonly property real tabContentHeight: 732*ratioH



    //vertical dimen
    readonly property real windowWidth: 375*ratioW


}
