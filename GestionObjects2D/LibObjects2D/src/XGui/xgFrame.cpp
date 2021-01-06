#ifdef X_GUI

#include "XGui/xgFrame.h"
#include "XGui/xgLabel.h"
#include "XGui/xgMgr.h"

//--------------------------------------------------------------------------//
// class XGuiFrame                                                          //
//--------------------------------------------------------------------------//

//-------- Allocators ------------------------------------------------------//
XGuiFrame::XGuiFrame(XGuiArea * parent,const Strings & title)
 : XGuiArea(parent),
   _titleLabel((XGuiLabel *)0), _inWindow(None)
{
setMinSize(4*getXGuiManager()->getMargin(),
           getXGuiManager()->getCharHeight()+3*getXGuiManager()->getMargin());
setTitle(title);
}

XGuiFrame::~XGuiFrame(void)
{
_inWindow=None; // destroyed by _window
// _titleLabel is auto-deleted
}

//-------- Inspectors ------------------------------------------------------//
XGuiElement::Type XGuiFrame::getElemType(void) const // virtual
{
return(XGuiElement::FRAME);
}

bool XGuiFrame::isA(XGuiElement::Type type) const // virtual
{
return((type==XGuiElement::FRAME)||XGuiArea::isA(type));
}

int XGuiFrame::getInWidth(void) const // virtual
{
return(_width-2*getXGuiManager()->getMargin());
}

int XGuiFrame::getInHeight(void) const // virtual
{
return(_height-getXGuiManager()->getCharHeight()-
               getXGuiManager()->getMargin());
}

Window XGuiFrame::getInWindow(void) const // virtual
{
return(_inWindow);
}

//-------- Modifiers -------------------------------------------------------//
void XGuiFrame::setWidth(int width) // virtual
{
XGuiElement::setWidth(width);
if(_inWindow)
  {
  XWindowChanges changes;
  changes.width=_width-2*getXGuiManager()->getMargin();
  XConfigureWindow(getXGuiManager()->getDisplay(),_inWindow,
                   CWWidth,&changes);
  }
adjustMenu(getInWidth(),getInHeight());
redraw();
if(_callback) (*_callback)(this,_data);
}

void XGuiFrame::setHeight(int height) // virtual
{
XGuiElement::setHeight(height);
if(_inWindow)
  {
  XWindowChanges changes;
  changes.height=_height-getXGuiManager()->getCharHeight()-
                         getXGuiManager()->getMargin();
  XConfigureWindow(getXGuiManager()->getDisplay(),_inWindow,
                   CWHeight,&changes);
  }
adjustMenu(getInWidth(),getInHeight());
redraw();
if(_callback) (*_callback)(this,_data);
}

void XGuiFrame::setTitle(const Strings & title) // virtual
{
if(title.len())
  {
  if(!_titleLabel)
    {
    _titleLabel=new XGuiLabel(this,title);
    _titleLabel->setHeight(getXGuiManager()->getCharHeight());
    _titleLabel->setX(4*getXGuiManager()->getMargin());
    _titleLabel->setY(0);
    }
  else _titleLabel->setTitle(title);
  _titleLabel->setWidth(getXGuiManager()->getTextWidth(title)+
                        2*getXGuiManager()->getMargin());
  }
else
  {
  if(_titleLabel) delete _titleLabel;
  _titleLabel=(XGuiLabel *)0;
  }
XGuiElement::setTitle(title);
}

void XGuiFrame::setInWidth(int inWidth) // virtual
{
setWidth(inWidth+2*getXGuiManager()->getMargin());
}

void XGuiFrame::setInHeight(int inHeight) // virtual
{
setHeight(inHeight+getXGuiManager()->getCharHeight()+
                   getXGuiManager()->getMargin());
}

void XGuiFrame::show(void) // virtual
{
if(!_window)
  {
  _window=getXGuiManager()->getNewWindow(((XGuiArea *)_parent)->getInWindow(),
                                         _x,_y,_width,_height);
  XSelectInput(getXGuiManager()->getDisplay(),_window,ExposureMask);
  _inWindow=getXGuiManager()->getNewWindow(_window,
                                           getXGuiManager()->getMargin(),
                                           getXGuiManager()->getCharHeight(),
                                           getInWidth(),getInHeight());
  XMapWindow(getXGuiManager()->getDisplay(),_window);
  XMapWindow(getXGuiManager()->getDisplay(),_inWindow);
  if(_titleLabel)
    {
    Window tmp=_inWindow;
    _inWindow=_window;
    _titleLabel->show();
    _inWindow=tmp;
    }
  }
XGuiElement::show();
}

void XGuiFrame::hide(void) // virtual
{
XGuiElement::hide();
_inWindow=None; // destroyed by _window
}

void XGuiFrame::processEvent(const XEvent & event) // virtual
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

void XGuiFrame::redraw(void) // virtual
{
if(_window)
  {
  getXGuiManager()->background(_window,0,0,_width,_height);
  int offset=getXGuiManager()->getCharHeight()-
             getXGuiManager()->getMargin();
  getXGuiManager()->drawBorderLineDown(_window,
                                       0,offset,_width,_height-offset);
  }
}

#endif // X_GUI

