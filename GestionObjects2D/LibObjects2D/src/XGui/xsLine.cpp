#ifdef X_GUI

#include "XGui/xsLine.h"
#include "XGui/xgView2d.h"
#include "XGui/xgMgr.h"

//--------------------------------------------------------------------------//
// class XGuiLine                                                          //
//--------------------------------------------------------------------------//

//-------- Allocators ------------------------------------------------------//
XGuiLine::XGuiLine(double x,double y,double theta,const Strings & color,
                     double length)
 : XGuiShape2D(x,y,theta,color),
   _length(length)
{
computePosition();
}

XGuiLine::XGuiLine(const XGuiLine & s)
 : XGuiShape2D(s), _length(s._length),
   _x1(s._x1), _y1(s._y1)
{}

XGuiLine::~XGuiLine(void)
{}

XGuiShape2D * XGuiLine::duplicate(void) const // virtual
{
return(new XGuiLine(*this));
}

//-------- Inspectors ------------------------------------------------------//
// inline void XGuiLine::getLocalBoundingBox(double & xmin,double & ymin,
//                                           double & xmax,double & ymax)
//                                           const // virtual

// inline void XGuiLine::getBoundingBox(double & xmin,double & ymin,
//                                      double & xmax,double & ymax,
//                                      const XGuiViewer2D * viewer) const
//                                                               // virtual

// inline double XGuiLine::distanceTo(double x,double y,
//                                    const XGuiViewer2D * viewer)
//                                                         const // virtual

bool XGuiLine::isInside(double,double) const // virtual
{
return(false);
}

bool XGuiLine::intersectRay(double xRay,double yRay,double xDir,double yDir,
                            double & x,double & y) const // virtual
{
double a1=0.0,b1=0.0,c1=0.0,
       a2,b2,c2,dx,dy;
XGuiShape2D::_equationLine(xRay,yRay,xRay+xDir,yRay+yDir,a1,b1,c1);
if(!XGuiShape2D::_equationLine(_x0,_y0,_x1,_y1,a2,b2,c2)||
   !XGuiShape2D::_intersectLines(a1,b1,c1,a2,b2,c2,x,y))
   return(false); // no intersection
dx=x-xRay;
dy=y-yRay;
if(dx*xDir+dy*yDir<=0.0) return(false); // bad direction
if(_x0!=_x1)
  {
  dx=(x-_x0)/(_x1-_x0);
  if((dx>=0.0)&&(dx<=1.0)) return(true);
  }
else
  {
  dy=(y-_y0)/(_y1-_y0);
  if((dy>=0.0)&&(dy<=1.0)) return(true);
  }
return(false);
}

//-------- Input/Output ----------------------------------------------------//
Strings XGuiLine::print(void) const // virtual
{
Strings str="line("+Strings(_length)+")";
return(str);
}

//-------- Modifiers -------------------------------------------------------//
void XGuiLine::drawInViewer(XGuiViewer2D * viewer) // virtual
{
getXGuiManager()->chooseColor(_pixel);
XDrawLine(getXGuiManager()->getDisplay(),
          viewer->getPixmap(),getXGuiManager()->getGC(),
          viewer->getColumn(_x0),
          viewer->getLine(_y0),
          viewer->getColumn(_x1),
          viewer->getLine(_y1));
}

// inline void XGuiLine::computePosition(void) // virtual

#endif // X_GUI

