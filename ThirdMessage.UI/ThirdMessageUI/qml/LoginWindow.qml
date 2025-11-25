import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
import ThirdMessageUI.ViewModels

Window {
    id: loginWindow
    width: 640
    height: 360
    visible: true

    LoginViewModel{
        id:viewModel
    }

    RowLayout{
        anchors.fill: parent
        Rectangle {
            Layout.preferredWidth: parent.width / 2

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
                text:"登录"
                font.pixelSize:15
                width:260
                height:48
                onClicked:{
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
            }
        }
    }
}
