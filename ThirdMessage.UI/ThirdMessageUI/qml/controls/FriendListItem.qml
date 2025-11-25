import QtQuick

Rectangle {
    id: root
    height: 45
    width: parent.width

    property color normal_color: "White"
    property color entered_color: "#E6E6E6"
    property color pressed_color: "#b8b8b8"
    property color selected_color: "#cdcdcd"
    property bool isSelected

    signal clicked()

    Text{
        anchors.fill: parent
        font.pixelSize:18
        verticalAlignment: Text.AlignVCenter
        leftPadding:15
        text: userName
    }
    states: [
        State{
            name: "normal"
            PropertyChanges{
                target: root
                color: normal_color
            }
        },
        State{
            name: "entered"
            PropertyChanges{
                target: root
                color: entered_color
            }
        },
        State{
            name: "pressed"
            PropertyChanges{
                target: root
                color: pressed_color
            }
        },
        State{
            name: "selected"
            PropertyChanges{
                target: root
                color: selected_color
            }
        }
    ]

    MouseArea{
        id: area
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            if(!root.isSelected)
                root.state = "entered"
        }
        onPressed: {
            if(!root.isSelected)
                root.state = "pressed"
        }
        onExited: {
            if(!area.pressed && !root.isSelected)
                root.state = "normal"
        }
        onClicked: {
            root.clicked()
        }
    }

    function setSelected(selected){
        root.isSelected = selected
        if(isSelected){
            root.state = "selected"
        } else {
            root.state = "normal"
        }
    }
}
