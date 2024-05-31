#include "server.h"
#include "database.h"
#include <QTcpSocket>
#include <QDataStream>

Server* Server::m_instance = nullptr;

Server::Server(QObject *parent) : QObject(parent)
{
    m_server = new QTcpServer(this);
    connect(m_server, &QTcpServer::newConnection, this, &Server::newConnection);
}

Server* Server::instance()
{
    if (!m_instance)
        m_instance = new Server;
    return m_instance;
}

void Server::startServer()
{
    if (!m_server->listen(QHostAddress::Any, 33333)) {
        qCritical() << "Unable to start the server:" << m_server->errorString();
        return;
    }
    qDebug() << "Server started";
}

void Server::newConnection()
{
    QTcpSocket *clientSocket = m_server->nextPendingConnection();
    connect(clientSocket, &QTcpSocket::readyRead, this, &Server::readClient);
    connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
    qDebug()<<"client was connected";
}

void Server::readClient()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    QDataStream in(clientSocket);
    QString requestType;
    in >> requestType;

    if (requestType == "register") {
        QString username, password;
        in >> username >> password;
        bool success = Database::instance()->registerUser(username, password);
        QDataStream out(clientSocket);
        out << QString((success ? "success" : "failure"));
        qDebug()<<(success ? "success" : "failure");
    } else if (requestType == "login") {
        QString username, password;
        in >> username >> password;
        bool success = Database::instance()->authenticateUser(username, password);
        QDataStream out(clientSocket);
        out << QString((success ? "success" : "failure"));
        qDebug()<<(success ? "success" : "failure");
    } else if (requestType == "getTrains") {
        QList<QVariantMap> trains = Database::instance()->getTrains();
        QDataStream out(clientSocket);
        out << trains;
    } else if (requestType == "buyTicket") {
        int userId, trainId;
        in >> userId >> trainId;
        bool success = Database::instance()->buyTicket(userId, trainId);
        QDataStream out(clientSocket);
        out << QString((success ? "success" : "failure"));
    }
    else if (requestType == "user_inf"){
        QString username, password;
        in >> username >> password;
        QString success = Database::instance()->get_info(username, password);
        QDataStream out(clientSocket);
        out << QString(success);
    }
}
