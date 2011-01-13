#ifndef DIALOG_UTIL_H
#define DIALOG_UTIL_H

#include <QDialog>

namespace Ui {
    class Dialog_util;
}

class Dialog_util : public QDialog {
    Q_OBJECT
public:
    Dialog_util(QWidget *parent = 0);
    ~Dialog_util();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Dialog_util *ui;
};

#endif // DIALOG_UTIL_H
