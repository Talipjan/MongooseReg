import QtQuick 2.0
import QtQuick.Controls 1.4


MenuBar {
    Menu {
        title: "File"
        MenuItem {
            text: "Quit"
            shortcut: "Ctrl+Q"
            //iconSource: images/quit.png
            onTriggered: Qt.quit()
        }
    }
    Menu {
        title: "Edit"
        Menu {
            title: "Advanced"
            MenuItem {
                text: "Maximize"
                shortcut: "Ctrl+M"
                //iconSource: images/fullscreen.png
                onTriggered: window.windowState = Qt.WindowMaximized;
            }
        }
    }
    Menu {
        title: "Планшет"
        ConfigPlansh{
            id:conf
            visible: false
        }
        MenuItem {
            text: "Настройка"
            //iconSource: images/quit.png
            onTriggered: conf.show();
        }
    }
}

