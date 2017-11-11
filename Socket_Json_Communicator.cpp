#include "Socket_Json_Communicator.h"
#include <QJsonDocument>
#include <QHostAddress>
#include <QDataStream>

Socket_Json_Communicator::Socket_Json_Communicator()
{
    m_socket=nullptr;
}

//Socket_Json_Communicator::~Socket_Json_Communicator()
//{
//    foreach (auto &pair, m_clients) {
//        pair.first->disconnect();
//    }
//}

void Socket_Json_Communicator::Start(bool isServer)
{
    if (isServer){
        m_server=new QTcpServer(this);
        if(m_server->listen(QHostAddress::LocalHost, m_port)){
            qDebug()<<"Server start listening";
        }else{
            qDebug()<<m_server->errorString();
        }
        connect(m_server,SIGNAL(newConnection()),this,SLOT(newClient()));
    }else{
        if (!m_socket){
            m_socket=new QTcpSocket(this);
            connect(m_socket,SIGNAL(connected()),this,SIGNAL(connected()));
            connect(m_socket,SIGNAL(disconnected()),this,SIGNAL(disconnected()));
            connect(m_socket,SIGNAL(readyRead()),this,SLOT(on_read_message()));
        }
        m_socket->abort();
        m_socket->connectToHost(QHostAddress::LocalHost,m_port);
    }
}

void Socket_Json_Communicator::Send(QJsonObject obj)
{
    if (m_socket){
        m_socket->write(QJsonDocument(obj).toJson());
        m_socket->flush();
    }
}

void Socket_Json_Communicator::newClient()
{
    QTcpSocket *clientConnection = m_server->nextPendingConnection();
    m_clients.insert(std::make_pair(clientConnection,std::make_pair(clientConnection->peerAddress(),clientConnection->peerPort())));
    connect(clientConnection,SIGNAL(readyRead()),this,SLOT(on_read_message()));
    connect(clientConnection,SIGNAL(disconnected()),this,SLOT(on_lost_client()));
    connect(clientConnection,SIGNAL(disconnected()),clientConnection,SLOT(deleteLater()));
}

void Socket_Json_Communicator::on_read_message()
{
    QTcpSocket *Sender(qobject_cast<QTcpSocket*>(sender()));
    QTextStream ds(Sender);
    QJsonObject obj=QJsonDocument::fromJson(ds.readAll().toUtf8()).object();
    obj.insert("addres",Sender->peerAddress().toString());
    obj.insert("port",Sender->peerPort());
    qDebug()<<" [x] Received " << obj;
    emit MessageReceived(obj);

}

void Socket_Json_Communicator::on_lost_client()
{
    m_clients.erase(qobject_cast<QTcpSocket*>(sender()));
    sender()->deleteLater();
}
