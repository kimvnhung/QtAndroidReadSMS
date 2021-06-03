import QtQuick 2.14
import QtQuick.Controls 2.14
import SRC 1.0
import components 1.0

Item {
    Rectangle{
        anchors{
            top: parent.top
            right: parent.right
            left: parent.left
            bottom: parent.bottom
        }

        border.color: "green"
        border.width: 1
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
