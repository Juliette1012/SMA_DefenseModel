#ifdef X_GUI

#include "XGui/xgList.h"
#include "XGui/xgScroll.h"
#include "XGui/xgArea.h"
#include "XGui/xgMgr.h"

//--------------------------------------------------------------------------//
// class XGuiList                                                           //
//--------------------------------------------------------------------------//

//-------- Allocators ------------------------------------------------------//
XGuiList::XGuiList(XGuiArea * parent,const StringsVect & entries)
 : XGuiElement(8*getXGuiManager()->getMargin(),
               4*getXGuiManager()->getMargin()),
   _entries(), _result(-1), _lastTime(0), _isEntered(false),
   _textPixmap(None), _textX(0), _textY(0), _textWidth(0), _textHeight(0),
   _totalHeight(0), _offset(0), _scroll((XGuiScroller *)0), _pixmap(None)
{
parent->addElement(this);
_scroll=new XGuiScroller(this,false);
_scroll->setCallback(XGuiList::_scrollCB);
setEntries(entries);
int maxWidth=0;
for(int i=_entries.size();i--;)
  {
  int width=getXGuiManager()->getTextWidth(_entries[i]);
  if(width>maxWidth) maxWidth=width;
  }
setWidth(3*getXGuiManager()->getMargin()+maxWidth+_scroll->getWidth());
setHeight(2*getXGuiManager()->getMargin()+_totalHeight);
}

XGuiList::~XGuiList(void)
{
  // _scroll is auto-deleted
if(_textPixmap) XFreePixmap(getXGuiManager()->getDisplay(),_textPixmap);
if(_pixmap) XFreePixmap(getXGuiManager()->getDisplay(),_pixmap);
}

//-------- Inspectors ------------------------------------------------------//
XGuiElement::Type XGuiList::getElemType(void) const // virtual
{
return(XGuiElement::LIST);
}

bool XGuiList::isA(XGuiElement::Type type) const // virtual
{
return(type==XGuiElement::LIST);
}

int XGuiList::getResult(void) const
{
return(_result);
}

int XGuiList::getNbEntries(void) const
{
return(_entries.size());
}

const Strings & XGuiList::getEntry(int pos) const
{
return(_entries[pos]);
}

bool XGuiList::isEntered(void) const
{
return(_isEntered);
}

//-------- Modifiers -------------------------------------------------------//
void XGuiList::setEntries(const StringsVect & entries)
{
_result=-1;
_entries=entries;
_totalHeight=_entries.size()*getXGuiManager()->getCharHeight();
_scroll->setValue(0);
_scroll->setRatio(((double)_textHeight)/_totalHeight);
_buildPixmap();
redraw();
}

void XGuiList::setWidth(int width) // virtual
{
XGuiElement::setWidth(width);
int scrollWidth=_scroll->getWidth()+getXGuiManager()->getMargin();
_textX=getXGuiManager()->getMargin();
_textWidth=_width-scrollWidth-2*_textX;
_scroll->setX(_width-scrollWidth);
_buildPixmap();
redraw();
}

void XGuiList::setHeight(int height) // virtual
{
XGuiElement::setHeight(height);
_textY=getXGuiManager()->getMargin();
_textHeight=_height-2*_textY;
_scroll->setY(getXGuiManager()->getMargin());
_scroll->setHeight(_height-2*getXGuiManager()->getMargin());
_scroll->setRatio(((double)_textHeight)/_totalHeight);
_buildPixmap();
redraw();
}

void XGuiList::show(void) // virtual
{
if(!_window)
  {
  _window=getXGuiManager()->getNewWindow(((XGuiArea *)_parent)->getInWindow(),
                                         _x,_y,_width,_height);
  XSelectInput(getXGuiManager()->getDisplay(),_window,
               ExposureMask | KeyPressMask |
               ButtonPressMask | ButtonReleaseMask);
  _buildPixmap();
  XMapWindow(getXGuiManager()->getDisplay(),_window);
  }
XGuiElement::show();
}

void XGuiList::hide(void) // virtual
{
if(_textPixmap)
  {
  XFreePixmap(getXGuiManager()->getDisplay(),_textPixmap);
  _textPixmap=None;
  }
if(_pixmap)
  {
  XFreePixmap(getXGuiManager()->getDisplay(),_pixmap);
  _pixmap=None;
  }
XGuiElement::hide();
}

