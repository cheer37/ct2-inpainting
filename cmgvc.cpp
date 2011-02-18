#include "cmgvc.h"

CMgvc::CMgvc()
{
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
	int R, G, B;		// Valeur calculé du pixel pour chaque canal
	float Br, Bg, Bb;	// Beta pour chaque canal
	float Gr, Gg, Gb;	// Norme du gradient pour chaque canal

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

/*
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
						int bX = min(temp->getRedPixel(i+1,j) - temp->getRedPixel(i,j), temp->getRedPixel(i,j) - temp->getRedPixel(i-1,j));
						int fX = max(temp->getRedPixel(i,j) - temp->getRedPixel(i+1,j), temp->getRedPixel(i-1,j) - temp->getRedPixel(i,j));

						int bY = min(temp->getRedPixel(i,j+1) - temp->getRedPixel(i,j), temp->getRedPixel(i,j) - temp->getRedPixel(i,j-1));
						int fY = max(temp->getRedPixel(i,j) - temp->getRedPixel(i,j+1), temp->getRedPixel(i,j-1) - temp->getRedPixel(i,j));

						Gr = sqrt( pow(bX,2) + pow(fX,2) + pow(bY,2) + pow(fY,2));
					}
					else
					{
						int bX = max(temp->getRedPixel(i+1,j) - temp->getRedPixel(i,j), temp->getRedPixel(i,j) - temp->getRedPixel(i-1,j));
						int fX = min(temp->getRedPixel(i,j) - temp->getRedPixel(i+1,j), temp->getRedPixel(i-1,j) - temp->getRedPixel(i,j));

						int bY = max(temp->getRedPixel(i,j+1) - temp->getRedPixel(i,j), temp->getRedPixel(i,j) - temp->getRedPixel(i,j-1));
						int fY = min(temp->getRedPixel(i,j) - temp->getRedPixel(i,j+1), temp->getRedPixel(i,j-1) - temp->getRedPixel(i,j));

						Gr = sqrt( pow(bX,2) + pow(fX,2) + pow(bY,2) + pow(fY,2));
					}

					if ( Bg >= 0.0)
					{
						int bX = min(temp->getGreenPixel(i+1,j) - temp->getGreenPixel(i,j), temp->getGreenPixel(i,j) - temp->getGreenPixel(i-1,j));
						int fX = max(temp->getGreenPixel(i,j) - temp->getGreenPixel(i+1,j), temp->getGreenPixel(i-1,j) - temp->getGreenPixel(i,j));

						int bY = min(temp->getGreenPixel(i,j+1) - temp->getGreenPixel(i,j), temp->getGreenPixel(i,j) - temp->getGreenPixel(i,j-1));
						int fY = max(temp->getGreenPixel(i,j) - temp->getGreenPixel(i,j+1), temp->getGreenPixel(i,j-1) - temp->getGreenPixel(i,j));

						Gg = sqrt( pow(bX,2) + pow(fX,2) + pow(bY,2) + pow(fY,2));
					}
					else
					{
						int bX = max(temp->getGreenPixel(i+1,j) - temp->getGreenPixel(i,j), temp->getGreenPixel(i,j) - temp->getGreenPixel(i-1,j));
						int fX = min(temp->getGreenPixel(i,j) - temp->getGreenPixel(i+1,j), temp->getGreenPixel(i-1,j) - temp->getGreenPixel(i,j));

						int bY = max(temp->getGreenPixel(i,j+1) - temp->getGreenPixel(i,j), temp->getGreenPixel(i,j) - temp->getGreenPixel(i,j-1));
						int fY = min(temp->getGreenPixel(i,j) - temp->getGreenPixel(i,j+1), temp->getGreenPixel(i,j-1) - temp->getGreenPixel(i,j));

						Gg = sqrt( pow(bX,2) + pow(fX,2) + pow(bY,2) + pow(fY,2));
					}

					if ( Bb >= 0.0)
					{
						int bX = min(temp->getBluePixel(i+1,j) - temp->getBluePixel(i,j), temp->getBluePixel(i,j) - temp->getBluePixel(i-1,j));
						int fX = max(temp->getBluePixel(i,j) - temp->getBluePixel(i+1,j), temp->getBluePixel(i-1,j) - temp->getBluePixel(i,j));

						int bY = min(temp->getBluePixel(i,j+1) - temp->getBluePixel(i,j), temp->getBluePixel(i,j) - temp->getBluePixel(i,j-1));
						int fY = max(temp->getBluePixel(i,j) - temp->getBluePixel(i,j+1), temp->getBluePixel(i,j-1) - temp->getBluePixel(i,j));

						Gb = sqrt( pow(bX,2) + pow(fX,2) + pow(bY,2) + pow(fY,2));
					}
					else
					{
						int bX = max(temp->getBluePixel(i+1,j) - temp->getBluePixel(i,j), temp->getBluePixel(i,j) - temp->getBluePixel(i-1,j));
						int fX = min(temp->getBluePixel(i,j) - temp->getBluePixel(i+1,j), temp->getBluePixel(i-1,j) - temp->getBluePixel(i,j));

						int bY = max(temp->getBluePixel(i,j+1) - temp->getBluePixel(i,j), temp->getBluePixel(i,j) - temp->getBluePixel(i,j-1));
						int fY = min(temp->getBluePixel(i,j) - temp->getBluePixel(i,j+1), temp->getBluePixel(i,j-1) - temp->getBluePixel(i,j));

						Gb = sqrt( pow(bX,2) + pow(fX,2) + pow(bY,2) + pow(fY,2));
					}



					R = temp->getRedPixel(i,j)   + delta_t*(Br*Gr);
					G = temp->getGreenPixel(i,j) + delta_t*(Bg*Gg);
					B = temp->getBluePixel(i,j)  + delta_t*(Bb*Gb);

                    out->setPixel(i, j, qRgb(R,G,B));
                }
            }
		}*/
    }
	out->Copy(Laplacien->GetQImage());
//	ExpansionDynamique(out, masque);

}

void CMgvc::set_progressbar(QProgressBar * bar)
{
    this->progressbar = bar;
}
