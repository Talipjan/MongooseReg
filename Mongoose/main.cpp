#include <QObject>
#include <QtWidgets/QApplication>
#include <QtQml/QQmlEngine>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick/qquickview.h>
#include <QQmlContext.h>
#include <QVector>
#include "channelmodel.h"
#include "th_device.h"


int main(int argc, char *argv[])
{
   QApplication app(argc, argv);
//   QGuiApplication app(argc, argv);
   //ChannelList  *vChannelList  = new ChannelList();
   //PlanshClass  *vPlanshClass  = new PlanshClass;
   //ChannelModel *vChannelModel = new ChannelModel;
   //QQuickView view;
   Th_device DevMonggose;
   //QObject::connect(&app, SIGNAL(Quit()), &DevMonggose, SLOT(ThDone()));
   DevMonggose.start(QThread::NormalPriority);
   //view.rootContext()->setContextProperty("ChannelList", vChannelList);
   //view.rootContext()->setContextProperty("PlanshClass", vPlanshClass);
   //QObject::connect(&DevMonggose, SIGNAL(ThDataReadyHid(QVector<int>)), vChannelModel, SLOT(setData(const QVector<int>)));
   qmlRegisterType<ChannelModel>("Mongoose_Model", 1, 0, "ChannelModel");
   qmlRegisterType<ChElement>("Mongoose_Model", 1, 0, "ChElement");
   qmlRegisterType<AreaDraw>("Mongoose_Model", 1, 0, "AreaDraw");
//   view.rootContext()->setContextProperty("dataModel", DevMonggose.getChannelModel());

//   view.setSource(QUrl("qrc:main.qml"));
//   view.setSource(QUrl("qrc:ConfigChannel.qml"));
//   view.setWidth(500);
//   view.setHeight(500);
//   view.show();



   QQmlApplicationEngine engine;
   engine.rootContext()->setContextProperty("dataModel", DevMonggose.getChannelModel());
   engine.rootContext()->setContextProperty("applicationDirPath", QApplication::applicationDirPath());
   engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
   if (engine.rootObjects().isEmpty())
      return -1;

   //QObject::connect(&DevMonggose,SIGNAL(ThDataReadyHid(QVector<int>)),&ChannelModel,SLOT(setData(QVector<int>)));
   app.exec();

   DevMonggose.ThDone();
   return 0;
}
