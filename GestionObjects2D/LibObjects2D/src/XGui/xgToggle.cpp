#ifdef X_GUI

#include "XGui/xgToggle.h"
#include "XGui/xgArea.h"
#include "XGui/xgMgr.h"

//--------------------------------------------------------------------------//
// class XGuiToggle                                                         //
//--------------------------------------------------------------------------//

//-------- Allocators ------------------------------------------------------//
XGuiToggle::XGuiToggle(XGuiArea * parent,const Strings & title,bool big)
 : XGuiElement(2*getXGuiManager()->getMargin(),
               2*getXGuiManager()->getMargin()),
   _textX(0), _textY(0), _textWidth(0), _textHeight(0),
   _pressed(false), _inside(false), _big(big)
{
setTitle(title);
if(_big)
  setWidth(2*getXGuiManager()->getMargin()+_textWidth);
else
  setWidth(_textHeight+3*getXGuiManager()->getMargin()+_textWidth);
setHeight(2*getXGuiManager()->getMargin()+_textHeight);
parent->addElement(this);
}

XGuiToggle::XGuiToggle(XGuiElement * parent,const Strings & title,
                       bool big)                               // protected
 : XGuiElement(2*getXGuiManager()->getMargin(),
               2*getXGuiManager()->getMargin()),
   _textX(0), _textY(0), _textWidth(0), _textHeight(0),
   _pressed(false), _inside(false), _big(big)
{
setTitle(title);
if(_big)
  setWidth(2*getXGuiManager()->getMargin()+_textWidth);
else
  setWidth(_textHeight+3*getXGuiManager()->getMargin()+_textWidth);
setHeight(2*getXGuiManager()->getMargin()+_textHeight);
parent->addElement(this);
}

XGuiToggle::~XGuiToggle(void)
{
}

//-------- Inspectors ------------------------------------------------------//
XGuiElement::Type XGuiToggle::getElemType(void) const // virtual
{
return(XGuiElement::TOGGLE);
}

bool XGuiToggle::isA(XGuiElement::Type type) const // virtual
{
return(type==XGuiElement::TOGGLE);
}

bool XGuiToggle::isPressed(void) const
{
return(_pressed);
}

//-------- Modifiers -------------------------------------------------------//
void XGuiToggle::setPressed(bool isPressed,bool propagate)
{
if(_pressed!=isPressed)
  {
  _pressed=isPressed;
  redraw();
  if(_callback&&propagate) (*_callback)(this,_data);
  }
}

void XGuiToggle::setWidth(int width) // virtual
{
XGuiElement::setWidth(width);
if(_big)
  _textX=(_width-_textWidth)/2;
else
  _textX=getXGuiManager()->getCharHeight()+2*getXGuiManager()->getMargin();
redraw();
}

void XGuiToggle::setHeight(int height) // virtual
{
XGuiElement::setHeight(height);
_textY=(_height-_textHeight)/2;
redraw();
}

void XGuiToggle::setTitle(const Strings & title) // virtual
{
_textWidth=getXGuiManager()->getTextWidth(title);
if(_big)
  _textX=(_width-_textWidth)/2;
else
  _textX=getXGuiManager()->getCharHeight()+2*getXGuiManager()->getMargin();
_textHeight=getXGuiManager()->getCharHeight();
_textY=(_height-_textHeight)/2;
XGuiElement::setTitle(title);
}

void XGuiToggle::show(void) // virtual
{
if(!_window)
  {
  if(_parent->isA(XGuiElement::AREA))
    _window=getXGuiManager()->getNewWindow(
                              ((XGuiArea *)_parent)->getInWindow(),
                              _x,_y,_width,_height);
  else // TOGGLE_GROUP
    _window=getXGuiManager()->getNewWindow(_parent->getWindow(),
                                           _x,_y,_width,_height);
  XSelectInput(getXGuiManager()->getDisplay(),_window,
               ExposureMask | ButtonPressMask |
               EnterWindowMask | LeaveWindowMask);
  XMapWindow(getXGuiManager()->getDisplay(),_window);
  }
XGuiElement::show();
}

void XGuiToggle::processEvent(const XEvent & event) // virtual
{
switch(event.type)
  {
  case Expose:
    while(XCheckTypedWindowEvent(getXGuiManager()->getDisplay(),
                                 _window,Expose,(XEvent *)&event));
    redraw();
    break;
  case ButtonPress:
    if(event.xbutton.button==Button1)
      {
      setPressed(!_pressed);
      }
    break;
  case EnterNotify:
    _inside=true;
    redraw();
    break;
  case LeaveNotify:
    if(event.xcrossing.detail!=NotifyInferior)
      {
      _inside=false;
      redraw();
      }
    break;
  }
}

void XGuiToggle::redraw(void) // virtual
{
if(_window)
  {
  if(_inside)
    getXGuiManager()->highlight(_window,0,0,_width,_height);
  else
    getXGuiManager()->background(_window,0,0,_width,_height);
  if(_big)
    {
    if(_pressed)
      {
      getXGuiManager()->drawBorderDown(_window,0,0,_width,_height);
      getXGuiManager()->drawText(_window,_textX+1,_textY+1,_title);
      }
    else
      {
      getXGuiManager()->drawBorderUp(_window,0,0,_width,_height);
      getXGuiManager()->drawText(_window,_textX,_textY,_title);
      }
    }
  else
    {
    if(_pressed)
      getXGuiManager()->drawBorderDown(_window,getXGuiManager()->getMargin(),
                                              _textY,_textHeight,_textHeight);
    else
      getXGuiManager()->drawBorderUp(_window,getXGuiManager()->getMargin(),
                                             _textY,_textHeight,_textHeight);
    getXGuiManager()->drawText(_window,_textX,_textY,_title);
    }
  }
}

#endif // X_GUI

