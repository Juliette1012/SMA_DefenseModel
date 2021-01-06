#ifdef X_GUI

#include "XGui/xgLabel.h"
#include "XGui/xgArea.h"
#include "XGui/xgMgr.h"

//--------------------------------------------------------------------------//
// class XGuiLabel                                                          //
//--------------------------------------------------------------------------//

//-------- Allocators ------------------------------------------------------//
XGuiLabel::XGuiLabel(XGuiArea * parent,const Strings & title,
                     bool editable,bool deep)
 : XGuiElement(4*getXGuiManager()->getMargin(),
               2*getXGuiManager()->getMargin()),
   _textWindow(None), _deep(deep), _editable(editable),
   _textX(0), _textY(0), _textWidth(0), _textHeight(0),
   _selectMouse(false), _selectKey(false), _startSel(0), _endSel(0),
   _inside(false), _pos(0), _offset(0), _textPixmap(None), _pixmap(None)
{
setTitle(title);
setWidth(2*getXGuiManager()->getMargin()+
         getXGuiManager()->getTextWidth(_title));
setHeight(2*getXGuiManager()->getMargin()+
          getXGuiManager()->getCharHeight());
parent->addElement(this);
}

XGuiLabel::~XGuiLabel(void)
{
if(_textWindow) XDestroyWindow(getXGuiManager()->getDisplay(),_textWindow);
if(_textPixmap) XFreePixmap(getXGuiManager()->getDisplay(),_textPixmap);
if(_pixmap) XFreePixmap(getXGuiManager()->getDisplay(),_pixmap);
}

//-------- Inspectors ------------------------------------------------------//
XGuiElement::Type XGuiLabel::getElemType(void) const // virtual
{
return(XGuiElement::LABEL);
}

bool XGuiLabel::isA(XGuiElement::Type type) const // virtual
{
return(type==XGuiElement::LABEL);
}

//-------- Modifiers -------------------------------------------------------//
void XGuiLabel::setWidth(int width) // virtual
{
XGuiElement::setWidth(width);
_textX=getXGuiManager()->getMargin();
_textWidth=_width-2*_textX;
if(_textWindow)
  {
  XWindowChanges changes;
  changes.width=_textWidth;
  XConfigureWindow(getXGuiManager()->getDisplay(),_textWindow,
                   CWWidth,&changes);
  XFreePixmap(getXGuiManager()->getDisplay(),_textPixmap);
  _textPixmap=getXGuiManager()->getNewPixmap(_textWindow,
                                             _textWidth,_textHeight);
  XFreePixmap(getXGuiManager()->getDisplay(),_pixmap);
  _pixmap=getXGuiManager()->getNewPixmap(_window,_width,_height);
  }
redraw();
}

void XGuiLabel::setHeight(int height) // virtual
{
XGuiElement::setHeight(height);
_textHeight=getXGuiManager()->getCharHeight();
_textY=(_height-_textHeight)/2;
if(_textWindow)
  {
  XWindowChanges changes;
  changes.y=_textY;
  XConfigureWindow(getXGuiManager()->getDisplay(),_textWindow,
                   CWY,&changes);
  XFreePixmap(getXGuiManager()->getDisplay(),_pixmap);
  _pixmap=getXGuiManager()->getNewPixmap(_window,_width,_height);
  }
redraw();
}

void XGuiLabel::setTitle(const Strings & title) // virtual
{
_pos=0;
_endSel=_startSel=0;
_selectMouse=_selectKey=false;
XGuiElement::setTitle(title);
}

