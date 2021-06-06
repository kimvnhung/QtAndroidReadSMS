import QtQuick 2.14
import components 1.0
import SRC 1.0
import values 1.0

Item {
    property alias _itemList : dataTable.model

    Rectangle {
        anchors{
            fill: parent
        }
        width: parent.width
        height: parent.height
        Row {
            id : header
            height: Dimen.tableHeaderHeight
            width: parent.width
            anchors{
                top: parent.top
                left: parent.left
                right: parent.right
            }

            Text {
                text: "PHONE NO."
                height: parent.height
                font {
                    family: Draw.robotoRegular
                    pixelSize: Dimen.revenueTableHeaderFontSize
                }
                color: Color.revenueHeaderTextColor
                width: Dimen.phoneHeaderWidth
                horizontalAlignment: Text.AlignHCenter
            }
            Text {
                text: "TOP-UP CODE"
                font {
                    family: Draw.robotoRegular
                    pixelSize: Dimen.revenueTableHeaderFontSize
                }
                color: Color.revenueHeaderTextColor
                width: Dimen.topCodeHeaderWidth
                height: parent.height
                horizontalAlignment: Text.AlignHCenter
            }
            Text {
                text: "VALUE"
                font {
                    family: Draw.robotoRegular
                    pixelSize: Dimen.revenueTableHeaderFontSize
                }
                color: Color.revenueHeaderTextColor
                width: Dimen.valueHeaderWidth
                height: parent.height
                horizontalAlignment: Text.AlignHCenter
            }
            Text {
                text: "UPDATE"
                font {
                    family: Draw.robotoRegular
                    pixelSize: Dimen.revenueTableHeaderFontSize
                }
                color: Color.revenueHeaderTextColor
                width: Dimen.updateHeaderWidth
                height: parent.height
                horizontalAlignment: Text.AlignHCenter
            }
            Text {
                text: "STT"
                font {
                    family: Draw.robotoRegular
                    pixelSize: Dimen.revenueTableHeaderFontSize
                }
                color: Color.revenueHeaderTextColor
                width: Dimen.sttHeaderWidth
                height: parent.height
                horizontalAlignment: Text.AlignHCenter
            }

        }
        LineSperator{
            id: sperator
            anchors{
                top: header.bottom

            }
        }

        ListView{
            id : dataTable
            width: parent.width
            clip: true
            flickDeceleration: Flickable.HorizontalAndVerticalFlick
            anchors{
                bottom: parent.bottom
                bottomMargin: 10*Dimen.ratioV
                top: sperator.bottom
                left: parent.left
                right: parent.right
            }
            delegate : TransactionItem{
                width: parent.width
                height: Dimen.transactionItemHeight
                _item : modelData
            }
        }
    }
}