void XGuiList::processEvent(const XEvent & event) // virtual
{
switch(event.type)
  {
  case Expose:
    while(XCheckTypedWindowEvent(getXGuiManager()->getDisplay(),
                                 _window,Expose,(XEvent *)&event));
    redraw();
    break;
  case ButtonPress:
    switch(event.xbutton.button)
      {
      case Button1:
        if((event.xbutton.x>=_textX)&&(event.xbutton.x<=_textX+_textWidth)&&
           (event.xbutton.y>=_textY)&&(event.xbutton.y<=_textY+_textHeight))
          {
          int old=_result;
          long delta=event.xbutton.time-_lastTime;
          _lastTime=event.xbutton.time;
          _isEntered=((delta>0)&&(delta<getXGuiManager()->getClickTime()) ?
                     true : false);
          _result=(event.xbutton.y-_textY-_offset)/
                  getXGuiManager()->getCharHeight();
          if(_result>=(int)_entries.size())
            {
            _isEntered=false;
            _result=-1;
            _buildPixmap();
            redraw();
            }
          else
            {
            if(old!=_result) _isEntered=false;
            getXGuiManager()->setSelectionOwner(_window,_entries[_result]);
            _buildPixmap();
            redraw();
            if(_callback) (*_callback)(this,_data);
            }
          }
        break;
      case Button4: // wheel up
        _keyUp();
        break;
      case Button5: // wheel down
        _keyDown();
        break;
      }
    break;
  case ButtonRelease:
    if(event.xbutton.button==Button1)
      {
      _lastTime=event.xbutton.time;
      }
    break;
  case KeyPress:
    {
    static char buffer[0x10];
    KeySym keysym;
    XLookupString((XKeyEvent *)&event.xkey,
                  buffer,0x10,&keysym,(XComposeStatus*)0);
    switch(keysym)
      {
      case XK_Escape:
        if(_result>=0)
          {
          _result=-1;
          _buildPixmap();
          redraw();
          }
        break;
      case XK_Return:
      case XK_KP_Enter:
        if(_result>=0)
          {
          _isEntered=true;
          if(_callback) (*_callback)(this,_data);
          }
        break;
      case XK_Up:
      case XK_KP_Up:
        _keyUp();
        break;
      case XK_Down:
      case XK_KP_Down:
        _keyDown();
        break;
      case XK_Page_Up:
      case XK_KP_Page_Up:
        if(_result<0)
          _scroll->setValue(_scroll->getValue()-_scroll->getRatio()/2.0);
        else
          {
          if(_result>0)
            {
            int d=(_textHeight/getXGuiManager()->getCharHeight())/2;
            if(d) _result-=d;
            else _result--;
            if(_result<0) _result=0;
            getXGuiManager()->setSelectionOwner(_window,_entries[_result]);
            _buildPixmap();
            if(!_showResult()) redraw();
            _isEntered=false;
            if(_callback) (*_callback)(this,_data);
            }
          else _scroll->setValue(0.0);
          }
        break;
      case XK_Page_Down:
      case XK_KP_Page_Down:
        if(_result<0)
          _scroll->setValue(_scroll->getValue()+_scroll->getRatio()/2.0);
        else
          {
          if(_result<(int)_entries.size()-1)
            {
            int d=(_textHeight/getXGuiManager()->getCharHeight())/2;
            if(d) _result+=d;
            else _result++;
            if(_result>=(int)_entries.size()) _result=_entries.size()-1;
            getXGuiManager()->setSelectionOwner(_window,_entries[_result]);
            _buildPixmap();
            if(!_showResult()) redraw();
            _isEntered=false;
            if(_callback) (*_callback)(this,_data);
            }
          else _scroll->setValue(1.0-_scroll->getRatio());
          }
        break;
      case XK_Home:
      case XK_KP_Home:
        if(_result>0)
          {
          _result=0;
          getXGuiManager()->setSelectionOwner(_window,_entries[_result]);
          _buildPixmap();
          if(!_showResult()) redraw();
          _isEntered=false;
          if(_callback) (*_callback)(this,_data);
          }
        else _scroll->setValue(0.0);
        break;
      case XK_End:
      case XK_KP_End:
        if((_result>=0)&&(_result<(int)_entries.size()-1))
          {
          _result=_entries.size()-1;
          getXGuiManager()->setSelectionOwner(_window,_entries[_result]);
          _buildPixmap();
          if(!_showResult()) redraw();
          _isEntered=false;
          if(_callback) (*_callback)(this,_data);
          }
        else _scroll->setValue(1.0-_scroll->getRatio());
        break;
      }
    } 
    break;
  }
}

