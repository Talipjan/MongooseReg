import QtQuick 2.0
import QtQuick.Controls 2.2
import QtCharts 2.0

ChartView{
    id:chart
    signal planshChange
    antialiasing: true

    ValueAxis {
        id: axisY
        min: 0
        max: 100
        tickCount: 10
        minorTickCount: 5
        reverse: true
        gridLineColor: "black"
    }

    ValueAxis {
        id: axisX
        min: -0.5
        max: 65535
        minorTickCount: 5
        tickCount: 20
        gridLineColor: "black"
        labelsVisible: false
    }
    //--------------------------------------------------------------------------------------------
    Connections {
        target: dataModel
        onDataueChanged: {
            //textTime.text = dataModel.data.length;
            for(var i = 0; i < dataModel.data.length; i++){
                chart.series(i).append(dataModel.data[i].dataCh[dataModel.deep.length - 1],dataModel.deep[dataModel.deep.length - 1]);
                //console.log(chart.series(i).name);
            }
        }
        onDataChanged: {
            chart.planshChange();
        }
        onAreaChanged:
        {
            /*for(var i = 0; i < dataModel.area.length; i++){
                console.log(dataModel.area[i].begin);
            }*/
        }
    }
    //--------------------------------------------------------------------------------------------
    onPlanshChange:{
        chart.removeAllSeries();
        console.log("Length: " + dataModel.data.length.toString())
        for(var i = 0; i < dataModel.data.length; i++){
            //var scatter = chart.createSeries(ChartView.SeriesTypeLine, "series" + i.toString(), axisX, axisY);
            chart.createSeries(ChartView.SeriesTypeLine, "series" + i.toString(), axisX, axisY);
            chart.series(i).color = dataModel.data[i].color;
            chart.series(i).useOpenGL = true;
        }
        chart.update();
    }
    //--------------------------------------------------------------------------------------------
    // Add data dynamically to the series
    Component.onCompleted: {
        chart.removeAllSeries();

        for(var i = 0; i < dataModel.data.length; i++){
            //var scatter = chart.createSeries(ChartView.SeriesTypeLine, "series" + i.toString(), axisX, axisY);
            chart.createSeries(ChartView.SeriesTypeLine, "series" + i.toString(), axisX, axisY);
            chart.series(i).color = dataModel.data[i].color;
            chart.series(i).useOpenGL = true;
            //chart.series(i).width = 0.5;
        }
        chart.update();
        legend.visible = false;
    }
}
