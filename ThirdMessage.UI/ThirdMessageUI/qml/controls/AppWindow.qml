import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ThirdMessageUI.Helpers

Window {
    id: root
    flags: Qt.Window | Qt.FramelessWindowHint
    default property alias content: container.data
    property bool canResize: true
    property bool logoutButtonEnabled: true

    FramelessHelper {
        id: framelessHelper
        canResize: root.canResize
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0
        AppTitleBar {
            title: root.title
            currentWindow: root
        }
        Item {
            id: container
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }

    function closeWindow() {
        framelessHelper.onWindowClosing()
        root.close();
    }

    function minimize() {
        framelessHelper.showMinimized();
    }

    function toggleMaximized() {
        if (root.visibility === Window.Maximized) {
            framelessHelper.showNormal();
        } else {
            framelessHelper.showMaximized()
        }
    }
}