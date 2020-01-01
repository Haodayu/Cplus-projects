#ifndef DEFSTRUCT_H
#define DEFSTRUCT_H

#include <iostream>
#include <math.h>
#include <string.h>
using namespace std;

#define MAX_VERTEX_NUM 50
#define PI 3.1415926
#define EARTH_RADIUS 6378.137
#define INF 10000000

typedef struct SiteType {
    int ID;
    double pos[2];
}SiteType;//顶点详细信息


typedef struct ArcNode {
    int adjvex;
    struct ArcNode *nextarc;
    double length;
}ArcNode;//边表节点


typedef struct VNode {
    SiteType info;
    ArcNode *firstarc;
}VNode, AdjList[MAX_VERTEX_NUM];//顶点表节点

typedef struct {
    AdjList vertices;
    int vexnum, arcnum, blanknum;
}ALGraph;//顶点表，即邻接表

typedef struct {
    int start_site;
    int minipath[46][11];
}AllShort;//最短路径表

#endif // DEFSTRUCT_H
