#ifdef X_GUI

#include "XGui/xgCursor.h"
#include "XGui/xgArea.h"
#include "XGui/xgMgr.h"

//--------------------------------------------------------------------------//
// class XGuiCursor                                                         //
//--------------------------------------------------------------------------//

//-------- Allocators ------------------------------------------------------//
XGuiCursor::XGuiCursor(XGuiArea * parent,bool horizontal)
 : XGuiElement(3*getXGuiManager()->getMargin(),
               3*getXGuiManager()->getMargin()),
   _horizontal(horizontal), _value(0.0),
   _cursorX(0), _cursorY(0), _cursorWidth(0), _cursorHeight(0),
   _pressed(0), _offset(0), _inside(false), _pixmap(None)
{
if(_horizontal)
  {
  setWidth(_width);
  setHeight(4*getXGuiManager()->getMargin());
  }
else
  {
  setHeight(_height);
  setWidth(4*getXGuiManager()->getMargin());
  }
parent->addElement(this);
}

XGuiCursor::~XGuiCursor(void)
{
if(_pixmap) XFreePixmap(getXGuiManager()->getDisplay(),_pixmap);
}

//-------- Inspectors ------------------------------------------------------//
XGuiElement::Type XGuiCursor::getElemType(void) const // virtual
{
return(XGuiElement::CURSOR);
}

bool XGuiCursor::isA(XGuiElement::Type type) const // virtual
{
return(type==XGuiElement::CURSOR);
}

double XGuiCursor::getValue(void) const
{
return(_value);
}

//-------- Modifiers -------------------------------------------------------//
void XGuiCursor::setWidth(int width) // virtual
{
XGuiElement::setWidth(width);
if(_horizontal)
  {
  _cursorWidth=2*getXGuiManager()->getMargin();
  _cursorX=(int)(_value*(_width-_cursorWidth));
  }
else
  {
  _cursorWidth=_width;
  _cursorX=0;
  }
if(_pixmap)
  {
  XFreePixmap(getXGuiManager()->getDisplay(),_pixmap);
  _pixmap=getXGuiManager()->getNewPixmap(_window,_width,_height);
  }
redraw();
}

void XGuiCursor::setHeight(int height) // virtual
{
XGuiElement::setHeight(height);
if(_horizontal)
  {
  _cursorHeight=_height;
  _cursorY=0;
  }
else
  {
  _cursorHeight=2*getXGuiManager()->getMargin();
  _cursorY=(int)((1.0-_value)*(_height-_cursorHeight));
  }
if(_pixmap)
  {
  XFreePixmap(getXGuiManager()->getDisplay(),_pixmap);
  _pixmap=getXGuiManager()->getNewPixmap(_window,_width,_height);
  }
redraw();
}

void XGuiCursor::setValue(double value,bool propagate)
{
double oldValue=_value;
if(value>1.0) _value=1.0;
else if(value<0.0) _value=0.0;
else _value=value;
if(_horizontal) _cursorX=(int)(_value*(_width-_cursorWidth));
else _cursorY=(int)((1.0-_value)*(_height-_cursorHeight));
if(oldValue!=_value)
  {
  redraw();
  if(_callback&&propagate) (*_callback)(this,_data);
  }
}

void XGuiCursor::show(void) // virtual
{
if(!_window)
  {
  _window=getXGuiManager()->getNewWindow(
                            ((XGuiArea *)_parent)->getInWindow(),
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

void XGuiCursor::hide(void) // virtual
{
XGuiElement::hide();
if(_pixmap)
  {
  XFreePixmap(getXGuiManager()->getDisplay(),_pixmap);
  _pixmap=None;
  }
}

void XGuiCursor::processEvent(const XEvent & event) // virtual
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
      setValue(_value+0.1);
    else if(event.xbutton.button==Button5)  // wheel down
      setValue(_value-0.1);
    else
    if(!_pressed)
      {
      if(event.xbutton.button==Button1)
        {
        if(_horizontal)
          {
          if(event.xbutton.x<_cursorX)
            setValue(_value-0.1);
          else if(event.xbutton.x>_cursorX+_cursorWidth)
            setValue(_value+0.1);
          else
            {
            _pressed=event.xbutton.button;
            _offset=event.xbutton.x-_cursorX;
            }
          }
        else
          {
          if(event.xbutton.y<_cursorY)
            setValue(_value+0.1);
          else if(event.xbutton.y>_cursorY+_cursorHeight)
            setValue(_value-0.1);
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
          v=((double)(event.xbutton.x-_offset))/(_width-_cursorWidth);
          }
        else
          {
          _offset=_cursorHeight/2;
          v=1.0-((double)(event.xbutton.y-_offset))/(_height-_cursorHeight);
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
        setValue(((double)(event.xmotion.x-_offset))/(_width-_cursorWidth));
      else
        setValue(1.0-
                 ((double)(event.xmotion.y-_offset))/(_height-_cursorHeight));
      }
    break;
  }
}

void XGuiCursor::redraw(void) // virtual
{
if(_window)
  {
  getXGuiManager()->background(_pixmap,0,0,_width,_height);
  if(_horizontal)
    {
    getXGuiManager()->drawHLineDown(_pixmap,0,_height/2-1,_width);
    getXGuiManager()->drawVLineDown(_pixmap,0,0,_height);
    getXGuiManager()->drawVLineDown(_pixmap,_width-2,0,_height);
    }
  else
    {
    getXGuiManager()->drawVLineDown(_pixmap,_width/2-1,0,_height);
    getXGuiManager()->drawHLineDown(_pixmap,0,0,_width);
    getXGuiManager()->drawHLineDown(_pixmap,0,_height-2,_width);
    }
  if(_inside||(_pressed))
    getXGuiManager()->highlight(_pixmap,_cursorX,_cursorY,
                                _cursorWidth,_cursorHeight);
  else
    getXGuiManager()->background(_pixmap,_cursorX,_cursorY,
                                 _cursorWidth,_cursorHeight);
  getXGuiManager()->drawBorderUp(_pixmap,_cursorX,_cursorY,
                                 _cursorWidth,_cursorHeight);
  XCopyArea(getXGuiManager()->getDisplay(),_pixmap,_window,
            getXGuiManager()->getGC(),0,0,_width,_height,0,0);
  }
}

#endif // X_GUI

