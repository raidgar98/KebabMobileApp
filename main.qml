import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

Window
{

    id: root;

    //onWidthChanged: terminal.connect();

    width: Screen.width;
    height: Screen.height;
    visible: true
    visibility: Window.FullScreen;

    color: "#33312F";
    title: qsTr("")

    property var buttWidth: (width-10-20)/2.0;
    property var buttHeight: 75;
    property var buttAltHeight: height*0.15;
    property var buttRadius: 35;
    property var buttColor: "#ED952A"
    property var buttBorderWidth: 6;
    property var fontAltSize: (((root.width*0.95) / 3.0) + buttAltHeight)/15;
    property var buttBorderColor: "darkorange";
    property var buttFontHeight: 32;

    Rectangle
    {
        id: firstOne;
        visible: true;
        x: 10;
        y: 10;
        height: 75;

        border.color: "white";
        border.width: 1;

        RowLayout
        {
            width: root.width * 0.95;
            anchors.verticalCenter: parent.verticalCenter;
            spacing: 15;
            /*
            spacing: 10;

            Button
            {
                id: connectButton;
                text: "Połącz";
                font.pixelSize: buttFontHeight;
                width: root.buttWidth;
                height: firstOne.height/ menuRect.scaleX
                background: Rectangle
                {
                    radius: buttRadius
                    border.color: buttBorderColor;
                    border.width: buttBorderWidth;
                    color: buttColor;
                }

                onClicked:
                {
                    if(terminal.isConnected() && text == "Potwierdź")
                    {
                        msgOpenDial.open();
                        text="Odłącz";
                        return;
                        //zmien isConnected!!!
                    }

                    if(!terminal.isConnected() && text == "Potwierdź")
                    {
                        msgCloseDial.open();
                        text="Podłącz";
                        return;
                    }

                    if(terminal.isConnected())
                    {
                        terminal.close();
                        text="Potwierdź";


                    }else
                    {
                        popUpaddr.open();
                        text= "Potwierdź";
                    }

                }
            }
*/



            Button
            {
                text: "Lista Zamówień";
                font.pixelSize: buttFontHeight;
                //width: root.width* 0.95;
                Layout.fillWidth: true;
                height: firstOne.height/ menuRect.scaleX
                background: Rectangle
                {
                    radius: buttRadius
                    border.color: buttBorderColor;
                    border.width: buttBorderWidth;
                    color: buttColor;
                }

                onClicked:
                {
                    popupList.open();
                }
            }

            Button
            {
                text: "🔃";
                hoverEnabled: true
                antialiasing: true
                display: AbstractButton.TextOnly
                font.capitalization: Font.MixedCase
                font.family: "Arial"
                font.pixelSize: 28
                Layout.preferredWidth: 54
                Layout.preferredHeight: 54
                Layout.rightMargin: 5
                implicitWidth: firstOne.height/ menuRect.scaleX;
                implicitHeight: firstOne.height/ menuRect.scaleX;
                background: Rectangle
                {
                    radius: buttRadius
                    border.color: buttBorderColor;
                    border.width: buttBorderWidth;
                    color: buttColor;
                }
                onClicked:
                {
                    popUpaddr.open();
                }
            }
        }
    }

    ListView
    {
        id: menuRect;
        clip: true;
        Layout.alignment: Qt.AlignVCenter;

        y: firstOne.x + firstOne.height + 10;

        width: root.width;
        height: root.height - y;

        model: ListModel
        {
            //Ciasto
            ListElement
            {
                displayText1: "Duże Ciasto"
                sendText1: "DuzCia";
                displayText2: "Małe Ciasto"
                sendText2: "MalCia";
            }

            //Bułka
            ListElement
            {
                displayText1: "Duża Bułka"
                sendText1: "DuzBul";
                displayText2: "Mała Bułka"
                sendText2: "MalBul";
            }

            //Pita
            ListElement
            {
                displayText1: "Duża Pita"
                sendText1: "DuzPit";
                displayText2: "Mała Pita"
                sendText2: "MalPit";
            }

            //Kubełek
            ListElement
            {
                displayText1: "Duży Kubełek"
                sendText1: "DuzKub";
                displayText2: "Mały Kubełek"
                sendText2: "MalKub";
            }

            //Vege po Grecku
            ListElement
            {
                displayText1: "Duże Vege po Grecku"
                sendText1: "DuzGrek";
                displayText2: "Małe Vege po Grecku"
                sendText2: "MalGrek";
            }

            //Vege Kebab
            ListElement
            {
                displayText1: "Vege Kebab Ciasto"
                sendText1: "VegCia";
                displayText2: "Vege Kebab Bułka"
                sendText2: "VegBul";
            }

            //Grill
            ListElement
            {
                displayText1: "Grill Warzywa Ciasto"
                sendText1: "BBQCia";
                displayText2: "Grill Warzywa Bułka"
                sendText2: "BBQBul";
            }

            //Frytki
            ListElement
            {
                displayText1: "Duże Frytki"
                sendText1: "DuzFry";
                displayText2: "Małe Frytki"
                sendText2: "MalFry";
            }

            //Zapiekanka Wiejska i Diabelska
            ListElement
            {
                displayText1: "Zapiekanka Wiejska"
                sendText1: "ZapWie";
                displayText2: "Zapiekanka Diabelska"
                sendText2: "ZapDia";
            }

            //Zapiekanka Vege i Szpinakowa
            ListElement
            {
                displayText1: "Zapiekanka Vege"
                sendText1: "ZapVeg";
                displayText2: "Zapiekanka Szpinakowa"
                sendText2: "ZapSzp";
            }

            //Zapiekanka Dostosowana i Tymczasowe Danie
            ListElement
            {
                displayText1: "Zapiekanka Dostosowana"
                sendText1: "ZapDos";
                displayText2: "Tymczasowa Potrawa"
                sendText2: "Temp";
            }
        }

        property var scaleX: 2.0;
        property var defaultSpacing: 20;

        visible: true;

        delegate: RowLayout
        {
            ColumnLayout
            {
                Row
                {
                    spacing: menuRect.defaultSpacing;

                    Button
                    {
                        text: model.displayText1;
                        font.pixelSize: fontAltSize;
                        width: (root.width*0.95)/ menuRect.scaleX
                        height: root.buttAltHeight;
                        background: Rectangle
                        {
                            radius: buttRadius
                            border.color: buttBorderColor;
                            border.width: buttBorderWidth;
                            color: buttColor;
                        }

                        onClicked:
                        {
                            popupOrder.oPEN(model.sendText1);
                            // popupOrder.close();
                        }
                    }

                    Button
                    {
                        text: model.displayText2;
                        font.pixelSize: fontAltSize;
                        width: (root.width *0.95)/ menuRect.scaleX
                        height: root.buttAltHeight;
                        background: Rectangle
                        {
                            radius: buttRadius
                            border.color: buttBorderColor;
                            border.width: buttBorderWidth;
                            color: buttColor;
                        }

                        onClicked:
                        {
                            popupOrder.oPEN(model.sendText2);
                            // popupOrder.close();
                        }
                    }

                }
                Rectangle
                {
                    Layout.fillWidth: true;
                    implicitHeight: 20;
                    visible: true;
                    color: "#33312F";
                }
            }
        }
    }


    Popup
    {
        id: popupOrder;

        function oPEN(iDishName)
        {
            dishName = iDishName;
            popupOrder.open();
        }

        property var dishName: "Kebab";

        anchors.centerIn: parent;

        background: Rectangle
        {
            id: popRect;
            implicitWidth: buttWidth;
            radius: 20;
            border.width: buttBorderWidth;
            border.color: buttBorderColor;
            color: buttColor;
        }

        onOpened:
        {
            chkB1.currentIndex = 0;
            chkB2.checked = false;
            chkB3.checked = false;
            chkB4.checked = false;
            chkB5.checked = false;
            chkB6.checked = false;
            chkB7.checked = false;
        }

        ColumnLayout
        {
            //anchors.fill: parent
            anchors.centerIn: parent;
            Layout.fillWidth: true;
            Layout.fillHeight: true;

            ComboBox
            {
                id: chkB1;
                currentIndex: 0;
                Layout.fillWidth: true;
                model: ListModel
                {
                    id: cmbItems;
                    ListElement { text: "Brak Sosu"; }
                    ListElement { text: "Mieszany"; }
                    ListElement { text: "Łagodny"; }
                    ListElement { text: "Ostry"; }
                }

            }
            CheckBox { id: chkB2; text: qsTr("Dodatkowe Mięso"); }
            CheckBox { id: chkB3; text: qsTr("Dodatkowe Sałatki"); }
            CheckBox { id: chkB4; text: qsTr("Z Frytkami"); }
            CheckBox { id: chkB5; text: qsTr("Ser"); }
            CheckBox { id: chkB6; text: qsTr("Inne Dodatki"); }
            CheckBox { id: chkB7; text: qsTr("Na Wynos"); }

            Button
            {
                x: popRect.width/9.0;
                width: popRect.width/1.5;
                id: butt1;
                text: qsTr("Akceptuj");
                font.pixelSize: 20;
                Layout.fillWidth: true;

                onClicked:
                {
                    //chkB1.text =chkB1.checked;
                    terminal.newOrder(popupOrder.dishName.toString(), chkB1.currentIndex, chkB2.checked, chkB3.checked, chkB4.checked, chkB5.checked, chkB6.checked, chkB7.checked);
                    popupOrder.close();
                }
            }
        }
    }

    Popup
    {
        id: popupList;
        anchors.centerIn: parent;
        implicitHeight: root.height*0.95;

        background: Rectangle
        {
            id: popListRect;
            implicitWidth: buttWidth;
            radius: 20;
            border.width: buttBorderWidth;
            border.color: buttBorderColor;
            color: buttColor;
        }

        ColumnLayout
        {
            //anchors.fill: parent
            //spacing: 30;
            anchors.centerIn: parent;

            //---------------------
            TransactionHistory {}
            //---------------------

            Button
            {
                x: popRect.width/2.5;
                width: popRect.width/1.5;
                id: butt2;
                text: qsTr("Akceptuj");
                font.pixelSize: 20;
                Layout.fillWidth: true;

                onClicked:
                {
                    popupList.close();
                }
            }
        }
    }

    Popup
    {
        id: popUpaddr;
        anchors.centerIn: parent;

        onOpened:
        {
            visible = true;
        }

        implicitHeight: 220;

        background: Rectangle
        {
            implicitWidth: buttWidth;
            radius: 20;
            border.width: buttBorderWidth;
            border.color: buttBorderColor;
            color: buttColor;
        }

        Layout.fillWidth: true;

        ColumnLayout
        {
            //spacing: 20;
            Layout.fillWidth: true;
            clip: true;
            implicitHeight: 350;
            implicitWidth: parent.width;
            spacing: 20;

            Rectangle
            {
                radius: 5;
                border.width: 1;
                border.color: "gray";
                implicitWidth: parent.width;
                implicitHeight: 60;

                TextField
                {
                    text: "localhost";
                    id: addrTextEdit
                    font.pixelSize: 16;

                    //readOnly: true;
                    //Layout.fillWidth: true;
                    //Layout.fillHeight: true;
                    implicitHeight: parent.height;
                    implicitWidth: parent.width;
                    //anchors.top: checkBox.top;

                    onPressed:
                    {
                        popup1.open();
                    }

                    background: Rectangle
                    {
                        radius: 6;
                        border.width: 1;
                        border.color: "black";
                        Layout.fillWidth: true;
                        //Layout.fillHeight: true;
                    }
                }
            }


            SpinBox
            {
                id: addrSpinBox;

                from: 1024;
                to: 62000;
                value: 12345;

                Layout.fillWidth: true;
            }



            Button
            {
                Layout.fillWidth: true;
                text: "Połącz";
                onClicked:
                {
                    terminal.sync(addrTextEdit.text, addrSpinBox.value);
                    popUpaddr.visible = false;
                    popUpaddr.close();
                }
            }
        }

        MessageDialog
        {
            id: msgOpenDial;
            title: "Info";
            text: "Połączono";
            onAccepted:
            {
                msgOpenDial.close();
            }
        }

        MessageDialog
        {
            id: msgCloseDial;
            title: "Info";
            text: "Rozłączono";
            onAccepted:
            {
                msgOpenDial.close();
            }
        }
    }


}
