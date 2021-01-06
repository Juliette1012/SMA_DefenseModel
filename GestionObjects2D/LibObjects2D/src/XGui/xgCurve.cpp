#ifdef X_GUI

#include "XGui/xgCurve.h"
#include "XGui/xgGraph.h"
#include "XGui/xgMgr.h"

//--------------------------------------------------------------------------//
// class XGuiCurve                                                          //
//--------------------------------------------------------------------------//

//-------- Allocators ------------------------------------------------------//
XGuiCurve::XGuiCurve(const Strings & color)
 : _color(color), _pixel(0), _x(), _y(), _accumulate(false),
   _xmin(0.0), _ymin(0.0), _xmax(0.0), _ymax(0.0)
{
if(!getXGuiManager()->allocNamedColor(_color,_pixel))
  {
  getXGuiManager()->allocNamedColor("black",_pixel);
  }
}

XGuiCurve::~XGuiCurve(void)
{
getXGuiManager()->freeColor(_pixel);
}

//-------- Inspectors ------------------------------------------------------//
// inline const Strings & XGuiCurve::getColor(void) const

// inline int XGuiCurve::getNbPoints(void) const

// inline void XGuiCurve::getBoundingBox(double & xmin,double & ymin,
//                                       double & xmax,double & ymax) const
//                                                                 // virtual

//-------- Input/Output ----------------------------------------------------//
ostream & operator<<(ostream & stream,const XGuiCurve & curve)
{
return(stream << curve.print());
}

Strings XGuiCurve::print(void) const // virtual
{
Strings str;
return(str);
}

//-------- Modifiers -------------------------------------------------------//
void XGuiCurve::addPoint(double x,double y) // virtual
{
if(_accumulate)
  {
  _x.raz();
  _y.raz();
  _accumulate=false;
  }
int nb=_x.getSize();
if(nb) // compute bounding box
  {
  if(x<_xmin) _xmin=x;
  else if(x>_xmax) _xmax=x;
  if(y<_ymin) _ymin=y;
  else if(y>_ymax) _ymax=y;
  }
else
  {
  _xmin=_xmax=x;
  _ymin=_ymax=y;
  }
bool done=false;
if(nb>=2) // insertion needed ?
  {
  double dx1=_x[nb-1]-_x[nb-2];
  double dy1=_y[nb-1]-_y[nb-2];
  double dx2=x-_x[nb-2];
  double dy2=y-_y[nb-2];
  if((dy1*dx2)==(dy2*dx1))
    {
    if(dx1<0.0) {dx1=-dx1; dx2=-dx2;}
    if(dy1<0.0) {dy1=-dy1; dy2=-dy2;}
    if((dx2>=dx1)&&(dy2>=dy1))
      {
      _x[nb-1]=x;
      _y[nb-1]=y;
      done=true;
      }
    }
  }
if(!done)
  {
  _x.pushBack(x);
  _y.pushBack(y);
  }
}

void XGuiCurve::accumulatePoint(double x,double y) // virtual
{
if(!_accumulate)
  {
  _x.raz();
  _y.raz();
  _accumulate=true;
  }
bool done=false;
for(unsigned int i=0;!done&&(i<_x.getSize());i++) // try to insert
  {
  if(_x[i]==x)
    {
    _y[i]+=y;
    y=_y[i];
    done=true;
    }
  else if(_x[i]>x)
    {
    _x.insert(i,x);
    _y.insert(i,y);
    done=true;
    }
  }
if(_x.getSize()) // compute bounding box
  {
  if(x<_xmin) _xmin=x;
  else if(x>_xmax) _xmax=x;
  if(y<_ymin) _ymin=y;
  else if(y>_ymax) _ymax=y;
  }
else
  {
  _xmin=_xmax=x;
  if(y<0.0) {_ymin=y; _ymax=0.0;}
  else {_ymax=y; _ymin=0.0;}
  }
if(!done)
  {
  _x.pushBack(x);
  _y.pushBack(y);
  }
}

void XGuiCurve::drawInGrapher(XGuiGrapher * grapher) // virtual
{
XPoint * points=(XPoint *)malloc(_x.getSize()* sizeof(XPoint));
for(int i=_x.getSize();i--;)
  {
  points[i].x=grapher->getColumn(_x[i]);
  points[i].y=grapher->getLine(_y[i]);
  }
getXGuiManager()->chooseColor(_pixel);
XDrawLines(getXGuiManager()->getDisplay(),
           grapher->getPixmap(),getXGuiManager()->getGC(),
           points,_x.getSize(),CoordModeOrigin);
free(points);
}

#endif // X_GUI

