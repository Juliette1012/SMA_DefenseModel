#ifdef X_GUI

#include "XGui/xgTab.h"
#include "XGui/xgTabGrp.h"
#include "XGui/xgMgr.h"

//--------------------------------------------------------------------------//
// class XGuiTab                                                            //
//--------------------------------------------------------------------------//

//-------- Allocators ------------------------------------------------------//
XGuiTab::XGuiTab(XGuiTabGroup * parent,const Strings & title)
 : XGuiArea(parent)
{
_x=parent->_xOffset;
_y=parent->_yOffset;
_width=parent->getWidth()-2*parent->_xOffset;
_height=parent->getHeight()-parent->_yOffset-parent->_xOffset;
setTitle(title);
parent->addElement(this);
}

XGuiTab::~XGuiTab(void)
{
}

//-------- Inspectors ------------------------------------------------------//
XGuiElement::Type XGuiTab::getElemType(void) const // virtual
{
return(XGuiElement::TAB);
}

bool XGuiTab::isA(XGuiElement::Type type) const // virtual
{
return(type==XGuiElement::TAB);
}

int XGuiTab::getX(void) const // virtual
{
return(_parent->getX());
}

int XGuiTab::getY(void) const // virtual
{
return(_parent->getY());
}

int XGuiTab::getWidth(void) const // virtual
{
return(_parent->getWidth());
}

int XGuiTab::getHeight(void) const // virtual
{
return(_parent->getHeight());
}

int XGuiTab::getInWidth(void) const // virtual
{
return(_width);
}

int XGuiTab::getInHeight(void) const // virtual
{
return(_height);
}

//-------- Modifiers -------------------------------------------------------//
void XGuiTab::setX(int x) // virtual
{
_parent->setX(x);
}

void XGuiTab::setY(int y) // virtual
{
_parent->setY(y);
}

void XGuiTab::setWidth(int width) // virtual
{
width-=2*_x;
if(width!=_width)
  {
  XGuiArea::setWidth(width);
  _parent->setWidth(_width+2*_x);
  }
}

void XGuiTab::setHeight(int height) // virtual
{
height-=_y+_x;
if(height!=_height)
  {
  XGuiArea::setHeight(height);
  _parent->setHeight(_height+_y+_x);
  }
}

void XGuiTab::setInWidth(int inWidth) // virtual
{
if(inWidth!=_width)
  {
  XGuiArea::setWidth(inWidth);
  _parent->setWidth(_width+2*_x);
  }
}

void XGuiTab::setInHeight(int inHeight) // virtual
{
if(inHeight!=_height)
  {
  XGuiArea::setHeight(inHeight);
  _parent->setHeight(_height+_y+_x);
  }
}

void XGuiTab::setTitle(const Strings & title) // virtual
{
XGuiArea::setTitle(title);
if(_parent) ((XGuiTabGroup *)_parent)->_buildHeader();
}

void XGuiTab::show(void) // virtual
{
if(!_window)
  {
  _window=getXGuiManager()->getNewWindow(((XGuiTabGroup *)_parent)
                                         ->getWindow(),
                                         _x,_y,_width,_height);
  XMapWindow(getXGuiManager()->getDisplay(),_window);
  }
XGuiElement::show();
}

void XGuiTab::processEvent(const XEvent &) // virtual
{
  // nothing to do
}

void XGuiTab::redraw(void) // virtual
{
  // nothing to do
}

#endif // X_GUI

