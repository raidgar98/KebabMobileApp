import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

import Trans 1.0

ColumnLayout
{
    property alias frameContentHeight: frame.contentHeight
    //Layout.fillHeight: true;
    implicitHeight: popupList.height*0.95;
    Frame
    {
        id: frame
        Layout.topMargin: 10
        Layout.minimumHeight: popupList.height*0.6
        transformOrigin: Item.Top
        antialiasing: true
        Layout.preferredHeight: popupList.height*0.7;
        Layout.fillHeight: false
        Layout.fillWidth: true;

        ListView
        {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.fill: parent
            implicitWidth: 300;
            //  Layout.fillHeight: true;
            clip: true;


            model: TransModel
            {
                list: transList;
            }

            delegate: RowLayout
            {
                width: parent.width;

                CheckBox
                {
                    id: checkBox;

                    checked: model.toRemove;

                    onClicked: model.toRemove = checked;

                    indicator: Rectangle
                    {
                        //anchors.margins: 1;
                        radius: 8;
                        border.width: 2;
                        border.color: "black";
                        implicitWidth: 25;
                        implicitHeight: implicitWidth;
                        Rectangle
                        {
                            anchors.margins: 3;
                            visible: checkBox.checked;
                            color: "black";
                            anchors.verticalCenter: parent.verticalCenter;
                            anchors.horizontalCenter: parent.horizontalCenter;
                            implicitWidth: parent.width*0.5;
                            implicitHeight: implicitWidth;
                            radius: 4;
                        }
                    }
                }
                TextField
                {
                    id: textFieldInModel;
                    text: model.descTrans;
                    font.pixelSize: 12;
                    readOnly: true;
                    Layout.fillWidth: true;
                    // Layout.fillHeight: true;
                    implicitHeight: 25;
                    anchors.top: parent.top;

                    onPressed: { popupProperties.oPEN(model.descTrans); }

                    background: Rectangle
                    {
                        // y: -5;
                        radius: 6;
                        border.width: 1;
                        border.color: "black";
                        Layout.fillWidth: true;
                        //Layout.fillHeight: true;
                    }
                }
            }
        }

    }


    RowLayout
    {
        Button
        {
            text: qsTr("Usuń zaznaczone");
            Layout.fillWidth: true;
            onClicked: transList.removeSelectedItems();
        }
    }


    Popup
    {
        id: popupProperties;
        property var fontSize: 10;
        property var widthItem: 50;
        property var widthLongItem: 1.65*widthItem
        property var heightItem: fontSize*2.5;
        anchors.centerIn: parent;
        height: 15*heightItem;

        //property var src: "0000001MKebCia0001000";
        property var sRC : "";
        function oPEN(src)
        {
            //  src = String(src1);
            sRC = src;
            txt1.text = terminal.qmlGetID(src.toString()).toString();
            txt2.text = terminal.qmlGetName(src.toString()).toString();
            txt3.text = terminal.qmlGetSouce(src.toString()).toString();
            txt4.text = terminal.qmlGetMeat(src.toString()).toString();
            txt5.text = terminal.qmlGetSalad(src.toString()).toString();
            txt6.text = terminal.qmlGetFries(src.toString()).toString();
            txt7.text = terminal.qmlGetCheese(src.toString()).toString();
            txt8.text = terminal.qmlGetOther(src.toString()).toString();
            txt9.text = terminal.qmlGetTakeAway(src.toString()).toString();
            txt10.text = terminal.qmlGetComplete(src.toString()).toString();
            txt11.text = terminal.qmlGetDateTime(src.toString()).toString();
            popupProperties.open();

        }

        background: Rectangle
        {

            id: backgroundRectangleProps;
            border.width: buttBorderWidth;
            border.color: "#00000000";
            height: popupProperties.height;
            width: popupProperties.width;
            //anchors.centerIn: popupProperties;
            color: txt10.text == "TAK" ? "green" : "red";


        }

        width: 225;
        ColumnLayout
        {
            anchors.centerIn: parent;
            spacing: 3;


            RowLayout
            {
                TextField
                {
                    text: "ID: ";
                    //width: 40;
                    font.pixelSize: popupProperties.fontSize;
                    background: Rectangle
                    {
                        color: "#00000000";
                    }
                }

                TextField
                {
                    id: txt1;
                    font.pixelSize: popupProperties.fontSize;
                    readOnly: true;
                    implicitWidth: popupProperties.widthItem; implicitHeight: popupProperties.heightItem;
                }
            }

            RowLayout
            {
                TextField
                {
                    text: "Nazwa: ";
                    //width: 40;
                    font.pixelSize: popupProperties.fontSize;
                    background: Rectangle
                    {
                        color: "#00000000";
                    }
                }

                TextField
                {
                    id: txt2;
                    font.pixelSize: popupProperties.fontSize;
                    readOnly: true;
                    implicitWidth: popupProperties.widthLongItem;
                    implicitHeight: popupProperties.heightItem;
                }
            }

            RowLayout
            {
                TextField
                {
                    font.pixelSize: popupProperties.fontSize;
                    text: "Dodatkowy Sos: ";
                    //width: 40;
                    background: Rectangle
                    {
                        color: "#00000000";
                    }
                }

                TextField
                {
                    font.pixelSize: popupProperties.fontSize;
                    id: txt3;
                    readOnly: true;
                    implicitWidth: popupProperties.widthLongItem;
                    implicitHeight: popupProperties.heightItem;
                }
            }

            RowLayout
            {
                TextField
                {
                    font.pixelSize: popupProperties.fontSize;
                    text: "Dodatkowe Mięso: ";
                    //width: 40;
                    background: Rectangle
                    {
                        color: "#00000000";
                    }
                }

                TextField
                {
                    font.pixelSize: popupProperties.fontSize;
                    id: txt4;
                    readOnly: true;
                    implicitWidth: popupProperties.widthItem; implicitHeight: popupProperties.heightItem;
                }
            }

            RowLayout
            {
                TextField
                {
                    font.pixelSize: popupProperties.fontSize;
                    text: "Dodatkowa Sałatka: ";
                    //width: 40;
                    background: Rectangle
                    {
                        color: "#00000000";
                    }
                }

                TextField
                {
                    font.pixelSize: popupProperties.fontSize;
                    id: txt5;
                    readOnly: true;
                    implicitWidth: popupProperties.widthItem; implicitHeight: popupProperties.heightItem;
                }
            }

            RowLayout
            {
                TextField
                {
                    font.pixelSize: popupProperties.fontSize;
                    text: "Dodatkowe Frytki: ";
                    //width: 40;
                    background: Rectangle
                    {
                        color: "#00000000";
                    }
                }

                TextField
                {
                    font.pixelSize: popupProperties.fontSize;
                    id: txt6;
                    readOnly: true;
                    implicitWidth: popupProperties.widthItem; implicitHeight: popupProperties.heightItem;
                }
            }

            RowLayout
            {
                TextField
                {
                    font.pixelSize: popupProperties.fontSize;
                    text: "Dodatkowy Ser: ";
                    //width: 40;
                    background: Rectangle
                    {
                        color: "#00000000";
                    }
                }

                TextField
                {
                    font.pixelSize: popupProperties.fontSize;
                    id: txt7;
                    readOnly: true;
                    implicitWidth: popupProperties.widthItem; implicitHeight: popupProperties.heightItem;
                }
            }

            RowLayout
            {
                TextField
                {
                    font.pixelSize: popupProperties.fontSize;
                    text: "Inne Dodatki: ";
                    //width: 40;
                    background: Rectangle
                    {
                        color: "#00000000";
                    }
                }

                TextField
                {
                    font.pixelSize: popupProperties.fontSize;
                    id: txt8;
                    readOnly: true;
                    implicitWidth: popupProperties.widthItem; implicitHeight: popupProperties.heightItem;
                }
            }

            RowLayout
            {
                TextField
                {
                    font.pixelSize: popupProperties.fontSize;
                    text: "Na Wynos: ";
                    //width: 40;
                    background: Rectangle
                    {
                        color: "#00000000";
                    }
                }

                TextField
                {
                    font.pixelSize: popupProperties.fontSize;
                    id: txt9;
                    readOnly: true;
                    implicitWidth: popupProperties.widthItem; implicitHeight: popupProperties.heightItem;
                }
            }

            RowLayout
            {
                TextField
                {
                    font.pixelSize: popupProperties.fontSize;
                    text: "Ukończono: ";
                    //width: 40;
                    background: Rectangle
                    {
                        color: "#00000000";
                    }
                }

                TextField
                {
                    font.pixelSize: popupProperties.fontSize;
                    id: txt10;
                    readOnly: true;
                    implicitWidth: popupProperties.widthItem;
                    implicitHeight: popupProperties.heightItem;
                }
            }

            RowLayout
            {
                TextField
                {
                    font.pixelSize: popupProperties.fontSize;
                    text: "Zamówiono: ";
                    //width: 40;
                    background: Rectangle
                    {
                        color: "#00000000";
                    }
                }

                TextField
                {
                    font.pixelSize: popupProperties.fontSize;
                    id: txt11;
                    readOnly: true;
                    implicitWidth: popupProperties.widthLongItem * 1.6;
                    implicitHeight: popupProperties.heightItem;
                }
            }

            Button
            {
                Layout.fillWidth: true;
                text: backgroundRectangleProps.color == "green" ? "Nie zrobione" : "Zrobione";
                onClicked:
                {
                    terminal.buttonComplitedClicked(String(popupProperties.sRC));
                    //backgroundRectangleProps.color= (backgroundRectangleProps.color == "green") ? "red" : backgroundRectangleProps="green";
                    txt10.text = terminal.qmlGetComplete(popupProperties.sRC.toString()).toString();
                }
            }
        }
    }

}
