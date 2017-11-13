import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import Mongoose_Model 1.0
import QtCharts 2.0

//ChartView {
//    title: "Two Series, Common Axes"
//    anchors.fill: parent
//    legend.visible: false
//    antialiasing: true

//    ValueAxis {
//        id: axisX
//        min: 0
//        max: 10
//        tickCount: 5
//    }

//    ValueAxis {
//        id: axisY
//        min: -0.5
//        max: 1.5
//    }

//    LineSeries {
//        id: series1
//        axisX: axisX
//        axisY: axisY
//    }

//    ScatterSeries {
//        id: series2
//        axisX: axisX
//        axisY: axisY
//    }


//    // Add data dynamically to the series
//    Component.onCompleted: {
//        for (var i = 0; i <= 10; i++) {
//            series1.append(i, Math.random());
//            series2.append(i, Math.random());
//        }
//    }
//}


Rectangle {
    id: rectangle
    width: parent.width
    height: parent.height

    Connections {
        target: dataModel
        onDataueChanged: {
            textTime.text = dataModel.data.length;
            //            if(dataModel.data.length===4){
            //                textTime.text = chart.series(3).at(dataModel.deep[dataModel.deep.length - 1]).y;//dataModel.deep[dataModel.deep.length - 1];
            //            }
            for(var i = 0; i < dataModel.data.length; i++){
                chart.series(i).append(dataModel.deep[dataModel.deep.length - 1],dataModel.data[i].dataCh[dataModel.deep.length - 1]);
                //console.log(chart.series(i).name);
            }
        }
        onDataChanged: {

        }
    }

//    Column {
//        id: column
//        anchors.margins: 10
//        anchors.fill: parent
//        spacing: 10
        Text{
            id: textTime
            text: legendch.height.toString()
            anchors.top: parent.top
            anchors.topMargin: 0

            //dataModel.deeptime[0].x
        }
        //        onDataChanged: {
        //            textTime.text = "dataModel.deeptime[dataModel.deeptime.size - 1].x";
        //        }

        Item {
            id:legendch
            anchors.top: textTime.bottom
            anchors.topMargin: 10
            width:parent.width
            height: 50
            Repeater {
                //id:legendch
                anchors.margins: 10
                anchors.fill: parent
                height: 50
                model: dataModel.data

                Rectangle {
                    x: (model.area - 1)*(width + 2)
                    y: (model.areaindex)*(height + 2)
                    width: parent.width / dataModel.numarea
                    height: 50
                    color: "#1f73e8"
                    border.color: "black"
                    Text {
                        anchors.centerIn: parent
                        renderType: Text.NativeRendering
                        text: model.index
                    }
                }
            }
        }
            //        GridView {
            //            id: view
            //            flow: GridView.FlowLeftToRight
            //            layoutDirection: Qt.LeftToRight
            //            boundsBehavior: Flickable.DragAndOvershootBounds
            //            anchors.margins: 10
            //            anchors.fill: parent
            //            cellHeight: 98
            //            cellWidth: cellHeight
            //            //width: parent.width
            //            //height: parent.height - button.height - parent.spacing
            //            //spacing: 10
            //            model: dataModel.data
            //            clip: true
            //            focus: true
            //            x:50
            //            y:500
            //            highlight: Rectangle { width: 80; height: 80; color: "lightsteelblue" }

            //            delegate: Item {
            //                property var view: GridView.view
            //                property var isCurrent: GridView.isCurrentItem

            //                height:view.cellHeight
            //                width: view.cellWidth
            //                //x:(model.area - 1)*100
            //                Rectangle {
            //                    anchors.margins: 5
            //                    anchors.fill: parent
            //                    color: model.color
            //                    //x: (model.area - 1)*100
            //                    //y: (model.area - 1)*100
            //                    Text {
            //                        anchors.centerIn: parent
            //                        renderType: Text.NativeRendering
            //                        text: model.index
            //                    }
            //                    MouseArea {
            //                        anchors.fill: parent
            //                        onClicked: view.currentIndex = model.index
            //                    }
            //                }
            //            }
            //        }
            ChartView{
                id:chart

                anchors.bottomMargin: 50
                anchors.top: legendch.bottom
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.topMargin: 10
                antialiasing: true

                title: "Two Series, Common Axes"
                //            legend.visible: false

                ValueAxis {
                    id: axisX
                    min: 0
                    max: 100
                    tickCount: 5
                }

                ValueAxis {
                    id: axisY
                    min: -0.5
                    max: 65535
                }

                //            LineSeries {
                //                id: series1
                //                axisX: axisX
                //                axisY: axisY
                //                useOpenGL: true
                //            }

                //            LineSeries {
                //                id: series2
                //                axisX: axisX
                //                axisY: axisY
                //                useOpenGL: true
                //            }

                //            LineSeries {
                //                id: series3
                //                axisX: axisX
                //                axisY: axisY
                //                useOpenGL: true
                //            }

                // Add data dynamically to the series
                Component.onCompleted: {
                    chart.removeAllSeries();

                    for(var i = 0; i < dataModel.data.length; i++){
                        //var scatter = chart.createSeries(ChartView.SeriesTypeLine, "series" + i.toString(), axisX, axisY);
                        chart.createSeries(ChartView.SeriesTypeLine, "series" + i.toString(), axisX, axisY);
                        chart.series(i).color = dataModel.data[i].color;
                        chart.series(i).useOpenGL = true;
                        //                    for (var j = 0; j <= 10; j++) {
                        //                        scatter.append(j, Math.random());
                        //                    }
                    }
                    chart.update();
                }

            }

            Rectangle
            {
                id: button

                width: 100
                height: 40
                anchors.bottom: chart.bottom
                anchors.bottomMargin: -40
                anchors.horizontalCenter: parent.horizontalCenter
                border {
                    color: "black"
                    width: 1
                }

                Text {
                    anchors.centerIn: parent
                    renderType: Text.NativeRendering
                    text: "Add"
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        dataModel.add();
                        dataModel.setName("123");
                        chart.removeAllSeries();
                        chart.update();
                        for(var i = 0; i < dataModel.data.length; i++){
                            //var scatter = chart.createSeries(ChartView.SeriesTypeLine, "series" + i.toString(), axisX, axisY);
                            chart.createSeries(ChartView.SeriesTypeLine, "series" + i.toString(), axisX, axisY);
                            chart.series(i).color = dataModel.data[i].color;
                            chart.series(i).useOpenGL = true;
                            chart.update();
                        }
                    }
                }
            }
//        }
    }
