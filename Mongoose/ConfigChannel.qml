import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Window 2.2
import Qt.labs.platform 1.0

Window{
    id:configWindow
    property int indexData
    signal signalExit

    width: 200
    height: 300

    Button{
        x: 0
        y: 260
        text: "Ok"
        onClicked: {
            if(dataModel.data.length !== 0)
            {
                dataModel.data[indexData].text = textField.text;
                if(dataModel.area.length < areaField.text)
                {
                    areaField.text = dataModel.numarea;
                }
                dataModel.data[indexData].area = areaField.text;
                dataModel.data[indexData].color = colorField.text;
            }
            configWindow.signalExit();
            configWindow.close();
        }
    }

    TextField {
        id: textField
        x: 0
        y: 17
        text: qsTr(dataModel.data[indexData].text)
    }

    TextField {
        id: areaField
        x: 0
        y: 68
        text: dataModel.data[indexData].area.toString()
    }

    TextField {
        id: colorField
        x: 0
        y: 122
        text: dataModel.data[indexData].color
        MouseArea{
            anchors.fill: parent
            onClicked: {
                colorDialog.open();
                colorDialog.color = colorField.text;
            }
        }
    }
    ColorDialog {
        id: colorDialog
        currentColor: dataModel.data[indexData].color
        onAccepted: {
            colorField.text = colorDialog.color;
        }
    }

}
