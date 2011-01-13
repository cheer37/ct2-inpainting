#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->masque = 0;
    this->image = 0;
    this->resultat = 0;
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
    QString filters("Images (*.jpg *.jpeg *.pgm *.png *.gif *.bmp *.tga *.tif *.tiff)");

    QString filename = QFileDialog::getOpenFileName(this, "Choisir l'image...", ":", filters,0, QFileDialog::HideNameFilterDetails);

    if (!filename.isEmpty())
    {
        this->ui->checkBox_masque->setChecked(true);
        this->ui->checkBox_res->setChecked(false);
        this->image = new CImage(filename);
        scene = new QGraphicsScene();
        scene->addItem(this->image);

        this->masque = new CImage(this->image->width(), this->image->height(), 1);//1 pour image mono (masque) ARGB
        this->masque->set_pen_size(ui->spinBox_size->value());
        this->masque->set_pen_mode(1);
        scene->addItem(this->masque);
        this->resultat = new CImage(this->image->width(), this->image->height(), 0);//0 pour image normale RGB
        ui->graphicsView_img->setScene(scene);
    }
}

void MainWindow::on_actionOuvrir_un_masque_triggered()
{
    if (this->image == 0)
    {
        QMessageBox::information(this, "Attention", "Veuillez ouvrir une image en premier.") ;
    }
    else
    {
        QString filters("Images (*.jpg *.jpeg *.pgm *.png *.gif *.bmp *.tga *.tif *.tiff)");

        QString filename = QFileDialog::getOpenFileName(this, "Choisir le masque...", ":", filters,0, QFileDialog::HideNameFilterDetails);
        this->masque->charger_masque(filename);
    }
}

void MainWindow::on_actionEnregistrer_l_image_triggered()
{
    QString Path = QFileDialog::getSaveFileName(this,
                                                     "Choisir un dossier",
                                                     ":","Images (*.jpg *.pgm *.jpeg *.pgm *.png *.gif *.bmp *.tga *.tif *.tiff)");
    if(!Path.isNull())
    {
        /*QImage img(this->scene->width(), this->scene->height(), QImage::Format_RGB32);
        QPainter painter;
        painter.begin(&img);
        this->scene->render(&painter);
        painter.end();
        img.save(Path);*/
        this->resultat->save(Path);
    }
}

void MainWindow::on_actionEnregistrer_le_masque_triggered()
{
    QString Path = QFileDialog::getSaveFileName(this,
                                                     "Choisir un dossier",
                                                     ":","Images (*.jpg *.jpeg *.pgm *.png *.gif *.bmp *.tga *.tif *.tiff)");
    if(!Path.isNull())
    {
        this->masque->save(Path);
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
    if (this->masque != 0)
    {
        this->masque->set_pen_size(s);
    }
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


void MainWindow::on_checkBox_res_stateChanged(int a)
{
    if (this->resultat != 0)
    {
        if (a)
            scene->addItem(this->resultat);
        else
            scene->removeItem(this->resultat);
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



/*
  A modifier pr lancer le traitement sur les images, ici je fusionne juste l'image et le masque dans resultat pour exemple
  */
void MainWindow::on_pushButton_go_clicked()
{
    if (this->image != 0 && this->resultat != 0)// si image et resultat instanciées
    {
        if (this->ui->radioButton_1->isChecked())//si methode 1 coché
        {
            for (int i = 0; i < this->image->width(); ++i) {
                for(int j = 0; j < this->image->height(); ++j) {
                    if (this->masque->getPixel(i, j) == qRgba(0, 0, 0, 255))
                        this->resultat->setPixel(i, j, qRgb(0, 0, 0));
                    else
                        this->resultat->setPixel(i, j, this->image->getPixel(i, j));
                }
            }
        }
        else if (this->ui->radioButton_2->isChecked())
        {
            QMessageBox::information(this, "Attention", "Methode 2 non implementee!") ;
        }
    }
}
