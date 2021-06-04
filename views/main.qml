import QtQuick 2.14
import QtQuick.Layouts 1.14
import QtQuick.Window 2.14

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
        StackView{
            id: tabContent
            anchors{
                top: parent.top
            }

            width: parent.width
            height: Dimen.tabContentHeight
            initialItem: "qrc:/views/tabs/revenueTab.qml"
            clip: true
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
    }


}
