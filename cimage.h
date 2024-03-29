#ifndef CIMAGE_H
#define CIMAGE_H

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QDebug>
#include <QMessageBox>
#include <QGraphicsSceneMouseEvent>
#include "math.h"

class CImage : public QGraphicsItem
{

    public:
        QImage * image;

        CImage(QString);
        CImage(int width, int height, int type);

        QRectF boundingRect() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

        int width();
        int height();
        void setPixel(int x, int y, QRgb c);
        QRgb getPixel(int, int);
        int getRedPixel (int, int);
        int getGreenPixel (int, int);
        int getBluePixel (int, int);
        void Clear_img();
        void set_pen_size(int);
        void set_pen_mode(int s);
        void save(QString);
        void charger_masque(QString);
        void Copy(CImage * in);
        void Copy(QImage * in);

    private:
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        void mouseMoveEvent (QGraphicsSceneMouseEvent * event);
        void mouseReleaseEvent (QGraphicsSceneMouseEvent * event);

        QImage Filtre_lineraire(double m [], int n);

        bool move;
        bool mono;
        int pen_size;
        int pen_mode;//0 pour erase, 1 pour ecrire
};

#endif // CIMAGE_H
