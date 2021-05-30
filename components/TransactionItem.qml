import QtQuick 2.14
import SRC 1.0

Item {
    property Transaction _item

    Rectangle{
        border.color: "blue"
        border.width: 1
        anchors{
            fill: parent
            bottomMargin: 5
        }

        Column{
            Row{
                height: 30
                spacing: 5
                Text{
                    id : phoneTxt
                    text: _item.ui_phone
                    font.pixelSize: 15
                    wrapMode: Text.WordWrap
                }
                Text{
                    id : codeTxt
                    text: _item.ui_code
                    font.pixelSize: 15
                    wrapMode: Text.WordWrap
                }
                Text{
                    id : valueTxt
                    text: _item.ui_value
                    font.pixelSize: 15
                    wrapMode: Text.WordWrap
                }
            }
            Row{
                height: 30
                spacing: 5
                Text{
                    id : timeTxt
                    text: _item.ui_time
                    font.pixelSize: 15
                    wrapMode: Text.WordWrap
                }
                Text{
                    id : statusTxt
                    text: _item.ui_status?"updated":"not"
                    color: _item.ui_status?"green":"red"
                    font.pixelSize: 15
                    wrapMode: Text.WordWrap
                }
            }
        }

    }
}
