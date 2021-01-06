// @(#) ENIB/LI2 (c) - oRis - Version 2.3
//--------------------------------------------------------------------------//
// file        : xsRectan.cpp                                               //
// description : source file for the ENIB/LI2 class XGuiRectangle           //
// author(s)   : F. Harrouet                                                //
// copyright   : Laboratoire d'Informatique Industrielle (LI2)              //
//               Ecole Nationale d'Ingenieurs de Brest (ENIB)               //
//               CP 30815 - 29608 Brest Cedex - FRANCE                      //
//               Tel: (33) 02.98.05.66.31 , Fax: (33) 02.98.05.66.29        //
//               e-mail: li2@enib.fr                                        //
//--------------------------------------------------------------------------//
// Copyright (c) 1996-2000                                                  //
// Laboratoire d'Informatique Industrielle (LI2)                            //
// Ecole Nationale d'Ingenieurs de Brest (ENIB)                             //
//                                                                          //
// Permission to use, copy, modify, distribute and sell this software       //
// and its documentation for any purpose is hereby granted without fee,     //
// provided that the above copyright notice appear in all copies and        //
// that both that copyright notice and this permission notice appear        //
// in supporting documentation.                                             //
// ENIB/LI2 makes no representations about the suitability of this          //
// software for any purpose.                                                //
// It is provided "as is" without express or implied warranty.              //
//--------------------------------------------------------------------------//

#ifdef X_GUI

#include "XGui/xsRectan.h"
#include "XGui/xgView2d.h"
#include "XGui/xgMgr.h"


#define EPSILON 0.0001
#define ABS(x) ((x) < 0 ? -(x) : (x))
#define EQUAL(x,y) (ABS((x)-(y)) < EPSILON ? 1 : 0)

//--------------------------------------------------------------------------//
// class XGuiRectangle                                                     //
//--------------------------------------------------------------------------//

//-------- Allocators ------------------------------------------------------//
XGuiRectangle::XGuiRectangle(double x,double y,double theta,
                             const Strings & color,
                             double length,double width,bool filled)
 : XGuiShape2D(x,y,theta,color),
   _l_2(length/2.0), _w_2(width/2.0), _filled(filled)
{
computePosition();
}

XGuiRectangle::XGuiRectangle(const XGuiRectangle & s)
 : XGuiShape2D(s), _l_2(s._l_2), _w_2(s._w_2), _filled(s._filled)
{
for(int i=4;i--;)
  {
  _coordX[i]=s._coordX[i];
  _coordY[i]=s._coordY[i];
  }
}

XGuiRectangle::~XGuiRectangle(void)
{}

XGuiShape2D * XGuiRectangle::duplicate(void) const // virtual
{
return(new XGuiRectangle(*this));
}

//-------- Inspectors ------------------------------------------------------//
// inline void XGuiRectangle::getLocalBoundingBox(double & xmin,double & ymin,
//                                                double & xmax,double & ymax)
//                                                const // virtual

// inline void XGuiRectangle::getBoundingBox(double & xmin,double & ymin,
//                                           double & xmax,double & ymax,
//                                           const XGuiViewer2D * viewer)
//                                                         const // virtual

// inline double XGuiRectangle::distanceTo(double x,double y,
//                                         const XGuiViewer2D * viewer)
//                                                         const // virtual

bool XGuiRectangle::isInside(double x,double y) const // virtual
{
double cosTh=::cos(_theta0);
double sinTh=::sin(_theta0);
x-=_x0;
y-=_y0;
double xLocal=x*cosTh+y*sinTh;
double yLocal=y*cosTh-x*sinTh;
return((xLocal>-_l_2)&&(xLocal<_l_2)&&(yLocal>-_w_2)&&(yLocal<_w_2));
}

bool XGuiRectangle::intersectRay(double xRay,double yRay,
                                 double xDir,double yDir,
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
  if(!EQUAL(x1,x2)) // VR : avec -03, c'est ok x1==x2. Sinon if(!(EQUAL(x1,x2))
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
Strings XGuiRectangle::print(void) const // virtual
{
Strings str="square("+Strings(_l_2*2.0)+","+Strings(_w_2*2.0);
if(_filled) str+=",true)";
else str+=",false)";
return(str);
}

//-------- Modifiers -------------------------------------------------------//
void XGuiRectangle::drawInViewer(XGuiViewer2D * viewer) // virtual
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

// inline void XGuiRectangle::computePosition(void) // virtual

#endif // X_GUI

