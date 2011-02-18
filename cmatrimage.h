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

    int  GetVal (int x, int y, int canal); //  0 <= canal <= 2
    void SetVal (int x, int y, int canal, int val); //  0 <= canal <= 2
    void SetData (int width, int height, int * data);
    QRgb GetRgb (int x, int y);

	QImage * GetQImage ();

    void Laplacien (CImage * In);
    void Gradient (CImage * In, CMatriMage * Rx, CMatriMage * Ry);

private:
    int width;
    int height;
    int * data;
};

#endif // CMATRIMAGE_H
