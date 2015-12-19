#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "checkforupdate.h"

#include <QCoreApplication>
#include <QMainWindow>
#include <QMessageBox>

//class CheckForUpdate;

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

    //update
    CheckForUpdate update;

    void initSignalSlots();
    Ui::MainWindow *ui;

signals:

private slots:
    void showMessage(QString message);
    void aboutWindow(bool);

    //action
    void action_CheckForUpdate();
};

#endif // MAINWINDOW_H
