import QtQuick 2.14
import QtQuick.Layouts 1.14
import QtQuick.Window 2.14

import QtQuick.Controls 2.14

Window {
    // @disable-check M16
    width: 375
    // @disable-check M16
    height: 812
    // @disable-check M16
    visible: true

    Rectangle{
        anchors.fill: parent
        border.color: "red"
        border.width: 1
        StackView{
            id: tabContent
            anchors.top: parent.top
            width: parent.width
            height: 732
            initialItem: "qrc:/views/tabs/revenueTab.qml"
            clip: true
        }
        Label{
            anchors{
                top: tabContent.bottom
                left: parent.left
                right: parent.right
                bottom: parent.bottom
            }
            text: "Tab Control Bar"
            font.pixelSize: 20
            color: "blue"
        }
    }



}
