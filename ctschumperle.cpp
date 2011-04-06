#include "ctschumperle.h"
#include <iostream>

/**
* @fn CTschumperle constructeur
*/
CTschumperle::CTschumperle()
{

}

/**
* @fn appliquer Applique l'inpainting sur une image
* @param init image initiale, masque image correspodant au masque, out image resultat,
*        _iteration nb d'iterations a effectuer, dt delta t
*/
void CTschumperle::appliquer(CImage *init, CImage *masque, CImage *out, float _iteration, float dt)
{
    this->progressbar->setMaximum(_iteration);//initialise la progressbar

    CImage *I_tmp = new CImage(init->width(), init->height(), 0);
    out->Copy(init);

    for (int y = 0; y < init->height(); ++y)
    {
        for (int x = 0; x < init->width(); ++x)
        {
            if (masque->getPixel(x, y) == qRgba(0, 0, 0, 255))
            {
                out->setPixel(x, y, qRgb(0, 0, 0));
            }
        }
    }

    for (int it = 0; it < _iteration; ++it)
    {
        this->progressbar->setValue(this->progressbar->value()+1);//incremente la progressbar

        I_tmp->Copy(out);
        for (int j = 0; j < masque->height(); ++j)
        {
            for (int i = 0; i < masque->width(); ++i)
            {
                if (masque->getPixel(i, j) == qRgba(0, 0, 0, 255))
                {
                    /*Calcul de la hessienne pr un pixel du masque */
                    double *H_r = CHessian::GetHessian(I_tmp, i, j, 0);
                    double *H_g = CHessian::GetHessian(I_tmp, i, j, 1);
                    double *H_b = CHessian::GetHessian(I_tmp, i, j, 2);

                    /*Calcul du tenseur de diffusion*/
                    CDiffTensor T = CDiffTensor(I_tmp, i, j);
                    double *D_r = T.GetDiffTensor_r();
                    double *D_g = T.GetDiffTensor_g();
                    double *D_b = T.GetDiffTensor_b();/*AJOUTER GAUSSIENE SUR LES MATRICES 'D' */

                    /*Calcul de la matrice D.H*/
                    double Mat_res_r[4];
                    double Mat_res_g[4];
                    double Mat_res_b[4];

                    Mat_res_r[0] = D_r[0]*H_r[0]+D_r[1]*H_r[2];
                    Mat_res_r[1] = D_r[0]*H_r[1]+D_r[1]*H_r[3];
                    Mat_res_r[2] = D_r[2]*H_r[0]+D_r[3]*H_r[2];
                    Mat_res_r[3] = D_r[2]*H_r[1]+D_r[3]*H_r[3];

                    Mat_res_g[0] = D_g[0]*H_g[0]+D_g[1]*H_g[2];
                    Mat_res_g[1] = D_g[0]*H_g[1]+D_g[1]*H_g[3];
                    Mat_res_g[2] = D_g[2]*H_g[0]+D_g[3]*H_g[2];
                    Mat_res_g[3] = D_g[2]*H_g[1]+D_g[3]*H_g[3];

                    Mat_res_b[0] = D_b[0]*H_b[0]+D_b[1]*H_b[2];
                    Mat_res_b[1] = D_b[0]*H_b[1]+D_b[1]*H_b[3];
                    Mat_res_b[2] = D_b[2]*H_b[0]+D_b[3]*H_b[2];
                    Mat_res_b[3] = D_b[2]*H_b[1]+D_b[3]*H_b[3];

                    qDebug() << " DiffTensor R: [" << D_r[0] << "," <<  D_r[1] << "," <<  D_r[2] << "," <<  D_r[3] << "]\n"
                             << "Hessian    R: [" << H_r[0] << "," <<  H_r[1] << "," <<  H_r[2] << "," <<  H_r[3] << "]\n"
                             << "MatRes     R: [" << Mat_res_r[0] << "," <<  Mat_res_r[1] << "," <<  Mat_res_r[2] << "," <<  Mat_res_r[3] << "]\n";
                             /*<< "DiffTensor G: [" << D_g[0] << "," <<  D_g[1] << "," <<  D_g[2] << "," <<  D_g[3] << "]\n"
                             << "Hessian    G: [" << H_g[0] << "," <<  H_g[1] << "," <<  H_g[2] << "," <<  H_g[3] << "]\n"
                             << "MatRes     G: [" << Mat_res_g[0] << "," <<  Mat_res_g[1] << "," <<  Mat_res_g[2] << "," <<  Mat_res_g[3] << "]\n"
                             << "DiffTensor B: [" << D_b[0] << "," <<  D_b[1] << "," <<  D_b[2] << "," <<  D_b[3] << "]\n"
                             << "Hessian    B: [" << H_b[0] << "," <<  H_b[1] << "," <<  H_b[2] << "," <<  H_b[3] << "]\n"
                             << "MatRes     B: [" << Mat_res_b[0] << "," <<  Mat_res_b[1] << "," <<  Mat_res_b[2] << "," <<  Mat_res_b[3] << "]\n"*/


                    qDebug() << "Val px R: I_tmp->getRedPixel(i, j) : " << I_tmp->getRedPixel(i, j)
                             << " + dt*(Mat_res_r[0]+Mat_res_r[3]) : " << dt*(Mat_res_r[0]+Mat_res_r[3])
                             << " = " << (I_tmp->getRedPixel(i, j)+(dt*(Mat_res_r[0]+Mat_res_r[3])))
                            << "\n______________________________________________________\n";/*
                             << " Val px G: " << (dt*(Mat_res_g[0]+Mat_res_g[3]))
                             << " Val px B: " << (dt*(Mat_res_b[0]+Mat_res_b[3])) << '\n';*/

                    /*Calcul de la valeur a ajouter au pixel avec dt*trace(DH)*/
                    out->setPixel(i, j, qRgb(I_tmp->getRedPixel(i, j)+(dt*(Mat_res_r[0]+Mat_res_r[3])), I_tmp->getGreenPixel(i, j)+(dt*(Mat_res_g[0]+Mat_res_g[3])), I_tmp->getBluePixel(i, j)+(dt*(Mat_res_b[0]+Mat_res_b[3]))));
                }
            }
        }

    }
}

/**
* @fn set_progressbar affecte la progressBar afin de la faire evoluer
* @param bar pointeur vers la progressBar en question
*/
void CTschumperle::set_progressbar(QProgressBar * bar)
{
    this->progressbar = bar;
}
