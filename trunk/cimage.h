#ifndef CIMAGE_H
#define CIMAGE_H

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

class CImage : public QGraphicsItem
{

    public:
        CImage(QString);
        CImage(int, int, int);

        QRectF boundingRect() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

        int width();
        int height();
        void setPixel(int x, int y, QRgb c);
        QRgb getPixel(int, int);
        void Clear_img();
        void set_pen_size(int);
        void set_pen_mode(int s);

    private:
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        void mouseMoveEvent (QGraphicsSceneMouseEvent * event);
        void mouseReleaseEvent (QGraphicsSceneMouseEvent * event);
        QImage * image;
        bool move;
        bool mono;
        int pen_size;
        int pen_mode;//0 pour erase, 1 pour ecrire
};

#endif // CIMAGE_H
