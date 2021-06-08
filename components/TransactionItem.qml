import QtQuick 2.14
import SRC 1.0
import values 1.0

Item {
    property Transaction _item

    Rectangle{
        anchors{
            fill: parent
            bottomMargin: 5
        }
        width: parent.width
        height: parent.height

        Row{
            width: parent.width
            height: parent.height
            Text{
                id : phoneTxt
                text: _item.ui_phone
                height: parent.height
                width: Dimen.phoneHeaderWidth
                font{
                    family: Draw.robotoRegular
                    pixelSize: Dimen.transactionItemFontSize
                }
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                wrapMode: Text.WordWrap
            }
            Text{
                id : codeTxt
                text: _item.ui_code
                height: parent.height
                width: Dimen.topCodeHeaderWidth
                font{
                    family: Draw.robotoRegular
                    pixelSize: Dimen.transactionItemFontSize
                }
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                wrapMode: Text.WordWrap
            }
            Text{
                id : valueTxt
                text: _item.ui_value
                height: parent.height
                width: Dimen.valueHeaderWidth
                font{
                    family: Draw.robotoRegular
                    pixelSize: Dimen.transactionItemFontSize
                }
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                wrapMode: Text.WordWrap
            }
            Text{
                id : updateTimeTxt
                text: _item.ui_updateTime.length == 0?"---":_item.ui_updateTime
                height: parent.height
                width: Dimen.updateHeaderWidth
                font{
                    family: Draw.robotoRegular
                    pixelSize: Dimen.transactionItemFontSize
                }
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                wrapMode: Text.WordWrap
            }
            Rectangle{
                id : statusBg
                height: parent.height
                width: Dimen.sttHeaderWidth
                Image {
                    id: statusImg
                    width: Dimen.transactionStatusIconSize
                    height: Dimen.transactionStatusIconSize
                    x : (parent.width-statusImg.width)/2
                    y : (parent.height-statusImg.height)/2
                    source: _item.ui_status==0?"qrc:/images/pending_status_ic.svg":(_item.ui_status==1?"qrc:/images/accepted_status_ic.svg":"qrc:/images/reject_status_ic.svg")
                }
            }
        }
        LineSperator{
            anchors{
                bottom: parent.bottom
            }
        }
    }
}
