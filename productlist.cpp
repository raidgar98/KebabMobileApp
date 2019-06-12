#include "productlist.h"
#include <QVariant>
#include <QtSql/QSqlRecord>

ProductList::ProductList(QSqlDatabase * srcDb, QObject *parent) : QObject(parent)
{

	db = srcDb;

	db->open();

	QSqlQuery q("SELECT COUNT(*) FROM prices;");
	QSqlQuery q1("SELECT * FROM prices WHERE idPrice=1;");
	q.exec();
	q1.exec();

	db->close();

	q.next();
	q1.next();

	const quint16 count = static_cast<quint16>(q.value(0).toInt());
	quint16 row = 0;

	const quint8 name = static_cast<quint8>(q1.record().indexOf("name"));
	const quint8 fullName = static_cast<quint8>(q1.record().indexOf("fullName"));

	bool flagEmpty = false;

	while(row != count)
	{
		row++;
		QString baseQuerry = "SELECT * FROM prices WHERE idPrice=::0 AND isExtra='false';";
		baseQuerry = baseQuerry.replace("::0", QString::number(row));
		db->open();
		QSqlQuery q2(baseQuerry);
		q2.exec();
		db->close();
		q2.next();
		if(q2.value(0).isNull()) continue;

		QSqlQuery q3;

		do
		{
			row++;
			QString baseQuerry2 = "SELECT * FROM prices WHERE idPrice=::0 AND isExtra='false';";
			baseQuerry2 = baseQuerry2.replace("::0", QString::number(row));
			db->open();
			q3.prepare(baseQuerry2);
			q3.exec();
			db->close();
			q3.next();

			if(row == count) break;

		}while(q3.value(0).isNull());

		if(q3.value(0).isNull())
		{
			for(auto var : mItems)
			{
				if(var.SecondShort == "Temp")
				{
					var.SecondShort = q2.value(name).toString();
					var.Second = q2.value(fullName).toString();
					flagEmpty = false;
					return;

				}else flagEmpty = true;
			}
		}

		productListItem temp;
		temp.First = q2.value(fullName).toString();
		temp.FirstShort = q2.value(name).toString();
		temp.Second = flagEmpty ? "ERROR" : q3.value(fullName).toString();
		temp.SecondShort = flagEmpty ? "Temp" : q3.value(name).toString();

		mItems.append(temp);
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
