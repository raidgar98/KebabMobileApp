#include <QGuiApplication>
#include <QQmlApplicationEngine>

//To trzeba dodać
#include <QQmlEngine>
#include <QQmlContext>
#include <QQmlComponent>

#include "telnetadapter.h"
#include "translist.h"
#include "transmodel.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<TransModel>("Trans", 1, 0, "TransModel");
    qmlRegisterUncreatableType<TransList>("Trans", 1, 0, "TransList", QStringLiteral("TransList cannot be created in QML"));

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    TransList * transList = new TransList();
    QScopedPointer<TelnetAdapter> terminal(new TelnetAdapter(transList));

    TelnetAdapter::formatNum(6);

    //Dodawanie właściwości
    engine.rootContext()->setContextProperty("terminal", terminal.data());
    engine.rootContext()->setContextProperty("transList", transList);

    engine.load(url);

    return app.exec();
}
