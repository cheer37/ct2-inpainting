/**
 * @file chessian.cpp
 * @brief Methodes de la classe @see CHessian
 * @author Simon Reynard, Yoan Vergeot
 * @date 2010-2011
 *
 * Methodes de la classe CHessian
 *
 */
#include "chessian.h"

/**
* @fn CHessian constructeur
*/
CHessian::CHessian()
{
}

/**
* @fn GetHessian Renvoie la matrice correspondant a la hessienne pour un pixel et un canal d'une image donnée
*                _canal: 1:red, 2:green, 3:blue
* @param _img image a traiter, _x coord x du pixel, _y coord y du pixel, _canal canal a traiter
* @return double * matrice 2x2
*/
double * CHessian::GetHessian(CImageDouble * _img, int _x, int _y, int _canal)
{
    double * mat = new double[4];
    /*Calcul de la matrice hessienne pour un pixel selon le canal voulu*/
    if (_canal == 0)
    {
        mat[0] = (_img->getRedPixel(_x+1, _y)-2.0*_img->getRedPixel(_x, _y)+_img->getRedPixel(_x-1, _y));
        /*mat[1] = (_img->getRedPixel(_x+1, _y+1)-_img->getRedPixel(_x-1, _y+1)-_img->getRedPixel(_x+1, _y-1)+_img->getRedPixel(_x-1, _y-1));*/
        mat[1] = 0.25*(_img->getRedPixel(_x-1, _y-1)+_img->getRedPixel(_x+1, _y+1)-_img->getRedPixel(_x+1, _y-1)+_img->getRedPixel(_x-1, _y+1));
        mat[2] = mat[1];
        mat[3] = (_img->getRedPixel(_x, _y+1)-2.0*_img->getRedPixel(_x, _y)+_img->getRedPixel(_x, _y-1));
    }
    else if (_canal == 1)
    {
        mat[0] = (_img->getGreenPixel(_x+1, _y)-2.0*_img->getGreenPixel(_x, _y)+_img->getGreenPixel(_x-1, _y));
        /*mat[1] = (_img->getGreenPixel(_x+1, _y+1)-_img->getGreenPixel(_x-1, _y+1)-_img->getGreenPixel(_x+1, _y-1)+_img->getGreenPixel(_x-1, _y-1));*/
        mat[1] = 0.25*(_img->getGreenPixel(_x+1, _y+1)-_img->getGreenPixel(_x-1, _y+1)-_img->getGreenPixel(_x+1, _y-1)+_img->getGreenPixel(_x-1, _y-1));
        mat[2] = mat[1];
        mat[3] = (_img->getGreenPixel(_x, _y+1)-2.0*_img->getGreenPixel(_x, _y)+_img->getGreenPixel(_x, _y-1));
    }
    else if (_canal == 2)
    {
        mat[0] = (_img->getBluePixel(_x+1, _y)-2.0*_img->getBluePixel(_x, _y)+_img->getBluePixel(_x-1, _y));
       /* mat[1] = (_img->getBluePixel(_x+1, _y+1)-_img->getBluePixel(_x-1, _y+1)-_img->getBluePixel(_x+1, _y-1)+_img->getBluePixel(_x-1, _y-1));*/
        mat[1] = 0.25*(_img->getBluePixel(_x+1, _y+1)-_img->getBluePixel(_x-1, _y+1)-_img->getBluePixel(_x+1, _y-1)+_img->getBluePixel(_x-1, _y-1));
        mat[2] = mat[1];
        mat[3] = (_img->getBluePixel(_x, _y+1)-2.0*_img->getBluePixel(_x, _y)+_img->getBluePixel(_x, _y-1));
    }
    return mat;
}
