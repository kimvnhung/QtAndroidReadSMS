import QtQuick 2.14
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import components 1.0
import values 1.0


Item {
    Rectangle{
        width: parent.width
        height: parent.height

        Text {
            id: title
            text: "Revenue Report"
            font{
                family: Draw.robotoBold
                pixelSize: Dimen.settingTitleTextSize
            }
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors{
                top: parent.top
                topMargin: 51*Dimen.ratioV
            }

            x : 16*Dimen.ratioH
            color: Color.propertyContentTextColor
        }

        Image {
            id: calendarBt
            source: "qrc:/images/gift_icon.png"
            width: 30*Dimen.ratioH
            height: 30*Dimen.ratioV

        }
    }
}
