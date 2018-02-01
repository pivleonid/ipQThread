

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pingmodel.h"
#include <QThread>
#include <QSettings>
#include <QFile>

#include <QDesktopWidget>
#include <QStyle>
#include <QDesktopWidget>

#ifdef LINUXBASE
#include <QTextCodec>
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
#ifdef LINUXBASE
 QTextCodec* codec = QTextCodec::codecForName("UTF-8");
 QTextCodec::setCodecForLocale(codec);
 QTextCodec::setCodecForCStrings(codec);
 QTextCodec::setCodecForTr(codec);
#endif

    ui->setupUi(this);


    QDesktopWidget *pDescwidget = QApplication::desktop();
    move(pDescwidget->width()/2-width()/2, pDescwidget->height()/2-height()/2);


    /* Создаем строку для регулярного выражения */
    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    /* Создаем регулярное выражение с применением строки, как
     * повторяющегося элемента
     */
    QRegExp ipRegex ("^" + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange + "$");
    /* Создаем Валидатор регулярного выражения с применением
     * созданного регулярного выражения
     */
    QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);
    /* Устанавливаем Валидатор на QLineEdit */
    ui->lineEdit->setValidator(ipValidator);

    ui->btn_disconnect->setEnabled(false);

    model = new PingModel;

    connect(model, SIGNAL(signalData(QString)), ui->browser_dbg, SLOT(append(QString)));
    connect(model, SIGNAL(signalStartData()), this, SLOT(testStart()));
    connect(ui->btn_connect, SIGNAL(clicked()), this, SLOT(connectSlot()));
    connect(ui->btn_disconnect, SIGNAL(clicked(bool)),this, SLOT(disconnectSlot()));
    connect(ui->clearText, SIGNAL(clicked(bool)),  this, SLOT(clearSlot()));

    connect(&thread, SIGNAL(started()), model, SLOT(run()));


    //connect(model, SIGNAL(endThread()), &thread, SLOT(quit()));
    model->lineEditRead(ui->lineEdit->text());




    connect(ui->checkBox,SIGNAL(clicked(bool)), this, SLOT(updateScreen(bool)));
    ui->lineEdit->setToolTip("Поле ввода IP адреса");
    ui->btn_connect->setToolTip("Начать тестирование");
    ui->btn_disconnect->setToolTip("Закончить тестирование");


    connect(model, SIGNAL(signalError()), this, SLOT(errorMsb()));


    //Чтение настроек
    QFile file("ip.conf");
     if(file.size() == 0)
       return;
     QSettings settings( "ip.conf", QSettings::IniFormat );
     settings.beginGroup( "saveState" );
     bool check = settings.value("check").toBool();
     ui->checkBox->setChecked(check);
     QVariant text = settings.value("ip");
     ui->lineEdit->setText( text.toString());
     settings.endGroup();
     //
     if(ui->checkBox->isChecked() == false){
     ui->browser_dbg->setVisible(false);
     ui->clearText->setVisible(false);
     }
     QMainWindow::resize(QMainWindow::sizeHint());




}

void MainWindow::updateScreen(bool flag){
    if (flag == true){
        ui->browser_dbg->setVisible(true);
        ui->clearText->setVisible(true);
        QMainWindow::resize(626, 600);
        QMainWindow::setMaximumSize(626, 600);
        QMainWindow::resize(626, 600);

    }
    else{
        ui->browser_dbg->setVisible(false);
        ui->clearText->setVisible(false);
         QMainWindow::resize(626, 100);
         QMainWindow::setMaximumSize(626, 100);

    }

}

void MainWindow::testStart(){
     ui->statusLbl->setText("Тест запущен");
}

MainWindow::~MainWindow(){


    if(model->is_running()){
        model->disconPing();
        thread.quit();
    }

     delete model;
    delete ui;

}
void MainWindow::closeEvent(QCloseEvent* event){

    QSettings settings( "ip.conf", QSettings::IniFormat );
    settings.beginGroup( "saveState" );
    settings.setValue( "check", ui->checkBox->isChecked() );
    settings.setValue( "ip", ui->lineEdit->text() );
    settings.endGroup();
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
    thread.quit();
    ui->statusLbl->setText("Тест остановлен");
    //thread.wait(10);

}
void MainWindow::clearSlot(){
    ui->browser_dbg->clear();
}

