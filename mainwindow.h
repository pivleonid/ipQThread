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

public slots:
    void clearSlot();
    void connectSlot();
    void disconnectSlot();

};

#endif // MAINWINDOW_H
