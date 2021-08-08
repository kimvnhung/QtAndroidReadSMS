import QtQuick 2.14
import SRC 1.0
import values 1.0

Item {
    property PropertyAction _action
    width: Dimen.propertyButtonWidth
    height: Dimen.propertyButtonHeight
    Rectangle {
        id : background
        width: parent.width
        height: parent.height
//        LineSperator {
//            _color : Color.propertyLineSperatorColor
//            anchors{
//                top: parent.top
//            }
//        }
        Column {
            id : column
            width: parent.width
            x: 16*Dimen.ratioH
            Text {
                id: title
                text: _action!=null?_action.ui_title:""
                font {
                    family: Draw.robotoRegular
                    pixelSize: Dimen.propertyTextSize
                }
                color: Color.tabSelectedTextColor
                height: Dimen.propertyButtonHeight/2
                verticalAlignment: Text.AlignVCenter
            }
            Text {
                id: content
                text: _action!=null?_action.ui_content:""
                height: _action!=null?(_action.ui_isNotitle?Dimen.propertyButtonHeight:(Dimen.propertyButtonHeight/2)):(Dimen.propertyButtonHeight/2)
                font{
                    family: Draw.robotoRegular
                    pixelSize: Dimen.propertyTextSize
                }
                color: _action!=null?(_action.ui_isHightLight?Color.hightLightTextColor:Color.propertyContentTextColor):Color.propertyContentTextColor
                verticalAlignment: Text.AlignVCenter
            }
        }
        Image {
            id: icon
            y: (parent.height-icon.height)/2
            source: _action!=null?_action.ui_icon:""
            anchors{
                right: parent.right
                rightMargin: 17*Dimen.ratioH
            }
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
        LineSperator {
            _color : Color.propertyLineSperatorColor
            anchors{
                bottom: parent.bottom
            }
        }
    }

}
