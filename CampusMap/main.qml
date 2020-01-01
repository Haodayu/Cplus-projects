import QtQuick.Window 2.12
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.4

Window {
    id: root;
    visible: true;
    width: 1280;
    height: 720;
    color: '#e5e5e5';
    title: qsTr("SCAU导游地图");

    property var path;
    property var tempWidth;
    property var tempHeight;
    property var tempX;
    property var tempY;
    property var pathLength;
    property int walkTime;
    property int bikeTime;
    property var winClear: true;

    MapRoot {
        id: showImg;
        z: 2;
    }

    PopRec {
        id: s2;
        siteX: 0.190;
        siteY: 0.512;
        winurl: "/images/2.png";
        picurl: "/images/2pic.png";
    }
    PopRec {
        id: s7;
        siteX: 0.264;
        siteY: 0.818;
        winurl: "/images/7.png";
        picurl: "/images/7pic.png";
    }
    PopRec {
        id: s9;
        siteX: 0.458;
        siteY: 0.822;
        add: 0.7;
        winurl: "/images/9.png";
        picurl: "/images/9pic.png";
    }
    PopRec {
        id: s12;
        siteX: 0.653;
        siteY: 0.778;
        add: 0.7;
        winurl: "/images/12.png";
        picurl: "/images/12pic.png";
    }
    PopRec {
        id: s14;
        siteX: 0.710;
        siteY: 0.723;
        add: 0.6;
        winurl: "/images/14.png";
        picurl: "/images/14pic.png";
    }
    PopRec {
        id: s17;
        siteX: 0.677;
        siteY: 0.347;
        winurl: "/images/17.png";
        picurl: "/images/17pic.png";
    }
    PopRec {
        id: s23;
        siteX: 0.330;
        siteY: 0.473;
        winurl: "/images/23.png";
        picurl: "/images/23pic.png";
    }   
    PopRec {
        id: s26;
        siteX: 0.268;
        siteY: 0.512;
        winurl: "/images/26.png";
        picurl: "/images/26pic.png";
    }
    PopRec {
        id: s28;
        siteX: 0.268;
        siteY: 0.575;
        winurl: "/images/28.png";
        picurl: "/images/28pic.png";
    }
    PopRec {
        id: s31;
        siteX: 0.330;
        siteY: 0.607;
        winurl: "/images/31.png";
        picurl: "/images/31pic.png";
    }
    PopRec {
        id: s39;
        siteX: 0.527;
        siteY: 0.692;
        winurl: "/images/39.png";
        picurl: "/images/39pic.png";
    }

    SearchRec {
        id: searchrec;
        anchors.left: parent.left;
        anchors.leftMargin: 30;
        anchors.top: parent.top;
        anchors.topMargin: 30;
        z: 9;
    }

    Image {
        id: ns;
        source: "images/ns.png";
        anchors.left: parent.left;
        anchors.leftMargin: 30;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 10;
        z: 9;

        layer.enabled: true;
        layer.effect: DropShadow {
            horizontalOffset: 5;
            verticalOffset: 5;
            radius: 25;
            samples: 40;
            color: "#20000000";
        }
    }

    Canvas {
        id: paintroot;
        width: showImg.width;
        height: showImg.height;
        anchors.top: showImg.top;
        anchors.topMargin: showImg.width*2/1280;
        anchors.left: showImg.left;
        anchors.leftMargin: showImg.width*15/1280;
        contextType:"2d";
        z: 3;

        function paintPath() {
            paintroot.clearPath();
            paintroot.requestPaint();
            var ctx = getContext("2d");
            ctx.lineWidth = showImg.height/140;
            ctx.lineJoin = "round"
            ctx.strokeStyle = "#f84855";
            ctx.font = "42px sans-serif";

            for (var i in path) {
                if (i>1) {
                    ctx.beginPath();
                    var xy01 =  mapres.getXY(path[i-1]);
                    var xy02 =  mapres.getXY(path[i]);
                    ctx.moveTo(xy01[0]*showImg.width/1280,xy01[1]*showImg.height/720);
                    ctx.lineTo(xy02[0]*showImg.width/1280,xy02[1]*showImg.height/720);
                    ctx.closePath();
                    ctx.fill();
                    ctx.stroke();
                }
            }
        }

        function clearPath() {
            paintroot.requestPaint();
            var ctx = getContext("2d");
            ctx.reset();
        }
    }

    PropertyAnimation {
        id: scaleAllAni01;
        target: showImg;
        duration: 300;
        easing.type: Easing.InCurve;
        property: 'width';
        to: tempWidth;
    }

    PropertyAnimation {
        id: scaleAllAni02;
        target: showImg;
        duration: 300;
        easing.type: Easing.InCurve;
        property: 'height';
        to: tempHeight;
    }

    PropertyAnimation {
        id: scaleAllAni03;
        target: showImg;
        duration: 300;
        easing.type: Easing.InCurve;
        property: 'x';
        to: tempX;
    }

    PropertyAnimation {
        id: scaleAllAni04;
        target: showImg;
        duration: 300;
        easing.type: Easing.InCurve;
        property: 'y';
        to: tempY;
    }

    function scaleAll(x1,y1,x2,y2) {
        var bestx = 860;
        var besty = 360;
        var topScale = showImg.scaleValue**20;
        var tempValue = Math.min(700/Math.abs(x1-x2),650/Math.abs(y1-y2));
        tempWidth = showImg.width  * tempValue;
        tempHeight = showImg.height * tempValue;
        if (tempWidth > 1280*topScale) {
            tempWidth = 1280*topScale;
            tempHeight = 720*topScale;
        }
        tempX = -(x1+x2)*tempWidth/(showImg.width*2) + bestx;
        tempY = -(y1+y2)*tempHeight/(showImg.height*2) + besty;
        scaleAllAni01.start();
        scaleAllAni02.start();
        scaleAllAni03.start();
        scaleAllAni04.start();
        timer.start();
    }

    Timer {
        id: timer;
        interval: 300;
        repeat: false;
        onTriggered: {
            paintroot.paintPath();
        }
    }

    Image {
        id: infowin;
        opacity: 0;
        layer.enabled: true;
        layer.effect: DropShadow {
            horizontalOffset: 5;
            verticalOffset: 5;
            radius: 25;
            samples: 40;
            color: "#20000000";
        }

        PropertyAnimation {
            id: animFadeIn;
            target: infowin;
            duration: 400;
            easing.type: Easing.InCurve;
            property: 'opacity';
            from: 0;
            to: 1;
        }
        PropertyAnimation {
            id: animFadeOut;
            target: infowin;
            duration: 300;
            easing.type: Easing.OutCurve;
            property: 'opacity';
            from: 1;
            to: 0;
        }
        z: 8;
    }

}

