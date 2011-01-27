#include "ctschumperle.h"

CTschumperle::CTschumperle()
{

}

void CTschumperle::appliquer(CImage *init, CImage *masque, CImage *out, float param1, float param2)
{
    int w = init->width();
    this->progressbar->setMaximum(w);//initialise la progressbar
    for (int i = 0; i < init->width(); ++i)
    {
        this->progressbar->setValue(this->progressbar->value()+1);//incremente la progressbar
        for(int j = 0; j < init->height(); ++j)
        {
            if (masque->getPixel(i, j) == qRgba(0, 0, 0, 255))
                out->setPixel(i, j, qRgb(0, 0, 0));
            else
                out->setPixel(i, j, init->getPixel(i, j));
        }
    }
}

void CTschumperle::set_progressbar(QProgressBar * bar)
{
    this->progressbar = bar;
}
