#ifndef _UTILOBJECT2D_H_
#define _UTILOBJECT2D_H_

#include <math.h>

void cartesianToPolar(double x,
                      double y,
                      double * distanceOut,
                      double * angleOut);

void polarToCartesian(double distance,
                      double angle,
                      double * xOut,
                      double * yOut);

double cartToDist(double x,double y);

double cartToAngle(double x,double y);

double betweenPi(double a);

#endif // _UTILOBJECT2D_H_
