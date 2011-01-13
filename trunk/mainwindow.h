#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QFileDialog>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QtUiTools/quiloader.h>
#include "cimage.h"
#include "dialog_util.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    CImage * image;
    CImage * masque;
    CImage * resultat;
    QLabel * label_img;
    QGraphicsScene *scene;

    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    void setupMatrix(int i);

private slots:
    void on_actionUtilisation_triggered();
    void on_radioButton_2_clicked();
    void on_radioButton_1_clicked();
    void on_actionAbout_triggered();
    void on_pushButton_go_clicked();
    void on_checkBox_res_stateChanged(int );
    void on_actionOuvrir_un_masque_triggered();
    void on_actionEnregistrer_le_masque_triggered();
    void on_toolButton_erase_clicked();
    void on_toolButton_write_clicked();
    void on_checkBox_masque_stateChanged(int );
    void on_spinBox_size_valueChanged(int );
    void on_pushButton_clear_clicked();
    void on_Slider_valueChanged(int value);
    void on_actionEnregistrer_l_image_triggered();
    void on_actionOuvrir_une_image_triggered();
    void on_actionQuitter_triggered();
};

#endif // MAINWINDOW_H
