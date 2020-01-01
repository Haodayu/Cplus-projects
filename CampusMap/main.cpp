#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuickControls2>
#include <QQmlContext>
#include "CampusGraph.h"

void Start(CampusGraph &mapres)
{
    int path[][2] = {{0,1},{0,27},{1,2},{2,3},{3,4},{4,5},{5,6},{6,7},{6,45},{7,8},{8,9},{8,42},{9,10},
                     {10,11},{10,38},{10,44},{11,12},{11,39},{12,13},{13,14},{14,15},{15,16},{16,17},
                     {17,18},{18,19},{19,36},{19,20},{20,21},{20,35},{21,22},{21,33},{22,23},{22,24},
                     {22,31},{24,25},{24,29},{25,26},{25,27},{25,28},{28,29},{29,30},{30,31},{31,32},
                     {31,43},{32,33},{32,42},{33,34},{34,35},{35,36},{36,37},{37,38},{37,41},{38,39},
                     {41,40},{41,42},{40,44},{42,43},{45,30},{45,43}};

    int blank_ids[] = {0,1,3,4,5,6,8,10,11,13,15,16,18,19,
                       20,21,22,24,25,27,29,30,32,33,34,35,
                       36,37,38,40,41,42,43,44,45};

    double blank_poses[][2] = {{23.15810217,113.35009396},{23.15806272,113.34903717},
                               {23.15579883,113.34924638},{23.15574458,113.34992766},
                               {23.15508858,113.35053920},{23.15455096,113.35165500},
                               {23.15208479,113.35426211},{23.15305647,113.35725545},
                               {23.15303674,113.35924029},{23.15308606,113.36507141},
                               {23.15539438,113.36503922},{23.15543878,113.36417555},
                               {23.15959661,113.36003959},{23.15624273,113.35718916},
                               {23.15649921,113.35530281},{23.15674089,113.35457324},
                               {23.15681980,113.35367739},{23.15677541,113.35271716},
                               {23.15676062,113.35184812},{23.15679514,113.35098981},
                               {23.15631178,113.35270106},{23.15536479,113.35270106},
                               {23.15536972,113.35454106},{23.15577910,113.35454642},
                               {23.15580869,113.35511505},{23.15612929,113.35527598},
                               {23.15607997,113.35715889},{23.15464468,113.35715889},
                               {23.15402814,113.35718035},{23.15415145,113.35562467},
                               {23.15462495,113.35562467},{23.15466934,113.35455715},
                               {23.15467427,113.35363984},{23.15310086,113.35668683},
                               {23.15464636,113.35266351}};

    mapres.test();

    mapres.initMap(46, 59, 35);

    mapres.enterSiteData(2,23.15722918,113.34911227);
    mapres.enterSiteData(7,23.15230182,113.35188031);
    mapres.enterSiteData(9,23.15229688,113.35725009);
    mapres.enterSiteData(12,23.15309100,113.36261451);
    mapres.enterSiteData(14,23.15396895,113.36511969);
    mapres.enterSiteData(17,23.15970019,113.36382687);
    mapres.enterSiteData(23,23.15758429,113.35358083);
    mapres.enterSiteData(26,23.15713053,113.35183203);
    mapres.enterSiteData(28,23.15648934,113.35186958);
    mapres.enterSiteData(31,23.15532040,113.35365056);
    mapres.enterSiteData(39,23.15398868,113.35909008);
    mapres.enterBlankData(blank_ids,blank_poses);

    mapres.createMap(path);
    mapres.showALGraph();
    mapres.getAllShort();
}

int main(int argc, char *argv[])
{
    CampusGraph mapres;
    Start(mapres);

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Material");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.rootContext()->setContextProperty("mapres", &mapres);
    engine.load(url);

    return app.exec();
}
