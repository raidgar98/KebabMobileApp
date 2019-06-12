#pragma once

#include <QObject>
#include <QVector>

#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>

struct productListItem
{
	QString First;
	QString Second;
	QString FirstShort;
	QString SecondShort;
};

class ProductList : public QObject
{
	Q_OBJECT

public:

	explicit ProductList(QSqlDatabase * srcDb, QObject *parent = nullptr);

	QSqlDatabase * db;

	QVector<productListItem> items() const;

	bool setItemAt(int index, const productListItem& item);

signals:

//	void preProductAppend();
//	void postProductAppend();

public slots:

//	void appendItem();

private:

	QVector<productListItem> mItems;

};

