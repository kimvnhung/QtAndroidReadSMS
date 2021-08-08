import QtQuick 2.14
import SRC 1.0
import values 1.0

Item {
    property real _percent: 0
    property string _applicableDate: "30/05/2021"
    property string _expireDate: "01/06/2021"
    width: parent.width
    height: Dimen.percentCategoryHeight
    Rectangle {
        width: parent.width
        height: Dimen.percentCategoryHeight

        Row {
            width: parent.width - Dimen.normalLeftMargin*2
            height: parent.height
            spacing: 11*Dimen.ratioH
            anchors{
                left: parent.left
                leftMargin: Dimen.normalLeftMargin
            }
            Rectangle {
                width: 110*Dimen.ratioH
                height: parent.height
                border.color: Color.buyMoreTextColor
                border.width: 1
                radius: 5
                Text {
                    id: promoteNote
                    text: "PROMOCODE"
                    font {
                        family: Draw.robotoRegular
                        pixelSize: Dimen.offerPanelTextSize
                    }
                    color: Color.buyMoreTextColor
                    anchors{
                        top: parent.top
                        left: parent.left
                        topMargin: 54*Dimen.ratioV
                        leftMargin: 12*Dimen.ratioH
                    }
                }
                Text {
                    id: percentContent
                    text: "-"+_percent+"%"
                    font {
                        family: Draw.robotoRegular
                        pixelSize: 32*Dimen.ratioSq
                    }
                    color: Color.saveUptoTextColor
                    anchors{
                        top: parent.top
                        left: parent.left
                        topMargin: 10*Dimen.ratioV
                        leftMargin: 20*Dimen.ratioH
                    }
                }
            }
            Column {
                id : time
                spacing: 5*Dimen.ratioV
                width: 204*Dimen.ratioH
                height: 52*Dimen.ratioV
                y : (parent.height-time.height)/2
                Row {
                    spacing: 2*Dimen.ratioH
                    Text {
                        id: applicableTitle
                        text: "Applicable plan:"
                        font {
                            family: Draw.robotoBold
                            pixelSize: Dimen.textSizeLv2
                            bold: true
                        }
                        color: Color.saveUptoTextColor

                    }
                    Text {
                        id: applicableValue
                        text: _applicableDate
                        font {
                            family: Draw.robotoRegular
                            pixelSize: Dimen.textSizeLv2
                        }
                        color: Color.saveUptoTextColor

                    }
                }
                Row {
                    spacing: 2*Dimen.ratioH
                    Text {
                        id: expireTitle
                        text: "Expire plan:"
                        font {
                            family: Draw.robotoBold
                            pixelSize: Dimen.textSizeLv2
                            bold: true
                        }
                        color: Color.saveUptoTextColor

                    }
                    Text {
                        id: expireValue
                        text: _expireDate
                        font {
                            family: Draw.robotoRegular
                            pixelSize: Dimen.textSizeLv2
                        }
                        color: Color.saveUptoTextColor

                    }
                }
            }
        }
    }
}
