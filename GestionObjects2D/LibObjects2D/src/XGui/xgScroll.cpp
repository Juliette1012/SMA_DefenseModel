#ifdef X_GUI

#include "XGui/xgScroll.h"
#include "XGui/xgArea.h"
#include "XGui/xgMgr.h"

//--------------------------------------------------------------------------//
// class XGuiScroller                                                       //
//--------------------------------------------------------------------------//

//-------- Allocators ------------------------------------------------------//
XGuiScroller::XGuiScroller(XGuiArea * parent,bool horizontal)
 : XGuiElement(3*getXGuiManager()->getMargin(),
               3*getXGuiManager()->getMargin()),
   _horizontal(horizontal), _value(0.0), _ratio(1.0),
   _cursorX(0), _cursorY(0), _cursorWidth(0), _cursorHeight(0),
   _pressed(0), _offset(0), _inside(false), _pixmap(None)
{
setWidth(_width);
setHeight(_height);
parent->addElement(this);
}

XGuiScroller::XGuiScroller(XGuiElement * parent,bool horizontal) // protected
 : XGuiElement(3*getXGuiManager()->getMargin(),
               3*getXGuiManager()->getMargin()),
   _horizontal(horizontal), _value(0.0), _ratio(1.0),
   _cursorX(0), _cursorY(0), _cursorWidth(0), _cursorHeight(0),
   _pressed(0), _offset(0), _inside(false), _pixmap(None)
{
setWidth(_width);
setHeight(_height);
parent->addElement(this);
}

XGuiScroller::~XGuiScroller(void)
{
if(_pixmap) XFreePixmap(getXGuiManager()->getDisplay(),_pixmap);
}

//-------- Inspectors ------------------------------------------------------//
XGuiElement::Type XGuiScroller::getElemType(void) const // virtual
{
return(XGuiElement::SCROLLER);
}

bool XGuiScroller::isA(XGuiElement::Type type) const // virtual
{
return(type==XGuiElement::SCROLLER);
}

double XGuiScroller::getValue(void) const
{
return(_value);
}

double XGuiScroller::getRatio(void) const
{
return(_ratio);
}

//-------- Modifiers -------------------------------------------------------//
void XGuiScroller::setWidth(int width) // virtual
{
XGuiElement::setWidth(width);
if(_horizontal)
  {
  _cursorX=(int)(_value*_width);
  _cursorWidth=1+(int)(_ratio*_width);
  if(_cursorWidth<getXGuiManager()->getMargin())
    _cursorWidth=getXGuiManager()->getMargin();
  }
else
  {
  _cursorX=0;
  _cursorWidth=_width;
  }
if(_pixmap)
  {
  XFreePixmap(getXGuiManager()->getDisplay(),_pixmap);
  _pixmap=getXGuiManager()->getNewPixmap(_window,_width,_height);
  }
redraw();
}

void XGuiScroller::setHeight(int height) // virtual
{
XGuiElement::setHeight(height);
if(_horizontal)
  {
  _cursorY=0;
  _cursorHeight=_height;
  }
else
  {
  _cursorY=(int)(_value*_height);
  _cursorHeight=1+(int)(_ratio*_height);
  if(_cursorHeight<getXGuiManager()->getMargin())
    _cursorHeight=getXGuiManager()->getMargin();
  }
if(_pixmap)
  {
  XFreePixmap(getXGuiManager()->getDisplay(),_pixmap);
  _pixmap=getXGuiManager()->getNewPixmap(_window,_width,_height);
  }
redraw();
}

void XGuiScroller::setValue(double value,bool propagate)
{
double oldValue=_value;
if(value+_ratio>1.0) _value=1.0-_ratio;
else if(value<0.0) _value=0.0;
else _value=value;
if(_horizontal) _cursorX=(int)(_value*_width);
else _cursorY=(int)(_value*_height);
if(oldValue!=_value)
  {
  redraw();
  if(_callback&&propagate) (*_callback)(this,_data);
  }
}

void XGuiScroller::setRatio(double ratio,bool propagate)
{
if(ratio<0.0) _ratio=0.0;
else if(ratio>1.0) _ratio=1.0;
else _ratio=ratio;
if(_value+_ratio>1.0) setValue(1.0-_ratio,propagate);
if(_horizontal)
  {
  _cursorWidth=(int)(_ratio*_width);
  if(_cursorWidth<getXGuiManager()->getMargin())
    _cursorWidth=getXGuiManager()->getMargin();
  else if(_cursorWidth<_width) _cursorWidth++;
  }
else
  {
  _cursorHeight=(int)(_ratio*_height);
  if(_cursorHeight<getXGuiManager()->getMargin())
    _cursorHeight=getXGuiManager()->getMargin();
  else if(_cursorHeight<_height) _cursorHeight++;
  }
redraw();
}

