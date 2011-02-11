#ifndef CVECTOR2F_H
#define CVECTOR2F_H


#include <math.h>

class CVector2f
{
public:
    CVector2f();
    CVector2f(float x, float y);

    void SetVal (float x, float y);
    float GetX ();
    float GetY ();

    float  GetNorm ();

    float operator* (CVector2f vec);
	void  operator/ (float val);

private:
    float x;
    float y;
};

#endif // CVECTOR2F_H
