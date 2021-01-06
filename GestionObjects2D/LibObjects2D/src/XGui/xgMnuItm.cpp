#ifdef X_GUI

#include "XGui/xgMnuItm.h"
#include "XGui/xgMenu.h"
#include "XGui/xgMgr.h"

//--------------------------------------------------------------------------//
// class XGuiMenuItem                                                       //
//--------------------------------------------------------------------------//

//-------- Allocators ------------------------------------------------------//
XGuiMenuItem::XGuiMenuItem(XGuiMenu * parent,const Strings & title)
 : XGuiElement(2*getXGuiManager()->getMargin(),
               2*getXGuiManager()->getMargin()),
   _textX(0), _textY(0), _textWidth(0), _textHeight(0),
   _pressed(false), _inside(false), _menu((XGuiMenu *)0)
{
setTitle(title);
setWidth(2*getXGuiManager()->getMargin()+_textWidth);
setHeight(2*getXGuiManager()->getMargin()+_textHeight);
parent->addElement(this);
}

XGuiMenuItem::~XGuiMenuItem(void)
{
if(_menu) delete _menu;
}

//-------- Inspectors ------------------------------------------------------//
XGuiElement::Type XGuiMenuItem::getElemType(void) const // virtual
{
return(XGuiElement::MENU_ITEM);
}

bool XGuiMenuItem::isA(XGuiElement::Type type) const // virtual
{
return(type==XGuiElement::MENU_ITEM);
}

//-------- Modifiers -------------------------------------------------------//
void XGuiMenuItem::press(void)
{
if(_menu) _menu->show();
_pressed=true;
redraw();
}

void XGuiMenuItem::relax(void)
{
if(_menu) _menu->hide();
_pressed=false;
redraw();
}

void XGuiMenuItem::addElement(XGuiElement * element) // virtual
{
if(_menu) delete _menu;
_menu=(XGuiMenu *)element;
element->setParent(this);
}

void XGuiMenuItem::removeElement(XGuiElement * element) // virtual
{
if(_menu==element) _menu=(XGuiMenu *)0;
XGuiElement::removeElement(element);
}

void XGuiMenuItem::setWidth(int width) // virtual
{
XGuiElement::setWidth(width);
_textX=getXGuiManager()->getMargin();
redraw();
}

void XGuiMenuItem::setHeight(int height) // virtual
{
XGuiElement::setHeight(height);
_textY=(_height-_textHeight)/2;
redraw();
}

void XGuiMenuItem::setTitle(const Strings & title) // virtual
{
_textWidth=getXGuiManager()->getTextWidth(title);
_textX=getXGuiManager()->getMargin();
_textHeight=getXGuiManager()->getCharHeight();
_textY=(_height-_textHeight)/2;
XGuiElement::setTitle(title);
}

void XGuiMenuItem::show(void) // virtual
{
if(!_window)
  {
  _window=getXGuiManager()->getNewWindow(_parent->getWindow(),
                                         _x,_y,_width,_height);
  XSelectInput(getXGuiManager()->getDisplay(),_window,
               ExposureMask | OwnerGrabButtonMask |
               ButtonPressMask | ButtonReleaseMask |
               EnterWindowMask | LeaveWindowMask);
  XMapWindow(getXGuiManager()->getDisplay(),_window);
  }
XGuiElement::show();
}

void XGuiMenuItem::hide(void) // virtual
{
if(_menu) _menu->hide();
XGuiElement::hide();
_inside=false;
_pressed=false;
}

bool XGuiMenuItem::dispatchEvent(const XEvent & event) // virtual
{
if(XGuiElement::dispatchEvent(event)) return(true);
if(_menu) return(_menu->dispatchEvent(event));
return(false);
}

void XGuiMenuItem::processEvent(const XEvent & event) // virtual
{
switch(event.type)
  {
  case Expose:
    while(XCheckTypedWindowEvent(getXGuiManager()->getDisplay(),
                                 _window,Expose,(XEvent *)&event)) { ; }
    redraw();
    break;
  case ButtonPress:
    if(event.xbutton.button==Button1)
      {
      ((XGuiMenu *)_parent)->setActiveItem(this);
      redraw();
      }
    break;
  case ButtonRelease:
    if(event.xbutton.button==Button1)
      {
      if(_pressed)
        {
        getXGuiManager()->usingMenu((XGuiMenu *)0);
        redraw();
        if(_callback) (*_callback)(this,_data);
        }
      else redraw();
      }
    break;
  case EnterNotify:
    _inside=true;
    if(event.xcrossing.state&Button1Mask)
      {
      ((XGuiMenu *)_parent)->setActiveItem(this);
      }
    redraw();
    break;
  case LeaveNotify:
    _inside=false;
    redraw();
    break;
  }
}

void XGuiMenuItem::redraw(void) // virtual
{
if(_window)
  {
  if(_inside)
    getXGuiManager()->highlight(_window,0,0,_width,_height);
  else
    getXGuiManager()->background(_window,0,0,_width,_height);
  if(_pressed&&(_menu||_callback))
    getXGuiManager()->drawBorderUp(_window,0,0,_width,_height);
  getXGuiManager()->drawText(_window,_textX,_textY,_title);
  }
}

#endif // X_GUI

