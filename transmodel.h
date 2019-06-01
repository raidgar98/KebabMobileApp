#ifndef TRANSMODEL_H
#define TRANSMODEL_H

#include <QAbstractListModel>

class TransList;

class TransModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(TransList *list READ list WRITE setList);
public:
    explicit TransModel(QObject *parent = nullptr);

    enum
    {
		//bool souce, meat, salad, fries, cheese, other, takeaway;
        toRemoveRole = Qt::UserRole,
		descTransRole,
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    TransList *list() const;

    void setList(TransList *list);

private:

    TransList* mList;

};

#endif // TRANSMODEL_H
