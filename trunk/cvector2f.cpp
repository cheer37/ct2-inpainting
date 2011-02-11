#include "cvector2f.h"

CVector2f::CVector2f()
{
}



CVector2f::CVector2f(float x, float y)
{
    this->x = x;
    this->y = y;
}

void CVector2f::SetVal (float x, float y)
{
    this->x = x;
    this->y = y;
}

float CVector2f::GetX ()
{
    return this->x;
}

float CVector2f::GetY ()
{
    return this->y;
}

float  CVector2f::GetNorm ()
{
    return sqrt (pow(this->x, 2) + pow(this->y, 2));
}

float CVector2f::operator* (CVector2f vec)
{
    return this->x*vec.GetX() + this->y*vec.GetY();
}


void  CVector2f::operator/ (float val)
{
	this->x  = this->x / val;
	this->y  = this->y / val;
}
