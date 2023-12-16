
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Esterv.Styles.Simple
import Esterv.Iota.NodeConnection
import Esterv.CustomControls

ApplicationWindow {
    visible: true
    id:window

    background:Rectangle
    {
        color:Style.backColor1
    }
    ColumnLayout
    {
        anchors.fill: parent

        ThemeSwitch
        {
            id:themeswitch
        }

        NodeConnectionSettings
        {
            Layout.fillHeight: true
            Layout.fillWidth: true
            //defaultnodes:  ListModel {
             //   ListElement { text: "https://3216aae.online-server.cloud/" }
            //}
        }

    }


}
