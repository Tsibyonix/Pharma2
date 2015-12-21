#include "runquerydialog.h"
#include "ui_runquerydialog.h"

RunQueryDialog::RunQueryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RunQueryDialog)
{
    ui->setupUi(this);
}

RunQueryDialog::~RunQueryDialog()
{
    delete ui;
}
