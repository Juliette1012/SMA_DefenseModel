#ifdef X_GUI

#include "XGui/xgMgr.h"

//--------------------------------------------------------------------------//
// class XGuiElement                                                        //
//--------------------------------------------------------------------------//

//-------- Allocators ------------------------------------------------------//
XGuiElement::XGuiElement(int minWidth,int minHeight)
 : _parent((XGuiElement *)0), _elems(),
   _callback((void (*)(XGuiElement *,void *))0),
   _data((void *)0),
   _destroyCallback((void (*)(XGuiElement *,void *))0),
   _destroyData((void *)0),
   _x(0), _y(0), _width(minWidth), _height(minHeight),
   _minWidth(minWidth), _minHeight(minHeight),
   _title(), _window(None), _mapped(false)
{
setTitle("No Title !");
}

XGuiElement::~XGuiElement(void)
{
while(_elems.getSize()) delete _elems.accessBack();
if(_parent) _parent->removeElement(this);
if(_window)
  {
  XDestroyWindow(getXGuiManager()->getDisplay(),_window);
  _window=None;
  }
if(_destroyCallback) (*_destroyCallback)(this,_destroyData);
}

//-------- Inspectors ------------------------------------------------------//
// XGuiElement::Type XGuiButton::getElemType(void) const // virtual=0

// bool XGuiElement::isA(XGuiElement::Type type) const // virtual=0

// inline int XGuiElement::getX(void) const // virtual

// inline int XGuiElement::getY(void) const // virtual

// inline int XGuiElement::getWidth(void) const // virtual

// inline int XGuiElement::getHeight(void) const // virtual

// inline const Strings & XGuiElement::getTitle(void) const

// inline const XGuiElement * XGuiElement::getParent(void) const

// inline Window XGuiElement::getWindow(void) const

// inline bool XGuiElement::isVisible(void) const

// inline bool XGuiElement::isMapped(void) const

//-------- Modifiers -------------------------------------------------------//
void XGuiElement::setMinSize(int minWidth,int minHeight) // virtual
{
_minWidth=minWidth;
if(_width<_minWidth) setWidth(_minWidth);
_minHeight=minHeight;
if(_height<_minHeight) setHeight(_minHeight);
}

void XGuiElement::setX(int x) // virtual
{
_x=x;
if(_window)
  {
  XWindowChanges changes;
  changes.x=_x;
  XConfigureWindow(getXGuiManager()->getDisplay(),_window,CWX,&changes);
  }
}

void XGuiElement::setY(int y) // virtual
{
_y=y;
if(_window)
  {
  XWindowChanges changes;
  changes.y=_y;
  XConfigureWindow(getXGuiManager()->getDisplay(),_window,CWY,&changes);
  }
}

void XGuiElement::setWidth(int width) // virtual
{
_width=(width>=_minWidth ? width : _minWidth);
if(_window)
  {
  XWindowChanges changes;
  changes.width=_width;
  XConfigureWindow(getXGuiManager()->getDisplay(),_window,CWWidth,&changes);
  }
}

void XGuiElement::setHeight(int height) // virtual
{
_height=(height>=_minHeight ? height : _minHeight);
if(_window)
  {
  XWindowChanges changes;
  changes.height=_height;
  XConfigureWindow(getXGuiManager()->getDisplay(),_window,CWHeight,&changes);
  }
}

void XGuiElement::setTitle(const Strings & title) // virtual
{
_title=title;
if(_window) redraw();
}

// inline void XGuiElement::setParent(XGuiElement * parent)

// inline XGuiElement * XGuiElement::accessParent(void)

void XGuiElement::setMapped(bool mapped)
{
_mapped=mapped;
for(int i=_elems.getSize();i--;)
  _elems[i]->setMapped(mapped);
}

// inline void XGuiElement::setCallback(void (*callback)(XGuiElement *,
//                                                       void *),
//                                      void * data)

// inline void XGuiElement::setDestroyCallback(void (*callback)(XGuiElement *,
//                                                              void *),
//                                             void * data)

void XGuiElement::addElement(XGuiElement * element) // virtual
{
_elems.pushBack(element);
element->_parent=this;
}

void XGuiElement::removeElement(XGuiElement * element) // virtual
{
for(int i=_elems.getSize();i--;)
  if(_elems[i]==element)
    _elems.erase(i);
if(element->_parent==this) element->_parent=(XGuiElement *)0;
}

bool XGuiElement::dispatchEvent(const XEvent & event) // virtual
{
if(event.xany.window==_window)
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

// void XGuiElement::processEvent(const XEvent & event) // virtual=0

void XGuiElement::show(void) // virtual
{
_mapped=true;
for(int i=_elems.getSize();i--;)
  _elems[i]->show();
}

void XGuiElement::hide(void) // virtual
{
for(int i=_elems.getSize();i--;)
  _elems[i]->hide();
if(_window)
  {
  XDestroyWindow(getXGuiManager()->getDisplay(),_window);
  _window=None;
  }
}

void XGuiElement::usingMenu(XGuiMenu * menu) // virtual
{
for(int i=_elems.getSize();i--;)
  _elems[i]->usingMenu(menu);
}

void XGuiElement::usingSelection(Window owner) // virtual
{
for(int i=_elems.getSize();i--;)
  _elems[i]->usingSelection(owner);
}

// void XGuiElement::redraw(void) // virtual=0

bool XGuiElement::dump(const Strings & fileName)
{
bool fail=false;
if(_window&&_mapped)
  {
  unsigned char * red;
  unsigned char * green;
  unsigned char * blue;
  unsigned long * points;
  int width,height,nbColors;
  if(getXGuiManager()->dumpWindow(getWindow(),red,green,blue,nbColors,
                                              points,width,height))
    {
    FILE * file=::fopen(fileName,"wb");
    if(file)
      {
      Strings ext(fileName.extension());
      ext.toLower();
      if(ext==Strings(".bmp"))
        {
        if(!getXGuiManager()->writeBMP(file,red,green,blue,nbColors,
                                            points,width,height))
        fail=true;
        }
      else if(ext==Strings(".ras"))
        {
        if(!getXGuiManager()->writeRAS(file,red,green,blue,nbColors,
                                            points,width,height))
        fail=true;
        }
      ::fclose(file);
      }
    else fail=true;
    if(red) free(red);
    if(green) free(green);
    if(blue) free(blue);
    if(points) free(points);
    }
  else fail=true;
  }
else fail=true;
return(!fail);
}

#endif // X_GUI

