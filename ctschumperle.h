#ifndef CTSCHUMPERLE_H
#define CTSCHUMPERLE_H

#include "cimage.h"
#include "chessian.h"
#include "cdifftensor.h"
#include <QProgressBar>
#include <QDebug>

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
