#include <QQueue>
#include "translist.h"
#include <QDebug>

#define cout qDebug()

TransList::TransList(QObject *parent) : QObject(parent)
{/*
	mItems.append({false, QStringLiteral("Item nr: 1")});
	mItems.append({false, QStringLiteral("Item nr: 2")});
	mItems.append({false, QStringLiteral("Item nr: 3")});
	mItems.append({false, QStringLiteral("Item nr: 4")});*/
}

QList<TransItem> TransList::items() const
{
	return mItems;
	//XDD
}

bool TransList::setItemAt(int index, const TransItem &item)
{
	if(index < 0 || index >= mItems.size())
		return false;

	const TransItem & oldItem = mItems.at(index);
	if(item.toRemove == oldItem.toRemove && item.descTrans == oldItem.descTrans)
		return false;

	mItems[index] = item;
	return true;

}

void TransList::appendItem(QString data, QDateTime ordTime)
{
	//  cout<< this <<" Jestem tutaj append Item: "<<data;
	emit preItemAppend();

	TransItem item;
	item.toRemove = false;
	item.descTrans = data;
	item.orderTime = ordTime;
	//cout << this  << item.descTrans << " -> Rozpoczynam ustawianie zmiennych...";
	mItems.append(item);

	emit postItemAppend();

}

void TransList::removeSelectedItems()
{
	for(int i = 0; i < mItems.size(); )
	{
		if(mItems.at(i).toRemove == true)
		{
			emit preItemRemove(i);
			toRemove = mItems.at(i).descTrans;
			mItems.removeAt(i);
			emit postItemRemove();

		}else i++;
	}
	emit finishedRemoving();
}