void XGuiLabel::show(void) // virtual
{
if(!_window)
  {
  _window=getXGuiManager()->getNewWindow(((XGuiArea *)_parent)->getInWindow(),
                                         _x,_y,_width,_height);
  _textWindow=getXGuiManager()->getNewWindow(_window,
                                             _textX,_textY,
                                             _textWidth,_textHeight);
  long eventMask=ExposureMask | PropertyChangeMask |
                 ButtonPressMask | ButtonReleaseMask | Button1MotionMask;
  if(_editable)
    {
    eventMask|=EnterWindowMask | LeaveWindowMask | KeyPressMask;
    }
  XSelectInput(getXGuiManager()->getDisplay(),_window,eventMask);
  XSelectInput(getXGuiManager()->getDisplay(),_textWindow,eventMask);
  _pixmap=getXGuiManager()->getNewPixmap(_window,_width,_height);
  _textPixmap=getXGuiManager()->getNewPixmap(_textWindow,
                                             _textWidth,_textHeight);
  XMapWindow(getXGuiManager()->getDisplay(),_window);
  XMapWindow(getXGuiManager()->getDisplay(),_textWindow);
  }
XGuiElement::show();
}

void XGuiLabel::hide(void) // virtual
{
if(_textPixmap)
  {
  XFreePixmap(getXGuiManager()->getDisplay(),_textPixmap);
  _textPixmap=None;
  }
if(_textWindow)
  {
  XDestroyWindow(getXGuiManager()->getDisplay(),_textWindow);
  _textWindow=None;
  }
if(_pixmap)
  {
  XFreePixmap(getXGuiManager()->getDisplay(),_pixmap);
  _pixmap=None;
  }
XGuiElement::hide();
}

void XGuiLabel::usingSelection(Window owner) // virtual
{
if(owner!=_textWindow)
  {
  _selectMouse=_selectKey=false;
  _endSel=_startSel=0;
  redraw();
  }
}

bool XGuiLabel::dispatchEvent(const XEvent & event) // virtual
{
if((event.xany.window==_window)||
   (event.xany.window==_textWindow))
  {
  processEvent(event);
  return(true);
  }
else return(XGuiElement::dispatchEvent(event));
}

