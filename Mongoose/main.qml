import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
//import QtQuick.Controls 1.4
import Qt.labs.platform 1.0
import QtQuick.Layouts 1.3
import Mongoose_Model 1.0


ApplicationWindow {
    id: window
    //signal planshChange

    visible: true
    width: 640
    height: 480
    header: MenuBarMongoose {
                id: menuBar
           }

    //    menuBar: MenyBarMongoose {
    //        id: menuBar
    //    }
    HotPanel {
        id:panel

        anchors.top: menyBar.bottom
        anchors.topMargin: 0
        height: 51
        width: parent.width
        z: 10
    }
    AreaLegend {
        id:legendch
        width: chart.plotArea.width  + 3
        x:chart.plotArea.x + chart.x - 3
        anchors.top: panel.bottom
        anchors.topMargin: 0
        //anchors.leftMargin: chart.plotArea.x + chart.x
        //anchors.rightMargin: 15
        height: 50
        //anchors.right: parent.right
        //anchors.left: parent.left
        z: 1
        Component.onCompleted: {
            console.log(width);
        }
    }
    ChartDraw {
        id:chart

        height: 500
        smooth: true
        anchors.topMargin: -15
        anchors.bottomMargin: -30
        anchors.top: legendch.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.leftMargin: -10
        anchors.rightMargin: -30
        z: -1
        onPlotAreaChanged: {
            //console.log(chart.plotArea.x + chart.x + chart.plotArea.width);
        }
    }
    //    MongooseFileOpen{
    //        id:fileOpen
    //        visible: false
    //        folder: applicationDirPath
    //        onSignalExit:{
    //            var path = fileOpen.fileUrl.toString();
    //            // remove prefixed "file:///"
    //            path = path.replace(/^(file:\/{3})|(qrc:\/{2})|(http:\/{2})/,"");
    //            dataModel.openFile(path);
    //        }
    //    }
}


