#ifdef X_GUI

#include "XGui/xgTabGrp.h"
#include "XGui/xgArea.h"
#include "XGui/xgMgr.h"

//--------------------------------------------------------------------------//
// class XGuiTabGroup                                                       //
//--------------------------------------------------------------------------//

//-------- Allocators ------------------------------------------------------//
XGuiTabGroup::XGuiTabGroup(XGuiArea * parent)
 : XGuiElement(4*getXGuiManager()->getMargin(),
               6*getXGuiManager()->getMargin()+
               getXGuiManager()->getCharHeight()),
   _xOffset(getXGuiManager()->getMargin()),
   _yOffset(getXGuiManager()->getCharHeight()+
            3*getXGuiManager()->getMargin()),
   _tabs(), _current(-1), _inside(-1)
{
parent->addElement(this);
}

XGuiTabGroup::~XGuiTabGroup(void)
{
_destroyHeader();
}

//-------- Inspectors ------------------------------------------------------//
XGuiElement::Type XGuiTabGroup::getElemType(void) const // virtual
{
return(XGuiElement::TAB_GROUP);
}

bool XGuiTabGroup::isA(XGuiElement::Type type) const // virtual
{
return(type==XGuiElement::TAB_GROUP);
}

int XGuiTabGroup::getCurrentTab(void) const
{
return(_current);
}

int XGuiTabGroup::getNbTabs(void) const
{
return(_elems.getSize());
}

const Strings & XGuiTabGroup::getTab(int pos) const
{
return(_elems[pos]->getTitle());
}

//-------- Modifiers -------------------------------------------------------//
void XGuiTabGroup::setCurrentTab(int pos,bool propagate)
{
if(pos!=_current)
  {
  _current=pos;
  _buildHeader();
  if(_callback&&propagate) (*_callback)(this,_data);
  }
}

void XGuiTabGroup::setWidth(int width) // virtual
{
if(_width!=width)
  {
  XGuiElement::setWidth(width);
  for(int i=_elems.getSize();i--;)
    _elems[i]->setWidth(_width);
  redraw();
  }
}

void XGuiTabGroup::setHeight(int height) // virtual
{
if(_height!=height)
  {
  XGuiElement::setHeight(height);
  for(int i=_elems.getSize();i--;)
    _elems[i]->setHeight(_height);
  redraw();
  }
}

void XGuiTabGroup::addElement(XGuiElement * element) // virtual
{
XGuiElement::addElement(element);
_buildHeader();
}

void XGuiTabGroup::removeElement(XGuiElement * element) // virtual
{
XGuiElement::removeElement(element);
_buildHeader();
}

void XGuiTabGroup::show(void) // virtual
{
if(!_window)
  {
  _window=getXGuiManager()->getNewWindow(((XGuiArea *)_parent)->getInWindow(),
                                         _x,_y,_width,_height);
  XSelectInput(getXGuiManager()->getDisplay(),_window,ExposureMask);
  XMapWindow(getXGuiManager()->getDisplay(),_window);
  _buildHeader();
  }
}

void XGuiTabGroup::hide(void) // virtual
{
if(_window) _destroyHeader();
XGuiElement::hide();
}

bool XGuiTabGroup::dispatchEvent(const XEvent & event) // virtual
{
bool found=(event.xany.window==_window);
for(int i=_tabs.getSize();!found&&i--;)
  {
  if(_tabs[i]->window==event.xany.window) found=true;
  }
if(found)
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

void XGuiTabGroup::processEvent(const XEvent & event) // virtual
{
switch(event.type)
  {
  case Expose:
    {
    while(XCheckTypedWindowEvent(getXGuiManager()->getDisplay(),
                                 _window,Expose,(XEvent *)&event));
    for(int i=_tabs.getSize();i--;)
      {
      while(XCheckTypedWindowEvent(getXGuiManager()->getDisplay(),
                                   _tabs[i]->window,Expose,(XEvent *)&event));
      }
    redraw();
    }
    break;
  case ButtonPress:
    {
    for(int i=_tabs.getSize();i--;)
      {
      if(event.xbutton.window==_tabs[i]->window)
        {
        setCurrentTab(i);
        break;
        }
      }
    }
    break;
  case EnterNotify:
    {
    for(int i=_tabs.getSize();i--;)
      {
      if(event.xcrossing.window==_tabs[i]->window)
        {
        if(_inside!=i)
          {
          _inside=i;
          redraw();
          }
        break;
        }
      }
    }
    break;
  case LeaveNotify:
    {
    for(int i=_tabs.getSize();i--;)
      {
      if(event.xcrossing.window==_tabs[i]->window)
        {
        if(_inside==i)
          {
          _inside=-1;
          redraw();
          }
        break;
        }
      }
    }
    break;
  }
}
  
void XGuiTabGroup::redraw(void) // virtual
{
if(_window)
  {
  TabInfo * tab;
  for(int i=_tabs.getSize();i--;)
    {
    tab=_tabs[i];
    if(i==_inside)
      getXGuiManager()->highlight(tab->window,0,0,tab->width,_yOffset);
    else
      getXGuiManager()->background(tab->window,0,0,tab->width,_yOffset);
    getXGuiManager()->drawBorderUp(tab->window,0,0,tab->width,_yOffset);
    getXGuiManager()->drawText(tab->window,
                               getXGuiManager()->getMargin(),
                               getXGuiManager()->getMargin(),
                               _elems[i]->getTitle());
    }
  int y=_yOffset-getXGuiManager()->getMargin();
  getXGuiManager()->background(_window,0,y,_width,_height-y);
  getXGuiManager()->drawBorderUp(_window,0,y,_width,_height-y);
  }
}

void XGuiTabGroup::_buildHeader(void)
{
if(_elems.getSize())
  {
  if(_current<0) _current=0;
  else if(_current>=(int)_elems.getSize())
    _current=_elems.getSize()-1;
  }
else _current=-1;
if(_window)
  {
  _destroyHeader();
  TabInfo * tab;
  int x=0;
  for(int i=0;i<(int)_elems.getSize();i++)
    {
    tab=new TabInfo;
    tab->width=getXGuiManager()->getTextWidth(_elems[i]->getTitle())+
               2*getXGuiManager()->getMargin();
    if(i==_current)
      {
      tab->window=getXGuiManager()->getNewWindow(_window,x,0,tab->width,
                                                 _yOffset-2);
      _elems[i]->show();
      }
    else
      {
      tab->window=getXGuiManager()->getNewWindow(_window,
                                    x,getXGuiManager()->getMargin(),
                                    tab->width,
                                    _yOffset-2*getXGuiManager()->getMargin());
      _elems[i]->hide();
      }
    XSelectInput(getXGuiManager()->getDisplay(),tab->window,
                 ExposureMask | EnterWindowMask |
                 LeaveWindowMask | ButtonPressMask);
    XMapWindow(getXGuiManager()->getDisplay(),tab->window);
    x+=tab->width;
    _tabs.pushBack(tab);
    }
  }
redraw();
}

void XGuiTabGroup::_destroyHeader(void)
{
TabInfo * tab;
while(_tabs.getSize())
  {
  tab=_tabs.readPopBack();
  XDestroyWindow(getXGuiManager()->getDisplay(),tab->window);
  delete tab;
  }
}

#endif // X_GUI

