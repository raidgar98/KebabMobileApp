#ifndef PRODUCTMODEL_H
#define PRODUCTMODEL_H

#include <QAbstractListModel>

class ProductList;

class productModel : public QAbstractListModel
{
	Q_OBJECT
	Q_PROPERTY(ProductList* list READ list WRITE setList)

public:
	explicit productModel(QObject *parent = nullptr);

	enum
	{
		First = Qt::UserRole,
		Second,
		FirstShort,
		SecondShort
	};

	// Basic functionality:
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

	virtual QHash<int, QByteArray> roleNames() const override;

	ProductList * list() const;

	void setList(ProductList * list);

private:

	ProductList* mList;

};

#endif // PRODUCTMODEL_H
