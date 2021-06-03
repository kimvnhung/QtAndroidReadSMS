pragma Singleton
import QtQuick 2.9

Item {
    property alias fontAwesome: fontAwesomeLoader.name
    property alias robotoBold: robotoBoldLoader.name
    property alias robotoBoldItalic: robotoBoldItalicLoader.name
    property alias robotoItalic: robotoItalicLoader.name
    property alias robotoRegular: robotoRegularLoader.name

    readonly property string revenue_tab: ":/images/revenue_tab_ic.png"
    readonly property string revenue_untab : ":/images/revenue_untab_ic.png"

    FontLoader {
        id: fontAwesomeLoader
        source: "qrc:/values/fontawesome.ttf"
    }

    FontLoader {
        id: robotoBoldLoader
        source: "qrc:/values/Roboto-Bold.ttf"
    }

    FontLoader {
        id: robotoBoldItalicLoader
        source: "qrc:/values/Roboto-BoldItalic.ttf"
    }

    FontLoader {
        id: robotoItalicLoader
        source: "qrc:/values/Roboto-Italic.ttf"
    }

    FontLoader {
        id: robotoRegularLoader
        source: "qrc:/values/Roboto-Regular.ttf"
    }
}
