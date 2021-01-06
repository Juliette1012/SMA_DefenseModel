#ifdef X_GUI

#include "XGui/xsCircle.h"
#include "XGui/xgView2d.h"
#include "XGui/xgMgr.h"

//--------------------------------------------------------------------------//
// class XGuiCircle                                                         //
//--------------------------------------------------------------------------//

//-------- Allocators ------------------------------------------------------//
XGuiCircle::XGuiCircle(double x,double y,double theta,const Strings & color,
                       double radius,bool filled)
 : XGuiShape2D(x,y,theta,color), _radius(radius), _filled(filled)
{
computePosition();
}

XGuiCircle::XGuiCircle(const XGuiCircle & s)
 : XGuiShape2D(s), _radius(s._radius), _filled(s._filled)
{}

XGuiCircle::~XGuiCircle(void)
{}

XGuiShape2D * XGuiCircle::duplicate(void) const // virtual
{
return(new XGuiCircle(*this));
}

//-------- Inspectors ------------------------------------------------------//
// inline void XGuiCircle::getLocalBoundingBox(double & xmin,double & ymin,
//                                             double & xmax,double & ymax)
//                                             const // virtual

// inline void XGuiCircle::getBoundingBox(double & xmin,double & ymin,
//                                        double & xmax,double & ymax,
//                                        const XGuiViewer2D * viewer) const
//                                                               // virtual

// inline double XGuiCircle::distanceTo(double x,double y,
//                                      const XGuiViewer2D * viewer)
//                                                        const // virtual

bool XGuiCircle::isInside(double x,double y) const // virtual
{
double dx=x-_x0;
double dy=y-_y0;
return((dx*dx+dy*dy)<_radius*_radius);
}

bool XGuiCircle::intersectRay(double xRay,double yRay,double xDir,double yDir,
                              double & xInter,double & yInter) const
{                                                              // virtual
double a=0.0,b=0.0,c=0.0;
XGuiShape2D::_equationLine(xRay,yRay,xRay+xDir,yRay+yDir,a,b,c);
if(b)
  {
  a/=b;
  c/=b;
  b=1.0;
  double A=1.0+a*a;
  double B=-2.0*_x0+2.0*a*c+2.0*a*_y0;
  double C=_x0*_x0+c*c+2.0*c*_y0+_y0*_y0-_radius*_radius;
  double delta=B*B-4.0*A*C;
  if(delta)
    {
    if(delta>0.0)
      {
      bool found=false;
      delta=::sqrt(delta);
      double x1=(-B-delta)/(2.0*A);
      double y1=-a*x1-c;
      double dx1=x1-xRay;
      double dy1=y1-yRay;
      double d1=0.0;
      if(dx1*xDir+dy1*yDir>0.0)
        {
        d1=dx1*dx1+dy1*dy1;
        xInter=x1;
        yInter=y1;
        found=true;
        }
      double x2=(-B+delta)/(2.0*A);
      double y2=-a*x2-c;
      double dx2=x2-xRay;
      double dy2=y2-yRay;
      double d2;
      if(dx2*xDir+dy2*yDir>0.0)
        {
        d2=dx2*dx2+dy2*dy2;
        if(!found||(d2<d1))
          {
          xInter=x2;
          yInter=y2;
          found=true;
          }
        }
      return(found);
      }
    else return(false);
    }
  else
    {
    xInter=-B/(2.0*A);
    yInter=-a*xInter-c;
    double dx=xInter-xRay;
    double dy=yInter-yRay;
    if(dx*xDir+dy*yDir>0.0) return(true);
    else return(false);
    }
  }
else
  {
  b/=a;
  c/=a;
  a=1.0;
  double A=1.0+b*b;
  double B=-2.0*_y0+2.0*b*c+2.0*b*_x0;
  double C=_y0*_y0+c*c+2.0*c*_x0+_x0*_x0-_radius*_radius;
  double delta=B*B-4.0*A*C;
  if(delta)
    {
    if(delta>0.0)
      {
      bool found=false;
      delta=::sqrt(delta);
      double y1=(-B-delta)/(2.0*A);
      double x1=-b*y1-c;
      double dx1=x1-xRay;
      double dy1=y1-yRay;
      double d1=0.0;
      if(dx1*xDir+dy1*yDir>0.0)
        {
        d1=dx1*dx1+dy1*dy1;
        xInter=x1;
        yInter=y1;
        found=true;
        }
      double y2=(-B+delta)/(2.0*A);
      double x2=-b*y2-c;
      double dx2=x2-xRay;
      double dy2=y2-yRay;
      double d2;
      if(dx2*xDir+dy2*yDir>0.0)
        {
        d2=dx2*dx2+dy2*dy2;
        if(!found||(d2<d1))
          {
          xInter=x2;
          yInter=y2;
          found=true;
          }
        }
      return(found);
      }
    else return(false);
    }
  else
    {
    yInter=-B/(2.0*A);
    xInter=-b*yInter-c;
    double dx=xInter-xRay;
    double dy=yInter-yRay;
    if(dx*xDir+dy*yDir>0.0) return(true);
    else return(false);
    }
  }
}

//-------- Input/Output ----------------------------------------------------//
Strings XGuiCircle::print(void) const // virtual
{
Strings str="circle("+Strings(_radius);
if(_filled) str+=",true)";
else str+=",false)";
return(str);
}

//-------- Modifiers -------------------------------------------------------//
void XGuiCircle::drawInViewer(XGuiViewer2D * viewer) // virtual
{
int side=2*(unsigned int)(_radius*viewer->getScale());
if(side<2) side=2;
int x=viewer->getColumn(_x0-_radius);
int y=viewer->getLine(_y0+_radius);
getXGuiManager()->chooseColor(_pixel);
if(_filled)
  {
  XFillArc(getXGuiManager()->getDisplay(),
           viewer->getPixmap(),getXGuiManager()->getGC(),
           x,y,side,side,0,23040); // 360*64=23040
  }
XDrawArc(getXGuiManager()->getDisplay(),
         viewer->getPixmap(),getXGuiManager()->getGC(),
         x,y,side,side,0,23040); // 360*64=23040
}

// inline void XGuiCircle::computePosition(void) // virtual

#endif // X_GUI

