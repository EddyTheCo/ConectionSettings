import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import MyDesigns
import nodeConection


MyFrame
{
    id:root_
    signal connected()

    Connections {
        target: Node_Conection

        function onConnected() {
             root_.connected()
        }
    }
    description: qsTr("Conection settings")
    ColumnLayout
    {
        anchors.fill: parent
        spacing: 20
        MyTextField
        {
            id:node_addr_
            placeholderText:qsTr("Node address")
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.maximumHeight: 75
            Layout.minimumHeight: 45
            Layout.preferredHeight: 50
            Layout.minimumWidth: 20
            Layout.maximumWidth: 200
            focus: true
            tfield.onTextEdited: butt_.enabled=true;
            Layout.alignment: Qt.AlignLeft
        }
        MyTextField
        {
            id:jwt_
            placeholderText:qsTr("JSON web token (mandatory)")
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.maximumHeight: 75
            Layout.minimumHeight: 45
            Layout.minimumWidth:100
            Layout.preferredHeight: 50
            Layout.maximumWidth: 200
            Layout.alignment: Qt.AlignLeft
        }
        MyButton
        {
            id:butt_
            text:qsTr("Set")
            enabled: false
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
                Node_Conection.nodeaddr=node_addr_.tfield.text
                Node_Conection.jwt=jwt_.tfield.text
            }
        }
    }

}
