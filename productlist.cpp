#include "productlist.h"
#include <QVariant>
#include <QtSql/QSqlRecord>
#include <list>

struct simple
{
	QString arg1, arg2;
};

ProductList::ProductList(QSqlDatabase * srcDb, QObject *parent) : QObject(parent)
{

	db = srcDb;

	db->open();

	QSqlQuery q("SELECT COUNT(*) FROM prices;");
	QSqlQuery q1("SELECT name, fullName FROM prices WHERE idPrice=1;");
	q.exec();
	q1.exec();

	db->close();

	q.next();
	q1.next();

	const int count = q.value(0).toInt();
	quint16 row = 0;

	const quint8 name = static_cast<quint8>(q1.record().indexOf("name"));
	const quint8 fullName = static_cast<quint8>(q1.record().indexOf("fullName"));

	std::list<simple> found;

	do
	{

		row++;
		QString querTemplate = "SELECT name, fullName FROM prices WHERE idPrice=::1 AND isExtra='false';";
		querTemplate = querTemplate.replace("::1", QString::number(row));
		db->open();
		QSqlQuery quer(querTemplate);
		quer.exec();
		db->close();
		quer.next();
		if(quer.isNull(0)) continue;
		found.push_back({quer.value(name).toString(), quer.value(fullName).toString()});

	}while(row != count);


	if(found.size() % 2 != 0)
	{
		for(auto var = found.begin(); var != found.end(); var++)
		{
			if(var->arg1 == "Temp")
			{
				found.erase(var);
				break;
			}
		}
	}

	for(auto var = found.begin(); var != found.end(); var++)
	{
		auto temp = var;
		var++;
		mItems.append({temp->arg2, var->arg2, temp->arg1, var->arg1});
	}

	/*
	mItems.append({QStringLiteral("Kebab"), QStringLiteral("Pita"), QStringLiteral("MalCia"), QStringLiteral("MalCia")});
	mItems.append({QStringLiteral("Vege"), QStringLiteral("Nie vege"), QStringLiteral("MalCia"), QStringLiteral("MalCia")});
	*/
}

QVector<productListItem> ProductList::items() const
{
	return	mItems;
}

bool ProductList::setItemAt(int index, const productListItem & item)
{
	if(index < 0 || index >= mItems.size()) return false;

	const productListItem &oldItem = mItems.at(index);
	if(oldItem.First == item.First && oldItem.Second == item.Second) return false;

	mItems[index] = item;
	return true;

}
/*
void ProductList::appendItem()
{
	emit preProductAppend();

	productListItem item;
	item.First = "Kebab";
	item.Second = "Pita";
	mItems.append(item);

	emit postProductAppend();
}
*/