void XGuiList::redraw(void) // virtual
{
if(_window)
  {
  getXGuiManager()->background(_pixmap,0,0,_width,_height);
  getXGuiManager()->drawBorderLineUp(_pixmap,0,0,_width,_height);
  if(_textPixmap)
    {
    XCopyArea(getXGuiManager()->getDisplay(),_textPixmap,_pixmap,
              getXGuiManager()->getGC(),0,-_offset,_textWidth,_textHeight,
              _textX,_textY);
    }
  XCopyArea(getXGuiManager()->getDisplay(),_pixmap,_window,
            getXGuiManager()->getGC(),0,0,_width,_height,0,0);
  }
}

void XGuiList::_buildPixmap(void)
{
if(_window)
  {
  if(_pixmap) XFreePixmap(getXGuiManager()->getDisplay(),_pixmap);
  _pixmap=getXGuiManager()->getNewPixmap(_window,_width,_height);
  if(_textPixmap) XFreePixmap(getXGuiManager()->getDisplay(),_textPixmap);
  if(_entries.size())
    {
    int height=(_textHeight<_totalHeight ? _totalHeight : _textHeight);
    _textPixmap=getXGuiManager()->getNewPixmap(_window,_textWidth,height);
    getXGuiManager()->background(_textPixmap,0,0,_textWidth,height);
    for(int i=_entries.size();i--;)
      {
      if(i==_result)
        {
        getXGuiManager()->drawSelection(_textPixmap,0,
                                        i*getXGuiManager()->getCharHeight(),
                                        _entries[i],0,_entries[i].len());
        }
      else
        {
        getXGuiManager()->drawText(_textPixmap,0,
                                   i*getXGuiManager()->getCharHeight(),
                                   _entries[i]);
        }
      }
    }
  else _textPixmap=None;
  }
}

bool XGuiList::_showResult(void)
{
int y=_result*getXGuiManager()->getCharHeight();
if(y+_offset<0)
  {
  _scroll->setValue((double)y/_totalHeight);
  return(true);
  }
else if(y+_offset>_textHeight-getXGuiManager()->getCharHeight())
  {
  y-=_textHeight-getXGuiManager()->getCharHeight();
  _scroll->setValue((double)y/_totalHeight);
  return(true);
  }
else return(false);
}

void XGuiList::_keyUp(void)
{
if(_totalHeight)
  {
  if(_result<0)
    {
    _scroll->setValue(_scroll->getValue()-
           (double)(getXGuiManager()->getCharHeight())/_totalHeight);
    }
  else
    {
    if(_result>0)
      {
      _result--;
      getXGuiManager()->setSelectionOwner(_window,_entries[_result]);
      _buildPixmap();
      if(!_showResult()) redraw();
      _isEntered=false;
      if(_callback) (*_callback)(this,_data);
      }
    else _scroll->setValue(0.0);
    }
  }
}

void XGuiList::_keyDown(void)
{
if(_totalHeight)
  {
  if(_result<0)
    {
    _scroll->setValue(_scroll->getValue()+
           (double)(getXGuiManager()->getCharHeight())/_totalHeight);
    }
  else
    {
    if(_result<(int)_entries.size()-1)
      {
      _result++;
      getXGuiManager()->setSelectionOwner(_window,_entries[_result]);
      _buildPixmap();
      if(!_showResult()) redraw();
      _isEntered=false;
      if(_callback) (*_callback)(this,_data);
      }
    else _scroll->setValue(1.0-_scroll->getRatio());
    }
  }
}

//-------- Callbacks -------------------------------------------------------//

void XGuiList::_scrollCB(XGuiElement * calling,void *) // static
{
XGuiList * selection=(XGuiList *)calling->accessParent();
double value=((XGuiScroller *)calling)->getValue();
selection->_offset=(int)(-value*selection->_totalHeight);
selection->redraw();
}

#endif // X_GUI

