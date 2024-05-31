#include "client.h"
#include <QTcpSocket>
#include <QDataStream>
#include <QList>
#include <QVariantMap>
#include <QDebug>

Client* Client::m_instance = nullptr;

Client::Client(QObject *parent) : QObject(parent)
{
    m_socket = new QTcpSocket(this);
    m_socket->connectToHost("127.0.0.1", 33333);
}

Client* Client::instance()
{
    if (!m_instance)
        m_instance = new Client;
    return m_instance;
}

bool Client::registerUser(const QString &username, const QString &password)
{
    if (m_socket->state() == QAbstractSocket::ConnectedState) {
        QDataStream out(m_socket);
        out << QString("register") << username << password;

        m_socket->waitForReadyRead();
        QDataStream in(m_socket);
        QString response;
        in >> response;
        return response == "success";
    }
    return false;
}

bool Client::authenticateUser(const QString &username, const QString &password)
{
    if (m_socket->state() == QAbstractSocket::ConnectedState) {
        QDataStream out(m_socket);
        out << QString("login") << username << password;
        m_socket->waitForReadyRead();
        QDataStream in(m_socket);
        QString response;
        in >> response;
        qDebug()<<response;


            out << QString("user_inf")<<username<<password;
            m_socket->waitForReadyRead();

            QString user_id;
            in >> user_id;
            id = user_id;
            qDebug()<<id;

    return response == "success";

    }
    return false;
}

QList<QVariantMap> Client::getTrains()
{
    if (m_socket->state() == QAbstractSocket::ConnectedState) {
        QDataStream out(m_socket);
        out << QString("getTrains");

        m_socket->waitForReadyRead();
        QDataStream in(m_socket);
        QList<QVariantMap> trains;
        in >> trains;
        return trains;
    }
    return QList<QVariantMap>();
}

bool Client::buyTicket(QString userId, int trainId)
{
    if (m_socket->state() == QAbstractSocket::ConnectedState) {
        QDataStream out(m_socket);
        out << QString("buyTicket") << userId << trainId;
        m_socket->waitForReadyRead();
        QDataStream in(m_socket);
        QString response;
        in >> response;
        return response == "success";
    }
    return false;
}
