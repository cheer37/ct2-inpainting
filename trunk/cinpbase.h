#ifndef CINPBASE_H
#define CINPBASE_H

#include "cimage.h"
#include "cimagedouble.h"
#include <QProgressBar>
#include <QDebug>

class CInpBase
{
public:
    CInpBase();

    void appliquer(CImage *init, CImage *masque, CImage *out, float _lambda, float _dt, float _distance);
    void set_progressbar(QProgressBar *);
private:
    double TransformInterval (double x, double min1, double max1, double min2, double max2);
    void ExpansionDynamique (CImageDouble * im, CImage * masque);
    void Laplacien(CImageDouble *in, CImageDouble *out);
    double Distance(CImageDouble *im1, CImageDouble *im2);
    QProgressBar * progressbar;
};

#endif // CINPBASE_H
