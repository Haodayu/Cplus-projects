#include "CampusGraph.h"

void printArray(int array[46][11])
{
    for (int i=0;i<46;i++){
        for (int j=0;j<11;j++){
            printf("%7d",array[i][j]);
        }
        printf("\n");
    }
}

//计算经纬度间距离（m单位）
double getDistance(double lat1, double lng1, double lat2, double lng2)
{
    double radLat1 = lat1*PI/180.0;
    double radLat2 = lat2*PI/180.0;
    double a = radLat1 - radLat2;
    double b = lng1*PI/180.0 - lng2*PI/180.0;

    double dst = 2*asin((sqrt(pow(sin(a/2),2)+cos(radLat1)*cos(radLat2)*pow(sin(b/2),2))));

    dst = dst * EARTH_RADIUS;
    dst= round(dst * 10000) / 10;
    return dst;
}

CampusGraph::CampusGraph(QObject *parent) : QObject(parent){
}

void CampusGraph::initMap(int site_num, int path_num, int blank_num) {
    G->vexnum = site_num;
    G->arcnum = path_num;
    G->blanknum = blank_num;
}

void CampusGraph::test() {
    cout << "ALL IS OK." << endl;
}

void CampusGraph::enterSiteData(int id, double xpos, double ypos) {
    sites[id].ID = id;
    sites[id].pos[0] = xpos;
    sites[id].pos[1] = ypos;
}

void CampusGraph::enterBlankData(int ids[], double poses[][2]) {
    int id;
    for (int i =0; i<G->blanknum; i++) {
        id = ids[i];
        sites[id].ID = id;
        sites[id].pos[0] = poses[i][0];
        sites[id].pos[1] = poses[i][1];
    }
}

//创建地图
void CampusGraph::createMap(int path[][2]) {
    ArcNode *tempnode;
    //读入顶点信息，建立顶点表
    for (int i = 0; i < G->vexnum; i++) {
        //读入顶点信息
        G->vertices[i].info = sites[i];
        //将边表置为空表
        G->vertices[i].firstarc = NULL;
    }

    for (int n = 0; n < G->arcnum; n++) {
        int i,j;
        i = path[n][0];
        j = path[n][1];
        float length = getDistance(sites[i].pos[0],sites[i].pos[1],sites[j].pos[0],sites[j].pos[1]);

        tempnode = new ArcNode;
        tempnode->length = length;
        tempnode->adjvex = j;
        tempnode->nextarc = G->vertices[i].firstarc;
        G->vertices[i].firstarc = tempnode;

        tempnode = new ArcNode;
        tempnode->length = length;
        tempnode->adjvex = i;
        tempnode->nextarc = G->vertices[j].firstarc;
        G->vertices[j].firstarc = tempnode;
    }
}

void CampusGraph::showALGraph() {
    ArcNode *p;
    for (int i = 0; i < G->vexnum; i++)
    {
        cout << "Node " << i << ":";
        p = new ArcNode;
        p = G->vertices[i].firstarc;
        while (p)
        {
            cout << " --(" << p->length << ")--> [" << p->adjvex << "]";
            p = p->nextarc;
        }
        cout << " --> NULL" << endl;
    }
}

void CampusGraph::dijkstra(int start, int minipath[][11])
{
    //初始化最短路径长度的数组disk，INF是个极大值
    //初始化最短路径路线的数组path,[i][0]为标记是否已为最短
    //[i][j]表示从原点开始到第i点的第j个中途点是什么，-1代表终止
    int i,j,mindist,k=0,t;
    int disk[G->vexnum];
    int path[G->vexnum+1][G->vexnum];
    memset(path,-1,sizeof(path));
    ArcNode *p;

    for (i=0; i<G->vexnum; i++) {
        disk[i] = INF;
        path[0][i] = 0;
    }

    p = G->vertices[start].firstarc;
    //保存源点直接相连顶点的路径.
    while (p) {
        disk[p->adjvex] = p->length;
        path[1][p->adjvex] = start;
        path[2][p->adjvex] = p->adjvex;
        path[3][p->adjvex] = -1;
        p = p->nextarc;
    }
    //源点已为最短，标记为1
    path[0][start] = 1;
    disk[start] = 0;

    //寻找其余n-1个点的最短路径
    for (i=1; i<G->vexnum; i++) {
        mindist = INF;
        //找出现阶段从起点出发最短的点中，path[j][0]还未锁定，可以调用的点k
        for (j=0; j<G->vexnum; j++) {
            if (!path[0][j] && disk[j]<mindist) {
                k = j;
                mindist = disk[j];
            }
        }
        //如果没有找到，则说明已经无路，直接返回.
        if (mindist == INF) return;
        //标记找到最小路径的顶点，并锁定
        path[0][k] = 1;


        //以k为起点，继续寻找直接相连的最短路径点
        p = G->vertices[k].firstarc;
        while (p) {
            if (!path[0][p->adjvex] && disk[p->adjvex]>disk[k]+p->length) {
                disk[p->adjvex] = disk[k]+p->length;
                t = 1;
                while (path[t][k]!=-1) {      //复制k的路径
                    path[t][p->adjvex] = path[t][k];
                    t++;
                }
                path[t][p->adjvex] = p->adjvex;
                path[t+1][p->adjvex] = -1;   //结尾
            }
            p=p->nextarc;
        }
    }

    for (i = 0; i<(G->vexnum-G->blanknum); i++) {
        minipath[0][i] = disk[realsites[i]];
    }
    for (i = 0; i<(G->vexnum-G->blanknum); i++) {
        for (j = 1; j<G->vexnum; j++) {
            minipath[j][i] = path[j][realsites[i]];
        }
    }
}

void CampusGraph::getAllShort()
{
    for (int i = 0; i<G->vexnum-G->blanknum; i++) {
        minipaths[i].start_site = realsites[i];
        dijkstra(realsites[i],minipaths[i].minipath);
    }
}


QVariantList CampusGraph::getPath(int start, int end) {
    QVariantList path;
    int pass,n=0;
    pass = minipaths[start].minipath[n][end];
    while (pass!=-1) {
        path.append(pass);
        pass = minipaths[start].minipath[++n][end];
    }
    return path;
}

QVariantList CampusGraph::getXY(int id) {
    QVariantList poss;
    double x = (sites[id].pos[1]-113.34458470)*45103;
    double y = (23.16488374-sites[id].pos[0])*48000;
    poss.append(x);
    poss.append(y);
    return poss;
}
