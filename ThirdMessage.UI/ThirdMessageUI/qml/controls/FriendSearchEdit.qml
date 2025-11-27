import QtQuick
import QtQuick.Controls.FluentWinUI3

Item{
    id: root

    property var candidates:[]
    signal actived(string text);

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
            popup.open()
        }
    }
    Popup{
        id: popup
        x: edit.mapToItem(root, 0, edit.height).x
        y: edit.mapToItem(root, 0, edit.height).y + 5
        implicitWidth: parent.width - 10
        implicitHeight: 200 - 10
        padding:0
        margins:5
        modal: false
        background:Rectangle {
            width: parent.implicitWidth
            height: parent.implicitHeight
            color: "#e4e4e4"
            border.color: "#d5d5d5"
            border.width: 1
            radius:8
            clip:true

        }
        contentItem: ListView {
             anchors.fill: parent
            // model: filteredModel
        }
    }
}