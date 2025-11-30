import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: root
    width: currentWindow.width
    height: 32

    property Window currentWindow
    property string title : "ThirdMessage"

    RowLayout{
        anchors.fill: parent
        RowLayout{
            Image {
                id:logo
                Layout.preferredWidth: 20
                Layout.preferredHeight: 20
                Layout.leftMargin: 4
                Layout.rightMargin: 4
                fillMode: Image.PreserveAspectFit
                source: "qrc:/AppLogo.png"
            }
            Text{
                text: title
            }
        }
        Item{
            id: dragArea
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredHeight: 32
            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton
                onPressed: currentWindow.startSystemMove()
                propagateComposedEvents: false
            }
        }
        Row{
            TitleBarButton{
                visible: currentWindow.logoutButtonEnabled
                icon: "qrc:/icon/Logout.png"
                onClicked: {

                }
            }
            TitleBarButton{
                icon: "qrc:/icon/Minimize.png"
                onClicked: {
                    currentWindow.minimize()
                }
            }
            TitleBarButton{
                visible: currentWindow.canResize
                icon: "qrc:/icon/Maximize.png"
                onClicked: {
                    currentWindow.toggleMaximized()
                    if(currentWindow.visibility === Window.Maximized) {
                        icon = "qrc:/icon/ReMaximize.png"
                    }
                    else {
                        icon = "qrc:/icon/Maximize.png"
                    }
                }
            }
            TitleBarButton{
                icon: "qrc:/icon/Close.png"
                topRightRadius: 6
                hoverColor: "#ec0000"
                pressedColor: "#bd0000"
                onClicked:{
                    currentWindow.closeWindow()
                }
            }
        }
    }
}