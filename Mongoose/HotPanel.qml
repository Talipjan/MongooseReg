import QtQuick 2.0
import QtQuick.Controls 2.2

Item {
    id: panel

    Row{
        Text{
            id: textTime
            text: legendch.height.toString()
        }
        Button{
            text: "open"
            width: 40
            height: 40
            onClicked: {
                console.log("chart.series(i).name");
                fileOpen.visible = true;
            }
        }
        Button{
            text: "Save"
            width: 40
            height: 40
            onClicked: {
                console.log("chart.series(i).name");
                fileSave.visible = true;
            }
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
    MongooseFileOpen{
        id:fileSave
        visible: false
        selectExisting: false
        folder: applicationDirPath
        onSignalExit:{
            var path = fileSave.fileUrl.toString();
            // remove prefixed "file:///"
            path = path.replace(/^(file:\/{3})|(qrc:\/{2})|(http:\/{2})/,"");
            dataModel.saveFile(path);
        }
    }
}
