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
    settings.setValue("spliter", ui->splitter->saveState());
    settings.endGroup();
}

void MainWindow::loadSettings()
{
    qDebug() << "loading settings";
    QSettings settings(OrganizationName, ApplicationName);
    settings.beginGroup("MainWindow");

    //get values
    QRect rectWindow = settings.value("size", "800*600").toRect();
    QByteArray rectSpliter = settings.value("spliter").toByteArray();

    //set values
    this->setGeometry(rectWindow);
    ui->splitter->restoreState(rectSpliter);
}

void MainWindow::init_SignalSlots()
{
    //initialize signal and slots
    this->connect(&update, SIGNAL(broadcastMessage(QString)), this, SLOT(showMessage(QString)));

    //actions
    this->connect(ui->actionAbout, SIGNAL(triggered(bool)), this, SLOT(aboutWindow(bool)));
    this->connect(ui->actionCheck_for_Update, SIGNAL(triggered(bool)), this, SLOT(action_CheckForUpdate()));
    this->connect(ui->actionRun_Query, SIGNAL(triggered(bool)), this, SLOT(action_RunQuery()));
    this->connect(ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(action_Exit()));
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

void MainWindow::processQuery(QString Query)
{
    QSqlQuery qry;                          //var
    if(!qry.exec(Query))
       QMessageBox::warning(this, "Error", qry.lastError().text());
    else
    {
       showMessage("Query Execution Successfull");
       model = new QSqlQueryModel();
       model->setQuery(qry);

       //Query output
       QWidget *tabWidget;                  //var
       tabWidget = new QWidget();
       QTableView *tableView;               //var
       tableView = new QTableView(tabWidget);
       QHBoxLayout *hBoxLayout;             //var
       hBoxLayout = new QHBoxLayout(tabWidget);
       hBoxLayout->addWidget(tableView);
       tabWidget->setLayout(hBoxLayout);
       int index = ui->tabWidget->insertTab(ui->tabWidget->currentIndex() + 1, tabWidget, "Query output");
       ui->tabWidget->setCurrentIndex(index);
       tableView->setModel(model);
    }
}

//actions
void MainWindow::action_CheckForUpdate()
{
    update.updateCheck();
}

void MainWindow::action_RunQuery()
{
    RunQueryDialog runQueryDialog;
    runQueryDialog.setModal(true);
    runQueryDialog.setWindowTitle("Run Query");
    if(runQueryDialog.exec() == QDialog::Accepted)
    {
        qDebug() << "run query dialog accepted";
        QString Query;
        Query = runQueryDialog.returnQuery();
        qDebug() << "Transfered data: "+Query;

        processQuery(Query);
    }
}

void MainWindow::action_Exit()
{
    this->close();
}

MainWindow::~MainWindow()
{
    saveSettings();
    //database->closeDatabase();
    //qDebug() << "closing databse";
    delete ui;
}
