import QtQuick
import QtQuick.Controls.Windows
import QtQuick.Shapes
import ThirdMessageUI.WebSocket
import QtQuick.Layouts
import "./controls"

Window {
    width: 1080
    height: 680
    minimumHeight:480
    minimumWidth:840
    visible: true
    color: "#E9E9E9"
    title: qsTr("Third Message")

    RowLayout{
        spacing: 0
        anchors.fill: parent
        Rectangle{
            id: friendsListBackground
            color: "#E9E9E9"
            width: 280
            Layout.fillHeight: true
            ListView{
                id: friendsList
            }
        }

        ColumnLayout{
            spacing: 0
            Rectangle{
                id: messageListBackground
                color: "#CBCFCF"
                Layout.fillHeight: true
                Layout.fillWidth: true
                ListView{
                    id: messageList
                }
            }
            Rectangle{
                id: messageArea
                Layout.preferredHeight: 160
                Layout.fillWidth: true
                ColumnLayout{
                    anchors.fill: parent
                    Layout.fillWidth: true
                    ScrollView{
                        Layout.preferredHeight: 120
                        Layout.fillWidth: true
                        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
                        TextArea{
                            id: messageText
                            font.pixelSize:18
                            color: "#444444"
                            wrapMode:TextInput.WrapAnywhere
                            placeholderText:"输入消息..."
                            leftPadding:15
                            rightPadding:15
                            topPadding:10
                            bottomPadding:10
                        }
                    }
                    Rectangle {
                        id: toolsBar
                        Layout.fillWidth: true
                        height: 40
                        RowLayout {
                            anchors.fill: parent
                            spacing: 8

                            Item { Layout.fillWidth: true } // 占位，推送按钮到右侧

                            SendButton {
                                Layout.alignment: Qt.AlignRight
                                Layout.rightMargin: 10;
                                Layout.bottomMargin: 20;
                                onClicked: {
                                    WebSocketService.sendMessage(messageText.text);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    Connections{
        target: WebSocketService
        function onResponse(response) {
            messageText.text = ""
            console.log("服务器发出回应" + response)
        }
    }
}
