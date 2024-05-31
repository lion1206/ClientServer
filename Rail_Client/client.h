#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QList>
#include <QVariantMap>

class Client : public QObject
{
    Q_OBJECT
public:
    static Client* instance();
    bool registerUser(const QString &username, const QString &password);
    bool authenticateUser(const QString &username, const QString &password);
    QList<QVariantMap> getTrains();
    bool buyTicket(QString userId, int trainId);
    QString id;

private:
    explicit Client(QObject *parent = nullptr);
    static Client *m_instance;
    QTcpSocket *m_socket;
};

#endif // CLIENT_H
