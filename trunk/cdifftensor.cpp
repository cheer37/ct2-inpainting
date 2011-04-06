#include "cdifftensor.h"

CDiffTensor::CDiffTensor(CImage * _img, int _x, int _y)
{
    this->DTMat_r = new double [4];
    this->DTMat_g = new double [4];
    this->DTMat_b = new double [4];

    double * StrucTensor_r = new double[4];
    double * StrucTensor_g = new double[4];
    double * StrucTensor_b = new double[4];

    StrucTensor_r = this->GetStrucTensor(_img, _x, _y, 0);
    StrucTensor_g = this->GetStrucTensor(_img, _x, _y, 1);
    StrucTensor_b = this->GetStrucTensor(_img, _x, _y, 2);

    qDebug() << " StrucTensor R: [" << StrucTensor_r[0] << "," <<  StrucTensor_r[1] << "," <<  StrucTensor_r[2] << "," <<  StrucTensor_r[3] << "]\n";

    double Lambda_p, Lambda_m, det, a, b, c, tmp_mult;
    double teta_p[2];
    double teta_m[2];

    /*****************Pour le canal R*********************/

    /*Calcul des valeurs propres lambda+- */
    a = 1;
    b = StrucTensor_r[0] - StrucTensor_r[3];
    c = (StrucTensor_r[0]*StrucTensor_r[3]) - (StrucTensor_r[1]*StrucTensor_r[2]);
    det = pow(b, 2)-4*(a*c);

    Lambda_p = (-b+sqrt(det))/(2*a);
    Lambda_m = (-b-sqrt(det))/(2*a);
    qDebug() << " a: " << a << " b: " << b << " c: " << c <<" lambda-p :" << Lambda_p << " lambda-m :" << Lambda_m <<'\n';
    /*Si lambda+ < lambda- on echange */
    if (Lambda_m > Lambda_p)
    {
        double lambda_tmp = Lambda_p;
        Lambda_p = Lambda_m;
        Lambda_m = lambda_tmp;
    }
    /*si lambda+ est < 0, on le force a 0*/
    if(Lambda_p < 0.0) Lambda_p = 0.0;
    /*Idem lambda- */
    if(Lambda_m < 0.0) Lambda_m = 0.0;

    /*Determination des vecteurs propres teta+- en fonction de lambda+- */
    teta_p[0] = -StrucTensor_r[1];
    teta_p[1] = StrucTensor_r[0]-Lambda_p;

    teta_m[0] = -StrucTensor_r[1];
    teta_m[1] = StrucTensor_r[0]-Lambda_m;

    /*Si teta+ < teta- on echange */
    if (teta_m[1] > teta_p[1])
    {
         double teta_tmp = teta_p[1];
         teta_m[1] = teta_p[1];
         teta_p[1] = teta_tmp;
    }
    /*On norme les vecteurs propres teta+- */
    double norme = sqrt(pow(teta_p[0], 2)+pow(teta_p[1], 2));
    teta_p[0] /= norme;
    teta_p[1] /= norme;
    norme = sqrt(pow(teta_m[0], 2)+pow(teta_m[1], 2));
    teta_m[0] /= norme;
    teta_m[1] /= norme;


    tmp_mult = 1/(sqrt(1+Lambda_m+Lambda_p));
   // qDebug() << "lambda-p :" << Lambda_p << " lambda-m :" << Lambda_m << " tmp_multp r: " << tmp_mult << '\n';
    this->DTMat_r = this->CalcDiffTensMat(teta_m, tmp_mult);

    /*******************/

    /*Pour le canal G*/

    a = 1;
    b = StrucTensor_g[0] - StrucTensor_g[3];
    c = (StrucTensor_g[0]*StrucTensor_g[3]) - (StrucTensor_g[1]*StrucTensor_g[2]);
    det = pow(b, 2)-4*(a*c);

    Lambda_p = (-b+sqrt(det))/(2*a);
    Lambda_m = (-b-sqrt(det))/(2*a);

    if (Lambda_m > Lambda_p)
    {
        double lambda_tmp = Lambda_p;
        Lambda_p = Lambda_m;
        Lambda_m = lambda_tmp;
    }
    if(Lambda_p < 0.0) Lambda_p = 0.0;
    if(Lambda_m < 0.0) Lambda_m = 0.0;

    teta_p[0] = -StrucTensor_g[1];
    teta_p[1] = StrucTensor_g[0]-Lambda_p;

    teta_m[0] = -StrucTensor_g[1];
    teta_m[1] = StrucTensor_g[0]-Lambda_m;

    if (teta_m[1] > teta_p[1])
    {
         double teta_tmp = teta_p[1];
         teta_m[1] = teta_p[1];
         teta_p[1] = teta_tmp;
    }
    /*On norme les vecteurs propres teta+- */
    norme = sqrt(pow(teta_p[0], 2)+pow(teta_p[1], 2));
    teta_p[0] /= norme;
    teta_p[1] /= norme;
    norme = sqrt(pow(teta_m[0], 2)+pow(teta_m[1], 2));
    teta_m[0] /= norme;
    teta_m[1] /= norme;


    tmp_mult = 1/(sqrt(1+Lambda_m+Lambda_p));
    //qDebug() << "lambda-p :" << Lambda_p << " lambda-m :" << Lambda_m << " tmp_multp g: " << tmp_mult << '\n';
    this->DTMat_g = this->CalcDiffTensMat(teta_m, tmp_mult);

    /*******************/

    /*Pour le canal B*/

    a = 1;
    b = StrucTensor_b[0] - StrucTensor_b[3];
    c = (StrucTensor_b[0]*StrucTensor_b[3]) - (StrucTensor_b[1]*StrucTensor_b[2]);
    det = pow(b, 2)-4*(a*c);

    Lambda_p = (-b+sqrt(det))/(2*a);
    Lambda_m = (-b-sqrt(det))/(2*a);

    if (Lambda_m > Lambda_p)
    {
        double lambda_tmp = Lambda_p;
        Lambda_p = Lambda_m;
        Lambda_m = lambda_tmp;
    }
    if(Lambda_p < 0.0) Lambda_p = 0.0;
    if(Lambda_m < 0.0) Lambda_m = 0.0;

    teta_p[0] = -StrucTensor_b[1];
    teta_p[1] = StrucTensor_b[0]-Lambda_p;

    teta_m[0] = -StrucTensor_b[1];
    teta_m[1] = StrucTensor_b[0]-Lambda_m;

    if (teta_m[1] > teta_p[1])
    {
         double teta_tmp = teta_p[1];
         teta_m[1] = teta_p[1];
         teta_p[1] = teta_tmp;
    }
    /*On norme les vecteurs propres teta+- */
    norme = sqrt(pow(teta_p[0], 2)+pow(teta_p[1], 2));
    teta_p[0] /= norme;
    teta_p[1] /= norme;
    norme = sqrt(pow(teta_m[0], 2)+pow(teta_m[1], 2));
    teta_m[0] /= norme;
    teta_m[1] /= norme;

    tmp_mult = 1/(sqrt(1+Lambda_m+Lambda_p));

    //qDebug() << "lambda-p :" << Lambda_p << " lambda-m :" << Lambda_m << " tmp_multp b: " << tmp_mult << '\n';

    this->DTMat_b = this->CalcDiffTensMat(teta_m, tmp_mult);

    /*******************/
}


