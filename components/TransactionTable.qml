import QtQuick 2.14
import components 1.0
import SRC 1.0
import values 1.0

Item {
    property alias _itemList : dataTable.model
    property color _headerBackground: Color.white
    property color _headerTextColor: Color.blueDark0

    Rectangle {
        anchors{
            fill: parent
        }
        width: parent.width
        height: parent.height
        Rectangle {
            id : header
            height: Dimen.tableHeaderHeight
            width: parent.width
            anchors{
                top: parent.top
                left: parent.left
                right: parent.right
            }
            color: _headerBackground
            Row {
                width: parent.width
                height: parent.height
                Text {
                    text: "PHONE NO."
                    height: parent.height
                    font {
                        family: Draw.robotoRegular
                        pixelSize: Dimen.revenueTableHeaderFontSize
                    }
                    color: _headerTextColor
                    width: Dimen.phoneHeaderWidth
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                Text {
                    text: "TOP-UP CODE"
                    font {
                        family: Draw.robotoRegular
                        pixelSize: Dimen.revenueTableHeaderFontSize
                    }
                    color: _headerTextColor
                    width: Dimen.topCodeHeaderWidth
                    height: parent.height
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                Text {
                    text: "VALUE"
                    font {
                        family: Draw.robotoRegular
                        pixelSize: Dimen.revenueTableHeaderFontSize
                    }
                    color: _headerTextColor
                    width: Dimen.valueHeaderWidth
                    height: parent.height
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                Text {
                    text: "UPDATE"
                    font {
                        family: Draw.robotoRegular
                        pixelSize: Dimen.revenueTableHeaderFontSize
                    }
                    color: _headerTextColor
                    width: Dimen.updateHeaderWidth
                    height: parent.height
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                Text {
                    text: "STT"
                    font {
                        family: Draw.robotoRegular
                        pixelSize: Dimen.revenueTableHeaderFontSize
                    }
                    color: _headerTextColor
                    width: Dimen.sttHeaderWidth
                    height: parent.height
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
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
