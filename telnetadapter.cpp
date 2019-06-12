#include "telnetadapter.h"
#include "translist.h"

#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QtQuickControls2/QtQuickControls2>
#include <QStandardPaths>
#include <fstream>
//#include <iostream>


#define cout qDebug()

QString TelnetAdapter::formatNum(const size_t arg) noexcept
{
	QString num = QString::number(arg);
	QString zeros = "";
	for(int i =0; i < 7 - num.length(); i++)
	{
		zeros += "0";
	}

	zeros += num;

	return zeros;
}

void TelnetAdapter::setBooleans(QString& src, quint8 & souce, bool & meat, bool & salad, bool & fries, bool & cheese, bool & other, bool & takeaway) noexcept
{
	QQueue<quint8> q;

	for(int i = 8; i < src.length(); i++)
		if(src[i].isDigit()) q.push_back(QString(src[i]).toUInt());

	souce = q.front(); q.pop_front();
	meat = static_cast<bool>(q.front()); q.pop_front();
	salad = static_cast<bool>(q.front()); q.pop_front();
	fries = static_cast<bool>(q.front()); q.pop_front();
	cheese = static_cast<bool>(q.front()); q.pop_front();
	other = static_cast<bool>(q.front()); q.pop_front();
	takeaway = static_cast<bool>(q.front()); q.pop_front();
}

TelnetAdapter::TelnetAdapter(QSqlDatabase* dbSrc, TransList *src, QObject *parent) : QObject (parent), list(src)
{
	QObject::connect(list, &TransList::postItemAppend, this, &TelnetAdapter::addItemSQL);
	QObject::connect(list, &TransList::postItemRemove, this, &TelnetAdapter::removeItemSQL);
	QObject::connect(list, &TransList::finishedRemoving, this, &TelnetAdapter::sendBuffor);
	db = dbSrc;
	//db->setDatabaseName(QStandardPaths::writableLocation(QStandardPaths::DownloadLocation) + R"(/dataBase)");
	//writeQuerry(q);
	db->open();
	QSqlQuery q("SELECT MAX(orderID) FROM orders;");
	q.exec();
	db->close();
	q.next();
	maxID = q.value(0).toInt();
	connectionEstablished = true;
}

void TelnetAdapter::newOrder(QString dishName, const quint8 souce, const bool meat, const bool salad, const bool fries, const bool cheese, const bool other, const bool takeaway) noexcept
{
	maxID++;
	Dish a{maxID, dishName, souce, meat, salad, fries, cheese, other, takeaway};
	list->appendItem(a.toString(), a.__mOrderTime);
}

QVariant TelnetAdapter::qmlGetName(QString src) noexcept
{
	return TelnetAdapter::getName(src);;
}

QVariant TelnetAdapter::qmlGetID(QString src) const noexcept
{
	return QVariant(QString::number(TelnetAdapter::getID(src)));
}

QVariant TelnetAdapter::qmlGetSouce(QString src) const noexcept
{
	quint8 t1;
	bool t2, t3, t4 , t5, t6, t7;
	TelnetAdapter::setBooleans(src, t1,t2,t3,t4,t5,t6,t7);
	return QVariant(t1 == 0 ? "Brak Sosu" : t1 == 1 ? "Mieszany" : t1 == 2 ? "Łagodny" : "Ostry");
}

QVariant TelnetAdapter::qmlGetSalad(QString src) const noexcept
{
	quint8 t1;
	bool t2, t3, t4 , t5, t6, t7;
	TelnetAdapter::setBooleans(src, t1,t2,t3,t4,t5,t6,t7);
	return QVariant(t3 ? yes : no);
}

QVariant TelnetAdapter::qmlGetMeat(QString src) const noexcept
{
	quint8 t1;
	bool t2, t3, t4 , t5, t6, t7;
	TelnetAdapter::setBooleans(src, t1,t2,t3,t4,t5,t6,t7);
	return QVariant(t2 ? yes : no);
}

