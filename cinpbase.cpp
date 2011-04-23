#include "cinpbase.h"
#include "QDebug"

CInpBase::CInpBase()
{
}

double CInpBase::TransformInterval (double x, double min1, double max1, double min2, double max2)
{
        return ((x-min1)/(max1-min1)*(max2-min2)) + min2;
}

void CInpBase::ExpansionDynamique (CImageDouble * im, CImage * masque)
{
    double ValMin,ValMax, R, G, B;
    int first = 1;

    // double boucle de recherche des valeurs maximale et minimale dans l'image au niveau du masque
    for (int j = 0; j < im->height; ++j)
    {
        for (int i = 0; i < im->width; ++i)
        {
            if (masque->getPixel(i,j) == qRgba(0,0,0,255))
            {
                if (first == 1 )
                {
                    ValMin = im->getRedPixel(i,j);
                    ValMax = im->getRedPixel(i,j);
                    first = 0;
                }
                R = im->getRedPixel(i,j);
                G = im->getGreenPixel(i,j);
                B = im->getBluePixel(i,j);

                if (R > ValMax)
                        ValMax = R;
                else if (R < ValMin)
                        ValMin = R;

                if (G > ValMax)
                        ValMax = G;
                else if (G < ValMin)
                        ValMin = G;

                if (B > ValMax)
                        ValMax = B;
                else if (B < ValMin)
                        ValMin = B;
            }
        }
    }

    for (int j = 0; j < im->height; ++j)
    {
        for (int i = 0; i < im->width; ++i)
        {
            if (masque->getPixel(i,j) == qRgba(0,0,0,255))
            {
                R = TransformInterval(im->getRedPixel(i,j) , ValMin, ValMax, 0.0, 255.0);
                G = TransformInterval(im->getGreenPixel(i,j) , ValMin, ValMax, 0.0, 255.0);
                B = TransformInterval(im->getBluePixel(i,j) , ValMin, ValMax, 0.0, 255.0);
                im->setRedPixel(i,j,R);
                im->setGreenPixel(i,j,G);
                im->setBluePixel(i,j,B);
            }
        }
    }
}


void CInpBase::Laplacien(CImageDouble *in, CImageDouble *out)
{
    /*qDebug() << "Debut Laplacien, width:"<<in->width << ", height:" << in->height << '\n';*/
    double tmp;
    for(int i = 0; i < in->width; ++i)
    {
        for(int j = 0; j < in->height; ++j)
        {
            /*qDebug() << "[" << i << "," << j << "] 1 : "<< in->getRedPixel(i, j+1) << " \n";*/
            tmp = in->getRedPixel(i-1, j) + in->getRedPixel(i+1, j) + in->getRedPixel(i, j-1) + in->getRedPixel(i, j+1) - (4.0*in->getRedPixel(i, j)) ;
            out->setRedPixel(i, j, tmp);
            /*qDebug() << "[" << i << "," << j << "] 2\n";*/
            tmp = in->getGreenPixel(i-1, j) + in->getGreenPixel(i+1, j) + in->getGreenPixel(i, j-1) + in->getGreenPixel(i, j+1) - (4.0*in->getGreenPixel(i, j)) ;
            out->setGreenPixel(i, j, tmp);
            /*qDebug() << "[" << i << "," << j << "] 3\n";*/
            tmp = in->getBluePixel(i-1, j) + in->getBluePixel(i+1, j) + in->getBluePixel(i, j-1) + in->getBluePixel(i, j+1) - (4.0*in->getBluePixel(i, j)) ;
            out->setBluePixel(i, j, tmp);
        }
    }
   /* qDebug() << "Fin Laplacien\n";*/
}

double CInpBase::Distance(CImageDouble *im1, CImageDouble *im2)
{
        int i, j;
        double somme, somme1, somme_r = 0.0, somme_g = 0.0, somme_b = 0.0;
        for(i = 0; i < im1->width; ++i)
        {
            for(j = 0; j < im1->height; ++j)
            {
                 somme_r += pow(im1->getRedPixel(i, j) - im2->getRedPixel(i, j), 2);
                 somme_g += pow(im1->getGreenPixel(i, j) - im2->getGreenPixel(i, j), 2);
                 somme_b += pow(im1->getBluePixel(i, j) - im2->getBluePixel(i, j), 2);
             }
        }
        somme1 = ((somme_r > somme_g)?somme_r:somme_g);
        somme = ((somme_b > somme1)?somme_b:somme1);
        return sqrt(somme);
}

/**
* @fn appliquer Applique l'inpainting sur une image
* @param init image initiale, masque image correspodant au masque, out image resultat,
*        _iteration nb d'iterations a effectuer, dt delta t
*/
void CInpBase::appliquer(CImage *init, CImage *masque, CImage *out, float _lambda, float _dt)
{
    int i, j;
    int W = init->width();
    int H = init->height();
    double dist = 100.0, temp;

    qDebug() << "Debut de CInpBase\n";

    CImageDouble *U1 = new CImageDouble(init);
    CImageDouble *U2 = new CImageDouble(init);
    CImageDouble *Lap = new CImageDouble(init);

    while(dist > 0.05)
    {
        qDebug() << "1\n";
        Laplacien(U1, Lap);
        qDebug() << "2\n";
        for(i = 0; i < W; ++i)
        {
            for(j = 0; j < H; ++j)
            {
                temp = U1->getRedPixel(i, j)+_dt*(2.0*((double) (masque->getRedPixel(i, j))/255.)*((double) (init->getRedPixel(i, j))-U1->getRedPixel(i, j))+_lambda*Lap->getRedPixel(i, j));
                U2->setRedPixel(i, j, temp);
                temp = U1->getGreenPixel(i, j)+_dt*(2.0*((double) (masque->getGreenPixel(i, j))/255.)*((double) (init->getGreenPixel(i, j))-U1->getGreenPixel(i, j))+_lambda*Lap->getGreenPixel(i, j));
                U2->setGreenPixel(i, j, temp);
                temp = U1->getBluePixel(i, j)+_dt*(2.0*((double) (masque->getBluePixel(i, j))/255.)*((double) (init->getBluePixel(i, j))-U1->getBluePixel(i, j))+_lambda*Lap->getBluePixel(i, j));
                U2->setBluePixel(i, j, temp);
            }
        }
        qDebug() << "3\n";
        dist = Distance(U1, U2);
        U1->Copy(U2);
        qDebug() << "4\t dist : " << dist << "\n";
    }
    ExpansionDynamique(U2, masque);
    out->Copy(U2->getQimage());

    delete U1;
    delete U2;
    delete Lap;
}

/**
* @fn set_progressbar affecte la progressBar afin de la faire evoluer
* @param bar pointeur vers la progressBar en question
*/
void CInpBase::set_progressbar(QProgressBar * bar)
{
    this->progressbar = bar;
}
