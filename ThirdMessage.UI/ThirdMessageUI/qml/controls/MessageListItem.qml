import QtQuick
import QtQuick.Controls

Item {
    id: root
    width: Math.min(maxWidth, messageText.implicitWidth)
    height: messageText.implicitHeight
    anchors.right: isMy && parent ? parent.right : undefined
    anchors.left: !isMy && parent ? parent.left : undefined
    anchors.margins: 10

    property color myMessageColor: "#c6e7f8"
    property color otherMessageColor: "#efefef"
    property real maxWidth: 320

    Rectangle{
        anchors.fill: parent
        color: isMy ? myMessageColor : otherMessageColor
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