#include <QGuiApplication>
#include <QQmlApplicationEngine>

//To trzeba dodać
#include <QQmlEngine>
#include <QQmlContext>
#include <QQmlComponent>

#include "telnetadapter.h"
#include "translist.h"
#include "transmodel.h"
#include "productmodel.h"
#include "productlist.h"

#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>
#include <QStandardPaths>

int main(int argc, char *argv[])
{

	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName(QStandardPaths::writableLocation(QStandardPaths::DownloadLocation) + R"(/dataBase)");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<TransModel>("Trans", 1, 0, "TransModel");
    qmlRegisterUncreatableType<TransList>("Trans", 1, 0, "TransList", QStringLiteral("TransList cannot be created in QML"));

	qmlRegisterType<productModel>("Product", 1 ,0, "ProductModel");
	qmlRegisterUncreatableType<ProductList>("Product", 1, 0, "ProductList", QStringLiteral("productList cannot be created"));


    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

	QScopedPointer<TransList> transList(new TransList());
	QScopedPointer<ProductList> productList(new ProductList(&db));
	QScopedPointer<TelnetAdapter> terminal(new TelnetAdapter(&db, transList.data()));

    TelnetAdapter::formatNum(6);

    //Dodawanie właściwości
    engine.rootContext()->setContextProperty("terminal", terminal.data());
	engine.rootContext()->setContextProperty("transList", transList.data());
	engine.rootContext()->setContextProperty("productList", productList.data());

    engine.load(url);

    return app.exec();
}
