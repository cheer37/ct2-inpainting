#ifndef CIMAGE_H
#define CIMAGE_H

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>

class CImage : public QGraphicsItem
{

    public:
        QImage * image;

        CImage(QString);

        QRectF boundingRect() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // CIMAGE_H
