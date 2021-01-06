#ifdef X_GUI

#include "XGui/xgShap2d.h"
#include "XGui/xgView2d.h"
#include "XGui/xgMgr.h"

//--------------------------------------------------------------------------//
// class XGuiShape2D                                                        //
//--------------------------------------------------------------------------//

//-------- Allocators ------------------------------------------------------//
XGuiShape2D::XGuiShape2D(double x,double y,double theta,const Strings & color)
 : _x0(x), _y0(y), _theta0(theta),
   _color("white"), _pixel(0),
   _layer(0), _hasMoved(false),
   _keyCallback((void (*)(XGuiShape2D *,const Strings &,void *))0),
   _keyData((void *)0),
   _motionCallback((void (*)(XGuiShape2D *,double,double,void *))0),
   _motionData((void *)0),
   _selectCallback((void (*)(XGuiShape2D *,XGuiViewer2D *,bool,void *))0),
   _selectData((void *)0)
{
getXGuiManager()->allocNamedColor(_color,_pixel);
setColor(color);
XGuiViewer2D::addShape(this);
}

XGuiShape2D::XGuiShape2D(const XGuiShape2D & s)
 : _x0(s._x0), _y0(s._y0), _theta0(s._theta0),
   _color("white"), _pixel(0),
   _layer(s._layer), _hasMoved(s._hasMoved),
   _keyCallback(s._keyCallback), _keyData(s._keyData),
   _motionCallback(s._motionCallback), _motionData(s._motionData),
   _selectCallback(s._selectCallback), _selectData(s._selectData)
{
getXGuiManager()->allocNamedColor(_color,_pixel);
setColor(s._color);
XGuiViewer2D::addShape(this);
}

XGuiShape2D::~XGuiShape2D(void)
{
XGuiViewer2D::removeShape(this);
getXGuiManager()->freeColor(_pixel);
}

// virtual XGuiShape2D * XGuiShape2D::duplicate(void) const=0;

//-------- Inspectors ------------------------------------------------------//
// inline double XGuiShape2D::getX(void) const

// inline double XGuiShape2D::getY(void) const

// inline double XGuiShape2D::getTheta(void) const

// inline const Strings & XGuiShape2D::getColor(void) const

// inline int XGuiShape2D::getLayer(void) const

// virtual void XGuiShape2D::getLocalBoundingBox(double & xmin,double & ymin,
//                                               double & xmax,double & ymax)
//                                                                   const=0;

// inline bool XGuiShape2D::isScalable(void) const // virtual

// virtual void XGuiShape2D::getBoundingBox(double & xmin,double & ymin,
//                                          double & xmax,double & ymax,
//                                          const XGuiViewer2D * viewer)
//                                          const=0

// virtual double XGuiShape2D::distanceTo(double x,double y,
//                                        const XGuiViewer2D * viewer) const=0

// inline bool XGuiShape2D::hasMoved(void) const

//-------- Input/Output ----------------------------------------------------//
ostream & operator<<(ostream & stream,const XGuiShape2D & shape)
{
return(stream << shape.print());
}

// virtual Strings XGuiShape2D::print(void) const=0

//-------- Modifiers -------------------------------------------------------//
// inline void XGuiShape2D::addViewer(XGuiViewer2D *) // virtual

// inline void XGuiShape2D::removeViewer(XGuiViewer2D *) // virtual

// inline void XGuiShape2D::changedViewerBackground(XGuiViewer2D *) // virtual

// virtual bool XGuiShape2D::isInside(double x,double y)=0;

// virtual bool XGuiShape2D::intersectRay(double xRay,double yRay,
//                                        double xDir,double yDir,
//                                        double & x,double & y)=0;

// virtual void XGuiShape2D::drawInViewer(XGuiViewer2D * viewer)=0;

// inline void XGuiShape2D::computePosition(void) // virtual

// inline void XGuiShape2D::savePosition(void) // virtual

void XGuiShape2D::move(double x,double y,double theta)
{
if((_x0!=x)||(_y0!=y)||(_theta0!=theta))
  {
  _x0=x;
  _y0=y;
  _theta0=theta;
  _hasMoved=true;
  XGuiViewer2D::forceRedraw();
  }
}

void XGuiShape2D::setColor(const Strings & color)
{
getXGuiManager()->freeColor(_pixel);
_color=color;
if(!getXGuiManager()->allocNamedColor(_color,_pixel))
  {
  getXGuiManager()->allocNamedColor("white",_pixel);
  }
XGuiViewer2D::forceRedraw();
}

void XGuiShape2D::setLayer(int layer)
{
XGuiViewer2D::removeShape(this);
_layer=layer;
XGuiViewer2D::addShape(this);
}

// inline void XGuiShape2D::setKeyCallback(void (*keyCallback)(XGuiShape2D *,
//                                                             const Strings &,
//                                                             void *),
//                                         void * keyData)

// inline void XGuiShape2D::setMotionCallback(
//                          void (*motionCallback)(XGuiShape2D *,
//                                                 double,double,
//                                                 void *),
//                          void * motionData)

// inline void XGuiShape2D::setSelectCallback(
//                          void (*selectCallback)(XGuiShape2D *,
//                                                 XGuiViewer2D *,
//                                                 bool,
//                                                 void *),
//                          void * selectData)

// inline void XGuiShape2D::notifyKey(const Strings & key)

// inline void XGuiShape2D::notifyMotion(double dx,double dy)

// inline void XGuiShape2D::notifySelection(XGuiViewer2D * viewer,
//                                          bool selected)

//-------- Private Methods -------------------------------------------------//
double XGuiShape2D::_distanceToSegment(double x,double y,
                                       double x1,double y1,
                                       double x2,double y2) // static
{
x-=x1; // put (x1;y1) on (0;0)
y-=y1;
x2-=x1;
y2-=y1;
if(!x2&&!y2) // the segment is a point !
  {
  return(::sqrt((x*x)+(y*y)));
  }
double d;
if(::fabs(x2)>::fabs(y2))
  {
  double a=y2/x2;
  d=::fabs((a*x-y)/::sqrt((a*a)+1.0));
  }
else
  {
  double b=x2/y2;
  d=::fabs((x-b*y)/::sqrt(1.0+(b*b)));
  }
double p1p2=(x2*x2)+(y2*y2);
double dx2=x-x2;
double dy2=y-y2;
if(((x*x)+(y*y))>=((d*d)+p1p2)) // near from (x2;y2)
  {
  return(::sqrt((dx2*dx2)+(dy2*dy2)));
  }
if(((dx2*dx2)+(dy2*dy2))>=((d*d)+p1p2)) // near from (x1;y1)
  {
  return(::sqrt((x*x)+(y*y)));
  }
return(d); // between (x1;y1) and (x2;y2)
}

#endif // X_GUI

