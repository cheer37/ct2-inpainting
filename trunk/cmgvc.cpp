#include "cmgvc.h"

CMgvc::CMgvc()
{
}

void CMgvc::appliquer(CImage *init, CImage *masque, CImage *out, float nb_iter, float delta_t)
{

    this->progressbar->setMaximum(nb_iter);

    out->Copy(init);
    for (int n = 0; n < nb_iter; ++n)
    {
        this->progressbar->setValue(this->progressbar->value()+1);//incremente la progressbar

        init->Copy(out);
        //Laplacien de limage
        //Gradient de limage
        for (int i = 0; i < masque->height(); ++i)
        {
            for (int j = 0; j < masque->width(); ++j)
            {
                if (masque->getPixel(i, j) == qRgba(0, 0, 0, 255))
                {

                }
            }
        }
    }
}

void CMgvc::set_progressbar(QProgressBar * bar)
{
    this->progressbar = bar;
}
