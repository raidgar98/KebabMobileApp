#ifndef TRANSLIST_H
#define TRANSLIST_H

#include <QObject>
#include <QList>
#include <QDateTime>

struct TransItem
{
    bool toRemove;
    QString descTrans;
	//bool souce, meat, salad, fries, cheese, other, takeaway;
	//QString dishID, dishName, dishSouce, dshMeat, dishSalad, sidhFries, dishFries, dishCheese, dishOther, dishTakeaway;
	bool isComplited = false;
	QDateTime orderTime;

};

class TransList : public QObject
{
    Q_OBJECT
public:

    explicit TransList(QObject *parent = nullptr);

    QList<TransItem> items() const;

	QString toRemove = "";

    bool setItemAt(int index, const TransItem & item);

	QList<TransItem> mItems;

signals:

    void preItemAppend();
    void postItemAppend();
    void preItemRemove(int index);
    void postItemRemove();
	void finishedRemoving();

public slots:

	void appendItem(QString data, QDateTime ordTime);
    void removeSelectedItems();

private:



};

#endif // TRANSLIST_H
