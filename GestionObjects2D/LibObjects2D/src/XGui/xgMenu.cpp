#ifdef X_GUI

#include "XGui/xgMenu.h"
#include "XGui/xgMnuItm.h"
#include "XGui/xgOptMnu.h"
#include "XGui/xgArea.h"
#include "XGui/xgMgr.h"

//--------------------------------------------------------------------------//
// class XGuiMenu                                                           //
//--------------------------------------------------------------------------//

//-------- Allocators ------------------------------------------------------//
XGuiMenu::XGuiMenu(XGuiMenuItem * parent,bool horizontal)
 : XGuiElement(4*getXGuiManager()->getMargin(),
               4*getXGuiManager()->getMargin()),
   _horizontal(horizontal), _activeItem((XGuiMenuItem * )0)
{
setHeight(4*getXGuiManager()->getMargin()+getXGuiManager()->getCharHeight());
parent->addElement(this);
}

XGuiMenu::XGuiMenu(XGuiElement * parent,bool horizontal) // protected
 : XGuiElement(4*getXGuiManager()->getMargin(),
               4*getXGuiManager()->getMargin()),
   _horizontal(horizontal), _activeItem((XGuiMenuItem * )0)
{
setHeight(4*getXGuiManager()->getMargin()+getXGuiManager()->getCharHeight());
parent->addElement(this);
}

XGuiMenu::~XGuiMenu(void)
{}

//-------- Inspectors ------------------------------------------------------//
XGuiElement::Type XGuiMenu::getElemType(void) const // virtual
{
return(XGuiElement::MENU);
}

bool XGuiMenu::isA(XGuiElement::Type type) const // virtual
{
return(type==XGuiElement::MENU);
}

bool XGuiMenu::isHorizontal(void) const
{
return(_horizontal);
}

//-------- Modifiers -------------------------------------------------------//
void XGuiMenu::setActiveItem(XGuiMenuItem * item)
{
if(_activeItem!=item)
  {
  if(_activeItem) _activeItem->relax();
  _activeItem=item;
  if(_activeItem)
    {
    _activeItem->press();
    XGuiMenu * upperMenu=this;
    while(upperMenu->getParent()->isA(XGuiElement::MENU_ITEM))
      upperMenu=(XGuiMenu *)upperMenu->accessParent()->accessParent();
    getXGuiManager()->usingMenu(upperMenu);
    }
  }
}

void XGuiMenu::usingMenu(XGuiMenu * menu) // virtual
{
if(menu!=this) setActiveItem((XGuiMenuItem *)0);
}

void XGuiMenu::addElement(XGuiElement * element) // virtual
{
XGuiElement::addElement(element);
int width=2*getXGuiManager()->getMargin();
int height=2*getXGuiManager()->getMargin();
if(_horizontal)
  {
  for(int i=_elems.getSize();i--;) width+=_elems[i]->getWidth();
  setWidth(width);
  height+=element->getHeight();
  if(height>_height) setHeight(height);
  else element->setHeight(_height-2*getXGuiManager()->getMargin());
  }
else
  {
  for(int i=_elems.getSize();i--;) height+=_elems[i]->getHeight();
  setHeight(height);
  width+=element->getWidth();
  if(width>_width) setWidth(width);
  else element->setWidth(_width-2*getXGuiManager()->getMargin());
  }
}

void XGuiMenu::removeElement(XGuiElement * element) // virtual
{
XGuiElement::removeElement(element);
if(_horizontal) setWidth(_width-element->getWidth());
else setHeight(_height-element->getHeight());
}

void XGuiMenu::setWidth(int width) // virtual
{
XGuiElement::setWidth(width);
unsigned int i;
if(_horizontal)
  {
  int x=getXGuiManager()->getMargin();
  for(i=0;i<_elems.getSize();i++)
    {
    _elems[i]->setY(getXGuiManager()->getMargin());
    _elems[i]->setX(x);
    x+=_elems[i]->getWidth();
    }
  }
else
  {
  width=_width-2*getXGuiManager()->getMargin();
  for(i=_elems.getSize();i--;)
    {
    _elems[i]->setX(getXGuiManager()->getMargin());
    _elems[i]->setWidth(width);
    }
  }
}

