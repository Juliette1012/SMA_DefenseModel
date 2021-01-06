#ifdef X_GUI

#include "XGui/xgMnuSep.h"
#include "XGui/xgMenu.h"
#include "XGui/xgMgr.h"

//--------------------------------------------------------------------------//
// class XGuiMenuSepar                                                      //
//--------------------------------------------------------------------------//

//-------- Allocators ------------------------------------------------------//
XGuiMenuSepar::XGuiMenuSepar(XGuiMenu * parent)
 : XGuiElement(getXGuiManager()->getMargin(),
               getXGuiManager()->getMargin()),
   _horizontal(!parent->isHorizontal())
{
if(_horizontal)
  {
  setWidth(parent->getWidth()-2*getXGuiManager()->getMargin());
  setHeight(getXGuiManager()->getMargin());
  }
else
  {
  setWidth(getXGuiManager()->getMargin());
  setHeight(parent->getHeight()-2*getXGuiManager()->getMargin());
  }
parent->addElement(this);
}

XGuiMenuSepar::~XGuiMenuSepar(void)
{
}

//-------- Inspectors ------------------------------------------------------//
XGuiElement::Type XGuiMenuSepar::getElemType(void) const // virtual
{
return(XGuiElement::MENU_SEPAR);
}

bool XGuiMenuSepar::isA(XGuiElement::Type type) const // virtual
{
return(type==XGuiElement::MENU_SEPAR);
}

//-------- Modifiers -------------------------------------------------------//
void XGuiMenuSepar::setWidth(int width) // virtual
{
XGuiElement::setWidth(width);
redraw();
}

void XGuiMenuSepar::setHeight(int height) // virtual
{
XGuiElement::setHeight(height);
redraw();
}

void XGuiMenuSepar::show(void) // virtual
{
if(!_window)
  {
  _window=getXGuiManager()->getNewWindow(_parent->getWindow(),
                                         _x,_y,_width,_height);
  XSelectInput(getXGuiManager()->getDisplay(),_window,ExposureMask);
  XMapWindow(getXGuiManager()->getDisplay(),_window);
  }
XGuiElement::show();
}

void XGuiMenuSepar::processEvent(const XEvent & event) // virtual
{
switch(event.type)
  {
  case Expose:
    while(XCheckTypedWindowEvent(getXGuiManager()->getDisplay(),
                                 _window,Expose,(XEvent *)&event));
    redraw();
    break;
  }
}

void XGuiMenuSepar::redraw(void) // virtual
{
if(_window)
  {
  getXGuiManager()->background(_window,0,0,_width,_height);
  if(_horizontal)
    getXGuiManager()->drawHLineDown(_window,0,_height/2-1,_width);
  else
    getXGuiManager()->drawVLineDown(_window,_width/2-1,0,_height);
  }
}

#endif // X_GUI

