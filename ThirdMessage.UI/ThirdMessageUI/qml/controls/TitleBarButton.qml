import QtQuick
import QtQuick.Controls

Rectangle {
    id: root
    width: parent.height
    height: parent.height
    states: [
        State{
            name: "normal"
            PropertyChanges{
                target: root
                color: normalColor
            }
        },
        State{
            name: "hovered"
            PropertyChanges {
                target: root
                color: hoverColor
            }
        },
        State{
            name: "pressed"
            PropertyChanges {
                target: root
                color: pressedColor
            }
        }
    ]


    property string icon
    property color normalColor: "#ffffff"
    property color hoverColor: "#d0d0d0"
    property color pressedColor: "#b0b0b0"
    signal clicked()

    Image{
        anchors.fill:parent
        anchors.margins:10
        layer.enabled: true
        layer.smooth: true
        sourceSize: Qt.size(64, 64)
        source:icon
    }

    MouseArea{
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            root.state = "hovered"
        }
        onPressed: {
            root.state = "pressed"
        }
        onExited: {
            root.state = "normal"
        }
        onReleased: {
            root.state = containsMouse ? "hovered" : "normal"
        }
        onCanceled: {
            root.state = "normal"
        }
        onClicked:{
            root.clicked()
        }
    }
}