void XGuiMenu::setHeight(int height) // virtual
{
XGuiElement::setHeight(height);
unsigned int i;
if(_horizontal)
  {
  height=_height-2*getXGuiManager()->getMargin();
  for(i=_elems.getSize();i--;)
    {
    _elems[i]->setY(getXGuiManager()->getMargin());
    _elems[i]->setHeight(height);
    }
  }
else
  {
  int y=getXGuiManager()->getMargin();
  for(i=0;i<_elems.getSize();i++)
    {
    _elems[i]->setX(getXGuiManager()->getMargin());
    _elems[i]->setY(y);
    y+=_elems[i]->getHeight();
    }
  }
}

void XGuiMenu::show(void) // virtual
{
if(!_window)
  {
  Window parentWindow;
  if(_parent->isA(XGuiElement::MENU_ITEM))
    {
    parentWindow=getXGuiManager()->getRoot();
    getXGuiManager()->getRootPosition(_parent->getWindow(),_x,_y);
    if(((const XGuiMenu *)_parent->getParent())->isHorizontal())
      {
      if(_x<0) _x=0;
      _y+=_parent->getHeight();
      if(_y+_height>getXGuiManager()->getScreenHeight())
        {
        _y-=_parent->getHeight()+_height;
        if(_y<0) _y=0;
        }
      if(_x+_width>getXGuiManager()->getScreenWidth())
        _x+=_parent->getWidth()-_width;
      if(_x+_width>getXGuiManager()->getScreenWidth())
        _x=getXGuiManager()->getScreenWidth()-_width;
      }
    else
      {
      if(_y<0) _y=0;
      _x+=_parent->getWidth();
      if(_x+_width>getXGuiManager()->getScreenWidth())
        {
        _x-=_parent->getWidth()+_width;
        if(_x<0) _x=0;
        }
      if(_y+_height>getXGuiManager()->getScreenHeight())
        _y+=_parent->getHeight()-_height;
      if(_y+_height>getXGuiManager()->getScreenHeight())
        _y=getXGuiManager()->getScreenHeight()-_height;
      }
    }
  else if(_parent->isA(XGuiElement::OPTION_MENU))
    {
    parentWindow=getXGuiManager()->getRoot();
    getXGuiManager()->getRootPosition(_parent->getWindow(),_x,_y);
    int r=((const XGuiOptionMenu *)_parent)->getResult();
    if(r<0)
      _y-=(_height-_parent->getHeight())/2;
    else
      _y-=getXGuiManager()->getMargin()+r*_parent->getHeight();
    if(_x<0)
      _x=0;
    else if(_x+_width>getXGuiManager()->getScreenWidth())
      _x=getXGuiManager()->getScreenWidth()-_width;
    if(_y<0)
      _y=0;
    else if(_y+_height>getXGuiManager()->getScreenHeight())
      _y=getXGuiManager()->getScreenHeight()-_height;
    }
  else // AREA
    parentWindow=((XGuiArea *)_parent)->getInWindow();
  _window=getXGuiManager()->getNewWindow(parentWindow,_x,_y,_width,_height);
  XSetWindowAttributes winAttr;
  winAttr.override_redirect=true;
  winAttr.event_mask=ExposureMask | OwnerGrabButtonMask |
                     ButtonPressMask | ButtonReleaseMask;
  XChangeWindowAttributes(getXGuiManager()->getDisplay(),_window,
                          CWOverrideRedirect | CWEventMask,&winAttr);
  XMapWindow(getXGuiManager()->getDisplay(),_window);
  }
XGuiElement::show();
}

void XGuiMenu::hide(void) // virtual
{
XGuiElement::hide();
_activeItem=(XGuiMenuItem * )0;
}

void XGuiMenu::processEvent(const XEvent & event) // virtual
{
switch(event.type)
  {
  case Expose:
    while(XCheckTypedWindowEvent(getXGuiManager()->getDisplay(),
                                 _window,Expose,(XEvent *)&event)) { ; }
    redraw();
    break;
  }
}

void XGuiMenu::redraw(void) // virtual
{
if(_window)
  {
  getXGuiManager()->background(_window,0,0,_width,_height);
  getXGuiManager()->drawBorderUp(_window,0,0,_width,_height);
  }
}

#endif // X_GUI

