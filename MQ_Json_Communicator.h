#ifndef CDATAMQSENDER_H
#define CDATAMQSENDER_H
#include <IJson_Communicator.h>
#include "qamqpclient.h"
#include "qamqpqueue.h"
#include "qamqpexchange.h"
#include <QObject>

class MQ_Json_Commnunicator:public QObject, public Ijson_Communicator
{
    Q_OBJECT
    Q_INTERFACES(Ijson_Communicator)

    QAmqpClient m_client;
    QAmqpQueue *m_queue;
    QAmqpExchange *m_exchange;
    QString m_queueName;
    bool m_toRead;
public:
    explicit MQ_Json_Commnunicator();
    virtual void setHost(QString host);
    virtual void setUsername(QString username);
    virtual void setPassword(QString password);
    virtual void setPort(int port);
    virtual void setQueueName(QString queue);
    virtual void Start(bool toRead);

    virtual void Send(QJsonObject obj);
private slots:
    void on_amqpClient_connected();
    void on_amqpClient_queueDeclared();
    void on_message_received();
signals:
    void connected();
    void disconnected();
    void MessageReceived(QJsonObject msg);
};

#endif // CDATAMQSENDER_H