QVariant TelnetAdapter::qmlGetFries(QString src) const noexcept
{
	quint8 t1;
	bool t2, t3, t4 , t5, t6, t7;
	TelnetAdapter::setBooleans(src, t1,t2,t3,t4,t5,t6,t7);
	return QVariant(t4 ? yes : no);
}

QVariant TelnetAdapter::qmlGetCheese(QString src) const noexcept
{
	quint8 t1;
	bool t2, t3, t4 , t5, t6, t7;
	TelnetAdapter::setBooleans(src, t1,t2,t3,t4,t5,t6,t7);
	return QVariant(t5 ? yes : no);
}

QVariant TelnetAdapter::qmlGetOther(QString src) const noexcept
{
	quint8 t1;
	bool t2, t3, t4 , t5, t6, t7;
	TelnetAdapter::setBooleans(src, t1,t2,t3,t4,t5,t6,t7);
	return QVariant(t6 ? yes : no);
}

QVariant TelnetAdapter::qmlGetTakeAway(QString src) const noexcept
{
	quint8 t1;
	bool t2, t3, t4 , t5, t6, t7;
	TelnetAdapter::setBooleans(src, t1,t2,t3,t4,t5,t6,t7);
	return QVariant(t7 ? yes : no);
}

void TelnetAdapter::sync(QString address, quint16 port) noexcept
{
	socket = new QTcpSocket(nullptr);

	socket->connectToHost(address, port);

	socket->waitForConnected(3000);
	socket->flush();
	socket->write("conn\r\n\r\n\r\n");

	socket->waitForBytesWritten();
	socket->waitForReadyRead();

	QByteArray x= socket->readAll();

	if(!(x == "ok\r\n")) return;

	size_t min,max,row;

	db->open();
	QSqlQuery q1("SELECT MIN(orderID) FROM orders;");
	QSqlQuery q2("SELECT MAX(orderID) FROM orders;");
	db->close();
	q1.next();
	q2.next();
	min = q1.value(0).toInt();
	max = q2.value(0).toInt();
	row = min;

	db->open();
	//q.clear();
	QSqlQuery q("SELECT * FROM orders WHERE orderID="+QString::number(min)+";");
	q.exec();
	db->close();

	const quint8 orderID = static_cast<quint8>(q.record().indexOf("orderID"));
	const quint8 dishName = static_cast<quint8>(q.record().indexOf("dishName"));
	const quint8 dishSouce = static_cast<quint8>(q.record().indexOf("dishSouce"));
	const quint8 extraMeat = static_cast<quint8>(q.record().indexOf("extraMeat"));
	const quint8 extraSalad = static_cast<quint8>(q.record().indexOf("extraSalad"));
	const quint8 extraFries = static_cast<quint8>(q.record().indexOf("extraFries"));
	const quint8 extraCheese = static_cast<quint8>(q.record().indexOf("extraCheese"));
	const quint8 otherExtras = static_cast<quint8>(q.record().indexOf("otherExtras"));
	const quint8 takeAway = static_cast<quint8>(q.record().indexOf("takeAway"));
	const quint8 isComplete = static_cast<quint8>(q.record().indexOf("isComplete"));
	const quint8 orderDateTime = static_cast<quint8>(q.record().indexOf("orderDateTime"));

	q.clear();
	q.finish();

	//std::ofstream plik((QStandardPaths::writableLocation(QStandardPaths::DownloadLocation) + "/toSend.txt").toStdString());

	QByteArray toSend = "";
	toSend= toSend + ";dishName;dishSouce;extraMeat;extraSalad;extraFries;extraCheese;otherExtras;takeAway;isComplete;orderDateTime;\n";

	int amountOfRecordsLeft = 0;
	do
	{
		QString querrrry = "SELECT * FROM orders WHERE orderID=::0;";
		querrrry.replace("::0", QString::number(row));
		row++;
		db->open();
		q.prepare(querrrry);
		q.exec();
		db->close();
		q.next();

		if(q.value(0).isNull()) continue;

		toSend= toSend +
				q.value(dishName).toString().toStdString().c_str()
				   +";"+QString::number(static_cast<quint8>(q.value(dishSouce).toInt())).toStdString().c_str()
					 +";"+QString::number(static_cast<quint8>(q.value(extraMeat).toInt())).toStdString().c_str()
					   +";"+QString::number(static_cast<quint8>(q.value(extraSalad).toInt())).toStdString().c_str()
						 +";"+QString::number(static_cast<quint8>(q.value(extraFries).toInt())).toStdString().c_str()
						   +";"+QString::number(static_cast<quint8>(q.value(extraCheese).toInt())).toStdString().c_str()
							 +";"+QString::number(static_cast<quint8>(q.value(otherExtras).toInt())).toStdString().c_str()
							   +";"+QString::number(static_cast<quint8>(q.value(takeAway).toInt())).toStdString().c_str()
								 +";"+QString::number(static_cast<quint8>(q.value(isComplete).toInt())).toStdString().c_str()
								+";"+q.value(orderDateTime).toDateTime().toString("yyyy-MM-dd hh:mm:ss").toStdString().c_str()+";\n";

		q.clear();
		q.finish();

	}while (row <= max);

	toSend= toSend+"!END\r\n";


	socket->flush();
	socket->waitForBytesWritten();

	socket->write(toSend);

	socket->waitForBytesWritten();
	socket->waitForReadyRead();

	socket->write("^\r\n");
	socket->waitForBytesWritten();
	socket->waitForReadyRead();
	socket->close();
	socket->waitForDisconnected();
	disconnect(socket);
	delete socket;
	socket = nullptr;

}

