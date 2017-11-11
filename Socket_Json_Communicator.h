#ifndef SOCKET_JSON_COMMUNICATOR_H
#define SOCKET_JSON_COMMUNICATOR_H

#include <QTcpSocket>
#include <QTcpServer>
#include <QString>
#include <map>
#include <utility>
#include "IJson_Communicator.h"

class Socket_Json_Communicator:public Ijson_Communicator
{
    Q_OBJECT

    QTcpSocket *m_socket;
    QTcpServer *m_server;
    QString m_host;
    int m_port;
    std::map<QTcpSocket* , std::pair<QHostAddress,int> > m_clients;
public:
    Socket_Json_Communicator();

    // Ijson_Communicator interface
public:
    virtual void Start(bool isServer);
    virtual void Send(QJsonObject obj);
private slots:
    void newClient();
    void on_read_message();
    void on_lost_client();
signals:
    void connected();
    void disconnected();
    void MessageReceived(QJsonObject msg);
};

#endif // SOCKET_JSON_COMMUNICATOR_H
