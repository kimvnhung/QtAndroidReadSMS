import QtQuick 2.14
import SRC 1.0
import values 1.0

Item {
    property TabAction _action
    width: Dimen.tabButtonWidth
    height: Dimen.tabButtonHeight
    Rectangle{
        width: parent.width
        height: parent.height
        anchors{
            top: parent.top
            left: parent.left
            bottom: parent.bottom
            right: parent.right
        }

        Image {
            id: icon
            width: Dimen.tabButtonIconWidth
            height: Dimen.tabButtonIconHeight
            x: 29.5*Dimen.ratioH
            y: 10*Dimen.ratioV
            source: _action !== null?_action.ui_icon:""
            fillMode: Image.PreserveAspectFit
        }
        Text {
            id: name
            text: _action !== null?_action.ui_text:""
            anchors{
                top: icon.bottom
                topMargin: 6*Dimen.ratioV
            }
            x: (parent.width - name.width)/2
            font {
                family: Draw.robotoRegular
                pixelSize: Dimen.tabFontSize
            }
            wrapMode: Text.WordWrap
            color: (_action !== null && _action.ui_selected)?Color.tabSelectedTextColor:Color.tabDefaultTextColor
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
