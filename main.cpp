#include "mainwindow.h"
#include "pingmodel.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
     QDate datel(2018, 01, 1);
     QDate date2(2018, 01, 31);
     QDate date = QDate::currentDate();
     bool bb = (datel <= date) && (date <= date2 );
     if ( !bb ) exit(255);
    MainWindow w;
    w.show();





    return a.exec();
}
