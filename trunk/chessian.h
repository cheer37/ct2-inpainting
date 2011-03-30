#ifndef CHESSIAN_H
#define CHESSIAN_H

#include "cimage.h"

class CHessian
{
public:
    CHessian();
    static double * GetHessian(CImage * _img, int _x, int _y, int _canal);

};

#endif // CHESSIAN_H
