#ifndef CDATASENDER_H
#define CDATASENDER_H

#include <QString>
#include <QJsonObject>
#include <QObject>

class Ijson_Communicator:public QObject
{
    QString m_host;
    QString m_username;
    QString m_password;
    int m_port;
public:
    virtual void setHost(QString host){m_host=host;}
    virtual void setUsername(QString username){m_username=username;}
    virtual void setPassword(QString password){m_password=password;}
    virtual void setPort(int port){m_port=port;}
    virtual void Start(bool toRead){toRead=!toRead;}

    virtual void Send(QJsonObject obj){(void)obj;}

signals:
    void connected();
    void disconnected();
    void MessageReceived(QJsonObject msg);

};
//Q_DECLARE_INTERFACE(Ijson_Communicator,"Ijson_Communicator")


#endif // CDATASENDER_H
