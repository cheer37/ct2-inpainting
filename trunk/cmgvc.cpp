#include "cmgvc.h"

CMgvc::CMgvc()
{
}

bool isOnEdgeOfOmega (CImage * masque, int x, int y)
{
	for (int j = y-1; j <= y+1; ++j)
		for (int i = x-1; i <= x+1; ++i)
			if (masque->getPixel(i, j) == qRgba(255, 255, 255, 0))
				return true;

	return false;
}

void CMgvc::appliquer(CImage *init, CImage *masque, CImage *out, float nb_iter, float delta_t)
{

    this->progressbar->setMaximum(nb_iter);

    CMatriMage * Laplacien = new CMatriMage(init->width(), init->height());
    CMatriMage * Gradient  = new CMatriMage(init->width(), init->height());
    CMatriMage * SobelX    = new CMatriMage(init->width(), init->height());
    CMatriMage * SobelY    = new CMatriMage(init->width(), init->height());

    CImage * temp = new CImage(init->width(), init->height(), 0);
    CImage * masqueTemp = new CImage(init->width(), init->height(), 1);
	CImage * valEr;

    CVector2f deltaLr, deltaLg, deltaLb;
    CVector2f Nr, Ng, Nb;
    int R, G, B;

	masqueTemp->Copy(masque);
    out->Copy(init);

    for (int n = 0; n < nb_iter; ++n)
    {
		valEr = new CImage(init->width(), init->height(), 0);
        this->progressbar->setValue(this->progressbar->value()+1);//incremente la progressbar

        temp->Copy(out);

        Laplacien->Laplacien(temp);
        Gradient->Gradient(temp, SobelX, SobelY);


        for (int j = 0; j < masqueTemp->height(); ++j)
        {
            for (int i = 0; i < masqueTemp->width(); ++i)
            {
				if (masqueTemp->getPixel(i, j) == qRgba(0, 0, 0, 255) /*&& isOnEdgeOfOmega(masque, j, i)*/)
                {
					valEr->setPixel(i, j, qRgb(0,0,0));

                    deltaLr.SetVal(Laplacien->GetVal(i+1,j,0) - Laplacien->GetVal(i-1,j,0), Laplacien->GetVal(i+1,j,0) - Laplacien->GetVal(i-1,j,0));
                    deltaLg.SetVal(Laplacien->GetVal(i+1,j,1) - Laplacien->GetVal(i-1,j,1), Laplacien->GetVal(i+1,j,1) - Laplacien->GetVal(i-1,j,1));
                    deltaLb.SetVal(Laplacien->GetVal(i+1,j,2) - Laplacien->GetVal(i-1,j,2), Laplacien->GetVal(i+1,j,2) - Laplacien->GetVal(i-1,j,2));

                    Nr.SetVal(-(SobelY->GetVal(i,j, 0)), SobelX->GetVal(i,j, 0));
                    Ng.SetVal(-(SobelY->GetVal(i,j, 1)), SobelX->GetVal(i,j, 1));
                    Nb.SetVal(-(SobelY->GetVal(i,j, 2)), SobelX->GetVal(i,j, 2));

                    Nr/Nr.GetNorm();
                    Ng/Ng.GetNorm();
                    Nb/Nb.GetNorm();

                    R = temp->getRedPixel(i,j)   + delta_t*(deltaLr*Nr*Gradient->GetVal(i,j, 0));
                    G = temp->getGreenPixel(i,j) + delta_t*(deltaLg*Ng*Gradient->GetVal(i,j, 1));
                    B = temp->getBluePixel(i,j)  + delta_t*(deltaLb*Nb*Gradient->GetVal(i,j, 2));

                    out->setPixel(i, j, qRgb(R,G,B));
                }
            }
        }

		for (int j = 0; j < masqueTemp->height(); ++j)
		{
			for (int i = 0; i < masqueTemp->width(); ++i)
			{
				if (valEr->getPixel(i, j) == qRgb(0, 0, 0))
				{
					masqueTemp->setPixel(i, j, qRgba (255,255,255, 0));
				}
			}
		}
		delete valEr;
    }
}

void CMgvc::set_progressbar(QProgressBar * bar)
{
    this->progressbar = bar;
}
