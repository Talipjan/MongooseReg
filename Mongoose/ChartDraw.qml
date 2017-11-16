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
        max: dataModel.pagesize
        tickCount: 11
        minorTickCount: 4
        reverse: true
        gridLineColor: "black"
        minorGridLineColor: "grey"
    }

    ValueAxis {
        id: axisX
        min: 0
        max: 100
        minorTickCount: 4
        tickCount: 21
        gridLineColor: "black"
        labelsVisible: false
        minorGridLineColor: "grey"
    }
    //--------------------------------------------------------------------------------------------
    Connections {
        target: dataModel
        onDataueChanged: {
            //textTime.text = dataModel.data.length;
            var j;
            var areaWidth;
            var beg_point;
            var ch_x;
            var prev_y;
            var ch_y;
            var delta_y;
            var delta_chy;
            var sub_val;
            var pagemax;
            var pagesize;

            pagemax = dataModel.pageval;
            pagesize = dataModel.pagesize;
            ch_y = dataModel.deep[dataModel.deep.length - 1]/10.0;  //текущая глубина
            prev_y = dataModel.deep[dataModel.deep.length - 2]/10.0;// предыдущая глубина
            delta_y = ch_y - prev_y;                                //делта между ними

            //Сдвиг оси у глубина
            if(ch_y > axisY.max)
            {
                pagemax += pagesize*0.5;
                dataModel.pageval = pagemax;
                axisY.max = pagemax;
                axisY.min = pagemax - pagesize;
            }
            if(ch_y < axisY.min)
            {
                pagemax -= pagesize*0.5;
                dataModel.pageval = pagemax;
                axisY.max = pagemax;
                axisY.min = pagemax - pagesize;
            }
            // рисование кривых
            for(var i = 0; i < dataModel.data.length; i++){
                areaWidth = dataModel.area[dataModel.data[i].area - 1].width;                        // ширина дорожки
                beg_point = dataModel.area[dataModel.data[i].area - 1].begin;                        // начало дорожки
                ch_x = dataModel.data[i].dataCh[dataModel.deep.length - 1]/dataModel.data[i].diva;   // текущие показание кривой с учетом цены деления
                sub_val = dataModel.data[i].subval;                                                  // текщее велина для вычета чтобы вписать кривую в дорожку

                //сколько раз кривая перелетела дорожку
                delta_chy = (Math.abs(ch_x - sub_val)/areaWidth);
                if(delta_chy > 1)
                {
                   delta_chy = delta_y/delta_chy;
                }
                else {
                   delta_chy = delta_y;
                }

                j = 0;
                while(areaWidth < ch_x - sub_val)
                {
                    j++;
                    //console.log("+");
                    //console.log(delta_chy);
                    sub_val += areaWidth;
                    dataModel.data[i].subval = sub_val;
                    chart.series(i).append(beg_point + areaWidth,prev_y + delta_chy*j); //отрезок до конца дорожки
                    chart.series(i).append(beg_point ,prev_y + delta_chy*j);            //отрезок от начала дорожки до тек показания
//                    if(areaWidth < ch_x - sub_val)
//                    {
//                        chart.series(i).append(beg_point ,prev_y + delta_chy*j);
//                    }
                }
                j=0;
                while(ch_x - sub_val < 0)
                {
                    j++;
                    //console.log("-");
                    //console.log(delta_chy);
                    sub_val -= areaWidth;
                    dataModel.data[i].subval = sub_val;
                    chart.series(i).append(beg_point + areaWidth,prev_y + delta_chy*j);
                    if(ch_x - sub_val < 0)
                    {
                        chart.series(i).append(beg_point ,prev_y + delta_chy*j);
                    }
                }
                chart.series(i).append(beg_point + ch_x - sub_val,ch_y);
                //chart.series(i).append(dataModel.data[i].dataCh[dataModel.deep.length - 1],dataModel.deep[dataModel.deep.length - 1]/10.0);
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
