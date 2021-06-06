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
                text: _item.ui_time
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
            Text{
                id : statusTxt
                text: _item.ui_status?"updated":"not"
                color: _item.ui_status?"green":"red"
                height: parent.height
                width: Dimen.sttHeaderWidth
                font{
                    family: Draw.robotoRegular
                    pixelSize: Dimen.transactionItemFontSize
                }
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                wrapMode: Text.WordWrap
            }
        }
        LineSperator{
            anchors{
                bottom: parent.bottom
            }
        }
    }
}
