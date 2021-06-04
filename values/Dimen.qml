pragma Singleton
import QtQuick 2.14
import QtQuick.Window 2.2

Item {
    readonly property real scrHeight: Screen.desktopAvailableHeight
    readonly property real scrWidth: Screen.desktopAvailableWidth
    readonly property real designHeight: 745
    readonly property real designWidth: 375
    readonly property real ratioV: scrHeight/designHeight
    readonly property real ratioH: scrWidth/designWidth

    readonly property real ratioSq: scrHeight>scrWidth?ratioH:ratioV

    readonly property real demo_size : 233

    //square dimen
    readonly property real tabFontSize: 10*ratioSq
    readonly property real helloFontSize: 14*ratioSq

    //vertical dimen
    readonly property real windowHeight : 812*ratioV
    readonly property real tabContentHeight: 700*ratioV
    readonly property real tabButtonHeight: 46*ratioV
    readonly property real tabButtonIconHeight: 16*ratioV
    readonly property real revenuePanelHeight: 220*ratioV


    //horizontal dimen
    readonly property real windowWidth: 375*ratioH
    readonly property real tabButtonWidth: 75*ratioH
    readonly property real tabButtonIconWidth: 15.2*ratioH



}