void XGuiLabel::processEvent(const XEvent & event) // virtual
{
switch(event.type)
  {
  case Expose:
    while(XCheckTypedWindowEvent(getXGuiManager()->getDisplay(),
                                 _window,Expose,(XEvent *)&event));
    while(XCheckTypedWindowEvent(getXGuiManager()->getDisplay(),
                                 _textWindow,Expose,(XEvent *)&event));
    redraw();
    break;
  case EnterNotify:
    if(_editable)
      {
      _inside=true;
      redraw();
      }
    break;
  case LeaveNotify:
    if(_editable&&(event.xcrossing.detail!=NotifyInferior))
      {
      _inside=false;
      redraw();
      }
    break;
  case ButtonPress:
    if((event.xbutton.window==_textWindow)&&
       (event.xbutton.button==Button1))
      {
      _selectMouse=true;
      _selectKey=false;
      _pos=getXGuiManager()->getTextPosition(_title,event.xbutton.x-_offset);
      _endSel=_startSel=_pos;
      redraw();
      }
    else if(_editable&&(event.xbutton.button==Button2)&&_inside)
      {
      getXGuiManager()->convertSelection(_textWindow);
      }
    break;
  case ButtonRelease:
    if(_selectMouse&&
       (event.xbutton.window==_textWindow)&&
       (event.xbutton.button==Button1))
      {
      _pos=getXGuiManager()->getTextPosition(_title,
                                             event.xbutton.x-_offset);
      _endSel=_pos;
      if(_startSel!=_endSel)
        {
        int start,len;
        if(_startSel<_endSel)
          {start=_startSel;len=_endSel-start;}
        else
          {start=_endSel;len=_startSel-start;}
        getXGuiManager()->setSelectionOwner(_textWindow,
                                            _title.subString(start,len));
        }
      _selectMouse=false;
      redraw();
      }
    break;
  case MotionNotify:
    while(XCheckTypedWindowEvent(getXGuiManager()->getDisplay(),
                                 _window,MotionNotify,(XEvent *)&event));
    while(XCheckTypedWindowEvent(getXGuiManager()->getDisplay(),
                                 _textWindow,MotionNotify,(XEvent *)&event));
    if(_selectMouse)
      {
      _pos=getXGuiManager()->getTextPosition(_title,
                                             event.xmotion.x-_offset);
      if(_pos!=_endSel)
        {
        _endSel=_pos;
        redraw();
        }
      }
    break;
  case SelectionNotify:
    if(_editable)
      {
      getXGuiManager()->selectionNotify(event.xselection);
      if(_startSel!=_endSel) delSelection();
      addSelection();
      _endSel=_startSel=0;
      redraw();
      }
    break;
  case KeyPress:
    if(_editable)
      {
      bool hideSel=false;
      static char buffer[0x10];
      KeySym keysym;
      int nb=XLookupString((XKeyEvent *)&event.xkey,
                           buffer,0x10,&keysym,(XComposeStatus*)0);
      if((keysym==XK_Delete)&& // Sometimes BackSpace is converted in Delete
         (event.xkey.keycode==22)) // keycode for BackSpace
        {
        keysym=XK_BackSpace;
        buffer[0]='\b';
        nb=1;
        }
      if((nb==1)&&(buffer[0]>=' ')&&
         (keysym!=XK_Delete)&&(keysym!=XK_KP_Delete))
        {
        addChar(buffer[0]);
        }
      else if((nb==1)&&(event.xkey.state&ControlMask))
        {
        switch(buffer[0]+'@')
          {
          case 'C':
            if(_startSel!=_endSel)
              {
              int start,len;
              if(_startSel<_endSel)
                {start=_startSel;len=_endSel-start;}
              else
                {start=_endSel;len=_startSel-start;}
              getXGuiManager()->setSelectionOwner(_textWindow,
                                              _title.subString(start,len));
              }
            break;
          case 'V':
            getXGuiManager()->convertSelection(_textWindow);
            break;
          case 'X':
            if(_startSel!=_endSel)
              {
              int start,len;
              if(_startSel<_endSel)
                {start=_startSel;len=_endSel-start;}
              else
                {start=_endSel;len=_startSel-start;}
              getXGuiManager()->setSelectionOwner(_textWindow,
                                              _title.subString(start,len));
              delSelection();
              }
            break;
          }
        }
      else switch(keysym)
        {
        case XK_Return:
        case XK_KP_Enter:
          if(_callback) (*_callback)(this,_data);
          return; // no break --> do nothing after callback()
        case XK_BackSpace:
          if(_startSel!=_endSel) delSelection();
          else if(goLeft()) delChar();
          break;
        case XK_Delete:
        case XK_KP_Delete:
          if(_startSel!=_endSel) delSelection();
          else if(_pos<(int)_title.len()) delChar();
          break;
        case XK_Left:
        case XK_KP_Left:
          if(event.xkey.state&ShiftMask)
            {
            if(!_selectKey)
              {
              _startSel=_pos;
              _selectKey=true;
              _selectMouse=false;
              }
            goLeft();
            _endSel=_pos;
            }
          else
            {
            _selectKey=false;
            if(goLeft()) hideSel=true;
            }
          break;
        case XK_Right:
        case XK_KP_Right:
          if(event.xkey.state&ShiftMask)
            {
            if(!_selectKey)
              {
              _startSel=_pos;
              _selectKey=true;
              _selectMouse=false;
              }
            goRight();
            _endSel=_pos;
            }
          else
            {
            _selectKey=false;
            if(goRight()) hideSel=true;
            }
          break;
        case XK_Home:
        case XK_KP_Home:
          if(event.xkey.state&ShiftMask)
            {
            if(!_selectKey)
              {
              _startSel=_pos;
              _selectKey=true;
              _selectMouse=false;
              }
            goStart();
            _endSel=_pos;
            }
          else
            {
            _selectKey=false;
            if(goStart()) hideSel=true;
            }
          break;
        case XK_End:
        case XK_KP_End:
          if(event.xkey.state&ShiftMask)
            {
            if(!_selectKey)
              {
              _startSel=_pos;
              _selectKey=true;
              _selectMouse=false;
              }
            goEnd();
            _endSel=_pos;
            }
          else
            {
            _selectKey=false;
            if(goEnd()) hideSel=true;
            }
          break;
        }
      if(hideSel) _endSel=_startSel=0;
      redraw();
      }
    break;
  }
}
  
