#ifndef CDATASENDER_H
#define CDATASENDER_H

#include <QString>
#include <QJsonObject>
#include <QObject>

class Ijson_Communicator
{
public:
    virtual void setHost(QString host)=0;
    virtual void setUsername(QString username)=0;
    virtual void setPassword(QString password)=0;
    virtual void setPort(int port)=0;
    virtual void Start(bool toRead)=0;

    virtual void Send(QJsonObject obj)=0;

//signals:
//    virtual void connected()=0;
//    virtual void disconnected()=0;
//    virtual void MessageReceived(QJsonObject msg)=0;

};
Q_DECLARE_INTERFACE(Ijson_Communicator,"Ijson_Communicator")


#endif // CDATASENDER_H
