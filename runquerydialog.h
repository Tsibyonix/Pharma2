#ifndef RUNQUERYDIALOG_H
#define RUNQUERYDIALOG_H

#include <QDialog>

namespace Ui {
class RunQueryDialog;
}

class RunQueryDialog : public QDialog
{
    Q_OBJECT

public:
    QString returnQuery();
    explicit RunQueryDialog(QWidget *parent = 0);
    ~RunQueryDialog();

private:
    Ui::RunQueryDialog *ui;
};

#endif // RUNQUERYDIALOG_H
