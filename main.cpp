#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    a.setApplicationVersion("2.0");
//    a.setApplicationName("Pharma");
//    a.setApplicationDisplayName("Pharma");
    MainWindow w;
    w.show();

    return a.exec();
}
