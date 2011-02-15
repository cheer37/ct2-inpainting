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

int TransformInterval (int x, int min1, int max1, int min2, int max2)
{
	return ((x-min1)/(float)(max1-min1)*(max2-min2)) + min2;
}

void ExpansionDynamique (CImage * im, CImage * masque)
{
	int i, j, ValMin, ValMax, R, G, B;

	ValMin = im->getRedPixel(0,0);
	ValMax = im->getRedPixel(0,0);

	for (j = 0; j < im->height(); ++j)
	{
		for (i = 0; i < im->width(); ++i)
		{
			if (masque->getPixel(i,j) == qRgba(0,0,0,255))
			{
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
	for (j = 0; j < im->height(); ++j)
	{
		for (i = 0; i < im->width(); ++i)
		{
			if (masque->getPixel(i,j) == qRgba(0,0,0,255))
			{
				R = TransformInterval(im->getRedPixel(i,j)  , ValMin, ValMax, 0, 255);
				G = TransformInterval(im->getGreenPixel(i,j), ValMin, ValMax, 0, 255);
				B = TransformInterval(im->getBluePixel(i,j) , ValMin, ValMax, 0, 255);
				im->setPixel(i,j,qRgb(R,G,B));
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

	CImage * temp = new CImage(init->width(), init->height(), 0);

    CVector2f deltaLr, deltaLg, deltaLb;
    CVector2f Nr, Ng, Nb;
    int R, G, B;
	float Br, Bg, Bb;

    out->Copy(init);

	for (int y = 0; y < init->height(); ++y)
	{
		for (int x = 0; x < init->width(); ++x)
		{
			if (masque->getPixel(x, y) == qRgba(0, 0, 0, 255))
			{
				out->setPixel(x,y,qRgb(0,0,0));
			}
		}
	}

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
				if (masque->getPixel(i, j) == qRgba(0, 0, 0, 255) /*&& isOnEdgeOfOmega(masque, j, i)*/)
                {
                    deltaLr.SetVal(Laplacien->GetVal(i+1,j,0) - Laplacien->GetVal(i-1,j,0), Laplacien->GetVal(i+1,j,0) - Laplacien->GetVal(i-1,j,0));
                    deltaLg.SetVal(Laplacien->GetVal(i+1,j,1) - Laplacien->GetVal(i-1,j,1), Laplacien->GetVal(i+1,j,1) - Laplacien->GetVal(i-1,j,1));
                    deltaLb.SetVal(Laplacien->GetVal(i+1,j,2) - Laplacien->GetVal(i-1,j,2), Laplacien->GetVal(i+1,j,2) - Laplacien->GetVal(i-1,j,2));

                    Nr.SetVal(-(SobelY->GetVal(i,j, 0)), SobelX->GetVal(i,j, 0));
                    Ng.SetVal(-(SobelY->GetVal(i,j, 1)), SobelX->GetVal(i,j, 1));
                    Nb.SetVal(-(SobelY->GetVal(i,j, 2)), SobelX->GetVal(i,j, 2));

					if (Nr.GetNorm() > 0.0)
						Nr/Nr.GetNorm();
					else
						Nr/0.000001;

					if (Ng.GetNorm() > 0.0)
						Ng/Ng.GetNorm();
					else
						Ng/0.000001;

					if (Nb.GetNorm() > 0.0)
						Nb/Nb.GetNorm();
					else
						Nb/0.000001;

					Br = deltaLr*Nr;
					Bg = deltaLg*Ng;
					Bb = deltaLb*Nb;


					R = temp->getRedPixel(i,j)   + delta_t*(Br*Gradient->GetVal(i,j, 0));
					G = temp->getGreenPixel(i,j) + delta_t*(Bg*Gradient->GetVal(i,j, 1));
					B = temp->getBluePixel(i,j)  + delta_t*(Bb*Gradient->GetVal(i,j, 2));

                    out->setPixel(i, j, qRgb(R,G,B));
                }
            }
        }
    }
	ExpansionDynamique(out, masque);

}

void CMgvc::set_progressbar(QProgressBar * bar)
{
    this->progressbar = bar;
}
