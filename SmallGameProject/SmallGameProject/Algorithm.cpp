#include "Algorithm.h"
#include "MyMathLib.h"

int Algorithm::GetParabola(int x)
{
	return pow(x, 2);
}

void Algorithm::GetParabola(int& x, int& y, float t)
{
	x = t;
	y = pow(t, 2);
}

void Algorithm::GetCircle(int& x, int&y, float t)
{
    //float t2 = Math::DEGREES_TO_RADIANS * t;
	x = cos(t);
	y = sin(t);
}


void Algorithm::GetEllipse(int& x, int& y, float t, int a, int b)
{
	x = a * cos(t);
	y = b * sin(t);
}

void Algorithm::GetLissajousCurve(int& x, int& y, float t, int a, int b, int xLobes, int yLobes)
{
	x = a * cos(xLobes * t);
	y = b * sin(yLobes * t);
}

void Algorithm::GetHypotrochoid(int& x, int&y, float t, int bigR, int r, int d)
{
	int tX = 0, tY = 0;
	int distanceFromOrigo = bigR - r;
	GetCircle(tX, tY, t);
	//Apply the distance
	tX *= distanceFromOrigo;
	tY *= distanceFromOrigo;
	//Angle between origin and innerCircleOrigin.
	float angle = atan2(tX, tY);
	//Calculate the local x and y
	x = distanceFromOrigo * cos(angle) + d * cos((distanceFromOrigo / r) * angle);
	y = distanceFromOrigo * sin(angle) - d * sin((distanceFromOrigo / r) * angle);
}


void Algorithm::GetSawtoothWave(int& x, int& y, int t, int period, int min, int max)
{
	x = t;
	y = (t % period) * max + min;
}

void Algorithm::GetTriangleWave(int & x, int & y, float t, int period, int min, int max)
{
	x = t;
	y = abs((x % period) - max) + min;
}

void Algorithm::GetSquareWave(int& x, int& y, float t, int period, int max, int min)
{
	x = t;
	y = (x % period) < max ? min : max;
}

//Note that the "period" variable have a different inplication in this case
void Algorithm::GetSineWave(int & x, int & y, float t, int period, int max, int min)
{
	x = t;
	y = (max - min) * sin((float)x / period) + min;
}
