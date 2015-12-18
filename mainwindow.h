#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCoreApplication>
#include <QMainWindow>
#include <QMessageBox>

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
    //QCoreApplication info;
    QString ApplicationName;
    QString ApplicationVersion;
    QString OrganizationName;
    QString SubVersion;


    void initSignalSlots();
    Ui::MainWindow *ui;

private slots:
    void aboutWindow(bool);
};

#endif // MAINWINDOW_H
