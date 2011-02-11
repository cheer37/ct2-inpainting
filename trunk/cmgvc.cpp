#include "cmgvc.h"

CMgvc::CMgvc()
{
}

void CMgvc::appliquer(CImage *init, CImage *masque, CImage *out, float nb_iter, float delta_t)
{

    this->progressbar->setMaximum(nb_iter);
    
	CMatriMage * Laplacien = new CMatriMage(init->width(), init->height());
	CMatriMage * Gradient  = new CMatriMage(init->width(), init->height());
	CMatriMage * SobelX    = new CMatriMage(init->width(), init->height());
	CMatriMage * SobelY    = new CMatriMage(init->width(), init->height());

	CImage * temp = new CImage(init->width(), init->height(), 0);

    CVector2f deltaLr, deltaLg, deltaLb;
	CVector2f Nr, Ng, Nb;
	int R, G, B;

	out->Copy(init);
    for (int n = 0; n < nb_iter; ++n)
    {
        this->progressbar->setValue(this->progressbar->value()+1);//incremente la progressbar

		temp->Copy(out);

		Laplacien->Laplacien(temp);
		Gradient->Gradient(temp, SobelX, SobelY);


        for (int j = 0; j < masque->height(); ++j)
        {
            for (int i = 0; i < masque->width(); ++i)
            {
                if (masque->getPixel(i, j) == qRgba(0, 0, 0, 255))
                {
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
    }
}

void CMgvc::set_progressbar(QProgressBar * bar)
{
    this->progressbar = bar;
}
