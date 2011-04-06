/**
 * @file ctschumperle.h
 * @brief Classe CTschumperle
 * @author Simon Reynard, Yoan Vergeot
 * @date 2010-2011
 *
 * Description de la classe CDiffTensor, methode d'inpainting de Tschumperle
 *
 */
#ifndef CTSCHUMPERLE_H
#define CTSCHUMPERLE_H

#include "cimage.h"
#include "chessian.h"
#include "cdifftensor.h"
#include <QProgressBar>
#include <QDebug>

/** @class CTschumperle
 * @brief application d'inpainting
 *
 * Classe permettant d'effectuer un inpainting sur une image
 */
class CTschumperle
{
public:
    CTschumperle();

    void appliquer(CImage *init, CImage *masque, CImage *out, float _iteration, float dt);
    void set_progressbar(QProgressBar *);
private:
    QProgressBar * progressbar;

};

#endif // CTSCHUMPERLE_H
