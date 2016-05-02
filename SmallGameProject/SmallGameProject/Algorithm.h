#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <cmath>
#include <DirectXMath.h>

namespace Algorithm {
	int GetParabola(int x);
	//Stores the result in x and y
	void GetParabola(int& x, int& y, float t);
	//Stores the result in x and y
	void GetCircle(int& x, int&y, float t);
	//
	void GetEllipse(int& x, int& y, float t, int a, int b);
	//xLobes and yLobes describe the number of lobes of the figure
	void GetLissajousCurve(int& x, int& y, float t, int a, int b, int xLobes, int yLobes);
	//A curve traced by a point attached to a circle of radius r rolling around the inside of a fixed circle of radius R, where the point is at a distance d from the center of the interior circle.
	void GetHypotrochoid(int& x, int&y, float t, int bigR, int r, int d);

	void GetSawtoothWave(int& x, int& y, int t, int period, int min, int max);
	void GetTriangleWave(int & x, int & y, float t, int period, int min, int max);
	void GetSquareWave(int & x, int & y, float t, int period, int max, int min);
	void GetSineWave(int& x, int& y, float t, int period, int max, int min);
}


#endif
