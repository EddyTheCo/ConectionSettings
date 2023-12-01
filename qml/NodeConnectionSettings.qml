import QtQuick
import QtQuick.Layouts
import MyDesigns
import nodeConnection


MyFrame
{
    id:root
    description: qsTr("Conection settings")

    ColumnLayout
    {
        visible: (root.collapsed>0.7)
        anchors.fill: parent

        spacing: 5
        MyTextField
        {
            id:node_addr_
            label.text: qsTr("Node address")
            textfield.placeholderText:qsTr("https://")
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredHeight: 75
            textfield.onEditingFinished:
            {
                NodeConnection.setNodeAddr(node_addr_.textfield.text);
            }

        }
        MyTextField
        {
            id:jwt_
            label.text: "JSON web token"
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredHeight: 75
            textfield.onEditingFinished:
            {
                NodeConnection.setJWT(jwt_.textfield.text);
            }


        }
    }

}
