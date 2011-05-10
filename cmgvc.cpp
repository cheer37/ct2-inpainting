#include "cmgvc.h"

CMgvc::CMgvc()
{
}


double min(double A, double B)
{
        if (A > B)
                return B;
        return A;
}

double max(double A, double B)
{
        if (A > B)
                return A;
        return B;
}

double CMgvc::TransformInterval (double x, double min1, double max1, double min2, double max2)
{
        return ((x-min1)/(max1-min1)*(max2-min2)) + min2;
}

void CMgvc::ExpansionDynamique (CImageDouble * im, CImage * masque)
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


void CMgvc::Laplacien(CImageDouble *in, CImageDouble *out)
{
    double tmp;
    for(int i = 0; i < in->width; ++i)
    {
        for(int j = 0; j < in->height; ++j)
        {
            tmp = in->getRedPixel(i-1, j) + in->getRedPixel(i+1, j) + in->getRedPixel(i, j-1) + in->getRedPixel(i, j+1) - (4.0*in->getRedPixel(i, j)) ;
            out->setRedPixel(i, j, tmp);
            tmp = in->getGreenPixel(i-1, j) + in->getGreenPixel(i+1, j) + in->getGreenPixel(i, j-1) + in->getGreenPixel(i, j+1) - (4.0*in->getGreenPixel(i, j)) ;
            out->setGreenPixel(i, j, tmp);
            tmp = in->getBluePixel(i-1, j) + in->getBluePixel(i+1, j) + in->getBluePixel(i, j-1) + in->getBluePixel(i, j+1) - (4.0*in->getBluePixel(i, j)) ;
            out->setBluePixel(i, j, tmp);
        }
    }
}

void CMgvc::Gradient(CImageDouble * in, CImageDouble * ResX, CImageDouble * ResY, CImageDouble * out)
{

    double SobelX [] = {-1.0, 0.0, 1.0,
                        -2.0, 0.0, 2.0,
                        -1.0, 0.0, 1.0};

    double SobelY [] = {-1.0, -2.0, -1.0,
                        0.0, 0.0, 0.0,
                        1.0, 2.0, 1.0};

    double ValRx, ValRy, ValGx, ValGy, ValBx, ValBy, ValGr, ValGg, ValGb;
    int cpt;

    for (int y = 0; y < in->height; ++y)
    {
        for (int x = 0; x < in->width; ++x)
        {
            ValRx = 0;
            ValGx = 0;
            ValBx = 0;

            ValRy = 0;
            ValGy = 0;
            ValBy = 0;

            cpt = 0;

            for (int j = y-1; j <= y+1; ++j)
            {
                for (int i = x-1; i <= x+1; ++i)
                {
                    ValRx += SobelX[cpt] * in->getRedPixel(i,j);
                    ValRy += SobelY[cpt] * in->getRedPixel(i,j);

                    ValGx += SobelX[cpt] * in->getGreenPixel(i,j);
                    ValGy += SobelY[cpt] * in->getGreenPixel(i,j);

                    ValBx += SobelX[cpt] * in->getBluePixel(i,j);
                    ValBy += SobelY[cpt] * in->getBluePixel(i,j);

                    ++cpt;
                }
            }

            ValGr = sqrt(pow(ValRx, 2)+pow(ValRy, 2));
            ValGg = sqrt(pow(ValGx, 2)+pow(ValGy, 2));
            ValGb = sqrt(pow(ValBx, 2)+pow(ValBy, 2));

            if (ResX)
            {
                ResX->setRedPixel  (x, y, ValRx);
                ResX->setGreenPixel(x, y, ValGx);
                ResX->setBluePixel (x, y, ValBx);
            }

            if (ResY)
            {
                ResY->setRedPixel  (x, y, ValRy);
                ResY->setGreenPixel(x, y, ValGy);
                ResY->setBluePixel (x, y, ValBy);
            }

            out->setRedPixel  (x, y, ValGr);
            out->setGreenPixel(x, y, ValGg);
            out->setBluePixel (x, y, ValGb);
        }
    }
}

