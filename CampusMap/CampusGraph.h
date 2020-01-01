#ifndef CAMPUSGRAPH_H
#define CAMPUSGRAPH_H

#include <QObject>
#include <QMap>
#include <QVariant>
#include <QVariantList>
#include "DefStruct.h"

class CampusGraph: public QObject
{
    Q_OBJECT
public:
    explicit CampusGraph(QObject *parent = nullptr);

    void test();
    void enterSiteData(int id, double xpos, double ypos);
    void enterBlankData(int ids[], double poses[][2]);
    //初始化地图
    void initMap(int site_num, int path_num, int blank_num);
    //创建地图
    void createMap(int path[][2]);
    //打印地图
    void showALGraph();
    //计算源点到各景点之间最短路径
    void dijkstra(int start, int minipath[][11]);
    //输出所有景点之间的最短路径
    void getAllShort();

    Q_INVOKABLE QVariantList getPath(int start, int end);
    Q_INVOKABLE QVariantList getXY(int id);

private:
    AllShort minipaths[11];
    ALGraph *G = new ALGraph;
    SiteType sites[46];
    int realsites[11] = {2,7,9,12,14,17,23,26,28,31,39};
};

#endif // CAMPUSGRAPH_H
