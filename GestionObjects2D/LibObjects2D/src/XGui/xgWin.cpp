#ifdef X_GUI

#include "XGui/xgWin.h"
#include "XGui/xgMgr.h"

//--------------------------------------------------------------------------//
// class XGuiWindow                                                         //
//--------------------------------------------------------------------------//

bool XGuiWindow::_deltaComputed=false;

int XGuiWindow::_dx=0;

int XGuiWindow::_dy=0;

int XGuiWindow::_dw=0;

int XGuiWindow::_dh=0;


//-------- Allocators ------------------------------------------------------//
XGuiWindow::XGuiWindow(const Strings & title)
 : XGuiArea((XGuiArea *)0),
   _inWindow(None), _inWidthGiven(true), _inHeightGiven(true),
   _closeCallback((void (*)(XGuiElement *,void *))0),
   _closeData((void *)0)
{
setMinSize(_minWidth+XGuiWindow::_dw,_minHeight+XGuiWindow::_dh);
setTitle(title);
}

XGuiWindow::~XGuiWindow(void)
{
if(_inWindow!=_window) // reparented ?
  {
  _window=_inWindow; // destroyed by XGuiElement
  _inWindow=None;
  }
}

//-------- Inspectors ------------------------------------------------------//
XGuiElement::Type XGuiWindow::getElemType(void) const // virtual
{
return(XGuiElement::WINDOW);
}

bool XGuiWindow::isA(XGuiElement::Type type) const // virtual
{
return((type==XGuiElement::WINDOW)||XGuiArea::isA(type));
}

int XGuiWindow::getInWidth(void) const // virtual
{
return(_width-XGuiWindow::_dw);
}

int XGuiWindow::getInHeight(void) const // virtual
{
return(_height-XGuiWindow::_dh);
}

Window XGuiWindow::getInWindow(void) const // virtual
{
return(_inWindow);
}

//-------- Modifiers -------------------------------------------------------//
void XGuiWindow::setMinSize(int minWidth,int minHeight) // virtual
{
XGuiElement::setMinSize(minWidth,minHeight);
if(_inWindow)
  {
  XSizeHints * hints=XAllocSizeHints();
  hints->flags=PMinSize;
  hints->min_width=_minWidth;
  hints->min_height=_minHeight;
  XSetWMNormalHints(getXGuiManager()->getDisplay(),_inWindow,hints);
  XFree(hints);
  }
}

void XGuiWindow::setX(int x) // virtual
{
_x=x;
if(_inWindow)
  {
  XWindowChanges changes;
  changes.x=_x+XGuiWindow::_dx;
  XConfigureWindow(getXGuiManager()->getDisplay(),_inWindow,CWX,&changes);
  }
}

void XGuiWindow::setY(int y) // virtual
{
_y=y;
if(_inWindow)
  {
  XWindowChanges changes;
  changes.y=_y+XGuiWindow::_dy;
  XConfigureWindow(getXGuiManager()->getDisplay(),_inWindow,CWY,&changes);
  }
}

void XGuiWindow::setWidth(int width) // virtual
{
_inWidthGiven=false;
_width=(width>=_minWidth ? width : _minWidth);
if(_inWindow)
  {
  XWindowChanges changes;
  changes.width=_width-XGuiWindow::_dw;
  XConfigureWindow(getXGuiManager()->getDisplay(),_inWindow,CWWidth,&changes);
  }
}

void XGuiWindow::setHeight(int height) // virtual
{
_inHeightGiven=false;
_height=(height>=_minHeight ? height : _minHeight);
if(_inWindow)
  {
  XWindowChanges changes;
  changes.height=_height-XGuiWindow::_dh;
  XConfigureWindow(getXGuiManager()->getDisplay(),_inWindow,CWHeight,&changes);
  }
}

void XGuiWindow::setTitle(const Strings & title) // virtual
{
if(_inWindow) XStoreName(getXGuiManager()->getDisplay(),_inWindow,title);
XGuiElement::setTitle(title);
}

void XGuiWindow::setInWidth(int inWidth) // virtual
{
setWidth(inWidth+XGuiWindow::_dw);
_inWidthGiven=true;
}

void XGuiWindow::setInHeight(int inHeight) // virtual
{
setHeight(inHeight+XGuiWindow::_dh);
_inHeightGiven=true;
}

void XGuiWindow::setCloseCallback(void (*callback)(XGuiElement *,void *),
                                  void * data)
{
_closeCallback=callback;
_closeData=data;
}

