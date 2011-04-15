#include "cimagedouble.h"

CImageDouble::CImageDouble(CImage *_in)
{
    this->width = _in->width();
    this->height = _in->height();
    this->r_c = new double[this->width*this->height];
    this->g_c = new double[this->width*this->height];
    this->b_c = new double[this->width*this->height];

    for(int j = 0; j < this->height; ++j)
    {
        for(int i = 0; i < this->width; ++i)
        {
            this->r_c[i+(j*this->width)] = (double)_in->getRedPixel(i, j);
            this->g_c[i+(j*this->width)] = (double)_in->getGreenPixel(i, j);
            this->b_c[i+(j*this->width)] = (double)_in->getBluePixel(i, j);
        }
    }
}

CImageDouble::~CImageDouble()
{
    delete this->r_c;
    delete this->g_c;
    delete this->b_c;
}

double CImageDouble::getRedPixel(int _x, int _y)
{
    if ( _x > this->width )
        _x = this->width - (_x-this->width) - 1;
    else if ( _x < 0)
        _x = abs(_x)-1;

    if ( _y > this->height )
        _y = this->height - (_y-this->height) - 1;
    else if (_y < 0)
        _y = abs(_y)-1;

    return this->r_c[_x+(_y*this->width)];
}
double CImageDouble::getGreenPixel(int _x, int _y)
{
    if ( _x > this->width )
        _x = this->width - (_x-this->width) - 1;
    else if ( _x < 0)
        _x = abs(_x)-1;

    if ( _y > this->height )
        _y = this->height - (_y-this->height) - 1;
    else if (_y < 0)
        _y = abs(_y)-1;
    return this->g_c[_x+(_y*this->width)];
}
double CImageDouble::getBluePixel(int _x, int _y)
{
    if ( _x > this->width )
        _x = this->width - (_x-this->width) - 1;
    else if ( _x < 0)
        _x = abs(_x)-1;

    if ( _y > this->height )
        _y = this->height - (_y-this->height) - 1;
    else if (_y < 0)
        _y = abs(_y)-1;
    return this->b_c[_x+(_y*this->width)];
}

void CImageDouble::setRedPixel(int _x, int _y, double _val)
{
    this->r_c[_x+(_y*this->width)] = _val;
}
void CImageDouble::setGreenPixel(int _x, int _y, double _val)
{
     this->g_c[_x+(_y*this->width)] = _val;
}
void CImageDouble::setBluePixel(int _x, int _y, double _val)
{
     this->b_c[_x+(_y*this->width)] = _val;
}

void CImageDouble::Copy(CImageDouble * _in)
{
    if (_in->width == this->width && _in->height == this->height)
    {
        for(int j = 0; j < this->height; ++j)
        {
            for(int i = 0; i < this->width; ++i)
            {
                this->r_c[i+(j*this->width)] = _in->getRedPixel(i, j);
                this->g_c[i+(j*this->width)] = _in->getGreenPixel(i, j);
                this->b_c[i+(j*this->width)] = _in->getBluePixel(i, j);
            }
        }
    }
    else
    {
        delete this->r_c;
        delete this->g_c;
        delete this->b_c;
        this->width = _in->width;
        this->height = _in->height;
        this->r_c = new double[this->width*this->height];
        this->g_c = new double[this->width*this->height];
        this->b_c = new double[this->width*this->height];

        for(int j = 0; j < this->height; ++j)
        {
            for(int i = 0; i < this->width; ++i)
            {
                this->r_c[i+(j*this->width)] = _in->getRedPixel(i, j);
                this->g_c[i+(j*this->width)] = _in->getGreenPixel(i, j);
                this->b_c[i+(j*this->width)] = _in->getBluePixel(i, j);
            }
        }
    }

}
QImage * CImageDouble::getQimage()
{
    QImage *res = new QImage(this->width, this->height, QImage::Format_RGB32);

    for (int y = 0; y < this->height; ++y)
    {
        for(int x = 0; x < this->width; ++x)
            res->setPixel(x, y, qRgb(this->getRedPixel(x, y),this->getGreenPixel(x, y), this->getBluePixel(x, y)));
    }
    return res;
}

void CImageDouble::afficher_valeurs()
{
    for(int j = 0; j < 1; ++j)
    {
        for(int i = 0; i < this->width; ++i)
        {
            qDebug() << "[" << i << "," << j << "]: RGB[" << this->getRedPixel(i, j) << "," <<  this->getGreenPixel(i, j) << "," <<  this->getBluePixel(i, j)
                     << "]\n";
        }
    }
}
