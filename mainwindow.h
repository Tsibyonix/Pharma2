#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "checkforupdate.h"
#include "loaddatabase.h"
#include "runquerydialog.h"

#include <QCoreApplication>
#include <QMainWindow>
#include <QMessageBox>
#include <QStandardPaths>
#include <QDebug>
#include <QSettings>
#include <QThread>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QPushButton>
#include <QLayoutItem>
#include <QSqlTableModel>

//ui

#include <QTableView>

//class CheckForUpdate;
class LoadDatabase;

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
    QString ApplicationName;
    QString ApplicationVersion;
    QString OrganizationName;
    QString SubVersion;

    QStringList dbPathList;

    QThread *LoadDatabaseThread;

    QSqlQueryModel *model;

    QPushButton *addButton;
    QPushButton *deleteButton;
    QPushButton *submitButton;
    QPushButton *revertButton;

    //update
    CheckForUpdate update;

    //database
    LoadDatabase *database;

    QTableView *tableView;
    QSqlTableModel *tableModel;

    //settings
    void saveSettings();
    void loadSettings();

    void init_SignalSlots();
    void init_LoadDatabase();


    void processQuery(QString Query, QString Title);
    void createTab(QString selection);
    void setupTable(QString table);
    Ui::MainWindow *ui;

signals:

private slots:
    void showMessage(QString message);
    void aboutWindow(bool);
    void closeTab(int index);
    void tabChanged(int index);

    void tableListSelectionChanged(QModelIndex index);
    void addButtonPressed();
    void deleteButtonPressed();
    void submitButtonPressed();

    //action
    void action_CheckForUpdate();
    void action_RunQuery();
    void action_Exit();

    void init_TableList();
};

#endif // MAINWINDOW_H
