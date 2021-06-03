import QtQuick 2.14
import SRC 1.0
import values 1.0

Item {
    property TabAction _action
    width: Dimen.tabButtonSize
    height: Dimen.tabButtonSize
    Rectangle{
        anchors{
            fill: parent
        }
        Image {
            id: icon
            width: Dimen.tabButtonIconSize
            height: Dimen.tabButtonIconSize
            anchors{
                centerIn: parent
            }
            source: _action !== null?_action.ui_icon:""
            fillMode: Image.PreserveAspectFit
        }
        Text {
            id: name
            text: _action !== null?_action.ui_text:""
            font {
                family: Draw.robotoRegular
                pixelSize: Dimen.tabFontSize
            }
        }
        MouseArea{
            anchors{
                fill: parent
            }
            onClicked: {
                if(_action !== null){
                    _action.click()
                }
            }
        }
    }
}
