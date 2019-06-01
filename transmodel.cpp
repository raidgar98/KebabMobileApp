#include "transmodel.h"

#include "translist.h"

TransModel::TransModel(QObject *parent)
	: QAbstractListModel(parent),
	  mList(nullptr)
{
}

int TransModel::rowCount(const QModelIndex &parent) const
{
	// For list models only the root node (an invalid parent) should return the list's size. For all
	// other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
	if (parent.isValid() || !mList)
		return 0;

	return mList->items().size();

}

QVariant TransModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid() || !mList)
		return QVariant();

	const TransItem item = mList->items().at(index.row());
	switch(role)
	{
		case toRemoveRole: return QVariant(item.toRemove);
		case descTransRole: return QVariant(item.descTrans);
	}
	return QVariant();
}


/*
		id,
		name,
		souce,
		meat,
		salad,
		fries,
		cheese,
		other,
		takeaway
*/

bool TransModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if(!mList)
		return false;

	TransItem item = mList->items().at(index.row());
	switch(role)
	{
		case toRemoveRole: item.toRemove = value.toBool(); break;
		case descTransRole: item.descTrans = value.toString(); break;

	}

	if (!mList->setItemAt(index.row(), item))
	{
		emit dataChanged(index, index, QVector<int>() << role);
		return true;
	}
	return false;
}

Qt::ItemFlags TransModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	return Qt::ItemIsEditable;
}


QHash<int, QByteArray> TransModel::roleNames() const
{
	QHash<int, QByteArray> names;
	names[toRemoveRole] = "toRemove";
	names[descTransRole] = "descTrans";

	return names;
}

TransList *TransModel::list() const
{
	return mList;
}

void TransModel::setList(TransList *list)
{
	beginResetModel();

	if(mList)
		mList->disconnect(this);

	mList = list;

	if(mList)
	{
		connect(mList, &TransList::preItemAppend, this, [=](){ const int index = mList->items().size(); beginInsertRows(QModelIndex(), index, index); });
		connect(mList, &TransList::postItemAppend, this, [=](){ endInsertRows();});

		connect(mList, &TransList::preItemRemove, this, [=](int index){beginRemoveRows(QModelIndex(), index, index); });
		connect(mList, &TransList::postItemRemove, this, [=](){ endRemoveRows();});
	}

	endResetModel();
}
