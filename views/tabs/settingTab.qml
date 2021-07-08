import QtQuick 2.14
import components 1.0
import values 1.0
import SRC 1.0


Item {

    Rectangle{
        width: parent.width
        height: parent.height
        Text {
            id: title
            text: "Setting"
            anchors{
                top: parent.top
                topMargin: 51*Dimen.ratioV
            }

            x : 16*Dimen.ratioH
            font{
                family: Draw.robotoRegular
                pixelSize: Dimen.settingTitleTextSize
            }
            color: Color.propertyContentTextColor
        }
        Rectangle {
            id : languagueTitle
            width: parent.width
            anchors{
                top: title.bottom
                topMargin: 20*Dimen.ratioV
            }

            height: Dimen.settingTitleAreaHeight
            color: Color.revenueHeaderTextColor
            Text {
                id: languagueTitleContent
                x: 16*Dimen.ratioH
                y: (languagueTitle.height-languagueTitleContent.height)/2
                text: "Language & currency"
                font{
                    family: Draw.robotoRegular
                    pixelSize: Dimen.propertyTextSize
                }
                color : Color.white
            }
        }
    }

}
