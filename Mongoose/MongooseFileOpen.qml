import QtQuick 2.2
import QtQuick.Dialogs 1.0

FileDialog {
    id: fileDialog
    title: "Выберите файл планшета"
    signal signalExit
    //folder: shortcuts.home
    visible: false
    //modality:
    //selectExisting: false //сохранить
    selectExisting: true    //открыть
    selectMultiple: false
    //selectFolder:
    nameFilters: [ "Plansh files (*.xml )" ]
    selectedNameFilter: "Plansh files (*.xml )"
    sidebarVisible: true
    onAccepted: {
        console.log("You chose: " + fileDialog.fileUrls);
        fileDialog.signalExit();
        fileDialog.close();
    }
    onRejected: {
        console.log("Canceled")
        fileDialog.close();
    }
    //Component.onCompleted: visible = false
}
