import QtQuick 2.14
import values 1.0

Item {
    property color _color: Color.lineSperatorColor
    width: parent.width
    height: 1
    Rectangle{
        width: parent.width
        height: parent.height
        color: _color
    }
}
