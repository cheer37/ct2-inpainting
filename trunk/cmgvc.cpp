#include "cmgvc.h"

CMgvc::CMgvc()
{
}


float min(float A, float B)
{
        if (A > B)
                return B;
        return A;
}

float max(float A, float B)
{
        if (A > B)
                return A;
        return B;
}

float TransformInterval (float x, float min1, float max1, float min2, float max2)
{
        return ((x-min1)/(max1-min1)*(max2-min2)) + min2;
}

void ExpansionDynamique (CMatriMage * im, CImage * masque)
{
    float ValMin,ValMax, R, G, B;
    int first = 1;

    for (int j = 0; j < im->height; ++j)
    {
        for (int i = 0; i < im->width; ++i)
        {
            if (masque->getPixel(i,j) == qRgba(0,0,0,255))
            {
                if (first == 1 )
                {
                    ValMin = im->GetVal(i,j,0);
                    ValMax = im->GetVal(i,j,0);
                    first = 0;
                }
                R = im->GetVal(i,j,0);
                G = im->GetVal(i,j,1);
                B = im->GetVal(i,j,2);

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

    std::cerr  << "ValMin = " << ValMin << ", ValMax = " << ValMax << "\n\n";

    for (int j = 0; j < im->height; ++j)
    {
        for (int i = 0; i < im->width; ++i)
        {
            if (masque->getPixel(i,j) == qRgba(0,0,0,255))
            {
                R = TransformInterval(im->GetVal(i,j,0) , ValMin, ValMax, 0.0, 255.0);
                G = TransformInterval(im->GetVal(i,j,1) , ValMin, ValMax, 0.0, 255.0);
                B = TransformInterval(im->GetVal(i,j,2) , ValMin, ValMax, 0.0, 255.0);
                im->SetVal(i,j,0,R);
                im->SetVal(i,j,1,G);
                im->SetVal(i,j,2,B);
            }
        }
    }
}

void CMgvc::appliquer(CImage *init, CImage *masque, CImage *out, float nb_iter, float delta_t)
{

    this->progressbar->setMaximum(nb_iter);

    CMatriMage * Laplacien = new CMatriMage(init->width(), init->height());
    CMatriMage * Gradient  = new CMatriMage(init->width(), init->height());
    CMatriMage * SobelX    = new CMatriMage(init->width(), init->height());
    CMatriMage * SobelY    = new CMatriMage(init->width(), init->height());

    CMatriMage * temp = new CMatriMage(init);
    CMatriMage * res  = new CMatriMage(init);


    CVector2f deltaLr, deltaLg, deltaLb;
    CVector2f Nr, Ng, Nb;
    float R, G, B;	// Valeur calculé du pixel pour chaque canal
    float Br, Bg, Bb;	// Beta pour chaque canal
    float Gr, Gg, Gb;	// Norme du gradient pour chaque canal

    for (int y = 0; y < init->height(); ++y)
    {
        for (int x = 0; x < init->width(); ++x)
        {
            if (masque->getPixel(x, y) == qRgba(0, 0, 0, 255))
            {
                res->SetVal(x,y,0, 0.0);
                res->SetVal(x,y,1, 0.0);
                res->SetVal(x,y,2, 0.0);
            }
        }
    }

    for (int n = 0; n < nb_iter; ++n)
    {
        this->progressbar->setValue(this->progressbar->value()+1);//incremente la progressbar

        temp->Copy(res);

        Laplacien->Laplacien(temp);
        Gradient->Gradient(temp, SobelX, SobelY);


        for (int j = 0; j < masque->height(); ++j)
        {
            for (int i = 0; i < masque->width(); ++i)
            {
                if (masque->getPixel(i, j) == qRgba(0, 0, 0, 255))
                {
                    deltaLr.SetVal(Laplacien->GetVal(i+1,j,0) - Laplacien->GetVal(i-1,j,0), Laplacien->GetVal(i,j+1,0) - Laplacien->GetVal(i,j-1,0));
                    deltaLg.SetVal(Laplacien->GetVal(i+1,j,1) - Laplacien->GetVal(i-1,j,1), Laplacien->GetVal(i,j+1,1) - Laplacien->GetVal(i,j-1,1));
                    deltaLb.SetVal(Laplacien->GetVal(i+1,j,2) - Laplacien->GetVal(i-1,j,2), Laplacien->GetVal(i,j+1,2) - Laplacien->GetVal(i,j-1,2));

                    Nr.SetVal(-(SobelY->GetVal(i,j, 0)), SobelX->GetVal(i,j, 0));
                    Ng.SetVal(-(SobelY->GetVal(i,j, 1)), SobelX->GetVal(i,j, 1));
                    Nb.SetVal(-(SobelY->GetVal(i,j, 2)), SobelX->GetVal(i,j, 2));

                    Nr/(Nr.GetNorm()+0.000000001);
                    Ng/(Ng.GetNorm()+0.000000001);
                    Nb/(Nb.GetNorm()+0.000000001);

                    Br = deltaLr*Nr;
                    Bg = deltaLg*Ng;
                    Bb = deltaLb*Nb;

                    if ( Br >= 0.0)
                    {
                        float bX = min(temp->GetVal(i+1,j,0) - temp->GetVal(i,j,0), temp->GetVal(i,j,0) - temp->GetVal(i-1,j,0));
                        float fX = max(temp->GetVal(i,j,0) - temp->GetVal(i+1,j,0), temp->GetVal(i-1,j,0) - temp->GetVal(i,j,0));

                        float bY = min(temp->GetVal(i,j+1,0) - temp->GetVal(i,j,0), temp->GetVal(i,j,0) - temp->GetVal(i,j-1,0));
                        float fY = max(temp->GetVal(i,j,0) - temp->GetVal(i,j+1,0), temp->GetVal(i,j-1,0) - temp->GetVal(i,j,0));

                        Gr = sqrt( pow(bX,2) + pow(fX,2) + pow(bY,2) + pow(fY,2));
                    }
                    else
                    {
                        float bX = max(temp->GetVal(i+1,j,0) - temp->GetVal(i,j,0), temp->GetVal(i,j,0) - temp->GetVal(i-1,j,0));
                        float fX = min(temp->GetVal(i,j,0) - temp->GetVal(i+1,j,0), temp->GetVal(i-1,j,0) - temp->GetVal(i,j,0));

                        float bY = max(temp->GetVal(i,j+1,0) - temp->GetVal(i,j,0), temp->GetVal(i,j,0) - temp->GetVal(i,j-1,0));
                        float fY = min(temp->GetVal(i,j,0) - temp->GetVal(i,j+1,0), temp->GetVal(i,j-1,0) - temp->GetVal(i,j,0));

                        Gr = sqrt( pow(bX,2) + pow(fX,2) + pow(bY,2) + pow(fY,2));
                    }

                    if ( Bg >= 0.0)
                    {
                        int bX = min(temp->GetVal(i+1,j,1) - temp->GetVal(i,j,1), temp->GetVal(i,j,1) - temp->GetVal(i-1,j,1));
                        int fX = max(temp->GetVal(i,j,1) - temp->GetVal(i+1,j,1), temp->GetVal(i-1,j,1) - temp->GetVal(i,j,1));

                        int bY = min(temp->GetVal(i,j+1,1) - temp->GetVal(i,j,1), temp->GetVal(i,j,1) - temp->GetVal(i,j-1,1));
                        int fY = max(temp->GetVal(i,j,1) - temp->GetVal(i,j+1,1), temp->GetVal(i,j-1,1) - temp->GetVal(i,j,1));

                        Gg = sqrt( pow(bX,2) + pow(fX,2) + pow(bY,2) + pow(fY,2));
                    }
                    else
                    {
                        int bX = max(temp->GetVal(i+1,j,1) - temp->GetVal(i,j,1), temp->GetVal(i,j,1) - temp->GetVal(i-1,j,1));
                        int fX = min(temp->GetVal(i,j,1) - temp->GetVal(i+1,j,1), temp->GetVal(i-1,j,1) - temp->GetVal(i,j,1));

                        int bY = max(temp->GetVal(i,j+1,1) - temp->GetVal(i,j,1), temp->GetVal(i,j,1) - temp->GetVal(i,j-1,1));
                        int fY = min(temp->GetVal(i,j,1) - temp->GetVal(i,j+1,1), temp->GetVal(i,j-1,1) - temp->GetVal(i,j,1));

                        Gg = sqrt( pow(bX,2) + pow(fX,2) + pow(bY,2) + pow(fY,2));
                    }

                    if ( Bb >= 0.0)
                    {
                        int bX = min(temp->GetVal(i+1,j,2) - temp->GetVal(i,j,2), temp->GetVal(i,j,2) - temp->GetVal(i-1,j,2));
                        int fX = max(temp->GetVal(i,j,2) - temp->GetVal(i+1,j,2), temp->GetVal(i-1,j,2) - temp->GetVal(i,j,2));

                        int bY = min(temp->GetVal(i,j+1,2) - temp->GetVal(i,j,2), temp->GetVal(i,j,2) - temp->GetVal(i,j-1,2));
                        int fY = max(temp->GetVal(i,j,2) - temp->GetVal(i,j+1,2), temp->GetVal(i,j-1,2) - temp->GetVal(i,j,2));

                        Gb = sqrt( pow(bX,2) + pow(fX,2) + pow(bY,2) + pow(fY,2));
                    }
                    else
                    {
                        int bX = max(temp->GetVal(i+1,j,2) - temp->GetVal(i,j,2), temp->GetVal(i,j,2) - temp->GetVal(i-1,j,2));
                        int fX = min(temp->GetVal(i,j,2) - temp->GetVal(i+1,j,2), temp->GetVal(i-1,j,2) - temp->GetVal(i,j,2));

                        int bY = max(temp->GetVal(i,j+1,2) - temp->GetVal(i,j,2), temp->GetVal(i,j,2) - temp->GetVal(i,j-1,2));
                        int fY = min(temp->GetVal(i,j,2) - temp->GetVal(i,j+1,2), temp->GetVal(i,j-1,2) - temp->GetVal(i,j,2));

                        Gb = sqrt( pow(bX,2) + pow(fX,2) + pow(bY,2) + pow(fY,2));
                    }



                    R = temp->GetVal(i,j,0) + delta_t*(Br*Gr);
                    G = temp->GetVal(i,j,1) + delta_t*(Bg*Gg);
                    B = temp->GetVal(i,j,2) + delta_t*(Bb*Gb);

                    res->SetVal(i,j,0,R);
                    res->SetVal(i,j,1,G);
                    res->SetVal(i,j,2,B);
                }
            }
        }
        ExpansionDynamique(res, masque);
    }
    out->Copy(res->GetQImage());

}

void CMgvc::set_progressbar(QProgressBar * bar)
{
    this->progressbar = bar;
}
