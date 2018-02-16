#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTcpSocket>
#include <QMainWindow>
#include <QXmlStreamReader>
#include <QDebug>
#include <QTime>
#include <QDataStream>
#include "pingmodel.h"
#include <QThread>
#include <QApplication>
#include <QMessageBox>

#include <QTimer>
#include "myudp.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTcpSocket *sock;
    PingModel* model;
    QThread thread;
    QByteArray dataByte_;
    QTimer tmr_;
    MyUDP udp_;


public slots:
    void clearSlot();
    void connectSlot();
    void disconnectSlot();
    void updateScreen(bool);
    void closeEvent(QCloseEvent* event);
    void testStart();
    void errorMsb(){
        QMessageBox msb;
        msb.setText("Такого адреса не существует");
        disconnectSlot();
        msb.exec();
    }
    void startTransmitUDP();
    void stopTransmitUDP();
    void timerUDP();

};

#endif // MAINWINDOW_H
