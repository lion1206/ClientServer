#include "database.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QList>
#include <QSqlRecord>
#include <QMap>

Database* Database::m_instance = nullptr;

Database::~Database()
{
    m_db.close();
}

Database::Database(QObject *parent) : QObject(parent)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("Test.db");

    if (!m_db.open()) {
        qCritical() << "Cannot open database:" << m_db.lastError();
    }
    else {
        qDebug()<<"db is connected";
    }

    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS User ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "login TEXT NOT NULL, "
                    "password TEXT NOT NULL)")) {
        qDebug() << "Error creating table User:" << query.lastError().text();
    }

    if (!query.exec("CREATE TABLE IF NOT EXISTS Train ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "train_number TEXT NOT NULL, "
                    "departure_time TEXT NOT NULL, "
                    "arrival_time TEXT NOT NULL, "
                    "available_seats INTEGER NOT NULL)")) {
        qDebug() << "Error creating table Train:" << query.lastError().text();
    }

    if (!query.exec("CREATE TABLE IF NOT EXISTS Ticket ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "user_id INTEGER NOT NULL, "
                    "train_id INTEGER NOT NULL, "
                    "FOREIGN KEY(user_id) REFERENCES User(id), "
                    "FOREIGN KEY(train_id) REFERENCES Train(id))")) {
        qDebug() << "Error creating table Ticket:" << query.lastError().text();
    }
}

Database* Database::instance()
{
    if (!m_instance)
        m_instance = new Database;
    return m_instance;
}

bool Database::registerUser(const QString &username, const QString &password)
{
    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password) VALUES (:username, :password)");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    return query.exec();
}

bool Database::authenticateUser(const QString &username, const QString &password)
{
    QSqlQuery query;
    query.prepare("SELECT id FROM users WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    query.exec();

    return query.next();
}

QList<QVariantMap> Database::getTrains()
{
    QSqlQuery query("SELECT * FROM Train");
    QList<QVariantMap> trains;

    while (query.next()) {
        QVariantMap train;
        train["id"] = query.value("id");
        train["train_number"] = query.value("train_number");
        train["departure_time"] = query.value("departure_time");
        train["arrival_time"] = query.value("arrival_time");
        train["available_seats"] = query.value("available_seats");
        trains.append(train);
    }
    return trains;
}

bool Database::buyTicket(int userId, int trainId)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Ticket (user_id, train_id) VALUES (:user_id, :train_id)");
    query.bindValue(":user_id", userId);
    query.bindValue(":train_id", trainId);
    return query.exec();
}

QString Database::get_info(const QString &username, const QString &password)
{
    QSqlQuery query;
    query.prepare("SELECT id FROM users WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    query.exec();
    QString id;
    if (query.next()){
        id = query.value(0).toString();
    }
    return id;
}
