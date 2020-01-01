import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle {
    id: showImg;
    width: 1280;
    height: 720;
    color: "transparent";

    Image {
        id: testmap;
        source: "/images/map.jpg"
        asynchronous: true;
        cache: false;
        anchors.fill: parent;
        fillMode: Image.PreserveAspectCrop;
    }

    property double scaleValue: 1.05;

    function zoomIn(x,y){
        var beforeWidth  = showImg.width;
        var beforeHeight = showImg.height;
        showImg.width = showImg.width   * scaleValue;
        showImg.height = showImg.height * scaleValue;
        showImgMouseArea.width = showImg.width;
        showImgMouseArea.height = showImg.height;

        showImg.x = showImg.x + x - showImg.width  * x / beforeWidth;
        showImg.y = showImg.y + y - showImg.height * y / beforeHeight;
    }

    function zoomOut(x,y){
        var beforeWidth  = showImg.width;
        var beforeHeight = showImg.height;
        showImg.width = showImg.width   / scaleValue;
        showImg.height = showImg.height / scaleValue;
        showImgMouseArea.width = showImg.width;
        showImgMouseArea.height = showImg.height;
        showImg.x = showImg.x + x - showImg.width  * x / beforeWidth;
        showImg.y = showImg.y + y - showImg.height * y / beforeHeight;
    }


     MouseArea{
         id: showImgMouseArea;
         anchors.fill: showImg;
         drag.target: showImg;
         drag.axis: Drag.XAndYAxis;
         hoverEnabled: true;
         onWheel: {
             if(wheel.angleDelta.y>0&&showImg.width<=1280*scaleValue**20){//图像放大处理
                 showImg.transformOriginPoint.x = wheel.x;
                 showImg.transformOriginPoint.y = wheel.y;
                 zoomIn(wheel.x,wheel.y);
             }
             else if(wheel.angleDelta.y<0&&showImg.width>=1280){//图像缩小处理
                 showImg.transformOriginPoint.x = wheel.x;
                 showImg.transformOriginPoint.y = wheel.y;
                 zoomOut(wheel.x,wheel.y);
             }
             if (!winClear) {
                 paintroot.paintPath();
             }
         }
     }
}
