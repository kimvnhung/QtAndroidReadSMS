import QtQuick 2.14
import components 1.0
import values 1.0


Item {
    Rectangle{
        width: parent.width
        height: parent.height

        Text {
            id: title
            text: "Specical offers"
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

        Rectangle {
            id: offerPanel
            color: Color.offerPanelBackgroundColor
            width: parent.width
            height: Dimen.offerPanelHeight
            anchors{
                top: title.bottom
                topMargin: 20*Dimen.ratioV
            }
            Image {
                id: gifIcon
                anchors{
                    top: parent.top
                    topMargin: 23*Dimen.ratioV
                    left: parent.left
                    leftMargin: 45*Dimen.ratioH
                }
                source: "qrc:/images/gift_icon.png"
                width: 100*Dimen.ratioH
                height: 97*Dimen.ratioV

            }

            Text {
                text: "BUY MORE PAY LESS"
                color: Color.buyMoreTextColor
                font {
                    family: Draw.robotoRegular
                    pixelSize: Dimen.offerPanelTextSize
                }
                anchors{
                    top: parent.top
                    left: parent.left
                    topMargin: 26*Dimen.ratioV
                    leftMargin: 191*Dimen.ratioH
                }
            }
            Text {
                text: "SAVE UP TO"
                width: 43*Dimen.ratioH
                height: 42*Dimen.ratioV
                color: Color.saveUptoTextColor
                wrapMode: Text.WordWrap
                anchors{
                    top: parent.top
                    left: parent.left
                    topMargin: 47*Dimen.ratioV
                    leftMargin: 191*Dimen.ratioH
                }
                font {
                    family: Draw.robotoRegular
                    pixelSize: Dimen.offerPanelTextSize2
                    bold: true
                }
            }
            Text {
                id: percent
                text: "50%"
                color: Color.saveUptoTextColor
                anchors{
                    top: parent.top
                    left: parent.left
                    topMargin: 42*Dimen.ratioV
                    leftMargin: 239*Dimen.ratioH
                }
                font {
                    family: Draw.robotoRegular
                    pixelSize: Dimen.offerPanelPercentTextSize
                }
            }
        }

        Column {
            width: parent.width
            spacing: 20*Dimen.ratioV
            anchors{
                top: offerPanel.bottom
                topMargin: 30*Dimen.ratioV
            }
            PromoteComponent {
                _percent : 50
            }
            PromoteComponent {
                _percent : 20
            }
            PromoteComponent {
                _percent : 10
            }
        }
    }

}
