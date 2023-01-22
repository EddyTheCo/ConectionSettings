import QtQuick.Controls
import QtQuick
import nodeConection

ApplicationWindow {
    visible: true
    width:700
    height:700

    background: Rectangle {
            color:"#1e1e1e"
        }



    Node_Connections{

        anchors.centerIn: parent
        visible:true
    }
}
