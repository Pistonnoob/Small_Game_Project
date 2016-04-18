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
	y = b * sin(t);
}

void GetLissajousCurve(int& x, int& y, int t, int a, int b, int xLobes, int yLobes)
{
	x = a * cos(xLobes * t);
	y = b * sin(yLobes * t);
}

void GetHypotrochoid(int& x, int&y, int t, int bigR, int r, int d)
{
	int tX = 0, tY = 0;
	int distanceFromOrigo = bigR - r;
	GetCircle(tX, tY, distanceFromOrigo);
	//Apply the distance
	tX *= distanceFromOrigo;
	tY *= distanceFromOrigo;
	//Angle between origin and innerCircleOrigin.
	float angle = atan2(tX, tY);
	//Calculate the local x and y
	x = distanceFromOrigo * cos(angle) + d * cos((distanceFromOrigo / r) * angle);
	y = distanceFromOrigo * sin(angle) - d * sin((distanceFromOrigo / r) * angle);


}