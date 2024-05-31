#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QList>
#include <QVariantMap>

class Database : public QObject
{
    Q_OBJECT
public:
    static Database* instance();
    bool registerUser(const QString &username, const QString &password);
    bool authenticateUser(const QString &username, const QString &password);
    QList<QVariantMap> getTrains();
    bool buyTicket(int userId, int trainId);
    QString get_info(const QString &username, const QString &password);

private:
    explicit Database(QObject *parent = nullptr);
    static Database *m_instance;
    QSqlDatabase m_db;
    virtual ~Database(); // Объявление деструктора
};

#endif // DATABASE_H
