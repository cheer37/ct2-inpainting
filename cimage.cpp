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
    return this->image->pixel(x, y);
}

void CImage::save(QString path)
{
    this->image->save(path);
}
