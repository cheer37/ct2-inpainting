#ifndef CMGVC_H
#define CMGVC_H

#include "cimage.h"
#include "cmatrimage.h"
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
    QProgressBar * progressbar;
};

#endif // CMGVC_H
