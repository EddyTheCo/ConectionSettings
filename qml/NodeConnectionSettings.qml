import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Esterv.Iota.NodeConnection
import Esterv.Styles.Simple


Frame
{
    id:control
    Component.onCompleted: NodeConnection.setNodeAddr(node_addr.currentText);
    property ListModel defaultnodes: ListModel {
        ListElement { text: "https://3216aae.online-server.cloud/" }
        ListElement { text: "https://multiverse.dlt.builders/" }
        ListElement { text: "https://lithuania.dlt.green/" }
    }

    ColumnLayout
    {
        anchors.fill: parent
        RowLayout
        {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 5
            Label
            {
                text:qsTr("Connection settings")
                elide:Text.ElideRight
                horizontalAlignment: TextEdit.AlignLeft
                verticalAlignment: TextEdit.AlignVCenter
                Layout.fillWidth: true
            }
            Rectangle
            {
                color:(NodeConnection.state)?"green":"red"
                implicitHeight: 16
                implicitWidth: 16
                radius: 16
                Layout.alignment: Qt.AlignRight
                ToolTip.text: (NodeConnection.state)?qsTr("Connected"):qsTr("Waiting for node")
                ToolTip.visible: hovered
            }
        }
        GridLayout
        {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignTop
            columns : 2
            flow:(width<350)?GridLayout.TopToBottom:GridLayout.LeftToRight
            Label
            {
                text: qsTr("URL:")
                Layout.fillWidth: true
            }
            ComboBox {

                id:node_addr
                editable: true
                model: control.defaultnodes

                onAccepted: {
                    if (find(editText) === -1)
                        control.defaultnodes.append({text: editText})
                }
                onActivated: {
                    NodeConnection.setNodeAddr(node_addr.currentText);
                }
                Layout.fillWidth: true
                Layout.minimumWidth: 100
            }
            Label
            {
                text: qsTr("JWT(optional):")
                Layout.fillWidth: true
            }
            TextField
            {
                id:jwt
                onEditingFinished:
                {
                    NodeConnection.setJWT(jwt.text);
                }
                Layout.fillWidth: true
                Layout.minimumWidth: 100
            }
        }
    }


}

