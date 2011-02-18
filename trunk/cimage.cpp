#include "cimage.h"

CImage::CImage(QString s)
{
    this->image = new QImage(s);
    this->move = false;
    this->mono = false;
    this->pen_size = 0;
}

CImage::CImage(int width, int height, int type)
{
    if (type == 1)
    {
        this->image = new QImage(width, height, QImage::Format_ARGB32);
        for (int i = 0; i < this->image->width(); ++i) {
            for(int j = 0; j < this->image->height(); ++j)
                this->image->setPixel(i, j, qRgba(255, 255, 255, 0));
        }
        this->move = false;
        this->mono = true;
        this->pen_size = 1;
    }
    else if (type == 0)
    {
        this->image = new QImage(width, height, QImage::Format_RGB32);
        for (int i = 0; i < this->image->width(); ++i) {
            for(int j = 0; j < this->image->height(); ++j)
                this->image->setPixel(i, j, qRgb(255, 255, 255));
        }
        this->move = false;
        this->mono = false;
        this->pen_size = 0;
    }

}

void CImage::Clear_img()
{
    for (int i = 0; i < this->image->width(); ++i) {
        for(int j = 0; j < this->image->height(); ++j)
            this->image->setPixel(i, j, qRgba(255, 255, 255, 0));
    }
    this->update();
}

void CImage::set_pen_size(int s)
{
    if (mono)
        this->pen_size = s;
}

void CImage::set_pen_mode(int s)
{
    if (mono)
        this->pen_mode = s;
}

QRectF CImage::boundingRect() const
{
    return QRectF(0, 0, this->image->width(), this->image->height());
}

void CImage::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);
    this->setZValue(5);
    painter->drawImage(QPoint(0, 0), *this->image);
}

void CImage::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    this->move = true;
}

void CImage::mouseMoveEvent (QGraphicsSceneMouseEvent * event)
{
    if (this->move && this->mono) {
        QPointF pt = event->scenePos();
        if (this->pen_mode)
        {
            for (int i = -this->pen_size; i < this->pen_size; ++i)
                for(int j = -this->pen_size; j < this->pen_size; ++j) {
                    if ((pt.x()+i >= 0 && pt.x()+i < this->image->width() && pt.y()+j >= 0 && pt.y()+j < this->image->height()))
                        this->image->setPixel(pt.x()+i, pt.y()+j, qRgba(0, 0, 0, 255));
                }
        }
        else
        {
            for (int i = -this->pen_size; i < this->pen_size; ++i)
                for(int j = -this->pen_size; j < this->pen_size; ++j) {
                    if ((pt.x()+i >= 0 && pt.x()+i < this->image->width() && pt.y()+j >= 0 && pt.y()+j < this->image->height()))
                        this->image->setPixel(pt.x()+i, pt.y()+j, qRgba(255, 255, 255, 0));
                }
        }
        this->update();
    }
}

void CImage::charger_masque(QString s)
{
    if (this->mono)
    {
        QImage *tmp = new QImage(s);
        if (tmp->width() != this->image->width() || tmp->height() != this->image->height())
             QMessageBox::warning(0, "Attention", "Le masque n'est pas de la meme taille que l'image!") ;
        else
        {
            if (tmp->format() != QImage::Format_ARGB32)
            {
                for (int i = 0; i < this->image->width(); ++i) {
                    for(int j = 0; j < this->image->height(); ++j)
                    {
                        if (tmp->pixel(i, j) == qRgb(255, 255, 255))
                            this->image->setPixel(i, j, qRgba(255, 255, 255, 0));
                        else
                            this->image->setPixel(i, j, qRgba(0, 0, 0, 255));
                    }
                }
            }
            else
            {
                for (int i = 0; i < this->image->width(); ++i) {
                    for(int j = 0; j < this->image->height(); ++j)
                    {
                        if (tmp->pixel(i, j) == qRgba(255, 255, 255, 0))
                            this->image->setPixel(i, j, qRgba(255, 255, 255, 0));
                        else
                            this->image->setPixel(i, j, qRgba(0, 0, 0, 255));
                    }
                }
            }
        }
        delete tmp;
        this->update();
    }

}

void CImage::mouseReleaseEvent (QGraphicsSceneMouseEvent * event)
{
    Q_UNUSED(event);
    this->move = false;
}

int CImage::width()
{
    return this->image->width();
}

int CImage::height()
{
    return this->image->height();
}

void CImage::setPixel(int x, int y, QRgb c)
{
    this->image->setPixel(x, y, c);
}

QRgb CImage::getPixel(int x, int y)
{
	if ( x < 0)
		x = abs(x)-1;
	else if ( x >= this->width())
		x = this->width() - (x-this->width()) - 1;
	if ( y < 0)
		y = abs(y)-1;
	else if ( y >= this->height())
		y = this->height() - (y-this->height()) - 1;

    return this->image->pixel(x, y);
}

int CImage::getRedPixel (int x, int y)
{
    return qRed(this->getPixel(x,y));
}

int CImage::getGreenPixel (int x, int y)
{
    return qGreen(this->getPixel(x,y));
}


int CImage::getBluePixel (int x, int y)
{
    return qBlue(this->getPixel(x,y));
}

void CImage::save(QString path)
{
    this->image->save(path);
}


void CImage::Copy(CImage * in)
{
	delete this->image;
	QImage * tmp = new QImage(*in->image);
	this->image = tmp;
}

void CImage::Copy(QImage * in)
{
	delete this->image;
	QImage * tmp = new QImage(*in);
	this->image = tmp;
}

QImage CImage::Filtre_lineraire(double m [], int n)
{
    return QImage();
}

QImage CImage::Laplacien()
{
    double m [] = {0.0, 0.0, -1.0, -1.0, -1.0, 0.0, 0.0,
                   0.0, -1.0, -3.0, -3.0, -3.0, -1.0, 0.0,
                   -1.0, -3.0, 0.0, 7.0, 0.0, -3.0, -1.0,
                   -1.0, -3.0, 7.0, 24.0, 7.0, -3.0, -1.0,
                   -1.0, -3.0, 0.0, 7.0, 0.0, -3.0, -1.0,
                   0.0, -1.0, -3.0, -3.0, -3.0, -1.0, 0.0,
                   0.0, 0.0, -1.0, -1.0, -1.0, 0.0, 0.0};
    return Filtre_lineraire(m, 7);
}

QImage CImage::Gradient()
{
    /*double dx [] = {-1.0, 0.0, 1.0,
                    -2.0, 0.0, 2.0,
                    -1.0, 0.0, 1.0};
    double dy [] = {-1.0, -2.0, -1.0,
                    0.0, 0.0, 0.0,
                    1.0, 2.0, 1.0};

    QImage i_dx = Filtre_lineraire(dx, 3);
    QImage i_dy = Filtre_lineraire(dy, 3);
    QImage tmp(i_dx.width(), i_dx.height(), QImage::Forma);

    for (int i = 0; i < i_dx.width(); ++i)
    {
        for (int j = 0; j < i_dx.height(); ++j)
        {
            QRgb px = i_dx.pixel(i, j);
            QRgb py = i_dy.pixel(i, j);
            int r = sqrt(qRed(px)*qRed(px)+qRed(py)*qRed(py));
            int g = sqrt(qGreen(px)*qGreen(px)+qGreen(py)*qGreen(py));
            int b = sqrt(qBlue(px)*qBlue(px)+qBlue(py)*qBlue(py));
            int val = (r+g+b)/3;
            tmp.setPixel(i, j, qGray(r, g, b));
        }
    }
    delete i_dx;
    delete i_dy;
    return tmp;*/
    return QImage();
}
