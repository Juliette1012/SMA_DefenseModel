#include "XGui/xgHScAre.h"
#include "XGui/xgScroll.h"
#include "XGui/xgMgr.h"

//--------------------------------------------------------------------------//
// class XGuiHScrolledArea                                                  //
//--------------------------------------------------------------------------//

//-------- Allocators ------------------------------------------------------//
XGuiHScrolledArea::XGuiHScrolledArea(XGuiArea * parent)
 : XGuiArea(parent),
   _screenWindow(None), _inWindow(None),
   _inWidth(2*getXGuiManager()->getMargin()),
   _scrollH(new XGuiScroller(this,true))
{
_scrollH->setCallback(XGuiHScrolledArea::_moveHCB,this);
setMinSize(2*getXGuiManager()->getMargin(),
           2*getXGuiManager()->getMargin()+_scrollH->getHeight());
_scrollH->setX(0);
_scrollH->setY(_height-_scrollH->getHeight());
_scrollH->setWidth(_width);
}

XGuiHScrolledArea::~XGuiHScrolledArea(void)
{
_screenWindow=None; // destroyed by _window
_inWindow=None; // destroyed by _window
// _scrollH is auto-deleted
}

//-------- Inspectors ------------------------------------------------------//
XGuiElement::Type XGuiHScrolledArea::getElemType(void) const // virtual
{
return(XGuiElement::SCROLLED_H_AREA);
}

bool XGuiHScrolledArea::isA(XGuiElement::Type type) const // virtual
{
return((type==XGuiElement::SCROLLED_H_AREA)||XGuiArea::isA(type));
}

int XGuiHScrolledArea::getInWidth(void) const // virtual
{
return(_inWidth);
}

int XGuiHScrolledArea::getInHeight(void) const // virtual
{
return(_height-_scrollH->getHeight());
}

Window XGuiHScrolledArea::getInWindow(void) const // virtual
{
return(_inWindow);
}

//-------- Modifiers -------------------------------------------------------//
void XGuiHScrolledArea::setWidth(int width) // virtual
{
XGuiElement::setWidth(width);
_scrollH->setWidth(_width);
if(_screenWindow)
  {
  XWindowChanges changes;
  changes.width=_width;
  XConfigureWindow(getXGuiManager()->getDisplay(),_screenWindow,
                   CWWidth,&changes);
  }
_adjustRatio();
}

void XGuiHScrolledArea::setHeight(int height) // virtual
{
XGuiElement::setHeight(height);
_scrollH->setY(_height-_scrollH->getHeight());
if(_screenWindow)
  {
  XWindowChanges changes;
  changes.height=_scrollH->getY();
  XConfigureWindow(getXGuiManager()->getDisplay(),_screenWindow,
                   CWHeight,&changes);
  XConfigureWindow(getXGuiManager()->getDisplay(),_inWindow,
                   CWHeight,&changes);
  }
if(_callback) (*_callback)(this,_data);
}

void XGuiHScrolledArea::setInWidth(int inWidth) // virtual
{
if(inWidth>2*getXGuiManager()->getMargin()) _inWidth=inWidth;
else _inWidth=2*getXGuiManager()->getMargin();
if(_inWindow)
  {
  XWindowChanges changes;
  changes.width=_inWidth;
  XConfigureWindow(getXGuiManager()->getDisplay(),_inWindow,CWWidth,&changes);
  }
adjustMenu(_inWidth,_height-_scrollH->getHeight());
_adjustRatio();
if(_callback) (*_callback)(this,_data);
}

void XGuiHScrolledArea::setInHeight(int inHeight) // virtual
{
setHeight(inHeight+_scrollH->getHeight());
}

void XGuiHScrolledArea::show(void) // virtual
{
if(!_window)
  {
  _window=getXGuiManager()->getNewWindow(((XGuiArea *)_parent)->getInWindow(),
                                         _x,_y,_width,_height);
  _screenWindow=getXGuiManager()->getNewWindow(_window,0,0,
                                               _width,
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
  _inWindow=tmp;
  }
XGuiElement::show();
_adjustRatio();
_moveHCB(_scrollH,this);
}

void XGuiHScrolledArea::hide(void) // virtual
{
XGuiElement::hide();
_screenWindow=None; // destroyed by _window
_inWindow=None; // destroyed by _window
}

void XGuiHScrolledArea::processEvent(const XEvent & event) // virtual
{
switch(event.type)
  {
  case ButtonPress:
    switch(event.xbutton.button)
      {
      case Button4: // wheel up
        _scrollH->setValue(_scrollH->getValue()-0.1);
        break;
      case Button5: // wheel down
        _scrollH->setValue(_scrollH->getValue()+0.1);
        break;
      }
    break;
  }
}

void XGuiHScrolledArea::redraw(void) // virtual
{
  // nothing to do
}

void XGuiHScrolledArea::_adjustRatio(void)
{
_scrollH->setRatio(((double)_scrollH->getWidth())/_inWidth);
}

//-------- Callbacks -------------------------------------------------------//

void XGuiHScrolledArea::_moveHCB(XGuiElement *,void * data) // static
{
XGuiHScrolledArea * area=(XGuiHScrolledArea *)data;
XWindowChanges changes;
changes.x=(int)(-area->_scrollH->getValue()*area->_inWidth);
XConfigureWindow(getXGuiManager()->getDisplay(),area->_inWindow,CWX,&changes);
}

#endif // X_GUI

