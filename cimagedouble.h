#ifndef CIMAGEDOUBLE_H
#define CIMAGEDOUBLE_H

#include "cimage.h"
#include "QImage"

class CImageDouble
{
    public:
        CImageDouble(CImage *_in);
        ~CImageDouble();

        double getRedPixel(int _x, int _y);
        double getGreenPixel(int _x, int _y);
        double getBluePixel(int _x, int _y);

        void setRedPixel(int _x, int _y, double _val);
        void setGreenPixel(int _x, int _y, double _val);
        void setBluePixel(int _x, int _y, double _val);

        void Copy(CImageDouble * _in);
        QImage * getQimage();

        void afficher_valeurs();

        int width, height;
    private:

        double *r_c;
        double *g_c;
        double *b_c;
};

#endif // CIMAGEDOUBLE_H
