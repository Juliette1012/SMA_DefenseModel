#ifdef X_GUI

#include "XGui/xsPolyli.h"
#include "XGui/xgView2d.h"
#include "XGui/xgMgr.h"

//--------------------------------------------------------------------------//
// class XGuiPolyline                                                      //
//--------------------------------------------------------------------------//

//-------- Allocators ------------------------------------------------------//
XGuiPolyline::XGuiPolyline(double x,double y,double theta,
                           const Strings & color, int nbPoints,
                           const double * xPoints,const double * yPoints)
 : XGuiShape2D(x,y,theta,color),
   _nb(nbPoints)
{
_x=(double *)malloc(_nb*sizeof(double));
_y=(double *)malloc(_nb*sizeof(double));
_coordX=(double *)malloc(_nb*sizeof(double));
_coordY=(double *)malloc(_nb*sizeof(double));
_points=(XPoint *)malloc(_nb*sizeof(XPoint));
for(int i=_nb;i--;)
  {
  _x[i]=xPoints[i];
  _y[i]=yPoints[i];
  }
computePosition();
}

XGuiPolyline::XGuiPolyline(const XGuiPolyline & s)
 : XGuiShape2D(s), _nb(s._nb)
{
_x=(double *)malloc(_nb*sizeof(double));
_y=(double *)malloc(_nb*sizeof(double));
_coordX=(double *)malloc(_nb*sizeof(double));
_coordY=(double *)malloc(_nb*sizeof(double));
_points=(XPoint *)malloc(_nb*sizeof(XPoint));
for(int i=_nb;i--;)
  {
  _x[i]=s._x[i];
  _y[i]=s._y[i];
  _coordX[i]=s._coordX[i];
  _coordY[i]=s._coordY[i];
  }
}

XGuiPolyline::~XGuiPolyline(void)
{
free(_x);
free(_y);
free(_coordX);
free(_coordY);
free(_points);
}

XGuiShape2D * XGuiPolyline::duplicate(void) const // virtual
{
return(new XGuiPolyline(*this));
}

//-------- Inspectors ------------------------------------------------------//
// inline void XGuiPolyline::getLocalBoundingBox(double & xmin,double & ymin,
//                                               double & xmax,double & ymax)
//                                               const // virtual

// inline void XGuiPolyline::getBoundingBox(double & xmin,double & ymin,
//                                          double & xmax,double & ymax,
//                                          const XGuiViewer2D * viewer) const
//                                                              // virtual

// inline double XGuiPolyline::distanceTo(double x,double y,
//                                        const XGuiViewer2D * viewer)
//                                                           const // virtual

bool XGuiPolyline::isInside(double,double) const // virtual
{
return(false);
}

bool XGuiPolyline::intersectRay(double xRay,double yRay,
                                double xDir,double yDir,
                                double & x,double & y) const // virtual
{
double a1=0.0,b1=0.0,c1=0.0,
       a2,b2,c2,x1,y1,x2,y2,xInter,yInter,dx,dy,d,dmin=0.0;
bool found=false;
XGuiShape2D::_equationLine(xRay,yRay,xRay+xDir,yRay+yDir,a1,b1,c1);
x1=_coordX[_nb-1];
y1=_coordY[_nb-1];
for(int i=_nb-1;i--;)
  {
  x2=x1;
  y2=y1;
  x1=_coordX[i];
  y1=_coordY[i];
  if(!XGuiShape2D::_equationLine(x1,y1,x2,y2,a2,b2,c2)||
     !XGuiShape2D::_intersectLines(a1,b1,c1,a2,b2,c2,xInter,yInter))
    continue; // no intersection
  dx=xInter-xRay;
  dy=yInter-yRay;
  d=dx*dx+dy*dy;
  if((found&&(d>=dmin))||
     (dx*xDir+dy*yDir<=0.0)) continue; // too far or bad direction
  if(x1!=x2)
    {
    dx=(xInter-x1)/(x2-x1);
    if((dx>=0.0)&&(dx<=1.0))
      {
      found=true;
      dmin=d;
      x=xInter;
      y=yInter;
      }
    }
  else
    {
    dy=(yInter-y1)/(y2-y1);
    if((dy>=0.0)&&(dy<=1.0))
      {
      found=true;
      dmin=d;
      x=xInter;
      y=yInter;
      }
    }
  }
return(found);
}

//-------- Input/Output ----------------------------------------------------//
Strings XGuiPolyline::print(void) const // virtual
{
Strings str("polyline([");
for(int i=0;i<_nb;i++)
  {
  if(i) str+=",";
  str+="["+Strings(_x[i])+","+Strings(_y[i])+"]";
  }
str+="])";
return(str);
}

//-------- Modifiers -------------------------------------------------------//
void XGuiPolyline::drawInViewer(XGuiViewer2D * viewer) // virtual
{
for(int i=_nb;i--;)
  {
  _points[i].x=viewer->getColumn(_coordX[i]);
  _points[i].y=viewer->getLine(_coordY[i]);
  }
getXGuiManager()->chooseColor(_pixel);
XDrawLines(getXGuiManager()->getDisplay(),
           viewer->getPixmap(),getXGuiManager()->getGC(),
           _points,_nb,CoordModeOrigin);
}

// inline void XGuiPolyline::computePosition(void) // virtual

#endif // X_GUI

