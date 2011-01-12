#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QFileDialog>
#include <QDir>
#include <QDebug>
#include "cimage.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    CImage * image;
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
    void on_Slider_valueChanged(int value);
    void on_actionEnregistrer_l_image_triggered();
    void on_actionOuvrir_une_image_triggered();
    void on_actionQuitter_triggered();
};

#endif // MAINWINDOW_H
