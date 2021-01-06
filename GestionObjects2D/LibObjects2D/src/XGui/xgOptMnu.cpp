#ifdef X_GUI

#include "XGui/xgOptMnu.h"
#include "XGui/xgMenu.h"
#include "XGui/xgMnuItm.h"
#include "XGui/xgArea.h"
#include "XGui/xgMgr.h"

//--------------------------------------------------------------------------//
// class XGuiOptionMenu                                                     //
//--------------------------------------------------------------------------//

//-------- Allocators ------------------------------------------------------//
XGuiOptionMenu::XGuiOptionMenu(XGuiArea * parent,const StringsVect & entries)
 : XGuiElement(2*getXGuiManager()->getMargin(),
               2*getXGuiManager()->getMargin()),
   _entries(entries), _result(0),
   _textX(0), _textY(0), _textWidth(0), _textHeight(0),
   _inside(false), _menu((XGuiMenu *)0)
{
_menu=new XGuiMenu(this,false);
XGuiMenuItem * item=(XGuiMenuItem *)0;
for(unsigned int i=0;i<_entries.size();i++)
  {
  item=new XGuiMenuItem(_menu,_entries[i]);
  item->setCallback(XGuiOptionMenu::_itemCB,this);
  }
if(_entries.size()) setTitle(_entries.front());
else
  {
  _result=-1;
  setTitle("");
  }
setWidth(_menu->getWidth()+getXGuiManager()->getMargin()+
         getXGuiManager()->getCharHeight());
setHeight(2*getXGuiManager()->getMargin()+_textHeight);
parent->addElement(this);
}

XGuiOptionMenu::~XGuiOptionMenu(void)
{
if(_menu) delete _menu;
}

//-------- Inspectors ------------------------------------------------------//
XGuiElement::Type XGuiOptionMenu::getElemType(void) const // virtual
{
return(XGuiElement::OPTION_MENU);
}

bool XGuiOptionMenu::isA(XGuiElement::Type type) const // virtual
{
return(type==XGuiElement::OPTION_MENU);
}

int XGuiOptionMenu::getResult(void) const
{
return(_result);
}

int XGuiOptionMenu::getNbEntries(void) const
{
return(_entries.size());
}

const Strings & XGuiOptionMenu::getEntry(int pos) const
{
return(_entries[pos]);
}

//-------- Modifiers -------------------------------------------------------//
void XGuiOptionMenu::setActiveEntry(int pos,bool propagate)
{
if(_result!=pos)
  {
  _result=pos;
  setTitle(_entries[pos]);
  if(_callback&&propagate) (*_callback)(this,_data);
  }
}

void XGuiOptionMenu::addElement(XGuiElement * element) // virtual
{
if(_menu) delete _menu;
_menu=(XGuiMenu *)element;
element->setParent(this);
}

void XGuiOptionMenu::removeElement(XGuiElement * element) // virtual
{
if(_menu==element) _menu=(XGuiMenu *)0;
XGuiElement::removeElement(element);
}

void XGuiOptionMenu::usingMenu(XGuiMenu * menu) // virtual
{
if(menu!=_menu)
  {
  _menu->hide();
  redraw();
  }
}

void XGuiOptionMenu::setWidth(int width) // virtual
{
XGuiElement::setWidth(width);
_textX=(_width-_textWidth-
        getXGuiManager()->getCharHeight()-
        getXGuiManager()->getMargin())/2;
redraw();
}

void XGuiOptionMenu::setHeight(int height) // virtual
{
XGuiElement::setHeight(height);
_textY=(_height-_textHeight)/2;
redraw();
}

void XGuiOptionMenu::setTitle(const Strings & title) // virtual
{
_textWidth=getXGuiManager()->getTextWidth(title);
_textX=(_width-_textWidth-
        getXGuiManager()->getCharHeight()-
        getXGuiManager()->getMargin())/2;
_textHeight=getXGuiManager()->getCharHeight();
_textY=(_height-_textHeight)/2;
XGuiElement::setTitle(title);
}

void XGuiOptionMenu::show(void) // virtual
{
if(!_window)
  {
  _window=getXGuiManager()->getNewWindow(((XGuiArea *)_parent)->getInWindow(),
                                         _x,_y,_width,_height);
  XSelectInput(getXGuiManager()->getDisplay(),_window,
               ExposureMask | OwnerGrabButtonMask |
               ButtonPressMask | ButtonReleaseMask |
               EnterWindowMask | LeaveWindowMask);
  XMapWindow(getXGuiManager()->getDisplay(),_window);
  }
XGuiElement::show();
}

void XGuiOptionMenu::hide(void) // virtual
{
if(_menu) _menu->hide();
XGuiElement::hide();
_inside=false;
}

bool XGuiOptionMenu::dispatchEvent(const XEvent & event) // virtual
{
if(XGuiElement::dispatchEvent(event)) return(true);
if(_menu) return(_menu->dispatchEvent(event));
return(false);
}

void XGuiOptionMenu::processEvent(const XEvent & event) // virtual
{
switch(event.type)
  {
  case Expose:
    while(XCheckTypedWindowEvent(getXGuiManager()->getDisplay(),
                                 _window,Expose,(XEvent *)&event)) { ; }
    redraw();
    break;
  case ButtonPress:
    if(event.xbutton.button==Button1)
      {
      getXGuiManager()->usingMenu(_menu);
      _menu->show();
      redraw();
      }
    break;
  case ButtonRelease:
    if(event.xbutton.button==Button1)
      {
      getXGuiManager()->usingMenu((XGuiMenu *)0);
      }
    break;
  case EnterNotify:
    _inside=true;
    if(event.xcrossing.state&Button1Mask)
      {
      getXGuiManager()->usingMenu(_menu);
      _menu->show();
      }
    redraw();
    break;
  case LeaveNotify:
    _inside=false;
    redraw();
    break;
  }
}

void XGuiOptionMenu::redraw(void) // virtual
{
if(_window)
  {
  if(_inside)
    getXGuiManager()->highlight(_window,0,0,_width,_height);
  else
    getXGuiManager()->background(_window,0,0,_width,_height);
  getXGuiManager()->drawBorderUp(_window,0,0,_width,_height);
  getXGuiManager()->drawBorderUp(_window,
                    _width-getXGuiManager()->getCharHeight()-
                           getXGuiManager()->getMargin(),
                    _height/2-getXGuiManager()->getMargin(),
                    getXGuiManager()->getCharHeight(),
                    2*getXGuiManager()->getMargin());
  getXGuiManager()->drawText(_window,_textX,_textY,_title);
  }
}

//-------- Callbacks -------------------------------------------------------//

void XGuiOptionMenu::_itemCB(XGuiElement * calling,void * data) // static
{
XGuiOptionMenu * option=(XGuiOptionMenu *)data;
for(int i=option->_entries.size();i--;)
  {
  if(option->_entries[i]==calling->getTitle())
    {
    option->setActiveEntry(i,true);
    break;
    }
  }
}

#endif // X_GUI

