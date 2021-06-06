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
        Text {
            id: incomeValue
            text: masterController.ui_revenueController.ui_todayIncome
            anchors{
                top: incomeTitle.bottom
                topMargin: 8*Dimen.ratioV
                left: parent.left
                leftMargin: (parent.width-incomeValue.width)/2
            }
            wrapMode: Text.WordWrap
            font{
                family: Draw.robotoBold
                pixelSize: Dimen.incomeValueFontSize
            }
            color: Color.white
        }
        //table
        TransactionTable{
            width: parent.width
            height: Dimen.revenueTableHeight
            anchors{
                top: panel.bottom
                topMargin: 5*Dimen.ratioV
                left: parent.left
                right: parent.right
            }

            _itemList : masterController.ui_revenueController.ui_transactionList
        }
    }
}
