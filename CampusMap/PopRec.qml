import QtQuick 2.12
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.12

Rectangle {
    property string winurl;
    property string picurl;
    property double siteX;
    property double siteY;
    property double add: 1;

    width: showImg.width/40;
    height: width;
    anchors.top: showImg.top;
    anchors.left: showImg.left;
    anchors.topMargin: siteY*showImg.height-width/2;
    anchors.leftMargin: siteX*showImg.width-width/2;

    id: poproot;
    color: 'transparent';
    z: 7;

    Image {
        id: poppic;
        source: picurl;
        width: showImg.width/(30*add);
        height: width;
        anchors.horizontalCenter: poproot.horizontalCenter;
        anchors.verticalCenter: poproot.verticalCenter;

        PropertyAnimation {
            id: picBig;
            target: poppic;
            duration: 100;
            easing.type: Easing.InCurve;
            property: 'scale';
            to: 1.3;
        }
        PropertyAnimation {
            id: picSmall;
            target: poppic;
            duration: 100;
            easing.type: Easing.InCurve;
            property: 'scale';
            to: 1;
        }
    }

    Rectangle {
        id: popcircle;
        width: 0;
        height: width;
        radius: width/2;
        border.color: "white";
        border.width: width;
        color: "transparent";
        opacity: 0;

        Component.onCompleted: {
            var docRoot = popcircle.parent;
            while(docRoot.parent) {
                docRoot = docRoot.parent;
            }
            popcircle.parent = docRoot;
            popcircle.z = 10;
        }
        PropertyAnimation {
            id: circleBig;
            target: popcircle;
            duration: 750;
            easing.type: Easing.InCurve;
            property: 'width';
            from: 0;
            to: 3000;
        }
        PropertyAnimation {
            id: circleSmall;
            target: popcircle;
            duration: 750;
            easing.type: Easing.OutCurve;
            property: 'border.width';
            from: 1500;
            to: 0;
        }
        MouseArea {
            id: circlearea;
            propagateComposedEvents: true;
            anchors.fill: popcircle;
            hoverEnabled: true;
            onClicked: {
                circleSmall.start();
                circlearea.visible = false;
            }
        }
    }

    MouseArea {
        id: area;
        propagateComposedEvents: true;
        anchors.fill: poproot;
        hoverEnabled: true;
        onEntered: {
            infowin.anchors.horizontalCenter = poproot.horizontalCenter;
            infowin.anchors.bottom = poproot.top;
            infowin.anchors.bottomMargin = 15;
            infowin.source = winurl;
            animFadeIn.start();
            picBig.start();
        }
        onExited: {
            animFadeOut.start();
            picSmall.start();
        }
        /*
        onClicked: {
            popcircle.anchors.horizontalCenter = poproot.horizontalCenter;
            popcircle.anchors.verticalCenter = poproot.verticalCenter;
            circleBig.start();
            circlearea.visible = true;
        }*/
    }

}
