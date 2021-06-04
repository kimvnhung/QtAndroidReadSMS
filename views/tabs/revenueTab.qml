import QtQuick 2.14
import QtQuick.Controls 2.14
import SRC 1.0
import components 1.0
import values 1.0

Item {
    Rectangle{
        anchors{
            top: parent.top
            right: parent.right
            left: parent.left
            bottom: parent.bottom
        }
        Image {
            id: panel
            width: parent.width
            height: Dimen.revenuePanelHeight
            anchors{
                top: parent.top
            }
            source: "qrc:/images/revenue_panel.png"
        }
        Text {
            id: helloTxt
            anchors{
                top: parent.top
                left: parent.left
                topMargin: 24*Dimen.ratioV
                leftMargin: 16*Dimen.ratioH
            }

            text: "HELLO!"
            font{
                family: Draw.robotoRegular
                pixelSize: Dimen.helloFontSize
            }
            color: Color.white
        }
        ListView{
            id : dataTable
            width: parent.width
            clip: true
            flickDeceleration: Flickable.HorizontalAndVerticalFlick
            anchors{
                bottomMargin: 10
                bottom: parent.bottom
                topMargin: 10
                top: parent.top
                left: parent.left
                leftMargin: 5
                right: parent.right
                rightMargin: 5
            }

            model: masterController.ui_revenueController.ui_transactionList
            delegate : TransactionItem{
                width: 300
                height: 60
                _item : modelData
            }
        }
    }
}
