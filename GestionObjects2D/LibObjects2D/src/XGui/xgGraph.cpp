#ifdef X_GUI

#include "XGui/xgGraph.h"
#include "XGui/xgCurve.h"
#include "XGui/xgArea.h"
#include "XGui/xgMgr.h"

#include <stdio.h>

//--------------------------------------------------------------------------//
// class XGuiGrapher                                                        //
//--------------------------------------------------------------------------//

XGuiGrapherList XGuiGrapher::_graphers;

bool XGuiGrapher::_mustDraw=true;

//-------- Static methods --------------------------------------------------//
// inline void XGuiGrapher::forceRedraw(void) // static

void XGuiGrapher::drawAll(void) // static
{
if(XGuiGrapher::_mustDraw)
  {
  XGuiGrapherList::iterator it=_graphers.begin();
  for(;it!=_graphers.end();it++) (*it)->redraw();
  XGuiGrapher::_mustDraw=false;
  }
}

//-------- Allocators ------------------------------------------------------//
XGuiGrapher::XGuiGrapher(XGuiArea * parent)
 : XGuiElement(getXGuiManager()->getTextWidth("-M.MMM")+
               4*getXGuiManager()->getMargin(),
               getXGuiManager()->getCharHeight()+
               4*getXGuiManager()->getMargin()),
   _xScale(1.0), _yScale(1.0), _xmin(0.0), _ymin(0.0), _xmax(0.0), _ymax(0.0),
   _color("white"), _pixel(0), _textPixel(getXGuiManager()->getForeground()),
   _curveMap(), _drawX(getXGuiManager()->getTextWidth("-M.MMM")),
   _drawY(getXGuiManager()->getMargin()),
   _drawWidth(_width-_drawX-getXGuiManager()->getMargin()-1),
   _drawHeight(_height-_drawY-getXGuiManager()->getCharHeight()-1),
   _ctrlPressed(false), _pressed(0), _mouseX(0), _mouseY(0),
   _pixmap(None), _region((Region)0)
{
getXGuiManager()->allocNamedColor(_color,_pixel);
parent->addElement(this);
XGuiGrapher::_graphers.push_back(this);
autoScale();
}

XGuiGrapher::~XGuiGrapher(void)
{
while(_curveMap.size()) clear((*_curveMap.begin()).first);
getXGuiManager()->freeColor(_pixel);
XGuiGrapherList::iterator it=XGuiGrapher::_graphers.begin();
while((*it)!=this) it++;
XGuiGrapher::_graphers.erase(it);
if(_pixmap) XFreePixmap(getXGuiManager()->getDisplay(),_pixmap);
if(_region) XDestroyRegion(_region);
}

//-------- Inspectors ------------------------------------------------------//
// inline XGuiElement::Type XGuiGrapher::getElemType(void) const // virtual

// inline bool XGuiGrapher::isA(XGuiElement::Type type) const // virtual

// inline double XGuiGrapher::getXScale(void) const

// inline double XGuiGrapher::getYScale(void) const

// inline double XGuiGrapher::getXmin(void) const

// inline double XGuiGrapher::getYmin(void) const

// inline double XGuiGrapher::getXmax(void) const

// inline double XGuiGrapher::getYmax(void) const

// inline int XGuiGrapher::getColumn(double x) const

// inline int XGuiGrapher::getLine(double y) const

// inline const Strings & XGuiGrapher::getBackground(void) const

// inline unsigned long XGuiGrapher::getBackgroundPixel(void) const

// inline Pixmap XGuiGrapher::getPixmap(void) const

//-------- Modifiers -------------------------------------------------------//
void XGuiGrapher::setBackground(const Strings & color)
{
unsigned long pixel;
if(getXGuiManager()->allocNamedColor(color,pixel))
  {
  unsigned short r,g,b;
  getXGuiManager()->queryColor(pixel,r,g,b);
  int nbDark=(r<0x8000)+(g<0x8000)+(b<0x8000);
  if(nbDark>=2)
    _textPixel=getXGuiManager()->getLightside();
  else
    _textPixel=getXGuiManager()->getForeground();
  getXGuiManager()->freeColor(_pixel);
  _pixel=pixel;
  _color=color;
  if(_window)
    {
    XSetWindowBackground(getXGuiManager()->getDisplay(),_window,pixel);
    }
  XGuiGrapher::_mustDraw=true;
  }
}

void XGuiGrapher::setViewPoint(double xmin,double ymin,double xmax,double ymax)
{
_xScale=_drawWidth/(xmax-xmin);
_yScale=_drawHeight/(ymax-ymin);
_xmin=xmin;
_ymin=ymin;
_xmax=xmax;
_ymax=ymax;
XGuiGrapher::_mustDraw=true;
}

