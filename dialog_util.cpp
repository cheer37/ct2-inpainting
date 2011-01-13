#include "dialog_util.h"
#include "ui_dialog_util.h"

Dialog_util::Dialog_util(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_util)
{
    ui->setupUi(this);
}

Dialog_util::~Dialog_util()
{
    delete ui;
}

void Dialog_util::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
