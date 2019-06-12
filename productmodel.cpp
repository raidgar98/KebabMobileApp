#include "productmodel.h"
#include "productlist.h"

productModel::productModel(QObject *parent)
	: QAbstractListModel(parent), mList(nullptr)
{
}

int productModel::rowCount(const QModelIndex &parent) const
{
	// For list models only the root node (an invalid parent) should return the list's size. For all
	// other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
	if (parent.isValid() || !mList)
		return 0;

	return mList->items().size();
}

QVariant productModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid() || !mList)
		return QVariant();
	const productListItem item = mList->items().at(index.row());
	switch(role)
	{
		case First: return QVariant(item.First);
		case Second: return QVariant(item.Second);
		case FirstShort: return QVariant(item.FirstShort);
		case SecondShort: return QVariant(item.SecondShort);
	}

	return QVariant();
}

QHash<int, QByteArray> productModel::roleNames() const
{
	QHash<int, QByteArray> names;
	names[First] = "First";
	names[Second] = "Second";
	names[FirstShort] = "FirstShort";
	names[SecondShort] = "SecondShort";
	return names;
}

ProductList * productModel::list() const
{
	return mList;
}

void productModel::setList(ProductList * list)
{
	beginResetModel();
	if(mList) mList->disconnect();

	mList = list;
/*
	if(mList)
	{
		connect(mList, &ProductList::preProductAppend, this, [=]()
		{
			const int index = mList->items().size();
			beginInsertRows(QModelIndex(), index, index);
		});
		connect(mList, &ProductList::postProductAppend, this, [=]()
		{
			endInsertRows();
		});
	}
	*/
}
