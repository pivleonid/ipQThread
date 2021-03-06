#ifndef PINGMODEL_H
#define PINGMODEL_H

#include <QObject>
#include <QProcess>
#include <QThread>


class PingModel :  public QObject
{
    Q_OBJECT
public:
    explicit PingModel(QObject *parent = 0);
    ~PingModel();


    bool is_running(){
        return running;
    }
    bool finished();
    void lineEditRead(QString ip);
    
signals:
    void signalData(QString data);
    void signalStartData();
    void endThread();
    void signalError();
    
public slots:
    void verifyStatus();
    void readResult();
    void disconPing();
    void run();
    void error();

private:
    QProcess *ping;
    bool running;
    bool closeProcess;
    QString ip;
    bool flag;
};

#endif // PINGMODEL_H