void XGuiGrapher::autoScale(void)
{
double gxmin=0.0,gymin=0.0,gxmax=0.0,gymax=0.0;
double xmin,ymin,xmax,ymax;
bool firstTime=true;
XGuiCurveMap::const_iterator it=_curveMap.begin();
for(;it!=_curveMap.end();it++)
  {
  if((*it).second->getNbPoints())
    {
    (*it).second->getBoundingBox(xmin,ymin,xmax,ymax);
    if(firstTime)
      {
      gxmin=xmin;
      gymin=ymin;
      gxmax=xmax;
      gymax=ymax;
      firstTime=false;
      }
    else
      {
      if(xmin<gxmin) gxmin=xmin;
      if(ymin<gymin) gymin=ymin;
      if(xmax>gxmax) gxmax=xmax;
      if(ymax>gymax) gymax=ymax;
      }
    }
  }
if(gxmax==gxmin) {gxmin-=1.0; gxmax+=1.0;}
if(gymax==gymin) {gymin-=1.0; gymax+=1.0;}
setViewPoint(gxmin,gymin,gxmax,gymax);
}

void XGuiGrapher::autoScaleX(void)
{
double gxmin=0.0,gxmax=0.0;
double xmin,ymin,xmax,ymax;
bool firstTime=true;
XGuiCurveMap::const_iterator it=_curveMap.begin();
for(;it!=_curveMap.end();it++)
  {
  if((*it).second->getNbPoints())
    {
    (*it).second->getBoundingBox(xmin,ymin,xmax,ymax);
    if(firstTime)
      {
      gxmin=xmin;
      gxmax=xmax;
      firstTime=false;
      }
    else
      {
      if(xmin<gxmin) gxmin=xmin;
      if(xmax>gxmax) gxmax=xmax;
      }
    }
  }
if(gxmax==gxmin) {gxmin-=1.0; gxmax+=1.0;}
setViewPoint(gxmin,_ymin,gxmax,_ymax);
}

void XGuiGrapher::autoScaleY(void)
{
double gymin=0.0,gymax=0.0;
double xmin,ymin,xmax,ymax;
bool firstTime=true;
XGuiCurveMap::const_iterator it=_curveMap.begin();
for(;it!=_curveMap.end();it++)
  {
  if((*it).second->getNbPoints())
    {
    (*it).second->getBoundingBox(xmin,ymin,xmax,ymax);
    if(firstTime)
      {
      gymin=ymin;
      gymax=ymax;
      firstTime=false;
      }
    else
      {
      if(ymin<gymin) gymin=ymin;
      if(ymax>gymax) gymax=ymax;
      }
    }
  }
if(gymax==gymin) {gymin-=1.0; gymax+=1.0;}
setViewPoint(_xmin,gymin,_xmax,gymax);
}

void XGuiGrapher::addPoint(const Strings & color,double x,double y)
{
XGuiCurveMap::iterator it=_curveMap.find(color);
XGuiCurve * curve;
if(it==_curveMap.end())
  {
  curve=new XGuiCurve(color);
  _curveMap.insert(XGuiCurveMap::value_type(color,curve));
  }
else curve=(*it).second;
curve->addPoint(x,y);
XGuiGrapher::_mustDraw=true;
}

void XGuiGrapher::accumulatePoint(const Strings & color,double x,double y)
{
XGuiCurveMap::iterator it=_curveMap.find(color);
XGuiCurve * curve;
if(it==_curveMap.end())
  {
  curve=new XGuiCurve(color);
  _curveMap.insert(XGuiCurveMap::value_type(color,curve));
  }
else curve=(*it).second;
curve->accumulatePoint(x,y);
XGuiGrapher::_mustDraw=true;
}

void XGuiGrapher::clear(const Strings & color)
{
XGuiCurveMap::iterator it=_curveMap.find(color);
if(it!=_curveMap.end())
  {
  delete (*it).second;
  _curveMap.erase(it);
  }
XGuiGrapher::_mustDraw=true;
}

void XGuiGrapher::setWidth(int width) // virtual
{
XGuiElement::setWidth(width);
_drawWidth=_width-_drawX-getXGuiManager()->getMargin()-1;
if(_window)
  {
  XFreePixmap(getXGuiManager()->getDisplay(),_pixmap);
  _pixmap=getXGuiManager()->getNewPixmap(_window,_width,_height);
  XDestroyRegion(_region);
  _region=XCreateRegion();
  XRectangle rect;
  rect.x=_drawX;
  rect.y=_drawY;
  rect.width=_drawWidth+1;
  rect.height=_drawHeight+1;
  XUnionRectWithRegion(&rect,_region,_region);
  setViewPoint(_xmin,_ymin,_xmax,_ymax);
  }
}

