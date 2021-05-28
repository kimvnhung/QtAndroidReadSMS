import QtQuick 2.0
import QtQuick.Controls 2.12
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
    Button{
        id :btn
        text: "Send"
        onClicked: masterController.ui_qtAndroidService.sendToService("abcXYZ")
    }

//    Connections{
//        target: masterController.ui_qtAndroidService
//        function onMessageFromService(message) {
//            if(message === "UPDATE_DATA"){
//                masterController.ui_revenueController.updateList()
//            }
//        }
//    }
}
