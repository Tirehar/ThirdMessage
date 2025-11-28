import QtQuick
import QtQuick.Controls.FluentWinUI3

Item{
    id: root

    property var listModel
    signal actived(string text)
    signal textChanged(string text)
    signal selected(string userName)

    TextField{
        id: edit
        font.pixelSize: 14
        padding: 8
        anchors.fill:parent
        placeholderText: "搜索好友.."
        Keys.onReturnPressed:{
            actived(edit.text);
        }
        onTextChanged:{
            root.textChanged(edit.text)
            popup.open()
        }
    }
    Popup{
        id: popup
        x: edit.mapToItem(root, 0, edit.height).x
        y: edit.mapToItem(root, 0, edit.height).y + 5
        implicitWidth: parent.width - 10
        implicitHeight: Math.min(list.contentHeight, 600)
        padding:0
        margins:5
        modal: false
        clip:true
        background:Rectangle {
            width: parent.implicitWidth
            height: parent.implicitHeight
            color: "#e4e4e4"
            border.color: "#d5d5d5"
            border.width: 1
            radius:8
        }

        contentItem: Rectangle {
            anchors.fill: parent
            anchors.margins: 1
            radius: 8
            color: "transparent"
            clip: true

            ListView {
                id: list
                anchors.fill: parent
                anchors.margins: 1
                model: listModel
                clip: true

                delegate: Rectangle {
                    height: 32
                    color: "transparent"
                    width: popup.implicitWidth
                    clip:true
                    Text {
                        font.pixelSize: 16
                        text: display
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 8
                    }
                    MouseArea{
                        anchors.fill: parent
                        hoverEnabled: true
                        preventStealing: true
                        onClicked: {
                            root.selected(display)
                            popup.close()
                        }
                    }
                }
            }
        }
    }
}