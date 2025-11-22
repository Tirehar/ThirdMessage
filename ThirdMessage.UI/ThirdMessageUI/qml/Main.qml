import QtQuick
import QtQuick.Controls
import QtQuick.Shapes
import ThirdMessageUI.WebSocket


Window {
    width: 1080
    height: 680
    minimumHeight:640
    minimumWidth:960
    visible: true
    color: "Gray"
    title: qsTr("Third Message")

    TextField{
        id: messageText
        width:750
        height:180
        font.pixelSize:20
        wrapMode:TextInput.WrapAnywhere
        placeholderText:"输入消息..."
        leftPadding:15
        rightPadding:15
        topPadding:10
        bottomPadding:10
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        background:Rectangle{
            border.width: 1
            border.color: "Gray"
            color:"White"
        }

        SendButton{
            anchors.right: parent.right
            anchors.bottom : parent.bottom
            anchors.rightMargin: 20
            anchors.bottomMargin: 15
            onClicked: {
                WebSocketService.sendMessage(messageText.text);
                messageText.text = ""
            }
        }
    }

    Connections{
        target: WebSocketService
        onResponse:{
            console.log("服务器发出回应" + response)
        }
    }
}