void CMgvc::appliquer(CImage *init, CImage *masque, CImage *out, float nb_iter, float delta_t)
{

    this->progressbar->setMaximum(nb_iter);

/*    CMatriMage * Laplacien = new CMatriMage(init->width(), init->height());
    CMatriMage * Gradient  = new CMatriMage(init->width(), init->height());
    CMatriMage * SobelX    = new CMatriMage(init->width(), init->height());
    CMatriMage * SobelY    = new CMatriMage(init->width(), init->height());

    CMatriMage * temp = new CMatriMage(init);
    CMatriMage * res  = new CMatriMage(init);*/

    CImageDouble * iLaplacien = new CImageDouble(init);
    CImageDouble * iGradient  = new CImageDouble(init);
    CImageDouble * iSobelX    = new CImageDouble(init);
    CImageDouble * iSobelY    = new CImageDouble(init);

    CImageDouble * iTemp      = new CImageDouble(init);
    CImageDouble * iRes       = new CImageDouble(init);


    CVector2f deltaLr, deltaLg, deltaLb;
    CVector2f Nr, Ng, Nb;
    double R, G, B;	// Valeur calculé du pixel pour chaque canal
    double Br, Bg, Bb;	// Beta pour chaque canal
    double Gr, Gg, Gb;	// Norme du gradient pour chaque canal
    double ValR, ValG, ValB;


    // Recopie du masque sur l'image en entrée
    for (int y = 0; y < init->height(); ++y)
    {
        for (int x = 0; x < init->width(); ++x)
        {
            if (masque->getPixel(x, y) == qRgba(0, 0, 0, 255))
            {
                iRes->setRedPixel(x,y, 0.0);
                iRes->setGreenPixel(x,y, 0.0);
                iRes->setBluePixel(x,y, 0.0);
            }
        }
    }


    for (int n = 0; n < nb_iter; ++n)
    {
        this->progressbar->setValue(this->progressbar->value()+1);//incremente la progressbar
/*        qDebug() << n << '/' << nb_iter << '\n';*/

        // copie de l'image resultat dans l'image temporaire
        iTemp->Copy(iRes);

        // Calcul du laplacien
        Laplacien(iTemp, iLaplacien);
        // Calcul  des composantes en X et Y du gradient
        Gradient(iTemp, iSobelX, iSobelY, iGradient);


        for (int j = 0; j < masque->height(); ++j)
        {
            for (int i = 0; i < masque->width(); ++i)
            {
                // Le traitement est effectué si le pixel parcouru est recouvert par le masque
                if (masque->getPixel(i, j) == qRgba(0, 0, 0, 255))
                {
                    // Calcul des deltaL (correspond à la formule (7) page 4 du pdf)
                    deltaLr.SetVal(iLaplacien->getRedPixel(i+1,j)   - iLaplacien->getRedPixel(i-1,j)  , iLaplacien->getRedPixel(i,j+1)   - iLaplacien->getRedPixel(i,j-1));
                    deltaLg.SetVal(iLaplacien->getGreenPixel(i+1,j) - iLaplacien->getGreenPixel(i-1,j), iLaplacien->getGreenPixel(i,j+1) - iLaplacien->getGreenPixel(i,j-1));
                    deltaLb.SetVal(iLaplacien->getBluePixel(i+1,j)  - iLaplacien->getBluePixel(i-1,j) , iLaplacien->getBluePixel(i,j+1)  - iLaplacien->getBluePixel(i,j-1));

                    // Calcul des vecteurs Nr, Ng et Nb (correspond à une partie de la formule (9) page 4 du pdf)
                    Nr.SetVal(-(iSobelY->getRedPixel(i,j))  , iSobelX->getRedPixel(i,j));
                    Ng.SetVal(-(iSobelY->getGreenPixel(i,j)), iSobelX->getGreenPixel(i,j));
                    Nb.SetVal(-(iSobelY->getBluePixel(i,j)) , iSobelX->getBluePixel(i,j));

                    // Normalisation des vecteurs Nr, Ng et Nb (correspond à l'autre partie de la formule (9) page 4 du pdf)
                    Nr/(pow(Nr.GetNorm(),2)+0.000000001);
                    Ng/(pow(Ng.GetNorm(),2)+0.000000001);
                    Nb/(pow(Nb.GetNorm(),2)+0.000000001);

                    // Calcul des valeurs des beta pour chaque canal (correspond à la formule (10) page 4 du pdf)
                    Br = deltaLr*Nr;
                    Bg = deltaLg*Ng;
                    Bb = deltaLb*Nb;

                    // Calcul de la norme du gradient pour le canal rouge (correspond à la formule (11) page 4 du pdf)
                    if ( Br >= 0.0)
                    {
                        double bX = min(iTemp->getRedPixel(i+1,j) - iTemp->getRedPixel(i,j), 0.0);
                        double fX = max(iTemp->getRedPixel(i,j) - iTemp->getRedPixel(i+1,j), 0.0);

                        double bY = min(iTemp->getRedPixel(i,j+1) - iTemp->getRedPixel(i,j), 0.0);
                        double fY = max(iTemp->getRedPixel(i,j) - iTemp->getRedPixel(i,j+1), 0.0);

                        Gr = sqrt( pow(bX,2) + pow(fX,2) + pow(bY,2) + pow(fY,2));
                    }
                    else
                    {
                        double bX = max(iTemp->getRedPixel(i+1,j) - iTemp->getRedPixel(i,j), 0.0);
                        double fX = min(iTemp->getRedPixel(i,j) - iTemp->getRedPixel(i+1,j), 0.0);

                        double bY = max(iTemp->getRedPixel(i,j+1) - iTemp->getRedPixel(i,j), 0.0);
                        double fY = min(iTemp->getRedPixel(i,j) - iTemp->getRedPixel(i,j+1), 0.0);

                        Gr = sqrt( pow(bX,2) + pow(fX,2) + pow(bY,2) + pow(fY,2));
                    }

                    // Calcul de la norme du gradient pour le canal vert (correspond à la formule (11) page 4 du pdf)
                    if ( Bg >= 0.0)
                    {
                        double bX = min(iTemp->getGreenPixel(i+1,j) - iTemp->getGreenPixel(i,j), 0.0);
                        double fX = max(iTemp->getGreenPixel(i,j) - iTemp->getGreenPixel(i+1,j), 0.0);

                        double bY = min(iTemp->getGreenPixel(i,j+1) - iTemp->getGreenPixel(i,j), 0.0);
                        double fY = max(iTemp->getGreenPixel(i,j) - iTemp->getGreenPixel(i,j+1), 0.0);

                        Gg = sqrt( pow(bX,2) + pow(fX,2) + pow(bY,2) + pow(fY,2));
                    }
                    else
                    {
                        double bX = max(iTemp->getGreenPixel(i+1,j) - iTemp->getGreenPixel(i,j), 0.0);
                        double fX = min(iTemp->getGreenPixel(i,j) - iTemp->getGreenPixel(i+1,j), 0.0);

                        double bY = max(iTemp->getGreenPixel(i,j+1) - iTemp->getGreenPixel(i,j), 0.0);
                        double fY = min(iTemp->getGreenPixel(i,j) - iTemp->getGreenPixel(i,j+1), 0.0);

                        Gg = sqrt( pow(bX,2) + pow(fX,2) + pow(bY,2) + pow(fY,2));
                    }

                    // Calcul de la norme du gradient pour le canal bleu (correspond à la formule (11) page 4 du pdf)
                    if ( Bb >= 0.0)
                    {
                        double bX = min(iTemp->getBluePixel(i+1,j) - iTemp->getBluePixel(i,j), 0.0);
                        double fX = max(iTemp->getBluePixel(i,j) - iTemp->getBluePixel(i+1,j), 0.0);

                        double bY = min(iTemp->getBluePixel(i,j+1) - iTemp->getBluePixel(i,j), 0.0);
                        double fY = max(iTemp->getBluePixel(i,j) - iTemp->getBluePixel(i,j+1), 0.0);

                        Gb = sqrt( pow(bX,2) + pow(fX,2) + pow(bY,2) + pow(fY,2));
                    }
                    else
                    {
                        double bX = max(iTemp->getBluePixel(i+1,j) - iTemp->getBluePixel(i,j), 0.0);
                        double fX = min(iTemp->getBluePixel(i,j) - iTemp->getBluePixel(i+1,j), 0.0);

                        double bY = max(iTemp->getBluePixel(i,j+1) - iTemp->getBluePixel(i,j), 0.0);
                        double fY = min(iTemp->getBluePixel(i,j) - iTemp->getBluePixel(i,j+1), 0.0);

                        Gb = sqrt( pow(bX,2) + pow(fX,2) + pow(bY,2) + pow(fY,2));
                    }

                    ValR = delta_t*(Br*Gr);
                    ValG = delta_t*(Bg*Gg);
                    ValB = delta_t*(Bb*Gb);

                    //Calcule de la nouvel valeur du pixel courant (correspond aux formules (5) et (6) page 4 du pdf)
                    R = iTemp->getRedPixel(i,j)   + delta_t*(Br*Gr);
                    G = iTemp->getGreenPixel(i,j) + delta_t*(Bg*Gg);
                    B = iTemp->getBluePixel(i,j)  + delta_t*(Bb*Gb);

                    iRes->setRedPixel  (i,j,R);
                    iRes->setGreenPixel(i,j,G);
                    iRes->setBluePixel (i,j,B);
                }
            }
        }
    }
//    ExpansionDynamique(res, masque);
    // Copie de l'image résultante dans l'image de sortie
    out->Copy(iRes->getQimage());
    std::cerr << "\n\n\n\n";

}

void CMgvc::set_progressbar(QProgressBar * bar)
{
    this->progressbar = bar;
}
