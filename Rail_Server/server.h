#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>

class Server : public QObject
{
    Q_OBJECT
public:
    static Server* instance();
    void startServer();

private slots:
    void newConnection();
    void readClient();

private:
    explicit Server(QObject *parent = nullptr);
    static Server *m_instance;
    QTcpServer *m_server;
};

#endif // SERVER_H
