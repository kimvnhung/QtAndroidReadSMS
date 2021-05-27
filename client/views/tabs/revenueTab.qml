import QtQuick 2.0
import SRC 1.0
import components 1.0

Item {
    width: 375
    height: 732
//    Repeater{
//        id : dataTable
//        model: masterController.ui_revenueController.ui_transactionList
//        delegate: TransactionItem{
//            _item : modelData
//        }
//    }
    Connections{
        target: masterController.ui_qtAndroidService
        function onMessageFromService(message) {
            if(message === "REFRESH_DATA"){
                masterController.ui_revenueController.updateList()
            }
        }
    }
}
