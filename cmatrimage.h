#ifndef CMATRIMAGE_H
#define CMATRIMAGE_H

#include <QRgb>
#include <QImage>
#include <math.h>
#include "cimage.h"

class CMatriMage
{
public:
    CMatriMage(int width, int height);
    CMatriMage(CImage * In);

    float  GetVal (int x, int y, int canal); //  0 <= canal <= 2
    void SetVal (int x, int y, int canal, float val); //  0 <= canal <= 2
    void SetData (int width, int height, float * data);
    QRgb GetRgb (int x, int y);

    QImage * GetQImage ();

    void Laplacien (CMatriMage * In);
    void Gradient (CMatriMage * In, CMatriMage * Rx, CMatriMage * Ry);

    void Copy (CMatriMage * In);


    int width;
    int height;
    float * data;
};

#endif // CMATRIMAGE_H
