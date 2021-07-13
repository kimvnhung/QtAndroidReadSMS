import QtQuick 2.14
import QtQuick.Controls 2.14
import components 1.0
import values 1.0
import SRC 1.0


Item {

    StackView {
        id: contentFrame
        anchors {
            fill: parent
        }
        initialItem: main
        clip: true
    }

    Component{
        id: main
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
                id : languageTitle
                width: parent.width
                anchors{
                    top: title.bottom
                    topMargin: 20*Dimen.ratioV
                }

                height: Dimen.settingTitleAreaHeight
                color: Color.revenueHeaderTextColor
                Text {
                    id: languageTitleContent
                    x: 16*Dimen.ratioH
                    y: (languageTitle.height-languageTitleContent.height)/2
                    text: "Language & currency"
                    font{
                        family: Draw.robotoRegular
                        pixelSize: Dimen.propertyTextSize
                    }
                    color : Color.white
                }
            }
            PropertyButton {
                id: languageProperty
                anchors{
                    top: languageTitle.bottom
                }

                _action : masterController.ui_settingController.ui_languageProperty
            }
            PropertyButton {
                id : currencyProperty
                anchors{
                    top: languageProperty.bottom
                }

                _action : masterController.ui_settingController.ui_currencyProperty
            }
            Rectangle {
                id : informationTitle
                width: parent.width
                anchors{
                    top: currencyProperty.bottom
                }

                height: Dimen.settingTitleAreaHeight
                color: Color.revenueHeaderTextColor
                Text {
                    id: informationTitleContent
                    x: 16*Dimen.ratioH
                    y: (informationTitle.height-informationTitleContent.height)/2
                    text: "Information"
                    font{
                        family: Draw.robotoRegular
                        pixelSize: Dimen.propertyTextSize
                    }
                    color : Color.white
                }
            }
            PropertyButton {
                id: aboutUsProperty
                anchors{
                    top: informationTitle.bottom
                }

                _action : masterController.ui_settingController.ui_aboutUsProperty
            }
            PropertyButton {
                id: logOutProperty
                anchors{
                    top: aboutUsProperty.bottom
                }

                _action : masterController.ui_settingController.ui_logOutProperty
            }

        }
    }
    Connections {
        target: masterController.ui_settingController
        function onLanguagePropertyClicked(){

        }
        function onAboutUsPropertyClicked(){
            contentFrame.push("qrc:/views/tabs/aboutTab.qml")
        }
    }
    Connections {
        target: masterController
        function onTabChanged(index){
            if(contentFrame.currentItem != main && index !== 4){
                contentFrame.pop()
            }
        }
    }
}
