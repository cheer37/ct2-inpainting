#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->masque = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::on_actionQuitter_triggered()
{
    this->close();
}

void MainWindow::on_actionOuvrir_une_image_triggered()
{
    QString filters("Images (*.jpg *.jpeg *.png *.gif *.bmp *.tga *.tif *.tiff)");

    QString filename = QFileDialog::getOpenFileName(this, "Choisir l'image...", ":", filters,0, QFileDialog::HideNameFilterDetails);

    this->image = new CImage(filename);
    scene = new QGraphicsScene();
    scene->addItem(this->image);
    this->masque = new CImage(this->image->width(), this->image->height(), 1);
    scene->addItem(this->masque);
    this->masque->set_pen_size(ui->spinBox_size->value());
    this->masque->set_pen_mode(1);
    ui->graphicsView_img->setScene(scene);
}

void MainWindow::on_actionEnregistrer_l_image_triggered()
{
    QString Path = QFileDialog::getSaveFileName(this,
                                                     "Choisir un dossier",
                                                     ":","Images (*.jpg *.jpeg *.png *.gif *.bmp *.tga *.tif *.tiff)");
    if(!Path.isNull())
    {
        QImage img(this->scene->width(), this->scene->height(), QImage::Format_RGB32);
        QPainter painter;
        painter.begin(&img);
        this->scene->render(&painter);
        painter.end();
        img.save(Path);
    }
}

void MainWindow::on_Slider_valueChanged(int value)
{
    this->setupMatrix(value);
}

void MainWindow::setupMatrix(int i)
{
    qreal scale = ::pow(2.0, (i - 250) / 50.0);

    QMatrix matrix;
    matrix.scale(scale, scale);
    ui->graphicsView_img->setMatrix(matrix);
}


void MainWindow::on_pushButton_clear_clicked()
{
    if (this->masque != 0)
    {
        this->masque->Clear_img();
    }
}

void MainWindow::on_spinBox_size_valueChanged(int s)
{
    this->masque->set_pen_size(s);
}

void MainWindow::on_checkBox_masque_stateChanged(int a)
{
    if (this->masque != 0)
    {
        if (a)
            scene->addItem(this->masque);
        else
            scene->removeItem(this->masque);
    }
}

void MainWindow::on_toolButton_write_clicked()
{
    if (this->masque != 0)
    {
        this->masque->set_pen_mode(1);
    }
}

void MainWindow::on_toolButton_erase_clicked()
{
    if (this->masque != 0)
    {
        this->masque->set_pen_mode(0);
    }
}
