import QtQuick 2.14
import SRC 1.0
import values 1.0

Item {
    property string _text: ""
    width: Dimen.windowWidth
    height: Dimen.settingTitleAreaHeight
    Rectangle {
        id : background
        width: parent.width
        height: parent.height
        color: Color.revenueHeaderTextColor
        Text {
            id: content
            x: 16*Dimen.ratioH
            y: (background.height-content.height)/2
            text: _text
            font{
                family: Draw.robotoRegular
                pixelSize: Dimen.propertyTextSize
            }
            color : Color.white
        }
    }
}
