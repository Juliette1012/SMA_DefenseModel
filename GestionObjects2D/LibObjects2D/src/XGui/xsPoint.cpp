#ifdef X_GUI

#include "XGui/xsPoint.h"
#include "XGui/xgView2d.h"
#include "XGui/xgMgr.h"

//--------------------------------------------------------------------------//
// class XGuiPoint                                                          //
//--------------------------------------------------------------------------//

//-------- Allocators ------------------------------------------------------//
XGuiPoint::XGuiPoint(double x,double y,double theta,const Strings & color)
 : XGuiShape2D(x,y,theta,color)
{
computePosition();
}

XGuiPoint::XGuiPoint(const XGuiPoint & s)
 : XGuiShape2D(s)
{}

XGuiPoint::~XGuiPoint(void)
{}

XGuiShape2D * XGuiPoint::duplicate(void) const // virtual
{
return(new XGuiPoint(*this));
}

//-------- Inspectors ------------------------------------------------------//
// inline void XGuiPoint::getLocalBoundingBox(double & xmin,double & ymin,
//                                            double & xmax,double & ymax)
//                                            const // virtual

// inline void XGuiPoint::getBoundingBox(double & xmin,double & ymin,
//                                       double & xmax,double & ymax,
//                                       const XGuiViewer2D * viewer) const
//                                                               // virtual

// inline double XGuiPoint::distanceTo(double x,double y,
//                                     const XGuiViewer2D * viewer)
//                                                        const // virtual

bool XGuiPoint::isInside(double x,double y) const // virtual
{
return((x==_x0)&&(y==_y0));
}

bool XGuiPoint::intersectRay(double xRay,double yRay,double xDir,double yDir,
                             double & xInter,double & yInter) const // virtual
{
double a=0.0,b=0.0,c=0.0;
XGuiShape2D::_equationLine(xRay,yRay,xRay+xDir,yRay+yDir,a,b,c);
if(a*_x0+b*_y0+c) return(false); // not on the line
double dx=_x0-xRay;
double dy=_y0-yRay;
if(dx*xDir+dy*yDir<=0.0) return(false); // bad direction
xInter=_x0;
yInter=_y0;
return(true);
}

//-------- Input/Output ----------------------------------------------------//
Strings XGuiPoint::print(void) const // virtual
{
return("point()");
}

//-------- Modifiers -------------------------------------------------------//
void XGuiPoint::drawInViewer(XGuiViewer2D * viewer) // virtual
{
getXGuiManager()->chooseColor(_pixel);
XDrawPoint(getXGuiManager()->getDisplay(),
           viewer->getPixmap(),getXGuiManager()->getGC(),
           viewer->getColumn(_x0),
           viewer->getLine(_y0));
}

// inline void XGuiPoint::computePosition(void) // virtual

#endif // X_GUI

