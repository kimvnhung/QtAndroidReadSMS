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
        Text {
            id: name
            text: masterController.ui_account.ui_name+"'s AGENCY"
            font{
                family: Draw.robotoBold
                capitalization: Font.AllUppercase
                pixelSize: Dimen.accountNameFontSize
            }
            color: Color.white
            anchors{
                top: parent.top
                topMargin: 45*Dimen.ratioV
                left: parent.left
                leftMargin: 16*Dimen.ratioH
            }
        }
        Image {
            id: avatar
            width: Dimen.avatarSize
            height: Dimen.avatarSize
            source: "qrc:/images/avatar.png"
            anchors{
                top: parent.top
                topMargin: 24*Dimen.ratioV
                right: parent.right
                rightMargin: 16*Dimen.ratioH
            }
        }
        Text {
            id: incomeTitle
            text: "Today's income"
            color: Color.white
            font{
                family: Draw.robotoRegular
                pixelSize: Dimen.accountNameFontSize
            }
            anchors{
                top: parent.top
                topMargin: 93*Dimen.ratioV
                left: parent.left
                leftMargin: 124*Dimen.ratioH
            }
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
                top: panel.bottom
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
