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

    dbPathList = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation);

    ui->setupUi(this);
    loadSettings();

    init_SignalSlots();
    init_LoadDatabase();
}

void MainWindow::saveSettings()
{
    qDebug() << "saving settings";
    QSettings settings(OrganizationName, ApplicationName);
    settings.beginGroup("MainWindow");
    settings.setValue("size", this->geometry());
    settings.endGroup();
}

void MainWindow::loadSettings()
{
    qDebug() << "loading settings";
    QSettings settings(OrganizationName, ApplicationName);
    settings.beginGroup("MainWindow");
    QRect rect = settings.value("size", "800*600").toRect();
    this->setGeometry(rect);
}

void MainWindow::init_SignalSlots()
{
    //initialize signal and slots
    this->connect(ui->actionAbout, SIGNAL(triggered(bool)), this, SLOT(aboutWindow(bool)));
    this->connect(ui->actionCheck_for_Update, SIGNAL(triggered(bool)), this, SLOT(action_CheckForUpdate()));
    this->connect(&update, SIGNAL(broadcastMessage(QString)), this, SLOT(showMessage(QString)));
}

void MainWindow::init_LoadDatabase()
{
    qDebug() << "Loading Database";
    database = new LoadDatabase(dbPathList, this);
    LoadDatabaseThread = new QThread;
    this->connect(database, SIGNAL(broadcastMessage(QString)), this, SLOT(showMessage(QString)));
    this->connect(LoadDatabaseThread, SIGNAL(started()), database, SLOT(loadDatabase()));
    this->connect(database, SIGNAL(finished()), LoadDatabaseThread, SLOT(quit()));
    this->connect(database, SIGNAL(finished()), database, SLOT(deleteLater()));
    this->connect(LoadDatabaseThread, SIGNAL(finished()), LoadDatabaseThread, SLOT(deleteLater()));
    LoadDatabaseThread->start();


    if(database->returnDatabaseState() == 0)
        showMessage("Database loaded");
    else
        showMessage("Database not loaded");
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
    saveSettings();
    database->closeDatabase();
    qDebug() << "closing databse";
    delete ui;
}
