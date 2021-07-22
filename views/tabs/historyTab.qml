import QtQuick 2.14
import components 1.0
import values 1.0


Item {
    Rectangle{
        width: parent.width
        height: parent.height

        Text {
            id: title
            text: "Transaction history"
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
        //table
        TransactionTable{
            width: parent.width
            height: Dimen.historyTableHeight
            _headerBackground : Color.blueDark0
            _headerTextColor : Color.white
            anchors{
                top: title.bottom
                topMargin: 20*Dimen.ratioV
                left: parent.left
                right: parent.right
            }

            _itemList : masterController.ui_historyController.ui_transactionList
        }
    }

}
