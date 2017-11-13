import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import Mongoose_Model 1.0


ApplicationWindow {
    id: window
    //signal planshChange

    visible: true
    width: 640
    height: 480

    menuBar: MenyBarMongoose {}

    HotPanel {
        id:panel

        anchors.top: parent.top
        anchors.topMargin: 0
        height: 51
        width: parent.width
    }
    AreaLegend {
        id:legendch

        anchors.top: panel.bottom
        anchors.topMargin: 0
        width:parent.width
        height: 50
    }
    ChartDraw {
        id:chart

        height: 500
        anchors.topMargin: -10
        anchors.bottomMargin: 10
        anchors.top: legendch.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.leftMargin: -10
        anchors.rightMargin: -30
    }
}


