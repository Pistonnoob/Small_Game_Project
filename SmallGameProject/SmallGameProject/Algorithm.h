#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <cmath>
#include <DirectXMath.h>

namespace Algorithm;

int GetParabola(int x);
//Stores the result in x and y
void GetParabola(int& x, int& y, int t);
//Stores the result in x and y
void GetCircle(int& x, int&y, int t);
//
void GetEllipse(int& x, int& y, int t, int a, int b);
//xLobes and yLobes describe the number of lobes of the figure
void GetLissajousCurve(int& x, int& y, int t, int a, int b, int xLobes, int yLobes);
//A curve traced by a point attached to a circle of radius r rolling around the inside of a fixed circle of radius R, where the point is at a distance d from the center of the interior circle.
void GetHypotrochoid(int& x, int&y, int t, int bigR, int r, int d);

#endif
