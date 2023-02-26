import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import MyDesigns
import nodeConection


MyFrame
{
    id:root_

    description: qsTr("Conection settings")
    ColumnLayout
    {
        anchors.fill: parent
        spacing: 5
        MyTextField
        {
            id:node_addr_
            placeholderText:qsTr("Node address")
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignHCenter
            Layout.minimumWidth: 150
            focus: true
            tfield.onTextEdited: butt_.enabled=true;

        }
        MyTextField
        {
            id:jwt_
            placeholderText:qsTr("JSON web token (mandatory)")
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: 150
            Layout.alignment: Qt.AlignHCenter
        }
        MyButton
        {
            id:butt_
            text:qsTr("Set")
            enabled: false
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.maximumHeight: 50
            Layout.maximumWidth: 75
            Layout.minimumHeight: 25
            Layout.minimumWidth:50
            Layout.preferredHeight: 40
            Layout.alignment: Qt.AlignHCenter
            onClicked:
            {
                Node_Conection.nodeaddr=node_addr_.tfield.text
                Node_Conection.jwt=jwt_.tfield.text
            }
        }
    }

}
