import QtQuick 2.14
import components 1.0
import values 1.0


Item {
    Rectangle{
        width: parent.width
        height: parent.height

        Text {
            id: name
            text: "Reports Tab"
            font{
                family: Draw.robotoBold
                pixelSize: 16*Dimen.ratioSq
            }
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.fill: parent
        }
    }

}
