#ifdef X_GUI

#include "XGui/xsSquare.h"
#include "XGui/xgView2d.h"
#include "XGui/xgMgr.h"

//--------------------------------------------------------------------------//
// class XGuiSquare                                                        //
//--------------------------------------------------------------------------//

//-------- Allocators ------------------------------------------------------//
XGuiSquare::XGuiSquare(double x,double y,double theta,const Strings & color,
                       double side,bool filled)
 : XGuiShape2D(x,y,theta,color),
   _s_2(side/2.0), _filled(filled)
{
computePosition();
}

XGuiSquare::XGuiSquare(const XGuiSquare & s)
 : XGuiShape2D(s), _s_2(s._s_2), _filled(s._filled)
{
for(int i=4;i--;)
  {
  _coordX[i]=s._coordX[i];
  _coordY[i]=s._coordY[i];
  }
}

XGuiSquare::~XGuiSquare(void)
{}

XGuiShape2D * XGuiSquare::duplicate(void) const // virtual
{
return(new XGuiSquare(*this));
}

//-------- Inspectors ------------------------------------------------------//
// inline void XGuiSquare::getLocalBoundingBox(double & xmin,double & ymin,
//                                             double & xmax,double & ymax)
//                                             const // virtual

// inline void XGuiSquare::getBoundingBox(double & xmin,double & ymin,
//                                        double & xmax,double & ymax,
//                                        const XGuiViewer2D * viewer) const
//                                                               // virtual

// inline double XGuiSquare::distanceTo(double x,double y,
//                                      const XGuiViewer2D * viewer)
//                                                          const // virtual

bool XGuiSquare::isInside(double x,double y) const // virtual
{
double cosTh=::cos(_theta0);
double sinTh=::sin(_theta0);
x-=_x0;
y-=_y0;
double xLocal=x*cosTh+y*sinTh;
double yLocal=y*cosTh-x*sinTh;
return((xLocal>-_s_2)&&(xLocal<_s_2)&&(yLocal>-_s_2)&&(yLocal<_s_2));
}

bool XGuiSquare::intersectRay(double xRay,double yRay,double xDir,double yDir,
                              double & x,double & y) const // virtual
{
double a1=0.0,b1=0.0,c1=0.0,
       a2,b2,c2,x1,y1,x2,y2,xInter,yInter,dx,dy,d,dmin=0.0;
bool found=false;
XGuiShape2D::_equationLine(xRay,yRay,xRay+xDir,yRay+yDir,a1,b1,c1);
x1=_coordX[0];
y1=_coordY[0];
for(int i=4;i--;)
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
Strings XGuiSquare::print(void) const // virtual
{
Strings str="square("+Strings(_s_2*2.0);
if(_filled) str+=",true)";
else str+=",false)";
return(str);
}

//-------- Modifiers -------------------------------------------------------//
void XGuiSquare::drawInViewer(XGuiViewer2D * viewer) // virtual
{
XPoint points[5];
for(int i=4;i--;)
  {
  points[i].x=viewer->getColumn(_coordX[i]);
  points[i].y=viewer->getLine(_coordY[i]);
  }
points[4].x=points[0].x;
points[4].y=points[0].y;
getXGuiManager()->chooseColor(_pixel);
if(_filled)
  {
  XFillPolygon(getXGuiManager()->getDisplay(),
               viewer->getPixmap(),getXGuiManager()->getGC(),
               points,4,Convex,CoordModeOrigin);
  }
XDrawLines(getXGuiManager()->getDisplay(),
           viewer->getPixmap(),getXGuiManager()->getGC(),
           points,5,CoordModeOrigin);
}

// inline void XGuiSquare::computePosition(void) // virtual

#endif // X_GUI

