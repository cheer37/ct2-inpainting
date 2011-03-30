#include "chessian.h"

CHessian::CHessian()
{
}

double * CHessian::GetHessian(CImage * _img, int _x, int _y, int _canal)
{
    double * mat = new double[4];
    if (_canal == 0)
    {
        mat[0] = (_img->getRedPixel(_x+1, _y)-2*_img->getRedPixel(_x, _y)+_img->getRedPixel(_x-1, _y))/4;
        mat[1] = (_img->getRedPixel(_x+1, _y+1)-_img->getRedPixel(_x-1, _y+1)-_img->getRedPixel(_x+1, _y-1)+_img->getRedPixel(_x-1, _y-1))/4;
        mat[2] = mat[1];
        mat[3] = (_img->getRedPixel(_x, _y+1)-2*_img->getRedPixel(_x, _y)+_img->getRedPixel(_x, _y-1))/4;
    }
    else if (_canal == 1)
    {
        mat[0] = (_img->getGreenPixel(_x+1, _y)-2*_img->getGreenPixel(_x, _y)+_img->getGreenPixel(_x-1, _y))/4;
        mat[1] = (_img->getGreenPixel(_x+1, _y+1)-_img->getGreenPixel(_x-1, _y+1)-_img->getGreenPixel(_x+1, _y-1)+_img->getGreenPixel(_x-1, _y-1))/4;
        mat[2] = mat[1];
        mat[3] = (_img->getGreenPixel(_x, _y+1)-2*_img->getGreenPixel(_x, _y)+_img->getGreenPixel(_x, _y-1))/4;
    }
    else if (_canal == 2)
    {
        mat[0] = (_img->getBluePixel(_x+1, _y)-2*_img->getBluePixel(_x, _y)+_img->getBluePixel(_x-1, _y))/4;
        mat[1] = (_img->getBluePixel(_x+1, _y+1)-_img->getBluePixel(_x-1, _y+1)-_img->getBluePixel(_x+1, _y-1)+_img->getBluePixel(_x-1, _y-1))/4;
        mat[2] = mat[1];
        mat[3] = (_img->getBluePixel(_x, _y+1)-2*_img->getBluePixel(_x, _y)+_img->getBluePixel(_x, _y-1))/4;
    }
    return mat;
}
