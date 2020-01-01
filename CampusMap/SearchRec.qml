import QtQuick 2.12
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.12
import QtQuick.Controls 1.4 as QC14
import QtQuick.Controls.Styles 1.4 as QCS14
import QtQuick.Controls.Material 2.1

Item {
    Rectangle {
        id: search_root;
        width: 430;
        height: 60;
        color: "white";

        layer.enabled: true;
        layer.effect: DropShadow {
            horizontalOffset: 5;
            verticalOffset: 5;
            radius: 25;
            samples: 40;
            color: "#20000000";
        }

        Text {
            text: "From";
            color: "#00a0e9";
            anchors.left: parent.left;
            anchors.leftMargin: 10;
            anchors.verticalCenter: parent.verticalCenter;

            font.family: "微软雅黑";
            font.pixelSize: 24;
            font.bold: true;
        }

        Text {
            text: "To";
            color: "#00a0e9";
            anchors.right: end_text.left;
            anchors.verticalCenter: parent.verticalCenter;
            anchors.rightMargin: 8;

            font.family: "微软雅黑";
            font.pixelSize: 24;
            font.bold: true;
        }

        ComboBox {
            id: start_text;
            width: 120;
            height: 30;
            anchors.left: parent.left;
            anchors.leftMargin: 78;
            anchors.top: parent.top;
            anchors.topMargin: 15;
            Material.accent: "#00a0e9";
            font.family: "微软雅黑";
            editable: true;
            model: ListModel {
                id: model;
                ListElement { text: qsTr("校史馆");}
                ListElement { text: qsTr("正门");}
                ListElement { text: qsTr("华农牌坊");}
                ListElement { text: qsTr("紫荆桥");}
                ListElement { text: qsTr("运动场");}
                ListElement { text: qsTr("涂鸦隧道");}
                ListElement { text: qsTr("图书馆");}
                ListElement { text: qsTr("博物馆");}
                ListElement { text: qsTr("红满堂");}
                ListElement { text: qsTr("行政楼");}
                ListElement { text: qsTr("树木园");}
            }
        }

        ComboBox {
            id: end_text;
            width: 120;
            height: 30;
            anchors.left: start_text.right;
            anchors.leftMargin: 40;
            anchors.top: parent.top;
            anchors.topMargin: 15;
            Material.accent: "#00a0e9";
            font.family: "微软雅黑";
            editable: true;
            model: model;
        }
    }

    QC14.Button {
        id: search_Button;
        anchors.top: search_root.top;
        anchors.right: search_root.right;

        property string nomerPic: "images/search_normal.png";
        property string hoverPic: "images/search_hover.png";
        property string pressPic: "images/search_hover.png";

        style: QCS14.ButtonStyle {
            background: Rectangle {
                implicitHeight: 60;
                implicitWidth:  60;
                color: "transparent";
                BorderImage{
                    anchors.fill: parent
                    source: control.hovered ? (control.pressed ? search_Button.pressPic : search_Button.hoverPic) : search_Button.nomerPic;
                }
            }
        }
        onClicked: {
            winClear = false;
            search_down.start();
            upIn.start();
            path = mapres.getPath(start_text.currentIndex,end_text.currentIndex);
            pathLength = path[0];
            walkTime = pathLength/90;
            bikeTime = pathLength/250;
            var xy01 =  mapres.getXY(path[1]);
            var xy02 =  mapres.getXY(path[path.length-1]);
            scaleAll(xy01[0]*showImg.width/1280,xy01[1]*showImg.height/720,xy02[0]*showImg.width/1280,xy02[1]*showImg.height/720);
        }
    }

    Rectangle {
        id: res_root;
        width: 370;
        height: 0;
        color: "white";
        anchors.top: search_root.bottom;
        anchors.topMargin: 10;
        anchors.left: search_root.left;

        Image {
            id: res_length01;
            source: "/images/res01.png";
            width: 110;
            height: 110;
            anchors.top: parent.top;
            anchors.topMargin: -10;
            anchors.left: parent.left;
            anchors.leftMargin: 16;
            opacity: 0.36;
        }

        Text {
            id: res_length02;
            text: qsTr(pathLength+"m");
            color: "#00a0e9";
            font.pixelSize: 60;
            anchors.top: parent.top;
            anchors.right: parent.right;
            anchors.topMargin: 12;
            anchors.rightMargin: 32;
            font.family: "微软雅黑";
            font.bold: true;
        }

        Rectangle {
            id: res_line;
            width: 340;
            height: 3;
            color: "#00a0e9";
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.top: parent.top;
            anchors.topMargin: 90;
        }

        Image {
            id: res_time01;
            source: "/images/res02.png";
            width: 70;
            height: 70;
            anchors.top: res_line.bottom;
            anchors.topMargin: -6;
            anchors.left: parent.left;
            anchors.leftMargin: 20;
        }
        Image {
            id: res_time02;
            source: "/images/res03.png";
            width: 45;
            height: 45;
            anchors.top: res_line.bottom;
            anchors.topMargin: 8;
            anchors.left: parent.left;
            anchors.leftMargin: 195;
        }
        Text {
            id: res_time03;
            text: walkTime;
            color: "#00a0e9";
            font.pixelSize: 36;
            anchors.top: res_line.bottom;
            anchors.topMargin: 10;
            anchors.left: res_time01.right;
            anchors.leftMargin: -13;
            font.family: "微软雅黑";
        }
        Text {
            id: res_time04;
            text: bikeTime;
            color: "#00a0e9";
            font.pixelSize: 36;
            anchors.top: res_line.bottom;
            anchors.topMargin: 10;
            anchors.right: parent.right;
            anchors.rightMargin: 100;
            font.family: "微软雅黑";
        }
        Text {
            id: res_time05;
            text: qsTr("min");
            color: "#00a0e9";
            font.pixelSize: 30;
            anchors.top: res_line.bottom;
            anchors.topMargin: 15;
            anchors.left: res_time03.right;
            anchors.leftMargin: 3;
            font.family: "微软雅黑";
        }
        Text {
            id: res_time06;
            text: qsTr("min");
            color: "#00a0e9";
            font.pixelSize: 30;
            anchors.top: res_line.bottom;
            anchors.topMargin: 15;
            anchors.left: res_time04.right;
            anchors.leftMargin: 3;
            font.family: "微软雅黑";
        }


        layer.enabled: true;
        layer.effect: DropShadow {
            horizontalOffset: 5;
            verticalOffset: 5;
            radius: 25;
            samples: 40;
            color: "#20000000";
        }

        Image {
            id: button_up;
            source: "/images/up.png";
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.bottom: parent.bottom;
            anchors.bottomMargin: 5;
            width: 30;
            height: 10;
            opacity: 0;

            PropertyAnimation {
                id: upIn;
                target: button_up;
                duration: 500;
                easing.type: Easing.InCurve;
                property: 'opacity';
                to: 1;
            }
            PropertyAnimation {
                id: upOut;
                target: button_up;
                duration: 200;
                easing.type: Easing.InCurve;
                property: 'opacity';
                to: 0;
            }

            MouseArea {
                id: uparea;
                propagateComposedEvents: true;
                anchors.fill: button_up;
                hoverEnabled: true;
                onClicked: {
                    winClear = true;
                    search_up.start();
                    upOut.start();
                    paintroot.clearPath();
                }
            }
        }

        PropertyAnimation{
            id: search_down;
            target: res_root;
            properties: "height";
            to: 180;
            duration: 700;
            easing.type: Easing.InOutQuad;
        }

        PropertyAnimation{
            id: search_up;
            target: res_root;
            properties: "height";
            to: 0;
            duration: 600;
            easing.type: Easing.InOutQuad;
        }
    }
}
