#ifndef CTSCHUMPERLE_H
#define CTSCHUMPERLE_H

#include "cimage.h"
#include "chessian.h"
#include "cdifftensor.h"
#include <QProgressBar>

class CTschumperle
{
public:
    CTschumperle();

    void appliquer(CImage *init, CImage *masque, CImage *out, float _iteration, float param2);
    void set_progressbar(QProgressBar *);
private:
    QProgressBar * progressbar;

};

#endif // CTSCHUMPERLE_H
