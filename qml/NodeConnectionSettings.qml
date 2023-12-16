import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Esterv.Iota.NodeConnection
import Esterv.Styles.Simple


Item
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

        Rectangle
        {
            color:Style.backColor3
            implicitHeight: con.implicitHeight+20
            implicitWidth: con.implicitWidth+20
            radius:Math.min(width,height)*0.5
            Layout.alignment: Qt.AlignRight
            Label
            {
                id:con
                anchors.centerIn:  parent
                text:(NodeConnection.state)?qsTr("Connected"):qsTr("Waiting for node")
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
                text: qsTr("Node URL:")
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
                text: qsTr("JSON web token:")
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




