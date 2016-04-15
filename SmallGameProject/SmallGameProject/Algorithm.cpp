#include "Algorithm.h"


int GetParabola(int x)
{
	return pow(x, 2);
}

void GetParabola(int& x, int& y, int t)
{
	x = t;
	y = pow(t, 2);
}

void GetCircle(int& x, int&y, int t)	
{
	x = cos(t);
	y = sin(t);
}


void GetEllipse(int& x, int& y, int t, int a, int b)
{
	x = a * cos(t);
	y = b * cos(y);
}

void GetLissajousCurve(int& x, int& y)
{

}