import QtQuick 2.14
import SRC 1.0
import values 1.0

Item {
    property PropertyAction _action
    width: Dimen.propertyButtonWidth
    height: Dimen.propertyButtonHeight
    Rectangle {
        id : background
        Row {
            id : row
            width: parent.width
            x: 0
            y: (parent.height-row.height)/2
            Text {
                id: title
                visible: _action!=null?_action.ui_isNotitle:false
                text: _action!=null?_action.ui_title:""
                font {
                    family: Draw.robotoRegular
                    pixelSize: Dimen.propertyTextSize
                }
                color: Color.tabSelectedTextColor
            }
            Text {
                id: content
                text: _action!=null?_action.ui_content:""
                font{
                    family: Draw.robotoRegular
                    pixelSize: Dimen.propertyTextSize
                }
                color: _action!=null?(_action.ui_isHightLight?Color.hightLightTextColor:Color.propertyContentTextColor):Color.propertyContentTextColor
            }
        }
        Image {
            id: icon
            source: _action!=null?_action.ui_icon:""
        }
        MouseArea {
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
