#ifdef X_GUI

#include "XGui/xgVScAre.h"
#include "XGui/xgScroll.h"
#include "XGui/xgMgr.h"

//--------------------------------------------------------------------------//
// class XGuiVScrolledArea                                                  //
//--------------------------------------------------------------------------//

//-------- Allocators ------------------------------------------------------//
XGuiVScrolledArea::XGuiVScrolledArea(XGuiArea * parent)
 : XGuiArea(parent),
   _screenWindow(None), _inWindow(None),
   _inHeight(2*getXGuiManager()->getMargin()),
   _scrollV(new XGuiScroller(this,false))
{
_scrollV->setCallback(XGuiVScrolledArea::_moveVCB,this);
setMinSize(2*getXGuiManager()->getMargin()+_scrollV->getWidth(),
           2*getXGuiManager()->getMargin());
_scrollV->setX(_width-_scrollV->getWidth());
_scrollV->setY(0);
_scrollV->setHeight(_height);
}

XGuiVScrolledArea::~XGuiVScrolledArea(void)
{
_screenWindow=None; // destroyed by _window
_inWindow=None; // destroyed by _window
// _scrollV is auto-deleted
}

//-------- Inspectors ------------------------------------------------------//
XGuiElement::Type XGuiVScrolledArea::getElemType(void) const // virtual
{
return(XGuiElement::SCROLLED_V_AREA);
}

bool XGuiVScrolledArea::isA(XGuiElement::Type type) const // virtual
{
return((type==XGuiElement::SCROLLED_V_AREA)||XGuiArea::isA(type));
}

int XGuiVScrolledArea::getInWidth(void) const // virtual
{
return(_width-_scrollV->getWidth());
}

int XGuiVScrolledArea::getInHeight(void) const // virtual
{
return(_inHeight);
}

Window XGuiVScrolledArea::getInWindow(void) const // virtual
{
return(_inWindow);
}

//-------- Modifiers -------------------------------------------------------//
void XGuiVScrolledArea::setWidth(int width) // virtual
{
XGuiElement::setWidth(width);
_scrollV->setX(_width-_scrollV->getWidth());
if(_screenWindow)
  {
  XWindowChanges changes;
  changes.width=_scrollV->getX();
  XConfigureWindow(getXGuiManager()->getDisplay(),_screenWindow,
                   CWWidth,&changes);
  XConfigureWindow(getXGuiManager()->getDisplay(),_inWindow,
                   CWWidth,&changes);
  }
if(_callback) (*_callback)(this,_data);
}

void XGuiVScrolledArea::setHeight(int height) // virtual
{
XGuiElement::setHeight(height);
_scrollV->setHeight(_height);
if(_screenWindow)
  {
  XWindowChanges changes;
  changes.height=_height;
  XConfigureWindow(getXGuiManager()->getDisplay(),_screenWindow,
                   CWHeight,&changes);
  }
_adjustRatio();
}

void XGuiVScrolledArea::setInWidth(int inWidth) // virtual
{
setWidth(inWidth+_scrollV->getWidth());
}

void XGuiVScrolledArea::setInHeight(int inHeight) // virtual
{
if(inHeight>2*getXGuiManager()->getMargin()) _inHeight=inHeight;
else _inHeight=2*getXGuiManager()->getMargin();
if(_inWindow)
  {
  XWindowChanges changes;
  changes.height=_inHeight;
  XConfigureWindow(getXGuiManager()->getDisplay(),_inWindow,CWHeight,&changes);
  }
adjustMenu(_width-_scrollV->getWidth(),_inHeight);
_adjustRatio();
if(_callback) (*_callback)(this,_data);
}

void XGuiVScrolledArea::show(void) // virtual
{
if(!_window)
  {
  _window=getXGuiManager()->getNewWindow(((XGuiArea *)_parent)->getInWindow(),
                                         _x,_y,_width,_height);
  _screenWindow=getXGuiManager()->getNewWindow(_window,0,0,
                                               _width-_scrollV->getWidth(),
                                               _height);
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
  _scrollV->show();
  _inWindow=tmp;
  }
XGuiElement::show();
_adjustRatio();
_moveVCB(_scrollV,this);
}

void XGuiVScrolledArea::hide(void) // virtual
{
XGuiElement::hide();
_screenWindow=None; // destroyed by _window
_inWindow=None; // destroyed by _window
}

void XGuiVScrolledArea::processEvent(const XEvent & event) // virtual
{
switch(event.type)
  {
  case ButtonPress:
    switch(event.xbutton.button)
      {
      case Button4: // wheel up
        _scrollV->setValue(_scrollV->getValue()-0.1);
        break;
      case Button5: // wheel down
        _scrollV->setValue(_scrollV->getValue()+0.1);
        break;
      }
    break;
  }
}

void XGuiVScrolledArea::redraw(void) // virtual
{
  // nothing to do
}

void XGuiVScrolledArea::_adjustRatio(void)
{
_scrollV->setRatio(((double)_scrollV->getHeight())/_inHeight);
}

//-------- Callbacks -------------------------------------------------------//

void XGuiVScrolledArea::_moveVCB(XGuiElement *,void * data) // static
{
XGuiVScrolledArea * area=(XGuiVScrolledArea *)data;
XWindowChanges changes;
changes.y=(int)(-area->_scrollV->getValue()*area->_inHeight);
XConfigureWindow(getXGuiManager()->getDisplay(),area->_inWindow,CWY,&changes);
}

#endif // X_GUI