void XGuiGrapher::setHeight(int height) // virtual
{
XGuiElement::setHeight(height);
_drawHeight=_height-_drawY-getXGuiManager()->getCharHeight()-1;
if(_window)
  {
  XFreePixmap(getXGuiManager()->getDisplay(),_pixmap);
  _pixmap=getXGuiManager()->getNewPixmap(_window,_width,_height);
  XDestroyRegion(_region);
  _region=XCreateRegion();
  XRectangle rect;
  rect.x=_drawX;
  rect.y=_drawY;
  rect.width=_drawWidth+1;
  rect.height=_drawHeight+1;
  XUnionRectWithRegion(&rect,_region,_region);
  setViewPoint(_xmin,_ymin,_xmax,_ymax);
  }
}

void XGuiGrapher::show(void) // virtual
{
if(!_window)
  {
  _window=getXGuiManager()->getNewWindow(((XGuiArea *)_parent)->getInWindow(),
                                         _x,_y,_width,_height);
  XSetWindowBackground(getXGuiManager()->getDisplay(),_window,_pixel);
  XSelectInput(getXGuiManager()->getDisplay(),_window,
               ExposureMask | EnterWindowMask |
               KeyPressMask | KeyReleaseMask |
               ButtonPressMask | ButtonMotionMask | ButtonReleaseMask);
  _pixmap=getXGuiManager()->getNewPixmap(_window,_width,_height);
  _region=XCreateRegion();
  XRectangle rect;
  rect.x=_drawX;
  rect.y=_drawY;
  rect.width=_drawWidth+1;
  rect.height=_drawHeight+1;
  XUnionRectWithRegion(&rect,_region,_region);
  XMapWindow(getXGuiManager()->getDisplay(),_window);
  XGuiGrapher::_mustDraw=true;
  }
XGuiElement::show();
}

void XGuiGrapher::hide(void) // virtual
{
XGuiElement::hide();
if(_pixmap)
  {
  XFreePixmap(getXGuiManager()->getDisplay(),_pixmap);
  _pixmap=None;
  }
if(_region)
  {
  XDestroyRegion(_region);
  _region=(Region)0;
  }
}

void XGuiGrapher::processEvent(const XEvent & event) // virtual
{
switch(event.type)
  {
  case Expose:
    while(XCheckTypedWindowEvent(getXGuiManager()->getDisplay(),
                                 _window,Expose,(XEvent *)&event)) { ; }
    XGuiGrapher::_mustDraw=true;
    break;
  case EnterNotify:
    if(event.xcrossing.state&ControlMask) _ctrlPressed=true;
    else _ctrlPressed=false;
    _chooseCursor();
    break;
  case KeyPress:
    {
    static char buffer[0x10];
    KeySym keysym;
    int nb=XLookupString((XKeyEvent *)&event.xkey,
                         buffer,0x10,&keysym,(XComposeStatus*)0);
    if(!nb)
      {
      switch(keysym)
        {
        case XK_Control_L:
        case XK_Control_R:
          _ctrlPressed=true;
          _chooseCursor();
          break;
        }
      }
    }
    break;
  case KeyRelease:
    {
    static char buffer[0x10];
    KeySym keysym;
    int nb=XLookupString((XKeyEvent *)&event.xkey,
                         buffer,0x10,&keysym,(XComposeStatus*)0);
    if(!nb)
      {
      switch(keysym)
        {
        case XK_Control_L:
        case XK_Control_R:
          _ctrlPressed=false;
          _chooseCursor();
          break;
        }
      }
    }
    break;
  case ButtonPress:
    if(!_pressed)
      {
      _pressed=event.xbutton.button;
      _mouseX=event.xbutton.x;
      _mouseY=event.xbutton.y;
      _chooseCursor();
      }
    break;
  case ButtonRelease:
    if(_pressed==event.xbutton.button)
      {
      _pressed=0;
      _chooseCursor();
      }
    break;
  case MotionNotify:
    while(XCheckTypedWindowEvent(getXGuiManager()->getDisplay(),
                                 _window,MotionNotify,(XEvent *)&event)) { ; }
    if(_pressed)
      {
      int dx=event.xbutton.x-_mouseX;
      int dy=event.xbutton.y-_mouseY;
      _mouseX=event.xbutton.x;
      _mouseY=event.xbutton.y;
      if(_ctrlPressed)
        {
        if(_pressed==Button1) // ---> translate
          {
          setViewPoint(_xmin-dx/_xScale,
                       _ymin+dy/_yScale,
                       _xmax-dx/_xScale,
                       _ymax+dy/_yScale);
          }
        else // other button ---> zoom
          {
          double x=(_xmin+_xmax)/2.0;
          double y=(_ymin+_ymax)/2.0;
          double xScale=_xScale*(dx<0 ? 1.0-2.0*dx/_drawWidth
                                      : 1.0/(1.0+2.0*dx/_drawWidth));
          double yScale=_yScale*(dy>0 ? 1.0+2.0*dy/_drawHeight
                                      : 1.0/(1.0-2.0*dy/_drawHeight));
          setViewPoint(x-_drawWidth/(2.0*xScale),
                       y-_drawHeight/(2.0*yScale),
                       x+_drawWidth/(2.0*xScale),
                       y+_drawHeight/(2.0*yScale));
          }
        }
      }
    break;
  }
}

