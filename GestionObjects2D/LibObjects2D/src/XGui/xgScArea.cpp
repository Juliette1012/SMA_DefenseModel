#ifdef X_GUI

#include "XGui/xgScArea.h"
#include "XGui/xgScroll.h"
#include "XGui/xgMgr.h"

//--------------------------------------------------------------------------//
// class XGuiScrolledArea                                                   //
//--------------------------------------------------------------------------//

//-------- Allocators ------------------------------------------------------//
XGuiScrolledArea::XGuiScrolledArea(XGuiArea * parent)
 : XGuiArea(parent),
   _screenWindow(None), _inWindow(None),
   _inWidth(2*getXGuiManager()->getMargin()),
   _inHeight(2*getXGuiManager()->getMargin()),
   _scrollH(new XGuiScroller(this,true)),
   _scrollV(new XGuiScroller(this,false))
{
_scrollH->setCallback(XGuiScrolledArea::_moveHCB,this);
_scrollV->setCallback(XGuiScrolledArea::_moveVCB,this);
setMinSize(2*getXGuiManager()->getMargin()+_scrollV->getWidth(),
           2*getXGuiManager()->getMargin()+_scrollH->getHeight());
_scrollV->setY(0);
_scrollH->setX(0);
_scrollV->setX(_width-_scrollV->getWidth());
_scrollH->setY(_height-_scrollH->getHeight());
_scrollV->setHeight(_scrollH->getY());
_scrollH->setWidth(_scrollV->getX());
}

XGuiScrolledArea::~XGuiScrolledArea(void)
{
_screenWindow=None; // destroyed by _window
_inWindow=None; // destroyed by _window
// _scrollH and _scrollV are auto-deleted
}

//-------- Inspectors ------------------------------------------------------//
XGuiElement::Type XGuiScrolledArea::getElemType(void) const // virtual
{
return(XGuiElement::SCROLLED_AREA);
}

bool XGuiScrolledArea::isA(XGuiElement::Type type) const // virtual
{
return((type==XGuiElement::SCROLLED_AREA)||XGuiArea::isA(type));
}

int XGuiScrolledArea::getInWidth(void) const // virtual
{
return(_inWidth);
}

int XGuiScrolledArea::getInHeight(void) const // virtual
{
return(_inHeight);
}

Window XGuiScrolledArea::getInWindow(void) const // virtual
{
return(_inWindow);
}

//-------- Modifiers -------------------------------------------------------//
void XGuiScrolledArea::setWidth(int width) // virtual
{
XGuiElement::setWidth(width);
_scrollV->setX(_width-_scrollV->getWidth());
_scrollH->setWidth(_scrollV->getX());
if(_screenWindow)
  {
  XWindowChanges changes;
  changes.width=_scrollV->getX();
  XConfigureWindow(getXGuiManager()->getDisplay(),_screenWindow,
                   CWWidth,&changes);
  }
_adjustRatio();
}

void XGuiScrolledArea::setHeight(int height) // virtual
{
XGuiElement::setHeight(height);
_scrollH->setY(_height-_scrollH->getHeight());
_scrollV->setHeight(_scrollH->getY());
if(_screenWindow)
  {
  XWindowChanges changes;
  changes.height=_scrollH->getY();
  XConfigureWindow(getXGuiManager()->getDisplay(),_screenWindow,
                   CWHeight,&changes);
  }
_adjustRatio();
}

void XGuiScrolledArea::setInWidth(int inWidth) // virtual
{
if(inWidth>2*getXGuiManager()->getMargin()) _inWidth=inWidth;
else _inWidth=2*getXGuiManager()->getMargin();
if(_inWindow)
  {
  XWindowChanges changes;
  changes.width=_inWidth;
  XConfigureWindow(getXGuiManager()->getDisplay(),_inWindow,CWWidth,&changes);
  }
adjustMenu(_inWidth,_inHeight);
_adjustRatio();
if(_callback) (*_callback)(this,_data);
}

