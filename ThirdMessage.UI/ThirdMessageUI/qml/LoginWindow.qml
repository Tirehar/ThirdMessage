import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
import ThirdMessageUI.ViewModels

Window {
    id: loginWindow
    width: 640
    height: 360
    visible: true
    title:"Third Message Login"
    LoginViewModel{
        id:viewModel
    }

    RowLayout{
        anchors.fill: parent
        Item{
            Layout.preferredWidth: parent.width / 2
            Layout.preferredHeight: parent.height
            Rectangle{
                anchors.fill: parent
                anchors.margins: 24
                Image {
                    id:logo
                    anchors.centerIn: parent
                    width: Math.min(parent.width * 0.6, 280)
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
            console.debug("登录回应：" + successful)
            if(successful){
                loginWindow.close();
                var mainWindow = Qt.createComponent("Main.qml");
                mainWindow.createObject(null, { visible: true});
            }else {
                loginButton.enabled = true;
            }
        }
    }
}
