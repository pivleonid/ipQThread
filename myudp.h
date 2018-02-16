
#ifndef MYUDP_H
#define MYUDP_H

#include <QObject>
#include <QUdpSocket>

class MyUDP : public QObject
{
    Q_OBJECT


public:
     explicit MyUDP(QObject *parent = 0);
public slots:
    bool setHost(QString host, int port);
    void sendData(QByteArray data);
    void HelloUDP();
     void readyRead();
signals:




private:
    QUdpSocket *socket;
    QHostAddress host_;
    int port_;

};

#endif // MYUDP_H
