import QtQuick

Rectangle{
    id: root
    width: 120
    height: 30
    border.width: 0
    color:normal_color
    border.color: normal_color
    radius: 4

    property color normal_color: "#B6B6B6"
    property color entered_background_color: "#CBCBCB"
    property color entered_border_color: "#CBCBCB"
    property color pressed_background_color: "#A9A9A9"
    property color pressed_border_color: "#CBCBCB"
    property string text: "发送"

    signal clicked()

    states: [
        State {
            name: "normal"
            PropertyChanges {
                target: root
                color: normal_color
                border.width: 0
            }
        },
        State {
            name: "entered"
            PropertyChanges {
                target: root
                color: entered_background_color
                border.color: entered_border_color
                border.width: 1
            }
        },
        State {
            name: "pressed"
            PropertyChanges {
                target: root
                color: pressed_background_color
                border.color: pressed_border_color
                border.width: 1
            }
        }
    ]

    transitions: [
        Transition {
            PropertyAnimation {
                properties: "color,border.color"
                duration: 100
            }
        }
    ]

    MouseArea{
        id: area
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            root.state = "entered"
        }
        onPressed: {
            root.state = "pressed"
        }
        onReleased: {
            root.state = "normal"
        }
        onExited: {
            if(!area.pressed)
                root.state = "normal"
        }
        onCanceled: {
            root.state = "normal"
        }
        onClicked: {
            parent.clicked()
        }
    }

    Text {
        text: parent.text
        anchors.centerIn: parent
        font.bold: true
        font.pixelSize: 15
        color: "#414141"
    }
}
