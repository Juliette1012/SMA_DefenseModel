#ifdef X_GUI

#include "XGui/xgTglGrp.h"
#include "XGui/xgToggle.h"
#include "XGui/xgArea.h"
#include "XGui/xgMgr.h"

//--------------------------------------------------------------------------//
// class XGuiToggleGroup                                                    //
//--------------------------------------------------------------------------//

//-------- Allocators ------------------------------------------------------//
XGuiToggleGroup::XGuiToggleGroup(XGuiArea * parent,const StringsVect & entries,
                                 bool horizontal,bool big)
 : XGuiElement(2*getXGuiManager()->getMargin(),
               2*getXGuiManager()->getMargin()),
   _horizontal(horizontal)
{
parent->addElement(this);
int width=0;
int height=0;
for(unsigned int i=0;i<entries.size();i++)
  {
  XGuiToggle * toggle=new XGuiToggle(this,entries[i],big);
  toggle->setCallback(XGuiToggleGroup::_toggleCB);
  if(_horizontal)
    {
    if(toggle->getHeight()>height) height=toggle->getHeight();
    width+=toggle->getWidth();
    }
  else
    {
    if(toggle->getWidth()>width) width=toggle->getWidth();
    height+=toggle->getHeight();
    }
  }
setWidth(width);
setHeight(height);
if(_elems.getSize()) ((XGuiToggle *)_elems.accessFront())->setPressed(true);
}

XGuiToggleGroup::~XGuiToggleGroup(void)
{}

//-------- Inspectors ------------------------------------------------------//
XGuiElement::Type XGuiToggleGroup::getElemType(void) const // virtual
{
return(XGuiElement::TOGGLE_GROUP);
}

bool XGuiToggleGroup::isA(XGuiElement::Type type) const // virtual
{
return(type==XGuiElement::TOGGLE_GROUP);
}

int XGuiToggleGroup::getResult(void) const
{
for(int i=_elems.getSize();i--;)
  if(((const XGuiToggle *)_elems[i])->isPressed()) return(i);
return(-1);
}

int XGuiToggleGroup::getNbEntries(void) const
{
return(_elems.getSize());
}

const Strings & XGuiToggleGroup::getEntry(int pos) const
{
return(_elems[pos]->getTitle());
}

//-------- Modifiers -------------------------------------------------------//
void XGuiToggleGroup::setActiveToggle(XGuiToggle * toggle,bool propagate)
{
XGuiToggle * tgl;
for(int i=_elems.getSize();i--;)
  {
  tgl=(XGuiToggle *)_elems[i];
  if(tgl==toggle)
    {
    tgl->setPressed(true,false);
    }
  else tgl->setPressed(false,false);
  }
if(_callback&&propagate) (*_callback)(this,_data);
}

void XGuiToggleGroup::setActiveEntry(int pos,bool propagate)
{
if(((XGuiToggle *)_elems[pos])->isPressed()) propagate=false;
setActiveToggle((XGuiToggle *)_elems[pos],propagate);
}

void XGuiToggleGroup::setWidth(int width) // virtual
{
XGuiElement::setWidth(width);
unsigned int i;
if(_horizontal)
  {
  int x=0;
  int dx=_width;
  for(i=_elems.getSize();i--;) dx-=_elems[i]->getWidth();
  if(_elems.getSize()>1) dx/=_elems.getSize()-1;
  else dx=0;
  for(i=0;i<_elems.getSize();i++)
    {
    if(i) x+=dx;
    _elems[i]->setX(x);
    x+=_elems[i]->getWidth();
    }
  }
else
  {
  for(i=_elems.getSize();i--;)
    {
    _elems[i]->setX(0);
    _elems[i]->setWidth(_width);
    }
  }
}

void XGuiToggleGroup::setHeight(int height) // virtual
{
XGuiElement::setHeight(height);
unsigned int i;
if(_horizontal)
  {
  for(i=_elems.getSize();i--;)
    {
    _elems[i]->setY(0);
    _elems[i]->setHeight(_height);
    }
  }
else
  {
  int y=0;
  int dy=_height;
  for(i=_elems.getSize();i--;) dy-=_elems[i]->getHeight();
  if(_elems.getSize()>1) dy/=_elems.getSize()-1;
  else dy=0;
  for(i=0;i<_elems.getSize();i++)
    {
    if(i) y+=dy;
    _elems[i]->setY(y);
    y+=_elems[i]->getHeight();
    }
  }
}

void XGuiToggleGroup::show(void) // virtual
{
if(!_window)
  {
  _window=getXGuiManager()->getNewWindow(((XGuiArea *)_parent)->getInWindow(),
                                         _x,_y,_width,_height);
  XMapWindow(getXGuiManager()->getDisplay(),_window);
  }
XGuiElement::show();
}

void XGuiToggleGroup::processEvent(const XEvent &) // virtual
{
  // nothing to do
}

void XGuiToggleGroup::redraw(void) // virtual
{
  // nothing to do
}

//-------- Callbacks -------------------------------------------------------//
void XGuiToggleGroup::_toggleCB(XGuiElement * calling,void *) // static
{
XGuiToggle * toggle=(XGuiToggle *)calling;
if(toggle->isPressed())
  {
  ((XGuiToggleGroup *)calling->accessParent())->setActiveToggle(toggle);
  }
else toggle->setPressed(true,false);
}

#endif // X_GUI