QVariant TelnetAdapter::qmlGetComplete(QString src) const noexcept
{
	for(auto i = list->items().begin(); i != list->items().end(); i++)
	{
		if(i->descTrans == src)
		{
			return QVariant(i->isComplited ? yes : no);
		}
	}

	//if(list->items().end()->descTrans == src) return QVariant(list->items().end()->isComplited ? yes : no);
}

QVariant TelnetAdapter::qmlGetDateTime(QString src) const noexcept
{
	//.toString("yyyy-mm-dd hh:mm:ss")
	for(auto i = list->items().begin(); i != list->items().end(); i++)
	{
		if(i->descTrans == src)
		{
			return QVariant(i->orderTime.toString("yyyy-MM-dd hh:mm:ss"));
		}
	}
	//if(list->items().end()->descTrans == src) return QVariant(list->items().end()->orderTime.toString("yyyy-mm-dd hh:mm:ss"));
}

void TelnetAdapter::buttonComplitedClicked(QString src) noexcept
{
	cout << "Tworzę iterator. src: "+src;
	QList<TransItem>::iterator it;

	cout << "Lecę po wszystkich iteratorach";
	for(QList<TransItem>::iterator i = list->mItems.begin(); i != list->mItems.end(); i++)
	{
		cout << "Iterator: "+i->descTrans;
		if(i->descTrans == src)
		{
			it = i;
		}
	}
	it->isComplited = !it->isComplited;

	QString q = "UPDATE orders SET isComplete=::1 WHERE orderID=::2;";
	q.replace("::1", QString::number(it->isComplited));
	q.replace("::2", QString::number(getID(src)));

	writeQuerry(q);
}

void TelnetAdapter::addItemSQL()
{
	const QString  desc = list->items().back().descTrans;
	Strigazable * a = nullptr;
	cout <<this<<desc;
	a = new Dish{desc};
	//socket->write(a->toSQL().toStdString().c_str());
	writeQuerry(a->toSQL());
}

void TelnetAdapter::removeItemSQL()
{
	buffor.push_back(("DELETE FROM orders WHERE orderID="+QString::number(TelnetAdapter::getID(list->toRemove))+";").toStdString().c_str());
}

