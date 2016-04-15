#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <cmath>
#include <DirectXMath.h>

int GetParabola(int x);
//Stores the result in x and y
void GetParabola(int& x, int& y, int t);
//Stores the result in x and y
void GetCircle(int& x, int&y, int t);
//
void GetEllipse(int& x, int& y, int t, int a, int b);
//xLobes and yLobes describe the number of lobes of the figure
void GetLissajousCurve(int& x, int& y, int a, int b, int xLobes, int yLobes);

#endif