void XGuiGrapher::redraw(void) // virtual
{
if(_window&&_mapped)
  {
  getXGuiManager()->chooseColor(_pixel);
  XFillRectangle(getXGuiManager()->getDisplay(),_pixmap,
                 getXGuiManager()->getGC(),0,0,_width,_height);
  _drawAxis();
  XSetRegion(getXGuiManager()->getDisplay(),
             getXGuiManager()->getGC(),_region);
  XGuiCurveMap::iterator it=_curveMap.begin();
  for(;it!=_curveMap.end();it++)
    (*it).second->drawInGrapher(this);
  XSetClipMask(getXGuiManager()->getDisplay(),
               getXGuiManager()->getGC(),None);
  XCopyArea(getXGuiManager()->getDisplay(),_pixmap,_window,
            getXGuiManager()->getGC(),0,0,_width,_height,0,0);
  }
}

void XGuiGrapher::_drawAxis(void)
{
static char buffer[0x20];
int px,py;
getXGuiManager()->chooseColor(_textPixel);
XDrawRectangle(getXGuiManager()->getDisplay(),_pixmap,
               getXGuiManager()->getGC(),
               _drawX,_drawY,_drawWidth,_drawHeight);
if((_xmin<0.0)&&(_xmax>0.0))
  {
  px=getColumn(0.0);
  XDrawLine(getXGuiManager()->getDisplay(),_pixmap,
            getXGuiManager()->getGC(),px,_drawY,px,_drawY+_drawHeight);
  }
if((_ymin<0.0)&&(_ymax>0.0))
  {
  py=getLine(0.0);
  XDrawLine(getXGuiManager()->getDisplay(),_pixmap,
            getXGuiManager()->getGC(),_drawX,py,_drawX+_drawWidth,py);
  }
double x,y;
int wX=0,wY=0;
Strings strX,strY;
XSetLineAttributes(getXGuiManager()->getDisplay(),getXGuiManager()->getGC(),
                   0,LineOnOffDash,CapButt,JoinMiter);
for(int i=0;i<5;i++)
  {
  x=_xmin+i*(_xmax-_xmin)/4.0;
  y=_ymin+i*(_ymax-_ymin)/4.0;
  px=getColumn(x);
  py=getLine(y);
  sprintf(buffer,"%.2f",x);
  strX=buffer;
  wX=getXGuiManager()->getTextWidth(strX);
  sprintf(buffer,"%.2f",y);
  strY=buffer;
  wY=getXGuiManager()->getTextWidth(strY);
  if(wY>_drawX) wY=_drawX;
  if(!i)
    {
    py-=getXGuiManager()->getCharHeight()/2; // align bottom
    // px+=wX/2; // align left
    }
  else if(i==4)
    {
    py+=getXGuiManager()->getCharHeight()/2; // align top
    px-=wX/2; // align right
    }
  else
    {
    XDrawLine(getXGuiManager()->getDisplay(),_pixmap,
              getXGuiManager()->getGC(),_drawX,py,_drawX+_drawWidth,py);
    XDrawLine(getXGuiManager()->getDisplay(),_pixmap,
              getXGuiManager()->getGC(),px,_drawY,px,_drawY+_drawHeight);
    }
  XDrawString(getXGuiManager()->getDisplay(),_pixmap,
              getXGuiManager()->getGC(),
              px-wX/2,_drawY+_drawHeight+getXGuiManager()->getFont()->ascent,
              strX,strX.len());
  XDrawString(getXGuiManager()->getDisplay(),_pixmap,
              getXGuiManager()->getGC(),
              _drawX-wY,py-getXGuiManager()->getCharHeight()/2+
              getXGuiManager()->getFont()->ascent,strY,strY.len());
  }
XSetLineAttributes(getXGuiManager()->getDisplay(),getXGuiManager()->getGC(),
                   0,LineSolid,CapButt,JoinMiter);
}

void XGuiGrapher::_chooseCursor(void)
{
if(_ctrlPressed)
  {
  if(_pressed&&(_pressed!=Button1))
    getXGuiManager()->setZoomXYCursor(_window);
  else
    getXGuiManager()->setMoveCursor(_window);
  }
else getXGuiManager()->setDefaultCursor(_window);
}

#endif // X_GUI