void XGuiScroller::show(void) // virtual
{
if(!_window)
  {
  if(_parent->isA(XGuiElement::AREA))
    _window=getXGuiManager()->getNewWindow(
                              ((XGuiArea *)_parent)->getInWindow(),
                              _x,_y,_width,_height);
  else // LIST or EDITOR
    _window=getXGuiManager()->getNewWindow(_parent->getWindow(),
                                           _x,_y,_width,_height);
  XSelectInput(getXGuiManager()->getDisplay(),_window,
               ExposureMask | ButtonMotionMask |
               EnterWindowMask | LeaveWindowMask |
               ButtonPressMask | ButtonReleaseMask);
  _pixmap=getXGuiManager()->getNewPixmap(_window,_width,_height);
  XMapWindow(getXGuiManager()->getDisplay(),_window);
  }
XGuiElement::show();
}

void XGuiScroller::hide(void) // virtual
{
XGuiElement::hide();
if(_pixmap)
  {
  XFreePixmap(getXGuiManager()->getDisplay(),_pixmap);
  _pixmap=None;
  }
}

void XGuiScroller::processEvent(const XEvent & event) // virtual
{
switch(event.type)
  {
  case Expose:
    while(XCheckTypedWindowEvent(getXGuiManager()->getDisplay(),
                                 _window,Expose,(XEvent *)&event));
    redraw();
    break;
  case EnterNotify:
    _inside=true;
    redraw();
    break;
  case LeaveNotify:
    _inside=false;
    redraw();
    break;
  case ButtonPress:
    if(event.xbutton.button==Button4)  // wheel up
      setValue(_value-_ratio/2.0);
    else if(event.xbutton.button==Button5)  // wheel down
      setValue(_value+_ratio/2.0);
    else
    if(!_pressed)
      {
      if(event.xbutton.button==Button1)
        {
        if(_horizontal)
          {
          if(event.xbutton.x<_cursorX)
            setValue(_value-_ratio/2.0);
          else if(event.xbutton.x>_cursorX+_cursorWidth)
            setValue(_value+_ratio/2.0);
          else
            {
            _pressed=event.xbutton.button;
            _offset=event.xbutton.x-_cursorX;
            }
          }
        else
          {
          if(event.xbutton.y<_cursorY)
            setValue(_value-_ratio/2.0);
          else if(event.xbutton.y>_cursorY+_cursorHeight)
            setValue(_value+_ratio/2.0);
          else
            {
            _pressed=event.xbutton.button;
            _offset=event.xbutton.y-_cursorY;
            }
          }
        }
      else
        {
        _pressed=event.xbutton.button;
        double v;
        if(_horizontal)
          {
          _offset=_cursorWidth/2;
          v=((double)(event.xbutton.x-_offset))/_width;
          }
        else
          {
          _offset=_cursorHeight/2;
          v=((double)(event.xbutton.y-_offset))/_height;
          }
        setValue(v);
        }
      }
    break;
  case ButtonRelease:
    _pressed=0;
    break;
  case MotionNotify:
    while(XCheckTypedWindowEvent(getXGuiManager()->getDisplay(),
                                 _window,MotionNotify,(XEvent *)&event));
    if(_pressed)
      {
      if(_horizontal)
        setValue(((double)(event.xmotion.x-_offset))/_width);
      else
        setValue(((double)(event.xmotion.y-_offset))/_height);
      }
    break;
  }
}

void XGuiScroller::redraw(void) // virtual
{
if(_window)
  {
  getXGuiManager()->background(_pixmap,0,0,_width,_height);
  getXGuiManager()->drawBorderDown(_pixmap,0,0,_width,_height);
  if(_inside||(_pressed))
    getXGuiManager()->highlight(_pixmap,_cursorX,_cursorY,
                                _cursorWidth,_cursorHeight);
  if(_horizontal)
    {
    if(_cursorWidth>3*getXGuiManager()->getMargin())
      {
      getXGuiManager()->drawVLineDown(_pixmap,
                        _cursorX+_cursorWidth/2-getXGuiManager()->getMargin(),
                        _cursorY,_cursorHeight);
      getXGuiManager()->drawVLineDown(_pixmap,
                        _cursorX+_cursorWidth/2+getXGuiManager()->getMargin(),
                        _cursorY,_cursorHeight);
      }
    getXGuiManager()->drawVLineDown(_pixmap,
                        _cursorX+_cursorWidth/2,_cursorY,_cursorHeight);
    }
  else
    {
    if(_cursorHeight>3*getXGuiManager()->getMargin())
      {
      getXGuiManager()->drawHLineDown(_pixmap,_cursorX,
                        _cursorY+_cursorHeight/2-getXGuiManager()->getMargin(),
                        _cursorWidth);
      getXGuiManager()->drawHLineDown(_pixmap,_cursorX,
                        _cursorY+_cursorHeight/2+getXGuiManager()->getMargin(),
                        _cursorWidth);
      }
    getXGuiManager()->drawHLineDown(_pixmap,_cursorX,
                        _cursorY+_cursorHeight/2,_cursorWidth);
    }
  getXGuiManager()->drawBorderUp(_pixmap,_cursorX,_cursorY,
                                 _cursorWidth,_cursorHeight);
  XCopyArea(getXGuiManager()->getDisplay(),_pixmap,_window,
            getXGuiManager()->getGC(),0,0,_width,_height,0,0);
  }
}

#endif // X_GUI

