import QtQuick 2.14
import components 1.0
import values 1.0


Item {
    Rectangle{
        width: parent.width
        height: parent.height

        Text {
            id: title
            text: "About & contact us"
            font{
                family: Draw.robotoBold
                pixelSize: Dimen.settingTitleTextSize
            }
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors{
                top: parent.top
                topMargin: 51*Dimen.ratioV
            }

            x : 16*Dimen.ratioH
            color: Color.propertyContentTextColor
        }

        TitleCategory {
            id : aboutUsTitle
            anchors{
                top: title.bottom
                topMargin: 20*Dimen.ratioV
            }
            height: Dimen.aboutUsTitleAreaHeight
            _text : "About us"
        }

        Column {
            id : aboutUsContent
            width: parent.width
            height: 182*Dimen.ratioV
            x: 16*Dimen.ratioH
            anchors{
                top: aboutUsTitle.bottom
                topMargin: 10*Dimen.ratioV
            }
            spacing: 5*Dimen.ratioV

            Text {
                width: parent.width
                text: ". Service is provided by 100% Vietnamese"
                font{
                    family: Draw.robotoRegular
                    pixelSize: Dimen.propertyTextSize
                }
                color: Color.propertyContentTextColor
                wrapMode: Text.WordWrap
            }

            Text {
                text: ". Our accounts are using Social media, real Like, real view, ..."
                width: parent.width
                font{
                    family: Draw.robotoRegular
                    pixelSize: Dimen.propertyTextSize
                }
                color: Color.propertyContentTextColor
                wrapMode: Text.WordWrap
            }
            Text {
                text: ". Buying in bulk will have the purchase and sale contract in accordance with the law"
                width: parent.width
                font{
                    family: Draw.robotoRegular
                    pixelSize: Dimen.propertyTextSize
                }
                color: Color.propertyContentTextColor
                wrapMode: Text.WordWrap
            }
            Text {
                text: ". We are committed to the best quality and price in the market"
                width: parent.width
                font{
                    family: Draw.robotoRegular
                    pixelSize: Dimen.propertyTextSize
                }
                color: Color.propertyContentTextColor
                wrapMode: Text.WordWrap
            }
        }

        TitleCategory {
            id : contactUsTitle
            anchors{
                top: aboutUsContent.bottom
                topMargin: 30*Dimen.ratioV
            }
            _text : "Contact us"
            height: Dimen.aboutUsTitleAreaHeight
        }

        Row {
            id : contactUsContent
            width: parent.width

            anchors{
                top: contactUsTitle.bottom
                topMargin: 10*Dimen.ratioV
                left: parent.left
                leftMargin: 16*Dimen.ratioH
            }
            spacing: 14*Dimen.ratioH
            Column {
                id: header
                width: 66*Dimen.ratioH
                spacing: 5*Dimen.ratioV
                Text {
                    text: "Email:"
                    font {
                        family: Draw.robotoRegular
                        pixelSize: Dimen.propertyTextSize
                    }
                    color: Color.propertyContentTextColor
                     wrapMode: Text.WordWrap
                     width: parent.width

                }
                Text {
                    text: "Hotline:"
                    font {
                        family: Draw.robotoRegular
                        pixelSize: Dimen.propertyTextSize
                    }
                    color: Color.propertyContentTextColor
                     wrapMode: Text.WordWrap
                     width: parent.width
                }
                Text {
                    text: "Fanpage:"
                    font {
                        family: Draw.robotoRegular
                        pixelSize: Dimen.propertyTextSize
                    }
                    color: Color.propertyContentTextColor
                     wrapMode: Text.WordWrap
                     width: parent.width
                }
            }
            Column {
                id : value
                width: 263*Dimen.ratioH
                spacing: 5*Dimen.ratioV
                Text {
                    text: "support@autolike.cc"
                    font {
                        family: Draw.robotoRegular
                        pixelSize: Dimen.propertyTextSize
                    }
                    color: Color.propertyContentTextColor
                     wrapMode: Text.WordWrap
                     width: parent.width
                }
                Text {
                    text: "039 438 6880"
                    font {
                        family: Draw.robotoRegular
                        pixelSize: Dimen.propertyTextSize
                    }
                    color: Color.propertyContentTextColor
                     wrapMode: Text.WordWrap
                     width: parent.width
                }
                Text {
                    text: "www.facebook.com/autolikecc"
                    font {
                        family: Draw.robotoRegular
                        pixelSize: Dimen.propertyTextSize
                    }
                    color: Color.propertyContentTextColor
                     wrapMode: Text.WordWrap
                     width: parent.width
                }
            }
        }
    }

}
