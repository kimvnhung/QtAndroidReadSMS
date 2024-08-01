import QtQuick 2.14
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import components 1.0
import values 1.0


Item {
    Rectangle{
        width: parent.width
        height: parent.height

        Text {
            id: title
            text: "Revenue Report"
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

        Image {
            id: calendarBt
            source: "qrc:/images/calendar.png"
            width: 22*Dimen.ratioH
            height: 22*Dimen.ratioV
            anchors{
                top: parent.top
                topMargin: 53*Dimen.ratioV
                right: parent.right
                rightMargin: 16*Dimen.ratioH
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    masterController.ui_reportController.showCalendar();
                }
            }
        }
        Rectangle {
            width: 92*Dimen.ratioH
            height: 44*Dimen.ratioV
            border{
                width: 1
                color: Color.propertyLineSperatorColor   
            }
            radius: 5*Dimen.ratioSq
            anchors{
                top: parent.top
                topMargin: 44*Dimen.ratioV
                left: parent.left
                leftMargin: 217*Dimen.ratioH
            }

            Text {
                id : datetxt
                width: 70*Dimen.ratioH
                height: 30*Dimen.ratioV
                anchors{
                    top: parent.top
                    topMargin: (parent.height-datetxt.height)/2
                    left: parent.left
                    leftMargin: (parent.width-datetxt.width)/2
                }

                text: masterController.ui_reportController.ui_selectedDate
                font {
                    family: Draw.robotoRegular
                    pixelSize: Dimen.textSizeLv0
                }
                color: Color.blueDark0
                wrapMode: Text.WordWrap
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
        Rectangle {
            width: 343*Dimen.ratioH
            height: 187*Dimen.ratioV
            anchors{
                top: title.bottom
                topMargin: 30*Dimen.ratioV
                left: parent.left
                leftMargin: Dimen.normalLeftMargin
                right: parent.right
                rightMargin: Dimen.normalLeftMargin
            }
            Image {
                id: background
                source: "qrc:/images/report_background.png"
                anchors.fill: parent
            }
            Text {
                width: 129*Dimen.ratioH
                height: 19*Dimen.ratioV
                anchors{
                    top: parent.top
                    topMargin: 60*Dimen.ratioV
                    left: parent.left
                    leftMargin: 20*Dimen.ratioH
                }

                text: "Total transactions"
                font {
                    family: Draw.robotoRegular
                    pixelSize: Dimen.textSizeLv2
                }
                color: Color.white
            }

            Text {
                width: 96*Dimen.ratioH
                height: 19*Dimen.ratioV
                anchors{
                    top: parent.top
                    topMargin: 60*Dimen.ratioV
                    right : parent.right
                    rightMargin: 47*Dimen.ratioH
                }

                text: "Total revenue"
                font {
                    family: Draw.robotoRegular
                    pixelSize: Dimen.textSizeLv2
                }
                color: Color.white
            }
            Image {
                id: diagonalLine
                source: "qrc:/images/diagonal_line.png"
                width: 36*Dimen.ratioH
                height: 88*Dimen.ratioV
                anchors{
                    top: parent.top
                    left: parent.left
                    topMargin: 50*Dimen.ratioV
                    leftMargin: 154*Dimen.ratioH
                }
            }
            Text {
                id: totalTrans
                text: masterController.ui_reportController.ui_totalTransaction
                font {
                    family: Draw.robotoRegular
                    pixelSize: Dimen.textSizeLv4
                }
                color: Color.white
                anchors{
                    top: parent.top
                    topMargin: 93*Dimen.ratioV
                    left: parent.left
                    leftMargin: 61*Dimen.ratioH
                }
            }
            Text {
                id: totalRevenue
                text: masterController.ui_reportController.ui_totalRevenue
                font {
                    family: Draw.robotoRegular
                    pixelSize: Dimen.textSizeLv4
                }
                color: Color.white
                anchors{
                    top: parent.top
                    topMargin: 93*Dimen.ratioV
                    left: parent.left
                    leftMargin: 186*Dimen.ratioH
                }
            }
        }
        DatePicker{
            id : datePicker
            _scale : 0.7
            visible: masterController.ui_reportController.ui_isCalendarVisible
            anchors{
                top: parent.top
                topMargin: 51*Dimen.ratioV
                right: parent.right
                rightMargin: 16*Dimen.ratioH
            }
            onOk : {
                masterController.ui_reportController.dateAccepted(datePicker.date)
            }

            onCancel: {
                masterController.ui_reportController.dateCancel()
            }
        }
    }
}
