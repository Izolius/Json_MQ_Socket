#include "IJson_Communicator.h"
#include <QHostAddress>
#include <QNetworkInterface>

void Ijson_Communicator::setHost(QString host){m_host=host;}

void Ijson_Communicator::setUsername(QString username){m_username=username;}

void Ijson_Communicator::setPassword(QString password){m_password=password;}

void Ijson_Communicator::setPort(int port){m_port=port;}

void Ijson_Communicator::Start(bool toRead){toRead=!toRead;}

void Ijson_Communicator::Send(QJsonObject obj){(void)obj;}

QString Ijson_Communicator::CurrentIP()
{
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
             return address.toString();
    }
    return QHostAddress(QHostAddress::LocalHost).toString();
}