bool XGuiLabel::goLeft(void)
{
if(_pos>0)
  {
  _pos--;
  return(true);
  }
else return(false);
}

bool XGuiLabel::goRight(void)
{
if(_pos<(int)_title.len())
  {
  _pos++;
  return(true);
  }
else return(false);
}

bool XGuiLabel::goStart(void)
{
if(_pos>0)
  {
  _pos=0;
  return(true);
  }
else return(false);
}

bool XGuiLabel::goEnd(void)
{
if(_pos<(int)_title.len())
  {
  _pos=_title.len();
  return(true);
  }
else return(false);
}

void XGuiLabel::addChar(char c)
{
if(_startSel!=_endSel) delSelection();
Strings newTitle=_title.subString(0,_pos);
newTitle+=c;
newTitle+=(const char *)_title+_pos;
_title=newTitle;
_pos++;
_selectMouse=_selectKey=false;
}

void XGuiLabel::addSelection(void)
{
Strings newTitle=_title.subString(0,_pos);
newTitle+=getXGuiManager()->getSelectedText();
newTitle+=(const char *)_title+_pos;
_title=newTitle;
_pos+=getXGuiManager()->getSelectedText().len();
_selectMouse=_selectKey=false;
}

void XGuiLabel::delChar(void)
{
Strings newTitle=_title.subString(0,_pos);
newTitle+=(const char *)_title+_pos+1;
_title=newTitle;
_selectMouse=_selectKey=false;
}

void XGuiLabel::delSelection(void)
{
int start,len;
if(_startSel<_endSel)
  {start=_startSel;len=_endSel-start;}
else
  {start=_endSel;len=_startSel-start;}
Strings newTitle=_title.subString(0,start);
newTitle+=(const char *)_title+start+len;
_title=newTitle;
_pos=start;
_endSel=_startSel=0;
_selectMouse=_selectKey=false;
}

void XGuiLabel::redraw(void) // virtual
{
if(_window)
  {
  getXGuiManager()->background(_pixmap,0,0,_width,_height);
  if(_deep) getXGuiManager()->drawBorderDown(_pixmap,0,0,_width,_height);
  XCopyArea(getXGuiManager()->getDisplay(),_pixmap,_window,
            getXGuiManager()->getGC(),0,0,_width,_height,0,0);
  getXGuiManager()->background(_textPixmap,0,0,_textWidth,_textHeight);
  int x=0;
  if(_editable)
    {
    x=getXGuiManager()->getTextWidth(_title.subString(0,_pos));
    int charWidth;
    if(_pos<(int)_title.len())
      charWidth=getXGuiManager()->getTextWidth(_title.subString(_pos,1));
    else
      charWidth=getXGuiManager()->getTextWidth(" ");
    if(x+charWidth>_textWidth-_offset) _offset=_textWidth-(x+charWidth);
    else if(x+_offset<0) _offset=-x;
    }
  getXGuiManager()->drawText(_textPixmap,_offset,0,_title);
  if(_startSel!=_endSel)
    {
    int start,len;
    if(_startSel<_endSel)
      {start=_startSel;len=_endSel-start;}
    else
      {start=_endSel;len=_startSel-start;}
    getXGuiManager()->drawSelection(_textPixmap,_offset,0,_title,start,len);
    }
  if(_editable)
    {
    getXGuiManager()->drawCursor(_textPixmap,_inside,x+_offset,0,
                                 _pos<(int)_title.len() ? _title[_pos] : ' ');
    }
  XCopyArea(getXGuiManager()->getDisplay(),_textPixmap,_textWindow,
            getXGuiManager()->getGC(),0,0,_width,_height,0,0);
  }
}

#endif // X_GUI

