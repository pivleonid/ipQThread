

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pingmodel.h"
#include <QThread>
#include <QSettings>
#include <QFile>

#include <QDesktopWidget>
#include <QStyle>
#include <QDesktopWidget>
#include <QBitArray>

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

    ui->statusLbl->setText("Тест не запущен");
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

    ui->btn_disconnectPing->setEnabled(false);
    ui->btn_disconnectUDP->setEnabled(false);

    model = new PingModel;

    connect(model, SIGNAL(signalData(QString)), ui->browser_dbg, SLOT(append(QString)));
    connect(model, SIGNAL(signalStartData()), this, SLOT(testStart()));
    connect(ui->btn_connectPing, SIGNAL(clicked()), this, SLOT(connectSlot()));
    connect(ui->btn_disconnectPing, SIGNAL(clicked(bool)),this, SLOT(disconnectSlot()));
    connect(ui->clearText, SIGNAL(clicked(bool)),  this, SLOT(clearSlot()));



    connect(&thread, SIGNAL(started()), model, SLOT(run()));


    //connect(model, SIGNAL(endThread()), &thread, SLOT(quit()));
    model->lineEditRead(ui->lineEdit->text());




    connect(ui->checkBox,SIGNAL(clicked(bool)), this, SLOT(updateScreen(bool)));
    ui->lineEdit->setToolTip("Поле ввода IP адреса");
    ui->btn_connectPing->setToolTip("Начать тестирование");
    ui->btn_disconnectPing->setToolTip("Закончить тестирование");

    ui->btn_connectUDP->setToolTip("Начать тестирование");
    ui->btn_disconnectUDP->setToolTip("Закончить тестирование");


    connect(model, SIGNAL(signalError()), this, SLOT(errorMsb()));


    //UDP

    connect(ui->btn_connectUDP, SIGNAL(clicked(bool)), this, SLOT(startTransmitUDP()));
    connect(ui->btn_disconnectUDP, SIGNAL(clicked(bool)), this, SLOT(stopTransmitUDP()));
    connect(&tmr_, SIGNAL(timeout()), this, SLOT(timerUDP()));

    QRegExp codeReg("[0-1]{1,8}");
    QRegExpValidator *ipValidator1 = new QRegExpValidator(codeReg, this);
    ui->lineEdit_packet1->setValidator(ipValidator1);

    ui->lineEdit_packet1->setToolTip("Последовательность из 8 бит. \n Первый бит- старший.");

//    Чтение настроек
    QFile file("ip.conf");
     if(file.size() == 0){
         ui->browser_dbg->setVisible(false);
         ui->clearText->setVisible(false);
         QMainWindow::resize(430, 150);
         QMainWindow::setMaximumSize(430, 150);
         return;
     }
     QSettings settings( "ip.conf", QSettings::IniFormat );
     settings.beginGroup( "saveState" );
     bool check = settings.value("check").toBool();
     ui->checkBox->setChecked(check);
     QVariant text = settings.value("ip");
     ui->lineEdit->setText( text.toString());
     ui->lineEdit_packet1->setText(settings.value("bit").toString());
     ui->spinBox->setValue(settings.value("spin").toInt());
     ui->spinBox_2->setValue(settings.value("spin2").toInt());
     settings.endGroup();
     //
     if(ui->checkBox->isChecked() == false){
         ui->browser_dbg->setVisible(false);
         ui->clearText->setVisible(false);
         QMainWindow::resize(430, 150);
         QMainWindow::setMaximumSize(430, 150);
     }
     // QMainWindow::resize(QMainWindow::sizeHint());
     else{
         QMainWindow::resize(430, 600);
         QMainWindow::setMaximumSize(430, 600);
     }
}




void MainWindow::startTransmitUDP(){
    //проверка
    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    QRegExp ipRegex ("^" + ipRange + "\\." + ipRange +
                     "\\." + ipRange + "\\." + ipRange + "$");
    if( ipRegex.exactMatch(ui->lineEdit->text()) == false){
        QMessageBox msb;
        msb.setText("Проверьте верность ip адреса");
        msb.exec();
        return;
    }
    //

    QString dataLbl(ui->lineEdit_packet1->text());
    QBitArray dataBit;//(str.count);
    dataBit.resize(dataLbl.count());
    //формирую массив битов
    for(int i = 0; i < dataBit.count(); i++){
        if(dataLbl[i] == '0')
            dataBit.setBit(i, false);
        if(dataLbl[i] == '1')
            dataBit.setBit(i, true);
    }
    // операция зеркалит данные dataByte[i/8] = (dataByte.at(i/8) | ((dataBit[i] ? 1 : 0) << (i % 8)));
    QBitArray temp(1);
    for(int i = 0; i < dataBit.size()/2; i++){
        temp[0] =  dataBit[i];
        dataBit[i] = dataBit[dataBit.size() - i - 1];
        dataBit[dataBit.size() - i -1] = temp[0];
    }
    dataByte_.clear();
    dataByte_.resize(dataBit.size()/ 8);
    for(int i = 0; i < dataByte_.size(); i++)
        dataByte_[i] = 0x00;
    for(int i = 0; i < dataBit.size(); i++)
        dataByte_[i/8] = (dataByte_.at(i/8) | ((dataBit[i] ? 1 : 0) << (i % 8)));
    QByteArray tempByte(dataByte_);
    for(int i = 0; i < ui->spinBox_2->value();  i++)
        dataByte_.append(tempByte);


    udp_.setHost(ui->lineEdit->text(), 666);
    tmr_.start(ui->spinBox->value());
    ui->btn_connectUDP->setEnabled(false);
    ui->btn_disconnectUDP->setEnabled(true);
}

void MainWindow::stopTransmitUDP(){

    tmr_.stop();
    ui->btn_connectUDP->setEnabled(true);
    ui->btn_disconnectUDP->setEnabled(false);
}


void MainWindow::timerUDP(){
    udp_.sendData(dataByte_);
}


void MainWindow::updateScreen(bool flag){
    if (flag == true){
        ui->browser_dbg->setVisible(true);
        ui->clearText->setVisible(true);
        QMainWindow::setMaximumSize(430, 600);
        QMainWindow::resize(430, 600);

    }
    else{
        ui->browser_dbg->setVisible(false);
        ui->clearText->setVisible(false);
         QMainWindow::resize(430, 150);
         QMainWindow::setMaximumSize(430, 150);

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
    //
    settings.setValue( "bit", ui->lineEdit_packet1->text() );
    settings.setValue( "spin", ui->spinBox->value() );
    settings.setValue( "spin2", ui->spinBox_2->value() );

    //
    settings.endGroup();
}

//Слоты

void MainWindow::connectSlot(){
    //проверка
    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    QRegExp ipRegex ("^" + ipRange + "\\." + ipRange +
                     "\\." + ipRange + "\\." + ipRange + "$");
    if( ipRegex.exactMatch(ui->lineEdit->text()) == false){
        QMessageBox msb;
        msb.setText("Проверьте верность ip адреса");
        msb.exec();
        return;
    }
    ui->statusLbl->setText("Подготовка к запуску");
    ui->btn_connectPing->setEnabled(false);
    ui->btn_disconnectPing->setEnabled(true);
    model->lineEditRead(ui->lineEdit->text());
    model->moveToThread(&thread);
    thread.start();

}
void MainWindow::disconnectSlot(){
ui->btn_connectPing->setEnabled(true);
 ui->btn_disconnectPing->setEnabled(false);
    model->disconPing();
    thread.quit();
    ui->statusLbl->setText("Тест остановлен");


}
void MainWindow::clearSlot(){
    ui->browser_dbg->clear();
}

