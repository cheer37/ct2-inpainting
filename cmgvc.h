#ifndef CMGVC_H
#define CMGVC_H

#include "cimage.h"
/*#include "cmatrimage.h"*/
#include "cimagedouble.h"
#include "cvector2f.h"
#include "QDebug"
#include <QProgressBar>
#include <iostream>

class CMgvc
{
public:
    CMgvc();

    void appliquer(CImage *init, CImage *masque, CImage *out, float param1, float param2);
    void set_progressbar(QProgressBar *);
private:
    double TransformInterval (double x, double min1, double max1, double min2, double max2);
    void ExpansionDynamique (CImageDouble * im, CImage * masque);
    void Laplacien(CImageDouble *in, CImageDouble *out);
    void Gradient(CImageDouble *in, CImageDouble * Rx, CImageDouble * Ry,CImageDouble *out);
    QProgressBar * progressbar;
};

#endif // CMGVC_H
