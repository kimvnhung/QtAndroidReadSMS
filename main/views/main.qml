import QtQuick 2.14
import QtQuick.Layouts 1.14
import QtQuick.Window 2.14
import QtQuick.Controls.Material 2.12

import QtQuick.Controls 2.14
import components 1.0
import values 1.0

Window {
    // @disable-check M16
    width: Dimen.windowWidth
    // @disable-check M16
    height: Dimen.windowHeight
    // @disable-check M16
    visible: true

    Component.onCompleted: {
        masterController.log("ScreenHei :"+Dimen.scrHeight)
        masterController.log("ScreenWid :"+Dimen.scrWidth)
    }

    Rectangle{
        anchors.fill: parent
        SwipeView{
            id: tabContent
            anchors{
                top: parent.top
            }

            width: parent.width
            height: Dimen.tabContentHeight
            clip: true

            Item {
                id: firstItem
                Loader {
                    // index 0
                    id: revenuePage
                    source: "qrc:/views/tabs/revenueTab.qml"
                    anchors.fill: parent
                    anchors.top: parent.top
                }
            }
            Item {
                id: secondItem
                Loader {
                    // index 1
                    id: reportsPage
                    source: "qrc:/views/tabs/reportsTab.qml"
                    anchors.fill: parent
                    anchors.top: parent.top
                }
            }
            Item {
                id: thirdItem
                Loader {
                    // index 2
                    id: historyPage
                    source: "qrc:/views/tabs/historyTab.qml"
                    anchors.fill: parent
                    anchors.top: parent.top
                }
            }
            Item {
                id: fourthItem
                Loader {
                    // index 3
                    id: offersPage
                    source: "qrc:/views/tabs/offersTab.qml"
                    anchors.fill: parent
                    anchors.top: parent.top
                }
            }
            Item {
                id: fifthItem
                Loader {
                    // index 4
                    id: settingPage
                    source: "qrc:/views/tabs/settingTab.qml"
                    anchors.fill: parent
                    anchors.top: parent.top
                }
            }

            onCurrentIndexChanged: {
                masterController.swippedTo(currentIndex)
            }
        }

        Rectangle{
            id : sperator
            color: Color.lineSperatorColor
            width: parent.width
            height: 1
            anchors{
                top: tabContent.bottom
            }
        }

        Row {
            id : tabLayout
            anchors{
                top: sperator.bottom
                left: parent.left
                right: parent.right
                bottom: parent.bottom
            }
            TabButton {
                _action : masterController.ui_revenueTab
            }
            TabButton {
                _action : masterController.ui_reportsTab
            }
            TabButton {
                _action : masterController.ui_historyTab
            }
            TabButton {
                _action : masterController.ui_offersTab
            }
            TabButton {
                _action : masterController.ui_settingTab
            }

        }

        Connections{
            target: masterController
            function onTabChanged(index) {
                switch(index){
                case 0:
                    tabContent.currentIndex = 0;
                    break;
                case 1:
                    tabContent.currentIndex = 1;
                    break;
                case 2:
                    tabContent.currentIndex = 2;
                    break;
                case 3:
                    tabContent.currentIndex = 3;
                    break;
                case 4:
                    tabContent.currentIndex = 4;
                    break;
                default:
                    tabContent.currentIndex = 0;
                    break;
                }
            }
        }
    }

    Rectangle {
         id: loading_bg
         width: parent.width
         height: parent.height
         color: "white"
         opacity: 0.7
         visible: masterController.ui_isLoading
    }
    Text {
        id: loading_content
        text: "Loading..."
        font {
            pixelSize:  Dimen.textSizeLv3
            family: Draw.robotoBold
            bold: true
        }
        color: Color.blueDark0
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        width: 100*Dimen.ratioH
        height: 40*Dimen.ratioV
        x: (parent.width-loading_content.width)/2
        y: (parent.height-loading_content.height)/2
        visible: masterController.ui_isLoading
    }
}
