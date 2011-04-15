/**
 * @file chessian.h
 * @brief Classe CHessian
 * @author Simon Reynard, Yoan Vergeot
 * @date 2010-2011
 *
 * Description de la classe CHessian, calcul de la hessienne d'un pixel
 *
 */
#ifndef CHESSIAN_H
#define CHESSIAN_H

#include "cimagedouble.h"

/** @class CHessian
 * @brief calcul de la hessienne
 *
 * Classe permettant de calculer la hessienne pour un pixel d'une image
 */
class CHessian
{
public:
    CHessian();
    static double * GetHessian(CImageDouble * _img, int _x, int _y, int _canal);

};

#endif // CHESSIAN_H
