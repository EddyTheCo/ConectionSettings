import QtQuick
import QtQuick.Layouts
import MyDesigns
import nodeConection


MyFrame
{
    id:root_

    description: qsTr("Conection settings")
    ColumnLayout
    {
        anchors.fill: parent
        spacing: 10
        MyTextField
        {
            id:node_addr_
            placeholderText:qsTr("Node address")
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignHCenter
            Layout.maximumWidth: 300
            Layout.maximumHeight: 50
            Layout.minimumHeight: 35
            focus: true
            tfield.onTextEdited: butt_.enabled=true;
        }
        MyTextField
        {
            id:jwt_
            placeholderText:qsTr("JSON web token (mandatory)")
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignHCenter
            Layout.maximumWidth: 300
            Layout.maximumHeight: 50
            Layout.minimumHeight: 35
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
            Layout.preferredWidth: 50
            Layout.minimumHeight: 25
            Layout.minimumWidth:50
            Layout.alignment: Qt.AlignHCenter
            onClicked:
            {
                Node_Conection.nodeaddr=node_addr_.tfield.text
                Node_Conection.jwt=jwt_.tfield.text
            }
        }
    }

}
