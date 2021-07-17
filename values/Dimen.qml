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

    readonly property real normalLeftMargin: 16*ratioH

    //square dimen
    readonly property real tabFontSize: 10*ratioSq
    readonly property real helloFontSize: 14*ratioSq
    readonly property real accountNameFontSize: 16*ratioSq
    readonly property real avatarSize: 40*ratioSq
    readonly property real incomeValueFontSize: 32*ratioSq
    readonly property real revenueTableHeaderFontSize: 12*ratioSq
    readonly property real transactionItemFontSize: 12*ratioSq
    readonly property real transactionStatusIconSize: 16*ratioSq

    readonly property real textSizeLv0: 14*ratioSq
    readonly property real textSizeLv1: 15*ratioSq
    readonly property real textSizeLv2: 16*ratioSq
    readonly property real textSizeLv3: 18*ratioSq
    readonly property real textSizeLv4: 32*ratioSq
    readonly property real textSizeLv5: 45*ratioSq

    //setting tab
    readonly property real propertyTextSize: 16*ratioSq
    readonly property real settingTitleTextSize: 18*ratioSq

    //offer tab
    readonly property real offerPanelTextSize : 14*ratioSq
    readonly property real offerPanelTextSize2 : 15*ratioSq
    readonly property real offerPanelPercentTextSize : 45*ratioSq

    /**
    *   vertical dimen
    */
    readonly property real windowHeight : 812*ratioV
    readonly property real tabContentHeight: 700*ratioV
    readonly property real tabButtonHeight: 46*ratioV
    readonly property real tabButtonIconHeight: 16*ratioV

    //revenue
    readonly property real revenuePanelHeight: 220*ratioV
    readonly property real tableHeaderHeight: 44*ratioV
    readonly property real revenueTableHeight: 490*ratioV
    readonly property real transactionItemHeight: 47*ratioV


    //settings
    readonly property real propertyButtonHeight: 75*ratioV
    readonly property real settingTitleAreaHeight: 59*ratioV
    readonly property real aboutUsTitleAreaHeight: 39*ratioV


    //special offer
    readonly property real offerPanelHeight: 115*ratioV
    readonly property real percentCategoryHeight: 80*ratioV

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
