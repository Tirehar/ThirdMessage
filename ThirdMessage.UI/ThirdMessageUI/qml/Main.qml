import QtQuick
import QtQuick.Controls.Windows
import QtQuick.Shapes
// import ThirdMessageUI.WebSocket
// import ThirdMessageUI.Message
import ThirdMessageUI.ViewModels
import QtQuick.Layouts
import QtQml.Models
import "./controls"

Window {
    width: 1080
    height: 680
    minimumHeight: 480
    minimumWidth: 840
    visible: true
    color: "#E9E9E9"

    title: "Third Message"

    MainViewModel {
        id: viewModel
    }

    RowLayout {
        spacing: 0
        anchors.fill: parent
        Rectangle {
            id: friendsListBackground
            color: "#E9E9E9"
            width: 280
            Layout.fillHeight: true
            ListView {
                id: friendsList
                anchors.fill: parent
                model: viewModel.friendListModel
                delegate: FriendListItem {
                    onClicked: {
                        if (friendsList.currentIndex !== index || !friendsList.isSelected) {
                            friendsList.currentItem.setSelected(false)
                            friendsList.currentIndex = index
                            friendsList.currentItem.setSelected(true)
                            friendsList.isSelected = true
                        }

                    }
                }
                property bool isSelected: false
            }
        }

        ColumnLayout {
            spacing: 0
            Rectangle {
                id: messageListBackground
                color: "#CBCFCF"
                Layout.fillHeight: true
                Layout.fillWidth: true

                ListModel {
                    id: messageListModel
                    ListElement {
                        isMyMessage: true
                        content: "你好！"
                    }
                    ListElement {
                        isMyMessage: false
                        content: "你好！很高兴认识你。"
                    }
                }
                ListView {
                    id: messageList
                    anchors.fill: parent
                    model: messageListModel
                    spacing: 10
                    clip: true
                    ScrollBar.vertical: ScrollBar {
                        width:5
                        policy: ScrollBar.Auto
                        contentItem: Rectangle { color: "#989898"; radius: 2 }
                    }
                    header: Item {
                        width: parent.width
                        height: 10
                    }
                    footer: Item {
                        width: parent.width
                        height: 10
                    }
                    delegate: MessageListItem {
                    }
                }
            }
            Rectangle {
                id: messageArea
                Layout.preferredHeight: 160
                Layout.fillWidth: true
                ColumnLayout {
                    anchors.fill: parent
                    Layout.fillWidth: true
                    ScrollView {
                        Layout.preferredHeight: 120
                        Layout.fillWidth: true
                        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
                        TextArea {
                            id: messageText
                            font.pixelSize: 18
                            color: "#444444"
                            wrapMode: TextInput.WrapAnywhere
                            placeholderText: "输入消息..."
                            leftPadding: 15
                            rightPadding: 15
                            topPadding: 10
                            bottomPadding: 10

                            Keys.onReturnPressed:{
                                sendMessage()
                            }
                            function sendMessage(){
                                if(messageText.text.trim() === "")
                                    return
                                //MessageService.sendMessage(messageText.text)
                                //WebSocketService.sendMessage(messageText.text);
                                messageListModel.append({
                                    isMyMessage: true,
                                    content: messageText.text
                                });
                                messageText.clear()
                            }
                        }
                    }
                    Rectangle {
                        id: toolsBar
                        Layout.fillWidth: true
                        height: 40
                        RowLayout {
                            anchors.fill: parent
                            spacing: 8

                            Item {
                                Layout.fillWidth: true
                            }

                            SendButton {
                                Layout.alignment: Qt.AlignRight
                                Layout.rightMargin: 10;
                                Layout.bottomMargin: 20;
                                onClicked: {
                                    sendMessage()
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

    // Connections{
    //     target: WebSocketService
    //     function onResponse(response) {
    //         messageText.text = ""
    //         console.log("服务器发出回应" + response)
    //     }
    // }