void XGuiWindow::show(void) // virtual
{
if(!_window)
  {
  _inWindow=getXGuiManager()->getNewWindow(getXGuiManager()->getRoot(),
                                           _x+XGuiWindow::_dx,
                                           _y+XGuiWindow::_dy,
                                           _width-XGuiWindow::_dw,
                                           _height-XGuiWindow::_dh);
  _window=_inWindow; // same window before reparenting
  XSizeHints * hints=XAllocSizeHints();
  hints->flags=USPosition | PMinSize;
  hints->x=_x+XGuiWindow::_dx;
  hints->y=_y+XGuiWindow::_dy;
  hints->min_width=_minWidth;
  hints->min_height=_minHeight;
  XSetWMNormalHints(getXGuiManager()->getDisplay(),_inWindow,hints);
  XFree(hints);
  XStoreName(getXGuiManager()->getDisplay(),_inWindow,_title);
  XSelectInput(getXGuiManager()->getDisplay(),_inWindow,
               ExposureMask | StructureNotifyMask |
               OwnerGrabButtonMask | ButtonPressMask | ButtonReleaseMask);
  Atom protocols[1];
  protocols[0]=XInternAtom(getXGuiManager()->getDisplay(),
                           "WM_DELETE_WINDOW",false);
  XSetWMProtocols(getXGuiManager()->getDisplay(),_inWindow,protocols,1);
  XMapWindow(getXGuiManager()->getDisplay(),_inWindow);
  _computeDelta();
  }
XGuiElement::show();
}

void XGuiWindow::hide(void) // virtual
{
if(_window!=_inWindow)
  {
  _window=_inWindow;
  _inWindow=None;
  }
XGuiElement::hide();
}

void XGuiWindow::processEvent(const XEvent & event) // virtual
{
switch(event.type)
  {
  case ClientMessage:
    if(_closeCallback)
      {
      char * atomName=XGetAtomName(getXGuiManager()->getDisplay(),
                                   event.xclient.data.l[0]);
      if(Strings(atomName)==Strings("WM_DELETE_WINDOW"))
        (*_closeCallback)(this,_closeData);
      XFree(atomName);
      }
    break;
  case Expose:
    while(XCheckTypedWindowEvent(getXGuiManager()->getDisplay(),
                                 _inWindow,Expose,(XEvent *)&event)) { ; }
    redraw();
    break;
  case MapNotify:
    setMapped(true);
    break;
  case UnmapNotify:
    setMapped(false);
    break;
  case ConfigureNotify:
    if(event.xconfigure.window==_inWindow)
      {
      while(XCheckTypedWindowEvent(getXGuiManager()->getDisplay(),
                                   _inWindow,ConfigureNotify,
                                   (XEvent *)&event)) { ; }
      getXGuiManager()->getRootPosition(_inWindow,_x,_y);
      _x-=XGuiWindow::_dx;
      _y-=XGuiWindow::_dy;
      int inWidth=event.xconfigure.width;
      int inHeight=event.xconfigure.height;
      _width=inWidth+XGuiWindow::_dw;
      _height=inHeight+XGuiWindow::_dh;
      adjustMenu(inWidth,inHeight);
      redraw();
      if(_callback) (*_callback)(this,_data);
      }
    break;
  }
}

void XGuiWindow::redraw(void) // virtual
{
  // nothing to do
}

void XGuiWindow::_computeDelta(void)
{
Window root,parent;
Window *children;
unsigned int nbChildren;
XEvent event;

#if 0                    // Avant

while(!XCheckTypedWindowEvent(getXGuiManager()->getDisplay(),
                              _inWindow,ReparentNotify,&event));

#else                    // Apres modification VR
//return;  // ???
while(XCheckTypedWindowEvent(getXGuiManager()->getDisplay(),
                             _inWindow,ReparentNotify,&event)) { ; }
#endif

parent=_inWindow;
do
  {
  _window=parent;
  XQueryTree(getXGuiManager()->getDisplay(),
             _window,&root,&parent,&children,&nbChildren);
  if(children) XFree(children);
  } while(parent!=getXGuiManager()->getRoot());
if(!XGuiWindow::_deltaComputed)
  {
  XGuiWindow::_deltaComputed=true;
  int inX,inY;
  getXGuiManager()->getRootPosition(_inWindow,inX,inY);
  XWindowAttributes winAttr,inWinAttr;
  XGetWindowAttributes(getXGuiManager()->getDisplay(),_window,&winAttr);
  XGetWindowAttributes(getXGuiManager()->getDisplay(),_inWindow,&inWinAttr);

  XGuiWindow::_dx=inX-winAttr.x;
  XGuiWindow::_dy=inY-winAttr.y;
  XGuiWindow::_dw=winAttr.width-inWinAttr.width;
  XGuiWindow::_dh=winAttr.height-inWinAttr.height;

#if 1 && defined __CYGWIN__  // Ajout ... a cause d'un probleme pour CYGWIN ???
  if (XGuiWindow::_dx==0) XGuiWindow::_dx = 5;
  if (XGuiWindow::_dy==0) XGuiWindow::_dy = 24;
//if (XGuiWindow::_dw==0) XGuiWindow::_dw = 10;
//if (XGuiWindow::_dh==0) XGuiWindow::_dh = 29;
#endif

  setMinSize(_minWidth+XGuiWindow::_dw,_minHeight+XGuiWindow::_dh);

  if(_inWidthGiven) _width+=XGuiWindow::_dw;
  if(_inHeightGiven) _height+=XGuiWindow::_dh;
  }
setX(_x);
setY(_y);
setWidth(_width);
setHeight(_height);
}

#endif // X_GUI

