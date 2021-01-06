#ifdef X_GUI

#include "XGui/xgMnuBar.h"
#include "XGui/xgArea.h"
#include "XGui/xgMgr.h"

//--------------------------------------------------------------------------//
// class XGuiMenuBar                                                        //
//--------------------------------------------------------------------------//

//-------- Allocators ------------------------------------------------------//
XGuiMenuBar::XGuiMenuBar(XGuiArea * parent,bool horizontal,bool pushLast)
 : XGuiMenu(parent,horizontal), _pushLast(pushLast)
{
setX(0);
setY(0);
if(_horizontal) setWidth(((XGuiArea *)_parent)->getInWidth());
else setHeight(((XGuiArea *)_parent)->getInHeight());
}

XGuiMenuBar::~XGuiMenuBar(void)
{}

//-------- Inspectors ------------------------------------------------------//
XGuiElement::Type XGuiMenuBar::getElemType(void) const // virtual
{
return(XGuiElement::MENU_BAR);
}

bool XGuiMenuBar::isA(XGuiElement::Type type) const // virtual
{
return((type==XGuiElement::MENU_BAR)||XGuiMenu::isA(type));
}

//-------- Modifiers -------------------------------------------------------//
void XGuiMenuBar::addElement(XGuiElement * element) // virtual
{
XGuiElement::addElement(element);
int width=2*getXGuiManager()->getMargin();
int height=2*getXGuiManager()->getMargin();
if(_horizontal)
  {
  setWidth(_width);
  height+=element->getHeight();
  if(height>_height) setHeight(height);
  else element->setHeight(_height-2*getXGuiManager()->getMargin());
  }
else
  {
  setHeight(_height);
  width+=element->getWidth();
  if(width>_width) setWidth(width);
  else element->setWidth(_width-2*getXGuiManager()->getMargin());
  }
}

void XGuiMenuBar::removeElement(XGuiElement * element) // virtual
{
XGuiElement::removeElement(element);
if(_horizontal) setWidth(_width);
else setHeight(_height);
}

void XGuiMenuBar::setWidth(int width) // virtual
{
XGuiMenu::setWidth(width);
if(_pushLast&&_horizontal&&(_elems.getSize()>1))
  {
  XGuiElement * element=_elems.accessBack();
  element->setX(_width-getXGuiManager()->getMargin()-element->getWidth());
  }
}

void XGuiMenuBar::setHeight(int height) // virtual
{
XGuiMenu::setHeight(height);
if(_pushLast&&!_horizontal&&(_elems.getSize()>1))
  {
  XGuiElement * element=_elems.accessBack();
  element->setY(_height-getXGuiManager()->getMargin()-element->getHeight());
  }
}

#endif // X_GUI

