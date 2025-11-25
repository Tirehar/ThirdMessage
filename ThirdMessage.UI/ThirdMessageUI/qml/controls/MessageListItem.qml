import QtQuick
import QtQuick.Controls

Item {
    id: root
    width: Math.min(maxWidth, messageText.implicitWidth)
    height: Math.min(maxHeight, messageText.implicitHeight)
    anchors.right: isMyMessage ? parent.right : undefined
    anchors.left: !isMyMessage ? parent.left : undefined
    anchors.margins: 10

    property color myMessageColor: "#c6e7f8"
    property color otherMessageColor: "#c3c2c2"
    property real maxWidth: 260
    property real maxHeight: 200

    Rectangle{
        anchors.fill: parent
        color: isMyMessage ? myMessageColor : otherMessageColor
        radius: 6
        Text{
            id: messageText
            anchors.fill: parent
            text: content
            font.pixelSize:16
            wrapMode: Text.WrapAnywhere
            padding: 10
        }
    }
}