void TelnetAdapter::remove()
{
	//cout <<buffor.front();
	//socket->write(buffor.front());
	writeQuerry(buffor.front());
}

void TelnetAdapter::writeQuerry(QString src)
{
	cout << "Sprawdzam połączenie";
	if(!connectionEstablished) return;
	cout << "Otwieram bazę";
	db->open();
	QSqlQuery q(src);
	cout << "Wysyłam zapytamnia: "+src;
	q.exec();
	cout << "Zamykam Bazę";
	db->close();
	cout << "Last err.: "+q.lastError().text();
}

void TelnetAdapter::connect()
{
	if(connectionEstablished) return;


	if(db->open())
	{
		connectionEstablished = true;
	}else connectionEstablished = false;
}

bool TelnetAdapter::isConnected()
{
	return connectionEstablished;
}

void TelnetAdapter::close()
{/*
	if(isConnected())
	{
		connectionEstablished = false;
		socket->write("^\r\n");
		socket->disconnect();
	}
	*/

	if(isConnected())
	{
		db->close();
	}
}

void TelnetAdapter::sendBuffor()
{
	cout <<this<<"Workin...";
	while (buffor.size() != 0)
	{
		writeQuerry(buffor.front());
		buffor.pop_front();
	}
}

size_t TelnetAdapter::getID(QString& src) noexcept
{
	QString temp = "";
	for(int i = 0; i < src.length(); i++)
		if(src[i] == '0') continue; else
			if(src[i].isDigit()) temp+=src[i]; else break;

	return temp.toUInt();
}

QString TelnetAdapter::getName(QString & src) noexcept
{
	QString temp = "";
	for(int i = 0; i < static_cast<size_t>(src.length()); i++)
	{
		if(!src[i].isDigit())
		{
			for(int j = i; j < static_cast<size_t>(src.length()); j++)
			{
				if(!src[j].isDigit()) temp += src[j]; else return temp;
			}
		}
	}
}

Dish::Dish(QString src)
	:__mCompleted(false), __mOrderTime{QDateTime::currentDateTime()}
{
	// cout << this<< "jestem tutaj: "+src + " " + src.length();
	ID = TelnetAdapter::getID(src);
	__mDishName = TelnetAdapter::getName(src);
	TelnetAdapter::setBooleans(src, __mSauce, __mMeat, __mSalad, __mFries, __mCheese, __mOther, __mTakeAway);
}

QString Dish::toString()
{
	QString data = TelnetAdapter::formatNum(ID) + __mDishName + QString::number(static_cast<int>(__mSauce)) + QString::number(static_cast<int>(__mMeat)) + QString::number(static_cast<int>(__mSalad)) +
			QString::number(static_cast<int>(__mFries)) + QString::number(static_cast<int>(__mCheese)) + QString::number(static_cast<int>(__mOther)) + QString::number(static_cast<int>(__mTakeAway));// + "\r\n\r\n\r\n";

	return data;
}

QString Dish::toSQL()
{
	//bool souce, meat, salad, fries, cheese, other, takeaway;
	cout << this<< __mSauce + __mSalad + __mMeat + __mFries + __mCheese + __mOther + __mTakeAway;
	QString data = "INSERT INTO orders VALUES( ::1, '::2' , ::3, ::4, ::salateria, ::5, ::6, ::7, ::8, ::9, '::d10');";
	data.replace("::1", QString::number(ID));
	data.replace("::2", __mDishName);
	data.replace("::3", QString::number(__mSauce));
	data.replace("::4", QString::number(__mMeat));
	data.replace("::salateria", QString::number(__mSalad));
	data.replace("::5", QString::number(__mFries));
	data.replace("::6", QString::number(__mCheese));
	data.replace("::7", QString::number(__mOther));
	data.replace("::8", QString::number(__mTakeAway));
	data.replace("::9", QString::number(__mCompleted));
	data.replace("::d10", __mOrderTime.toString("yyyy-MM-dd hh:mm:ss"));
	return data;
}
