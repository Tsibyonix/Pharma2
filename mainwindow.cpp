#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ApplicationName = "Pharma";
    ApplicationVersion = "2.0";
    OrganizationName = "tSibyonix";
    SubVersion = "0";

    ui->setupUi(this);

    initSignalSlots();
    //update->updateCheck();
}

void MainWindow::initSignalSlots()
{
    //initialize signal and slots
    this->connect(ui->actionAbout, SIGNAL(triggered(bool)), this, SLOT(aboutWindow(bool)));
    this->connect(ui->actionCheck_for_Update, SIGNAL(triggered(bool)), this, SLOT(action_CheckForUpdate()));
    this->connect(&update, SIGNAL(broadcastMessage(QString)), this, SLOT(showMessage(QString)));
}

void MainWindow::showMessage(QString message)
{
    ui->statusBar->showMessage(message, 6000);
}

void MainWindow::aboutWindow(bool action)
{
    QMessageBox messageBox;
    messageBox.information(this, "About", ApplicationName+" "+ApplicationVersion+"."+SubVersion);
    messageBox.show();
}

//actions
void MainWindow::action_CheckForUpdate()
{
    update.updateCheck();
}

MainWindow::~MainWindow()
{
    delete ui;
}
