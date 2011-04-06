#ifndef CDIFFTENSOR_H
#define CDIFFTENSOR_H

#include "cimage.h"
#include <QDebug>

class CDiffTensor
{
public:
    CDiffTensor(CImage * _img, int _x, int _y);

    double * GetDiffTensor_r();
    double * GetDiffTensor_g();
    double * GetDiffTensor_b();
private:
    double * GetStrucTensor(CImage * _img, int _x, int _y, int _canal);
    double * CalcDiffTensMat(double * teta_m, double tmp_mult);

    double * DTMat_r;
    double * DTMat_g;
    double * DTMat_b;
};

#endif // CDIFFTENSOR_H