double * CDiffTensor::CalcDiffTensMat(double * teta_m, double tmp_mult)
{
    double * mat_res = new double[4];
    mat_res[0] = tmp_mult*teta_m[0]*teta_m[0];
    mat_res[1] = tmp_mult*teta_m[1]*teta_m[0];
    mat_res[2] = tmp_mult*teta_m[0]*teta_m[1];
    mat_res[3] = tmp_mult*teta_m[1]*teta_m[1];

    return mat_res;
}

double * CDiffTensor::GetStrucTensor(CImage * _img, int _x, int _y, int _canal)
{
    float  SobelX [] = {-1.0, 0.0, 1.0,
                        -2.0, 0.0, 2.0,
                        -1.0, 0.0, 1.0};

    float  SobelY [] = {-1.0, -2.0, -1.0,
                        0.0, 0.0, 0.0,
                        1.0, 2.0, 1.0};
    double ValX = 0, ValY = 0;
    double * mat_res = new double [4];
    int cpt = 0;
    mat_res[0] = 0.0;
    mat_res[1] = 0.0;
    mat_res[2] = 0.0;
    mat_res[3] = 0.0;
    if (_canal == 0)
    {
        /*for (int y = _y-1; y <= _y+1; ++y)
        {
            for (int x = _x-1; x <= _x+1; ++x)
            {
                cpt = 0;
                for (int j = y-1; j <= y+1; ++j)
                {
                    for (int i = x-1; i <= x+1; ++i)
                    {
                        ValX += _img->getRedPixel(i, j)*SobelX[cpt];
                        ValY += _img->getRedPixel(i, j)*SobelY[cpt];
                        ++cpt;
                    }
                }
                mat_res[0] += ValX*ValX;
                mat_res[1] += ValX*ValY;
                mat_res[2] += ValX*ValY;
                mat_res[3] += ValY*ValY;
                ValX = 0;
                ValY = 0;
            }
        }*/
        for (int y = _y-1; y <= _y+1; ++y)
        {
             for (int x = _x-1; x <= _x+1; ++x)
             {
                 ValX = 0.5*(_img->getRedPixel(x+1, y)-_img->getRedPixel(x-1, y));
                 ValY = 0.5*(_img->getRedPixel(x, y+1)-_img->getRedPixel(x, y-1));
                 mat_res[0] += ValX*ValX;
                 mat_res[1] += ValX*ValY;
                 mat_res[2] += ValY*ValX;
                 mat_res[3] += ValY*ValY;
             }
        }
    }
    else if (_canal == 1)
    {
        /*for (int y = _y-1; y <= _y+1; ++y)
        {
            for (int x = _x-1; x <= _x+1; ++x)
            {
                cpt = 0;
                for (int j = y-1; j <= y+1; ++j)
                {
                    for (int i = x-1; i <= x+1; ++i)
                    {
                        ValX += _img->getGreenPixel(i, j)*SobelX[cpt];
                        ValY += _img->getGreenPixel(i, j)*SobelY[cpt];
                        ++cpt;
                    }
                }
                mat_res[0] += ValX*ValX;
                mat_res[1] += ValX*ValY;
                mat_res[2] += ValX*ValY;
                mat_res[3] += ValY*ValY;
                ValX = 0;
                ValY = 0;
            }
        }*/
        for (int y = _y-1; y <= _y+1; ++y)
        {
             for (int x = _x-1; x <= _x+1; ++x)
             {
                 ValX = 0.5*(_img->getGreenPixel(x+1, y)-_img->getGreenPixel(x-1, y));
                 ValY = 0.5*(_img->getGreenPixel(x, y+1)-_img->getGreenPixel(x, y-1));
                 mat_res[0] += ValX*ValX;
                 mat_res[1] += ValX*ValY;
                 mat_res[2] += ValY*ValX;
                 mat_res[3] += ValY*ValY;
             }
        }
    }
    else if (_canal == 2)
    {
        /*for (int y = _y-1; y <= _y+1; ++y)
        {
            for (int x = _x-1; x <= _x+1; ++x)
            {
                cpt = 0;
                for (int j = y-1; j <= y+1; ++j)
                {
                    for (int i = x-1; i <= x+1; ++i)
                    {
                        ValX += _img->getBluePixel(i, j)*SobelX[cpt];
                        ValY += _img->getBluePixel(i, j)*SobelY[cpt];
                        ++cpt;
                    }
                }
                mat_res[0] += ValX*ValX;
                mat_res[1] += ValX*ValY;
                mat_res[2] += ValX*ValY;
                mat_res[3] += ValY*ValY;
                ValX = 0;
                ValY = 0;
            }
        }*/
        for (int y = _y-1; y <= _y+1; ++y)
        {
             for (int x = _x-1; x <= _x+1; ++x)
             {
                 ValX = 0.5*(_img->getBluePixel(x+1, y)-_img->getBluePixel(x-1, y));
                 ValY = 0.5*(_img->getBluePixel(x, y+1)-_img->getBluePixel(x, y-1));
                 mat_res[0] += ValX*ValX;
                 mat_res[1] += ValX*ValY;
                 mat_res[2] += ValY*ValX;
                 mat_res[3] += ValY*ValY;
             }
        }
    }
    return mat_res;
}

double * CDiffTensor::GetDiffTensor_r()
{
    return this->DTMat_r;
}

double * CDiffTensor::GetDiffTensor_g()
{
    return this->DTMat_g;
}
double * CDiffTensor::GetDiffTensor_b()
{
    return this->DTMat_b;
}
