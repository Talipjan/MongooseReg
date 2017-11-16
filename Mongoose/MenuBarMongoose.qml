import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

ToolBar {
    height:40
    RowLayout {
        spacing: 1
        anchors.fill: parent
        ToolButton {
            id:menuFile
            width: 20
            height: 20
            text: qsTr("Файл")
            Menu {
                id: menu
                topMargin: 40
                //y: parent.height
                MenuItem {
                    text: "Quit"
                    //shortcut: "Ctrl+Q"
                    //iconSource: images/quit.png
                    onTriggered: Qt.quit()
                }
                MenuItem {
                    text: "New..."
                }
                MenuItem {
                    text: "Open..."
                }
                MenuItem {
                    text: "Save"
                }
            }
            onClicked: menu.open()
        }
        ToolSeparator {
            id:seprFP
            height: 20
            anchors.left: menuFile.right
        }
        ToolButton {
            width: 57
            height: 20
            text:"Планшет"
            anchors.left: seprFP.right
            Menu {
                id:plansh
                topMargin: 40
                MenuItem {
                    text: "Настройка"
                    //iconSource: images/quit.png
                    onTriggered: conf.show();
                }
                MenuItem {
                    text: "Открыть планшет"
                    //iconSource: images/quit.png
                    onTriggered: {
                        fileOpen.visible = true;
                    }
                }
            }
            onClicked: plansh.open()
        }
    }
    MongooseFileOpen{
        id:fileOpen
        visible: false
        folder: applicationDirPath
        onSignalExit:{
            var path = fileOpen.fileUrl.toString();
            // remove prefixed "file:///"
            path = path.replace(/^(file:\/{3})|(qrc:\/{2})|(http:\/{2})/,"");
            dataModel.openFile(path);
        }
    }
    ConfigPlansh{
        id:conf
        visible: false
    }
}
//MenuBar {
//    Menu {
//        title: "File"
//        MenuItem {
//            text: "Quit"
//            shortcut: "Ctrl+Q"
//            //iconSource: images/quit.png
//            onTriggered: Qt.quit()
//        }
//    }
////    Menu {
////        title: "Edit"
////        Menu {
////            title: "Advanced"
////            MenuItem {
////                text: "Maximize"
////                shortcut: "Ctrl+M"
////                //iconSource: images/fullscreen.png
////                onTriggered: window.windowState = Qt.WindowMaximized;
////            }
////        }
////    }
//    Menu {
//        title: "Планшет"
//        MenuItem {
//            text: "Настройка"
//            //iconSource: images/quit.png
//            onTriggered: conf.show();
//        }
//        MenuItem {
//            text: "Открыть планшет"
//            //iconSource: images/quit.png
//            onTriggered: {
//                fileOpen.visible = true;
//            }
//            Component.onCompleted: {
//                console.log(applicationDirPath);
//            }
//        }
//        MongooseFileOpen{
//            id:fileOpen
//            visible: false
//            folder: applicationDirPath
//            onSignalExit:{
//                var path = fileOpen.fileUrl.toString();
//                // remove prefixed "file:///"
//                path = path.replace(/^(file:\/{3})|(qrc:\/{2})|(http:\/{2})/,"");
//                dataModel.openFile(path);
//            }
//        }
//        ConfigPlansh{
//            id:conf
//            visible: false
//        }
//    }
//}

