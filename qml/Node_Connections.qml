import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import MyDesigns
import nodeConection

Popup {
    id: popup

    modal: true
    focus: true
    anchors.centerIn: Overlay.overlay
    closePolicy: Popup.CloseOnPressOutside
    background:Rectangle
    {
        color:"#0f171e"
        radius:8
    }

    Connections {
        target: Node_Conection

        function onConnected() {
             popup.close()
        }
    }
    MyFrame
    {
        id:root_
        anchors.fill:popup
        description: qsTr("Conection settings")
        ColumnLayout
        {
            anchors.fill: parent
            spacing: 20
            MyTextField
            {
                id:node_addr_
                placeholderText:qsTr("Node address")
                Layout.preferredWidth: 400
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.maximumHeight: 75
                Layout.minimumHeight: 45
                Layout.minimumWidth:100
                Layout.preferredHeight: 50


            }
            MyTextField
            {
                id:jwt_
                placeholderText:qsTr("JSON web token (optional)")
                Layout.preferredWidth: 400
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.maximumHeight: 75
                Layout.minimumHeight: 45
                Layout.minimumWidth:100
                Layout.preferredHeight: 50

            }
            MyButton
            {
                text:qsTr("Set")

                Layout.preferredWidth: 100
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.maximumHeight: 75
                Layout.maximumWidth: 150
                Layout.minimumHeight: 45
                Layout.minimumWidth:50
                Layout.preferredHeight: 50
                Layout.alignment: Qt.AlignHCenter
                onClicked:
                {
                    Node_Conection.nodeaddr=node_addr_.text
                    Node_Conection.jwt=jwt_.text
                }
            }
        }
    }
}
