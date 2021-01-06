#ifdef X_GUI

#include "XGui/xgButton.h"
#include "XGui/xgArea.h"
#include "XGui/xgMgr.h"

//--------------------------------------------------------------------------//
// class XGuiButton                                                         //
//--------------------------------------------------------------------------//
 
//-------- Allocators ------------------------------------------------------//
XGuiButton::XGuiButton(XGuiArea * parent,const Strings & title)
 : XGuiElement(2*getXGuiManager()->getMargin(),
               2*getXGuiManager()->getMargin()),
   _textX(0), _textY(0), _textWidth(0), _textHeight(0),
   _pressed(false), _inside(false)
{
setTitle(title);
setWidth(2*getXGuiManager()->getMargin()+_textWidth);
setHeight(2*getXGuiManager()->getMargin()+_textHeight);
parent->addElement(this);
}

XGuiButton::~XGuiButton(void)
{}

//-------- Inspectors ------------------------------------------------------//
XGuiElement::Type XGuiButton::getElemType(void) const // virtual
{
return(XGuiElement::BUTTON);
}

bool XGuiButton::isA(XGuiElement::Type type) const // virtual
{
return(type==XGuiElement::BUTTON);
}

//-------- Modifiers -------------------------------------------------------//
void XGuiButton::setWidth(int width) // virtual
{
XGuiElement::setWidth(width);
_textX=(_width-_textWidth)/2;
redraw();
}

void XGuiButton::setHeight(int height) // virtual
{
XGuiElement::setHeight(height);
_textY=(_height-_textHeight)/2;
redraw();
}

void XGuiButton::setTitle(const Strings & title) // virtual
{
_textWidth=getXGuiManager()->getTextWidth(title);
_textX=(_width-_textWidth)/2;
_textHeight=getXGuiManager()->getCharHeight();
_textY=(_height-_textHeight)/2;
XGuiElement::setTitle(title);
}

void XGuiButton::show(void) // virtual
{
if(!_window)
  {
  _window=getXGuiManager()->getNewWindow(((XGuiArea *)_parent)->getInWindow(),
                                         _x,_y,_width,_height);
  XSelectInput(getXGuiManager()->getDisplay(),_window,
               ExposureMask | ButtonPressMask | ButtonReleaseMask |
               EnterWindowMask | LeaveWindowMask);
  XMapWindow(getXGuiManager()->getDisplay(),_window);
  }
XGuiElement::show();
}

void XGuiButton::processEvent(const XEvent & event) // virtual
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
      _pressed=true;
      redraw();
      }
    break;
  case ButtonRelease:
    if(_inside&&_pressed&&_callback)
      {
      _pressed=false;
      redraw();
      (*_callback)(this,_data);
      }
    else
      {
      _pressed=false;
      redraw();
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

void XGuiButton::redraw(void) // virtual
{
if(_window)
  {
  if(_inside)
    getXGuiManager()->highlight(_window,0,0,_width,_height);
  else
    getXGuiManager()->background(_window,0,0,_width,_height);
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
}

#endif // X_GUI

