import QtQuick 2.0

Item {
    id:legendch
    property real areaHeight: 50;

    Repeater {
        id:line
        anchors.margins: 10
        anchors.fill: parent
        height: legendch.areaHeight
        model: dataModel.area

        Rectangle {
            width: 3
            x: parent.width * (model.begin/100.0)
            height: window.height - y
            border.color: "black"
            color: "black"

            Component.onCompleted: {
                if(model.index === 0) {
                    visible = false;
                }
            }
        }
    }
    Rectangle {
        width: parent.width
        x: 0
        height: 1
        border.color: "black"
        color: "black"
    }
    Rectangle {
        width: 1
        x: parent.width
        height: window.height - y
        border.color: "black"
        color: "black"
    }
    Repeater {
        id:area
        signal areaChange
        anchors.margins: 10
        anchors.fill: parent
        height: legendch.areaHeight
        model: dataModel.data

        Rectangle {
            id: rectangle1
            signal indexChange
            x: parent.width*(dataModel.area[model.area - 1].begin/100.0) + 2
            y: model.areaindex*(height - 1)
            width: parent.width*(dataModel.area[model.area - 1].width/100.0) - 2
            height: 50
            color: "#ffffff"
            border.color: "black"
//            radius: 5
//            gradient: Gradient {
//                GradientStop {
//                    position: 0
//                    color: "#ffffff"
//                }

//                GradientStop {
//                    position: 0.811
//                    color: "#4a80d1"
//                }

//                GradientStop {
//                    position: 1
//                    color: "#000000"
//                }
//            }

            Text {
                anchors.centerIn: parent
                renderType: Text.NativeRendering
                text: model.text
            }
            Text {
                anchors.left:parent.left
                renderType: Text.NativeRendering
                text: model.curval
            }
            Text {
                renderType: Text.NativeRendering
                text: "Изменить"
                anchors.right: parent.right
                anchors.rightMargin: 0

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        conf.indexData = model.index;
                        conf.show();
                    }
                }
            }
            Component.onCompleted: {
                if(legendch.height != y + height)
                {
                    legendch.height = y + height;
                }
                chart.series(model.index).color = model.color;
                //console.log("dataModel.area[model.area - 1]");
            }
            //                MouseArea {
            //                    anchors.fill: parent
            //                    onClicked: {
            //                        console.log(model.text);
            //                    }
            //                }

        }
        onAreaChange:{
            var array_area = [];
            var max_index = 0;
            for(var i=0;i<dataModel.area.length;i++)
            {
                array_area.push(0);
            }
            for(i=0;i<dataModel.data.length;i++)
            {
                dataModel.data[i].areaindex = array_area[dataModel.data[i].area - 1];
                if(max_index < array_area[dataModel.data[i].area - 1])
                {
                    max_index = array_area[dataModel.data[i].area - 1];
                }
                array_area[dataModel.data[i].area - 1]++;
            }
            //                if(legendch.height != max_index*(legendch.areaHeight + 2) + legendch.areaHeight)
            //                {
            //                    legendch.height = max_index*(legendch.areaHeight + 2) + legendch.areaHeight;
            //                }
            dataModel.dataChanged();
        }
    }
    ConfigChannel{
        id:conf

        onSignalExit: {
            area.areaChange();
        }
    }
}

