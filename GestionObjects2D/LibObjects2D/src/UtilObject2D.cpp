#include "UtilObject2D.h"

void
cartesianToPolar(double x,
                 double y,
                 double * distanceOut,
                 double * angleOut)
{
*distanceOut=sqrt(x*x+y*y);
*angleOut=(*distanceOut ? atan2(y,x) : 0.0);
}

void
polarToCartesian(double distance,
                 double angle,
                 double * xOut,
                 double * yOut)
{
*xOut=distance*cos(angle);
*yOut=distance*sin(angle);
}

double cartToDist(double x,double y)
{
 return(sqrt(x*x+y*y));
}

double cartToAngle(double x,double y)
{
 return(x||y ? atan2(y,x) : 0.0);
}

#define Constant_PI   3.14159265358979323846
#define Constant_2PI  6.28318530717958647692
#define Constant_PI_2 1.57079632679489661923

double betweenPi(double a)
{
 while(a>=Constant_PI)  a -= Constant_2PI;
 while(a<=-Constant_PI) a += Constant_2PI;
 return a;
}
