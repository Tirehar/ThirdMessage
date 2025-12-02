import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
import ThirdMessageUI.ViewModels
import "./controls"

AppWindow{
    id: loginWindow
    width: 640
    height: 360
    visible: true
    canResize: false
    logoutButtonEnabled: false
    title:"ThirdMessage Login"
    LoginViewModel{
        id:viewModel
    }
    RowLayout{
        anchors.fill: parent
        Item{
            Layout.preferredWidth: parent.width / 2
            Layout.preferredHeight: parent.height
            Column{
                anchors.centerIn:parent
                spacing: 10
                Image {
                    id:logo
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: Math.min(parent.width * 0.8, 280)
                    height: width
                    fillMode: Image.PreserveAspectFit
                    source: "qrc:/AppLogo.png"

                    opacity: 0.0
                    scale: 0.96
                    Behavior on opacity { NumberAnimation { duration: 300} }
                    Behavior on scale   {
                        NumberAnimation {
                            duration: 300
                            easing.type: Easing.InBack
                        }
                    }
                    Component.onCompleted: {
                        opacity = 1.0
                        scale = 1.0
                    }
                }
                Label{
                    text:"Third Message"
                    font.pixelSize:22
                    color:"#515151"
                    horizontalAlignment: Text.Center
                }
            }
        }

        Column{
            spacing:15
            Label{
                text:"账户登录"
                font.pixelSize:26
                color:"#444444"
                horizontalAlignment: Text.Center
            }
            TextField{
                id:usernameInput
                placeholderText:"账户"
                font.pixelSize:12
                height:32
                width:260
            }
            TextField{
                id:passwordInput
                placeholderText:"密码"
                echoMode: TextInput.Password
                font.pixelSize:12
                height:32
                width:260
            }
            Button{
                id: loginButton
                text:"登录"
                font.pixelSize:15
                width:260
                height:48
                onClicked:{
                    loginButton.enabled = false;
                    viewModel.login(usernameInput.text, passwordInput.text)
                }
            }
        }
    }

    Connections{
        target: viewModel
        function onLoginResponse(successful){
            if(successful){
                loginWindow.closeWindow();
                var mainWindow = Qt.createComponent("Main.qml");
                mainWindow.createObject();
                mainWindow.show()
            }else {
                loginButton.enabled = true;
            }
        }
    }
}