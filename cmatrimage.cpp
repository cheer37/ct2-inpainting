 #include "cmatrimage.h"


CMatriMage::CMatriMage(int width, int height)
{
    this->height = height;
    this->width = width;
    data = new int [width*height*3];
}

CMatriMage::CMatriMage(CImage * In)
{
    this->height = In->height();
    this->width = In->width();
    this->data = new int [width*height*3];
}


int CMatriMage::GetVal (int x, int y, int canal)
{
    if ( x > this->width )
        x = this->width - (x-this->width) - 1;
    else if ( x < 0)
        x = abs(x)-1;

    if ( y > this->height )
        y = this->height - (y-this->height) - 1;
    else if (y < 0)
        y = abs(y)-1;

    return this->data[ ((this->width*y)+x)*3 + canal];
}

void CMatriMage::SetVal (int x, int y, int canal, int val)
{
    if (canal > -1 && canal < 3)
        this->data[ ((this->width*y)+x)*3 + canal] = val;
}

void CMatriMage::SetData(int width, int height, int * data)
{
    delete this->data;
    this->width = width;
    this->height = height;
    this->data = data;
}

QRgb CMatriMage::GetRgb (int x, int y)
{
    return qRgb(GetVal(x,y,0),GetVal(x,y,1),GetVal(x,y,2));
}

void CMatriMage::Laplacien (CImage * In)
{

    if (!this->data || this->height != In->height() || this->width != In->width())
    {
        delete this->data;
        this->height = In->height();
        this->width = In->width();
        this->data = new int [width*height*3];
    }

    int ValR, ValG, ValB, cpt;

    float filtre [] = {0.0, 1.0, 0.0,
                       1.0, -4.0, 1.0,
                       0.0, 1.0, 1.0};


    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            ValR = 0;
            ValG = 0;
            ValB = 0;
            cpt = 0;
            for (int j = y-1; j <= y+1; ++j)
            {
				for (int i = x-1; i <= x+1; ++i)
                {
                    ValR += filtre[cpt]*In->getRedPixel(i,j);
                    ValG += filtre[cpt]*In->getGreenPixel(i,j);
                    ValB += filtre[cpt]*In->getBluePixel(i,j);
                    ++cpt;
                }
            }
            this->SetVal(x,y,0,ValR);
            this->SetVal(x,y,1,ValG);
            this->SetVal(x,y,2,ValB);
        }
    }
}

void CMatriMage::Gradient (CImage * In, CMatriMage * ResX, CMatriMage * ResY)
{
    if (!this->data || this->height != In->height() || this->width != In->width())
    {
        delete this->data;
        this->height = In->height();
        this->width = In->width();
        this->data = new int [width*height*3];
    }


    float  SobelX [] = {-1.0, 0.0, 1.0,
                        -2.0, 0.0, 2.0,
                        -1.0, 0.0, 1.0};

    float  SobelY [] = {-1.0, -2.0, -1.0,
                        0.0, 0.0, 0.0,
                        1.0, 2.0, 1.0};

    int ValRx, ValRy, ValGx, ValGy, ValBx, ValBy, ValGr, ValGg, ValGb, cpt;

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
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
                    ValRx += SobelX[cpt] * In->getRedPixel(i,j);
                    ValRy += SobelY[cpt] * In->getRedPixel(i,j);

                    ValGx += SobelX[cpt] * In->getGreenPixel(i,j);
                    ValGy += SobelY[cpt] * In->getGreenPixel(i,j);

                    ValBx += SobelX[cpt] * In->getBluePixel(i,j);
                    ValBy += SobelY[cpt] * In->getBluePixel(i,j);

                    ++cpt;
                }
            }

            ValGr = sqrt(pow(ValRx, 2)+pow(ValRy, 2));
            ValGg = sqrt(pow(ValGx, 2)+pow(ValGy, 2));
            ValGb = sqrt(pow(ValBx, 2)+pow(ValBy, 2));

            if (ResX)
            {
                ResX->SetVal(x, y, 0, ValRx);
                ResX->SetVal(x, y, 1, ValGx);
                ResX->SetVal(x, y, 2, ValBx);
            }

            if (ResY)
            {
                ResY->SetVal(x, y, 0, ValRy);
                ResY->SetVal(x, y, 1, ValGy);
                ResY->SetVal(x, y, 2, ValBy);
            }

            this->SetVal(x, y, 0, ValGr);
            this->SetVal(x, y, 1, ValGg);
            this->SetVal(x, y, 2, ValGb);
        }
    }
}
