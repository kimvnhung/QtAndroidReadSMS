import QtQuick 2.0
import QtQuick.Controls 2.12
import SRC 1.0
import components 1.0

Item {
    width: 375
    height: 732
    Rectangle{
        anchors.fill: parent
        border.color: "green"
        border.width: 1

        Repeater{
            id : dataTable
            height: 360
            anchors.top: parent.top
            model: masterController.ui_revenueController.ui_transactionList
            delegate: TransactionItem{
                _item : modelData
            }
        }
    }
}
