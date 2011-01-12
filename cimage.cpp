#include "cimage.h"

CImage::CImage(QString s)
{
    this->image = new QImage(s);
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

