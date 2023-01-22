import QtQuick.Controls
import QtQuick

ApplicationWindow {
    visible: true
    width:700
    height:700

    background: Rectangle {
            color:"#1e1e1e"
        }

    Node_Connections{
        width:parent.width*0.8
        height:parent.height*0.8
        anchors.centerIn: parent
        onClosed: {visible=false}
    }
}
