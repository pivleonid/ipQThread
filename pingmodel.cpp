#include <QString>
#include <QDebug>
#include "pingmodel.h"
#include <QProcess>
#include <QTextCodec>
#include <QCoreApplication>
#include <QMessageBox>


PingModel::PingModel(QObject *parent) :
    QObject(parent), running(false)
{
    ping = new QProcess(this);
    connect(ping, SIGNAL(started()), this, SLOT(verifyStatus()));
    connect(ping, SIGNAL(finished(int)), this, SLOT(readEndResult(int)));
    connect(ping, SIGNAL(readyReadStandardError()), this, SLOT(error()));
    closeProcess = false;
}

void PingModel::error(){
    qDebug() << "Err";
}

PingModel::~PingModel(){
    exit(0);
    delete ping;
}

void PingModel::verifyStatus(){
    if(ping->isReadable()){
        qDebug() << "read on ...";
        connect(ping, SIGNAL(readyRead()), this, SLOT(readResult()));
        if(ping->canReadLine()){
            qDebug() << "LINE read on ...";
        }
    }else{
        qDebug() << "not able to read ...";
    }
}

void PingModel::readResult(){

    running = true;
    QByteArray a = ping->readAll();
    if(a == "")
        return;
    QTextCodec* codec =  QTextCodec::codecForName("cp-866");
    QString fio = codec->toUnicode(a.data());
    emit signalData(fio);

}




void PingModel::disconPing(){
    if(running == false)
        return;

    QProcess::execute(QString("taskkill /PID %1 /F").arg(ping->processId()));
    QProcess::execute(QString("kill -SIGINT %1").arg(ping->processId()));
    closeProcess = true;
    running = false;
    ping->close();

}

void PingModel::run(){
#ifndef LINUXBASE
    closeProcess = false;
    QString command = "ping";
    QStringList args;
    args << PingModel::ip; //-t для бесконечных запросов
    ping->start(command, args); //вызывает сигнал started()
#endif

#ifdef LINUXBASE
    closeProcess = false;
    QString command = "ping";
    QStringList args;
    args <<"-t"<< PingModel::ip; //-t для бесконечных запросов
    ping->start(command, args); //вызывает сигнал started()
#endif

}


void PingModel::lineEditRead(QString ip){
    PingModel::ip = ip;
}
