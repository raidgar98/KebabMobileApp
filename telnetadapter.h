#ifndef TELNETADAPTER_H
#define TELNETADAPTER_H

#include <QObject>
#include <QDebug>
#include <QQmlEngine>
#include <QQmlContext>
#include <QDateTime>

#include <QTcpSocket>
#include <QQueue>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>

#include <QThread>

#define cout qDebug()
#define yes "TAK"
#define no "NIE"

class TransList;

struct Strigazable
{
public:
	virtual ~Strigazable() {};

	virtual QString toString() = 0;
	virtual QString toSQL() = 0;
};

class TelnetAdapter : public QObject
{

    Q_OBJECT

public:

    TransList* list = nullptr;

    QQmlComponent* component = nullptr;

	QQueue<QByteArray> buffor;

    size_t maxID = 0;

	QTcpSocket* socket;

	QSqlDatabase db;

	bool connectionEstablished = false;

	QString temporary;

public:

	void sendBuffor();

	static size_t getID(QString& src) noexcept;

	static QString getName(QString& src) noexcept;

    static QString formatNum(const size_t arg) noexcept;

	static void setBooleans(QString& src, quint8& souce, bool& meat, bool& salad, bool& fries, bool& cheese, bool& other, bool& takeaway) noexcept;

    explicit TelnetAdapter(TransList* src, QObject *parent = nullptr);

	~TelnetAdapter() { close(); }

	Q_INVOKABLE void newOrder(QString dishName, quint8 souce, bool meat, bool salad, bool fries, bool cheese, bool other, bool takeaway) noexcept;

	Q_INVOKABLE QVariant qmlGetName( QString src) noexcept;

	Q_INVOKABLE QVariant qmlGetID( QString src) const noexcept;

	Q_INVOKABLE QVariant qmlGetSouce( QString src) const noexcept;

	Q_INVOKABLE QVariant qmlGetSalad( QString src) const noexcept;

	Q_INVOKABLE QVariant qmlGetMeat( QString src) const noexcept;

	Q_INVOKABLE QVariant qmlGetFries( QString src) const noexcept;

	Q_INVOKABLE QVariant qmlGetCheese( QString src) const noexcept;

	Q_INVOKABLE QVariant qmlGetOther( QString src) const noexcept;

	Q_INVOKABLE QVariant qmlGetTakeAway( QString src) const noexcept;

	Q_INVOKABLE void sync(QString address, quint16 port) noexcept;

	Q_INVOKABLE QVariant qmlGetComplete( QString src) const noexcept;

	Q_INVOKABLE QVariant qmlGetDateTime( QString src) const noexcept;

	Q_INVOKABLE void buttonComplitedClicked(QString src) noexcept;


signals:

    void newOrder();

public slots:

    void addItemSQL();

    void removeItemSQL();

	void remove();

	void writeQuerry(QString src);

public:

	Q_INVOKABLE void connect();

	Q_INVOKABLE bool isConnected();

	Q_INVOKABLE void close();

};

struct Dish : public Strigazable
{
	size_t ID;
	QString __mDishName = "";
	quint8 __mSauce;
	bool  __mMeat, __mSalad, __mFries, __mCheese, __mOther, __mTakeAway, __mCompleted;
	QDateTime __mOrderTime;

	Dish(size_t id, QString dishName, quint8 s, bool m, bool sa, bool f, bool ch, bool ot, bool ta)
		:ID{id}, __mDishName{dishName}, __mSauce{s}, __mMeat{m}, __mSalad{sa}, __mFries{f}, __mCheese{ch}, __mOther{ot}, __mTakeAway{ta}, __mCompleted(false), __mOrderTime{QDateTime::currentDateTime()} {}

	explicit Dish(const QString src);

	virtual QString toString() override;

	virtual QString toSQL() override;
};

#endif // TELNETADAPTER_H
