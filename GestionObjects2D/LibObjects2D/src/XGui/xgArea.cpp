#ifdef X_GUI

#include "XGui/xgArea.h"
#include "XGui/xgMnuBar.h"
#include "XGui/xgTabGrp.h"
#include "XGui/xgMgr.h"

//--------------------------------------------------------------------------//
// class XGuiArea                                                           //
//--------------------------------------------------------------------------//

//-------- Allocators ------------------------------------------------------//
XGuiArea::XGuiArea(XGuiTabGroup * /* parent */) // protected
 : XGuiElement(2*getXGuiManager()->getMargin(),
               2*getXGuiManager()->getMargin())
{}

XGuiArea::XGuiArea(XGuiArea * parent)
 : XGuiElement(2*getXGuiManager()->getMargin(),
               2*getXGuiManager()->getMargin())
{
if(parent) parent->addElement(this);
else getXGuiManager()->addElement(this);
}

XGuiArea::~XGuiArea(void)
{
if(_parent)
  _parent->removeElement(this);
else
  getXGuiManager()->removeElement(this);
}

//-------- Inspectors ------------------------------------------------------//
XGuiElement::Type XGuiArea::getElemType(void) const // virtual
{
return(XGuiElement::AREA);
}

bool XGuiArea::isA(XGuiElement::Type type) const // virtual
{
return(type==XGuiElement::AREA);
}

unsigned long XGuiArea::getWindowID(void) const
{
return((unsigned long)getInWindow());
}

int XGuiArea::getInWidth(void) const // virtual
{
return(_width);
}

int XGuiArea::getInHeight(void) const // virtual
{
return(_height);
}

Window XGuiArea::getInWindow(void) const // virtual
{
return(_window);
}

//-------- Modifiers -------------------------------------------------------//
void XGuiArea::setWidth(int width) // virtual
{
XGuiElement::setWidth(width);
adjustMenu(_width,_height);
redraw();
if(_callback) (*_callback)(this,_data);
}

void XGuiArea::setHeight(int height) // virtual
{
XGuiElement::setHeight(height);
adjustMenu(_width,_height);
redraw();
if(_callback) (*_callback)(this,_data);
}

void XGuiArea::setInWidth(int inWidth) // virtual
{
setWidth(inWidth);
}

void XGuiArea::setInHeight(int inHeight) // virtual
{
setHeight(inHeight);
}

void XGuiArea::show(void) // virtual
{
if(!_window&&_parent)
  {
  _window=getXGuiManager()->getNewWindow(((XGuiArea *)_parent)->getInWindow(),
                                         _x,_y,_width,_height);
  XMapWindow(getXGuiManager()->getDisplay(),_window);
  }
XGuiElement::show();
}

bool XGuiArea::dispatchEvent(const XEvent & event) // virtual
{
if((event.xany.window==getWindow())||
   (event.xany.window==getInWindow()))
  {
  processEvent(event);
  return(true);
  }
else
  {
  for(int i=_elems.getSize();i--;)
    if(_elems[i]->dispatchEvent(event)) return(true);
  return(false);
  }
}

void XGuiArea::processEvent(const XEvent &) // virtual
{
  // nothing to do
}

void XGuiArea::redraw(void) // virtual
{
  // nothing to do
}

void XGuiArea::adjustMenu(int width,int height)
{
for(int i=_elems.getSize();i--;)
  {
  if(_elems[i]->isA(XGuiElement::MENU_BAR))
    {
    if(((XGuiMenuBar *)_elems[i])->isHorizontal())
      _elems[i]->setWidth(width);
    else
      _elems[i]->setHeight(height);
    }
  }
}

#endif // X_GUI

