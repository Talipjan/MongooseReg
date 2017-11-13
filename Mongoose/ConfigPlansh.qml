import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Window 2.2

Window {
    width: 640
    height: 480
    ScrollBar.vertical: ScrollBar {
        active: true
    }
    Column {
        id: column
        x: 8
        y: 8
        width: 624
        height: 600

        Row {
            id: nameRow
            anchors.top: column.top
            anchors.topMargin: 5
            //x: 8
            //y: 8
            width: 624
            height: 68
            TextField {
                id: nameField
                //x: 127
                //y: 103
                text: dataModel.name
            }
        }

        Row {
            id: driverRow
            anchors.top: nameRow.bottom
            anchors.topMargin: 5
            //x: 8
            //y: 82
            width: 624
            height: 82
            TextField {
                id: driverField
                //x: 127
                //y: 22
                text: dataModel.driver
            }
        }

        Rectangle {
            id: areaColapse
            anchors.top: driverRow.bottom
            anchors.topMargin: 5
            //x: 8
            //y: 170
            width: 624
            height: 56
            color: "#ffffff"
            border.color: "black"
            Row {
                Text {
                    id: araeText
                    text: qsTr("Дорожки")
                }
                Rectangle {
                    id: buttonAddArea
                    x: 574
                    y: 8
                    width: 42
                    height: 40
                    color: "#ffffff"
                    border.color: "black"
                    Text {
                        id: textAddArea
                        text: qsTr("+")
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            //добавить элемент
                            dataModel.addArea();
                        }
                    }
                }
                Rectangle {
                    id: buttonColapse
                    x: 574
                    y: 8
                    width: 42
                    height: 40
                    color: "#ffffff"
                    border.color: "black"
                    Text {
                        id: textAreaColapse
                        text: qsTr(">")
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            if(areaView.visible)
                            {
                                areaView.visible = false;
                                textAreaColapse.text = ">";
                            }
                            else {
                                areaView.visible = true;
                                textAreaColapse.text = "<";
                            }
                        }
                    }
                }
            }
        }

        ListView {
            id: areaView
            //x: 8
            //y: 232
            width: 624
            height: 132
            anchors.top: areaColapse.bottom
            anchors.topMargin: 5
            cacheBuffer: 640
            model: dataModel.area
            delegate: areaDelegate
            visible: false
            ScrollBar.vertical: ScrollBar {
                active: true
            }
            Component {
                id:areaDelegate
                Column {
                    Rectangle {
                        id: wrapper
                        height: 50
                        border.color: "black"
                        width: areaView.width
                        Row {
                            Text {
                                text: name
                            }
                            Rectangle {
                                id: elementDelArea
                                x: 574
                                y: 8
                                width: 42
                                height: 40
                                color: "#ffffff"
                                border.color: "black"
                                Text {
                                    id: textDelArea
                                    text: qsTr("-")
                                }
                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: {
                                        //удалить элемент
                                        dataModel.delArea(model.index);
                                        console.log(model.index);
                                    }
                                }
                            }
                            Rectangle {
                                id: areaColapse
                                x: 574
                                y: 8
                                width: 42
                                height: 40
                                color: "#ffffff"
                                border.color: "black"
                                Text {
                                    id: elementAreaColapse
                                    text: qsTr(">")
                                }
                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: {
                                        if(isOpened)
                                        {
                                            isOpened = false;
                                            //elementAreaColapse.text = ">";
                                        }
                                        else {
                                            isOpened = true;
                                            //elementAreaColapse.text = "<";
                                        }
                                    }
                                }
                            }
                        }
                        Rectangle {
                            id:areaNode
                            y:50
                            height: 50
                            border.color: "black"
                            visible: false
                            Column {
                                Row{
                                    Text {
                                        text: qsTr("Имя")
                                    }
                                    TextField {
                                        id: nameAreaField
                                        //x: 127
                                        //y: 103
                                        text: model.name
                                    }
                                }
                                Row {
                                    Text {
                                        text: qsTr("Ширина")
                                    }
                                    TextField {
                                        id: widthAreaField
                                        //x: 127
                                        //y: 103
                                        validator: IntValidator{bottom: 0; top: 100;}
                                        text: model.width
                                        onAccepted: {
                                            dataModel.setSizeArea(model.index,text);
                                        }
                                    }
                                }
                            }

                            state: "closeView"

                            Component.onCompleted: {
                                console.log(areaNode.state);
                            }
                        }
                    }

                    states: [
                        //Открытый элемент
                        State {
                            name: "openView"
                            when: isOpened
                            PropertyChanges {
                                target: areaNode
                                visible: true
                                //width: 32
                            }
                            PropertyChanges {
                                target: elementAreaColapse
                                text: "<"
                                //width: 32
                            }
                            PropertyChanges {
                                target: wrapper
                                height: 150
                                //width: 32
                            }
                        },
                        //Закрытый элемент
                        State {
                            name: "closeView"
                            when: !isOpened
                            PropertyChanges {
                                target: areaNode
                                visible: false
                                //width: 32
                            }
                            PropertyChanges {
                                target: elementAreaColapse
                                text: ">"
                                //width: 32
                            }
                            PropertyChanges {
                                target: wrapper
                                height: 50
                                //width: 32
                            }
                        }
                    ]
                }
            }
        }
        Rectangle {
            id: elementColapse
            anchors.top: areaView.bottom
            anchors.topMargin: 5
            //x: 8
            //y: 170
            width: 624
            height: 56
            color: "#ffffff"
            border.color: "black"
            Row {
                Text {
                    id: elementText
                    text: qsTr("Кривые")
                }
                Rectangle {
                    id: buttonAddElement
                    x: 574
                    y: 8
                    width: 42
                    height: 40
                    color: "#ffffff"
                    border.color: "black"
                    Text {
                        id: textAddElement
                        text: qsTr("+")
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            //добавить элемент
                            dataModel.add();
                        }
                    }
                }
                Rectangle {
                    id: butElementColapse
                    x: 574
                    y: 8
                    width: 42
                    height: 40
                    color: "#ffffff"
                    border.color: "black"
                    Text {
                        id: textElementColapse
                        text: qsTr(">")
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            if(elementView.visible)
                            {
                                elementView.visible = false;
                                textElementColapse.text = ">";
                            }
                            else {
                                elementView.visible = true;
                                textElementColapse.text = "<";
                            }
                        }
                    }
                }
            }
        }
        ListView {
            id: elementView
            //x: 8
            //y: 232
            width: 624
            height: 132
            anchors.top: elementColapse.bottom
            anchors.topMargin: 5
            cacheBuffer: 640
            model: dataModel.data
            delegate: elementDelegate
            visible: false
            ScrollBar.vertical: ScrollBar {
                active: true
            }
            Component {
                id:elementDelegate
                Column {
                    Rectangle {
                        id: wrapperElement
                        height: 50
                        border.color: "black"
                        width: elementView.width
                        Row {
                            Text {
                                text: model.text
                            }
                            Rectangle {
                                id: elementDel
                                x: 574
                                y: 8
                                width: 42
                                height: 40
                                color: "#ffffff"
                                border.color: "black"
                                Text {
                                    id: textDelElement
                                    text: qsTr("-")
                                }
                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: {
                                        //удалить элемент
                                        dataModel.delElement(model.index);
                                        console.log(model.index);
                                    }
                                }
                            }
                            Rectangle {
                                id: elementColapse
                                x: 574
                                y: 8
                                width: 42
                                height: 40
                                color: "#ffffff"
                                border.color: "black"
                                Text {
                                    id: elementTextColapse
                                    text: qsTr(">")
                                }
                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: {
                                        if(isOpened)
                                        {
                                            isOpened = false;
                                            //elementAreaColapse.text = ">";
                                        }
                                        else {
                                            isOpened = true;
                                            //elementAreaColapse.text = "<";
                                        }
                                    }
                                }
                            }
                        }
                        Rectangle {
                            id:elementNode
                            y:50
                            height: 50
                            border.color: "black"
                            visible: false
                            Column {
                                Row{
                                    Text {
                                        text: qsTr("Имя")
                                    }
                                    TextField {
                                        id: nameElementField
                                        //x: 127
                                        //y: 103
                                        text: model.convert
                                    }
                                }
                                Row {
                                    Text {
                                        text: qsTr("Дорожка")
                                    }
                                    TextField {
                                        id: areaElementField
                                        //x: 127
                                        //y: 103
                                        text: model.area
                                    }
                                }
                            }

                            state: "closeView"

                            Component.onCompleted: {
                                console.log(elementNode.state);
                            }
                        }
                    }

                    states: [
                        //Открытый элемент
                        State {
                            name: "openView"
                            when: isOpened
                            PropertyChanges {
                                target: elementNode
                                visible: true
                                //width: 32
                            }
                            PropertyChanges {
                                target: elementTextColapse
                                text: "<"
                                //width: 32
                            }
                            PropertyChanges {
                                target: wrapperElement
                                height: 150
                                //width: 32
                            }
                        },
                        //Закрытый элемент
                        State {
                            name: "closeView"
                            when: !isOpened
                            PropertyChanges {
                                target: elementNode
                                visible: false
                                //width: 32
                            }
                            PropertyChanges {
                                target: elementTextColapse
                                text: ">"
                                //width: 32
                            }
                            PropertyChanges {
                                target: wrapperElement
                                height: 50
                                //width: 32
                            }
                        }
                    ]
                }
            }
        }
    }
}
