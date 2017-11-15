#include "MQ_Json_Communicator.h"
#include <QNetworkInterface>
#include <QJsonDocument>

MQ_Json_Commnunicator::MQ_Json_Commnunicator()
{
    m_client.setAutoReconnect(true);
    connect(&m_client,SIGNAL(connected()),this,SLOT(on_amqpClient_connected()));
    connect(&m_client,SIGNAL(disconnected()),this,SIGNAL(disconnected()));
    connect(&m_client,SIGNAL(connected()),this,SIGNAL(connected()));
}

void MQ_Json_Commnunicator::setHost(QString host)
{
    m_client.setHost(host);
    m_queueName=host;
}

void MQ_Json_Commnunicator::setUsername(QString username)
{
    m_client.setUsername(username);
}

void MQ_Json_Commnunicator::setPassword(QString password)
{
    m_client.setPassword(password);
}

void MQ_Json_Commnunicator::setPort(int port)
{
    m_client.setPort(port);
}

void MQ_Json_Commnunicator::setQueueName(QString queue)
{
    m_queueName=queue;
}

void MQ_Json_Commnunicator::Start(bool toRead)
{
    m_client.connectToHost();
    m_toRead=toRead;
}

void MQ_Json_Commnunicator::on_amqpClient_connected()
{
    QAmqpQueue *queue=m_client.createQueue(m_queueName);
    connect(queue,SIGNAL(declared()),this,SLOT(on_amqpClient_queueDeclared()));
    queue->declare();
}

void MQ_Json_Commnunicator::on_amqpClient_queueDeclared()
{
    m_queue = qobject_cast<QAmqpQueue*>(sender());
    m_exchange=m_client.createExchange();
    m_exchange->declare();
    if (m_toRead){
        connect(m_queue,SIGNAL(messageReceived()),this,SLOT(on_message_received()));
        m_queue->consume(QAmqpQueue::coNoAck);
    }
    emit connected();
}

void MQ_Json_Commnunicator::on_message_received()
{
    QAmqpMessage message = m_queue->dequeue();
    QByteArray msg_raw=message.payload();
    QJsonDocument doc=QJsonDocument::fromJson(msg_raw);
    qDebug()<<" [x] Received " << doc.object();
    emit MessageReceived(doc.object());
}

void MQ_Json_Commnunicator::Send(QJsonObject obj)
{
    if (m_queue && m_queue){
        obj["address"]=CurrentIP();
        QJsonDocument doc(obj);
        m_exchange->publish(doc.toJson(),m_queueName);
    }
}

#include "moc_MQ_Json_Communicator.cpp"
