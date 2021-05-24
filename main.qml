import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12

import QtQuick.Controls 2.12

Window {
    property int counter: 0
    // @disable-check M16
    width: 640
    // @disable-check M16
    height: 480
    // @disable-check M16
    visible: true

    Column{
        width: parent.width
        height: parent.heigt
        spacing: 10
        Label{
            text: "Current counter = "+counter
            font.pixelSize: 20

        }
        Button{
            text: "Send count"
            onClicked: {
                qtAndroidService.sendToService(counter)
            }
        }
    }

    Connections {
        target: qtAndroidService
        function onMessageFromService(message) {
            console.log("onMessageFromService - "+message);
            counter = message*1+1;
        }
    }

}
