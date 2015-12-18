#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //info.setApplicationName("Pharma");
    //info.setApplicationVersion("2.0");
    //info.setOrganizationName("tSibyonixo");
    ApplicationName = "Pharma";
    ApplicationVersion = "2.0";
    OrganizationName = "tSibyonix";
    SubVersion = "0";


    ui->setupUi(this);
    initSignalSlots();
}

void MainWindow::initSignalSlots()
{
    //initialize signal and slots

    this->connect(ui->actionAbout, SIGNAL(triggered(bool)), this, SLOT(aboutWindow(bool)));
}

void MainWindow::aboutWindow(bool action)
{
    QMessageBox messageBox;
    messageBox.information(this, "About", ApplicationName+" "+ApplicationVersion+"."+SubVersion);
    messageBox.show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
