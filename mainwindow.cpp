

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pingmodel.h"
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


//    /* Создаем строку для регулярного выражения */
//    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
//    /* Создаем регулярное выражение с применением строки, как
//     * повторяющегося элемента
//     */
//    QRegExp ipRegex ("^" + ipRange
//                     + "\\." + ipRange
//                     + "\\." + ipRange
//                     + "\\." + ipRange + "$");
//    /* Создаем Валидатор регулярного выражения с применением
//     * созданного регулярного выражения
//     */
//    QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);
//    /* Устанавливаем Валидатор на QLineEdit */
//    ui->lineEdit->setValidator(ipValidator);

    ui->btn_disconnect->setEnabled(false);

    model = new PingModel;

    connect(model, SIGNAL(signalData(QString)), ui->browser_dbg, SLOT(append(QString)));
    connect(ui->btn_connect, SIGNAL(clicked()), this, SLOT(connectSlot()));
    connect(ui->btn_disconnect, SIGNAL(clicked(bool)),this, SLOT(disconnectSlot()));
    connect(ui->clearText, SIGNAL(clicked(bool)),  this, SLOT(clearSlot()));

    connect(&thread, SIGNAL(started()), model, SLOT(run()));


    //connect(model, SIGNAL(endThread()), &thread, SLOT(quit()));
    model->lineEditRead(ui->lineEdit->text());



}

MainWindow::~MainWindow()
{
if(model->is_running()){
    model->disconPing();
    thread.exit(0);
}
   //thread.quit();
    delete ui;
    delete model;
}

//Слоты

void MainWindow::connectSlot(){
    ui->btn_disconnect->setEnabled(true);
    ui->btn_connect->setEnabled(false);
    model->lineEditRead(ui->lineEdit->text());
    model->moveToThread(&thread);
    thread.start();

}
void MainWindow::disconnectSlot(){
ui->btn_disconnect->setEnabled(false);
 ui->btn_connect->setEnabled(true);
    model->disconPing();
    thread.exit(0);
    //thread.wait(10);

}
void MainWindow::clearSlot(){
    ui->browser_dbg->clear();
}

