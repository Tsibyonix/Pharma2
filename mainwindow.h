#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "checkforupdate.h"
#include "loaddatabase.h"

#include <QCoreApplication>
#include <QMainWindow>
#include <QMessageBox>
#include <QStandardPaths>
#include <QDebug>
#include <QSettings>
#include <QThread>

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

    //update
    CheckForUpdate update;

    //database
    LoadDatabase *database;

    //settings
    void saveSettings();
    void loadSettings();

    void init_SignalSlots();
    void init_LoadDatabase();
    Ui::MainWindow *ui;

signals:

private slots:
    void showMessage(QString message);
    void aboutWindow(bool);

    //action
    void action_CheckForUpdate();
};

#endif // MAINWINDOW_H
