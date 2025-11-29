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

    property var currentFriendUid
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
            ColumnLayout {
                anchors.fill: parent
                spacing: 0
                Rectangle {
                    id: topBar
                    color: "#bcc4cc"
                    z:2
                    Layout.preferredHeight: 36
                    Layout.fillWidth: true

                    FriendSearchEdit{
                        anchors.fill: parent
                        listModel: viewModel.friendSearchListModel
                        onActived: {
                            viewModel.friendAdd(text);
                        }
                        onTextChanged: {
                            viewModel.loadFriendSearchList(text);
                        }
                        onSelected: {
                            viewModel.friendAdd(userName);
                        }
                    }
                }

                ListView {
                    id: friendsList
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    model: viewModel.friendListModel
                    delegate: FriendListItem {
                        onClicked: {
                            if (friendsList.currentIndex !== index || !friendsList.isSelected) {
                                if (friendsList.currentItem) friendsList.currentItem.setSelected(false)
                                friendsList.currentIndex = index
                                if (friendsList.currentItem) friendsList.currentItem.setSelected(true)
                                friendsList.isSelected = true
                            }
                        }
                        onSelected: {
                            currentFriendUid = uid
                            messageArea.enabled = true
                            viewModel.loadMessageList(uid)
                        }
                    }
                    property bool isSelected: false
                }
            }
        }

        ColumnLayout {
            spacing: 0
            Rectangle {
                id: messageListBackground
                color: "#CBCFCF"
                Layout.fillHeight: true
                Layout.fillWidth: true
                ListView {
                    id: messageList
                    anchors.fill: parent
                    model: viewModel.messageListModel
                    spacing: 10
                    clip: true
                    ScrollBar.vertical: ScrollBar {
                        width:5
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
                enabled: false
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
                                viewModel.sendMessage(messageText.text, currentFriendUid)
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
                                    messageText.sendMessage()
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

