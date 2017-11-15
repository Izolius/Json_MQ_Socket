#ifndef CDATASENDER_H
#define CDATASENDER_H

#include <QString>
#include <QJsonObject>
#include <QObject>

class Ijson_Communicator:public QObject
{
protected:
    QString m_host;
    QString m_username;
    QString m_password;
    int m_port;
public:
    virtual void setHost(QString host);
    virtual void setUsername(QString username);
    virtual void setPassword(QString password);
    virtual void setPort(int port);
    virtual void Start(bool toRead);
    static QString CurrentIP();
    virtual void Send(QJsonObject obj);

signals:
    void connected();
    void disconnected();
    void MessageReceived(QJsonObject msg);

};
//Q_DECLARE_INTERFACE(Ijson_Communicator,"Ijson_Communicator")


#endif // CDATASENDER_H