void XGuiScrolledArea::setInHeight(int inHeight) // virtual
{
if(inHeight>2*getXGuiManager()->getMargin()) _inHeight=inHeight;
else _inHeight=2*getXGuiManager()->getMargin();
if(_inWindow)
  {
  XWindowChanges changes;
  changes.height=_inHeight;
  XConfigureWindow(getXGuiManager()->getDisplay(),_inWindow,CWHeight,&changes);
  }
adjustMenu(_inWidth,_inHeight);
_adjustRatio();
if(_callback) (*_callback)(this,_data);
}

void XGuiScrolledArea::show(void) // virtual
{
if(!_window)
  {
  _window=getXGuiManager()->getNewWindow(((XGuiArea *)_parent)->getInWindow(),
                                         _x,_y,_width,_height);
  _screenWindow=getXGuiManager()->getNewWindow(_window,0,0,
                                               _width-_scrollV->getWidth(),
                                               _height-_scrollH->getHeight());
  _inWindow=getXGuiManager()->getNewWindow(_screenWindow,0,0,
                                           getInWidth(),getInHeight());
  long eventMask=ButtonPressMask;
  XSelectInput(getXGuiManager()->getDisplay(),_window,eventMask);
  XSelectInput(getXGuiManager()->getDisplay(),_inWindow,eventMask);
  XMapWindow(getXGuiManager()->getDisplay(),_window);
  XMapWindow(getXGuiManager()->getDisplay(),_screenWindow);
  XMapWindow(getXGuiManager()->getDisplay(),_inWindow);
  Window tmp=_inWindow;
  _inWindow=_window;
  _scrollH->show();
  _scrollV->show();
  _inWindow=tmp;
  }
XGuiElement::show();
_adjustRatio();
_moveHCB(_scrollH,this);
_moveVCB(_scrollV,this);
}

void XGuiScrolledArea::hide(void) // virtual
{
XGuiElement::hide();
_screenWindow=None; // destroyed by _window
_inWindow=None; // destroyed by _window
}

void XGuiScrolledArea::processEvent(const XEvent & event) // virtual
{
switch(event.type)
  {
  case ButtonPress:
    switch(event.xbutton.button)
      {
      case Button4: // wheel up
        if(event.xbutton.x*_height>=event.xbutton.y*_width)
          _scrollV->setValue(_scrollV->getValue()-0.1);
        else
          _scrollH->setValue(_scrollH->getValue()-0.1);
        break;
      case Button5: // wheel down
        if(event.xbutton.x*_height>=event.xbutton.y*_width)
          _scrollV->setValue(_scrollV->getValue()+0.1);
        else
          _scrollH->setValue(_scrollH->getValue()+0.1);
        break;
      }
    break;
  }
}

void XGuiScrolledArea::redraw(void) // virtual
{
  // nothing to do
}

void XGuiScrolledArea::_adjustRatio(void)
{
_scrollH->setRatio(((double)_scrollH->getWidth())/_inWidth);
_scrollV->setRatio(((double)_scrollV->getHeight())/_inHeight);
}

//-------- Callbacks -------------------------------------------------------//

void XGuiScrolledArea::_moveHCB(XGuiElement *,void * data) // static
{
XGuiScrolledArea * area=(XGuiScrolledArea *)data;
XWindowChanges changes;
changes.x=(int)(-area->_scrollH->getValue()*area->_inWidth);
XConfigureWindow(getXGuiManager()->getDisplay(),area->_inWindow,CWX,&changes);
}

void XGuiScrolledArea::_moveVCB(XGuiElement *,void * data) // static
{
XGuiScrolledArea * area=(XGuiScrolledArea *)data;
XWindowChanges changes;
changes.y=(int)(-area->_scrollV->getValue()*area->_inHeight);
XConfigureWindow(getXGuiManager()->getDisplay(),area->_inWindow,CWY,&changes);
}

#endif // X_GUI

