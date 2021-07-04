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
    readonly property real accountNameFontSize: 16*ratioSq
    readonly property real avatarSize: 40*ratioSq
    readonly property real incomeValueFontSize: 32*ratioSq
    readonly property real revenueTableHeaderFontSize: 12*ratioSq
    readonly property real transactionItemFontSize: 12*ratioSq
    readonly property real transactionStatusIconSize: 16*ratioSq

    /**
    *   vertical dimen
    */
    readonly property real windowHeight : 812*ratioV
    readonly property real tabContentHeight: 700*ratioV
    readonly property real tabButtonHeight: 46*ratioV
    readonly property real tabButtonIconHeight: 16*ratioV

    //revenue
    readonly property real revenuePanelHeight: 220*ratioV
    readonly property real tableHeaderHeight: 30*ratioV
    readonly property real revenueTableHeight: 490*ratioV
    readonly property real transactionItemHeight: 47*ratioV


    //settings
    readonly property real propertyButtonHeight: 75*ratioV

    /**
    *   horizontal dimen
    */
    readonly property real windowWidth: 375*ratioH
    readonly property real tabButtonWidth: 75*ratioH
    readonly property real tabButtonIconWidth: 15.2*ratioH



    //revenue
    readonly property real phoneHeaderWidth: 84*ratioH
    readonly property real topCodeHeaderWidth: 101*ratioH
    readonly property real valueHeaderWidth: 71*ratioH
    readonly property real updateHeaderWidth: 82*ratioH
    readonly property real sttHeaderWidth: 37*ratioH
    readonly property real revenueTableWidth: phoneHeaderWidth+topCodeHeaderWidth+valueHeaderWidth+updateHeaderWidth+sttHeaderWidth

    //settings
    readonly property real propertyButtonWidth: 375*ratioH
}
