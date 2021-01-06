#ifdef X_GUI

#include "XGui/xgEditor.h"
#include "XGui/xgScroll.h"
#include "XGui/xgArea.h"
#include "XGui/xgMgr.h"

//--------------------------------------------------------------------------//
// class XGuiEditor                                                         //
//--------------------------------------------------------------------------//

//-------- Allocators ------------------------------------------------------//
XGuiEditor::XGuiEditor(XGuiArea * parent,
                       const Strings & content,bool readOnly)
 : XGuiElement(7*getXGuiManager()->getMargin(),
               7*getXGuiManager()->getMargin()),
  _textWindow(None), _textX(0), _textY(0), _textWidth(0), _textHeight(0),
  _pixmap(None), _pixWidth(0), _pixHeight(0),
  _editable(!readOnly), _lines(), _maxLine(0), _totalHeight(0),
  _spaceWidth(getXGuiManager()->getTextWidth(" ")),
  _scrollH(new XGuiScroller(this,true)),
  _scrollV(new XGuiScroller(this,false)),
  _inside(false), _showPos(true), _exposure(false),
  _posX(0), _posY(0), _offsetX(0), _offsetY(0),
  _selectMouse(false), _selectKey(false),
  _startSelX(0), _startSelY(0), _endSelX(0), _endSelY(0)
{
_scrollH->setCallback(_scrollHCB);
_scrollV->setCallback(_scrollVCB);
setContent(content);
setWidth(_lines[_maxLine]->second+_spaceWidth+
         2*getXGuiManager()->getMargin()+
         _scrollV->getWidth());
setHeight(_lines.getSize()*getXGuiManager()->getCharHeight()+
          2*getXGuiManager()->getMargin()+
          _scrollH->getHeight());
parent->addElement(this);
}

XGuiEditor::~XGuiEditor(void)
{
  // _scrollH and _scrollV are auto-deleted
while(_lines.getSize())
  {
  delete _lines.readPopBack();
  }
if(_textWindow)
  XDestroyWindow(getXGuiManager()->getDisplay(),_textWindow);
if(_pixmap)
  XFreePixmap(getXGuiManager()->getDisplay(),_pixmap);
}

//-------- Inspectors ------------------------------------------------------//
XGuiElement::Type XGuiEditor::getElemType(void) const // virtual
{
return(XGuiElement::EDITOR);
}

bool XGuiEditor::isA(XGuiElement::Type type) const // virtual
{
return(type==XGuiElement::EDITOR);
}

Strings XGuiEditor::getContent(void) const // virtual
{
Strings content;
for(unsigned int i=0;i<_lines.getSize();i++)
  {
  if(i) content+='\n';
  content+=_lines[i]->first;
  }
return(content);
}

//-------- Modifiers -------------------------------------------------------//
void XGuiEditor::setWidth(int width) // virtual
{
XGuiElement::setWidth(width);
_scrollH->setX(0);
_scrollH->setWidth(_width-_scrollV->getWidth());
_scrollV->setX(_scrollH->getWidth());
_textX=getXGuiManager()->getMargin();
_textWidth=_scrollH->getWidth()-2*_textX;
_adjustScrollHRatio();
if(_textWindow)
  {
  XWindowChanges changes;
  changes.width=_textWidth;
  XConfigureWindow(getXGuiManager()->getDisplay(),_textWindow,
                   CWWidth,&changes);
  }
}

void XGuiEditor::setHeight(int height) // virtual
{
XGuiElement::setHeight(height);
_scrollV->setY(0);
_scrollV->setHeight(_height-_scrollH->getHeight());
_scrollH->setY(_scrollV->getHeight());
_textY=getXGuiManager()->getMargin();
_textHeight=_scrollV->getHeight()-2*_textY;
_adjustScrollVRatio();
if(_textWindow)
  {
  XWindowChanges changes;
  changes.height=_textHeight;
  XConfigureWindow(getXGuiManager()->getDisplay(),_textWindow,
                   CWHeight,&changes);
  }
}

void XGuiEditor::setContent(const Strings & content) // virtual
{
_offsetX=0;
_offsetY=0;
_startSelX=0;
_endSelX=0;
_startSelY=0;
_endSelY=0;
_selectMouse=false;
_selectKey=false;
_posX=0;
_posY=0;
while(_lines.getSize())
  {
  delete _lines.readPopBack();
  }
_lines.pushBack(new XGuiEditor::EditorLine(Strings(),0));
addText(content);
_posX=0;
_posY=0;
_showPos=true;
_exposure=true;
redraw();
}

void XGuiEditor::show(void) // virtual
{
if(!_window)
  {
  _window=getXGuiManager()->getNewWindow(((XGuiArea *)_parent)->getInWindow(),
                                         _x,_y,_width,_height);
  _textWindow=getXGuiManager()->getNewWindow(_window,
                                             _textX,_textY,
                                             _textWidth,_textHeight);
  long eventMask=ExposureMask | KeyPressMask |
                 ButtonPressMask | ButtonReleaseMask | Button1MotionMask |
                 EnterWindowMask | LeaveWindowMask | PropertyChangeMask;
  XSelectInput(getXGuiManager()->getDisplay(),_window,eventMask);
  XSelectInput(getXGuiManager()->getDisplay(),_textWindow,eventMask);
  XMapWindow(getXGuiManager()->getDisplay(),_window);
  XMapWindow(getXGuiManager()->getDisplay(),_textWindow);
  _computeSize();
  _adjustSize();
  if((_startSelX!=_endSelX)||(_startSelY!=_endSelY)) _drawSelection();
  }
XGuiElement::show();
}

void XGuiEditor::hide(void) // virtual
{
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

bool XGuiEditor::dispatchEvent(const XEvent & event) // virtual
{
if((event.xany.window==_window)||
   (event.xany.window==_textWindow))
  {
  processEvent(event);
  return(true);
  }
else return(XGuiElement::dispatchEvent(event));
}

void XGuiEditor::usingSelection(Window owner) // virtual
{
if(owner!=_textWindow)
  {
  if((_startSelX!=_endSelX)||(_startSelY!=_endSelY))
    if(_window) _hideSelection();
  _selectMouse=_selectKey=false;
  _endSelX=_endSelY=_startSelX=_startSelY=0;
  redraw();
  }
}

void XGuiEditor::processEvent(const XEvent & event) // virtual
{
switch(event.type)
  {
  case Expose:
    while(XCheckTypedWindowEvent(getXGuiManager()->getDisplay(),
                                 _window,Expose,(XEvent *)&event));
    while(XCheckTypedWindowEvent(getXGuiManager()->getDisplay(),
                                 _textWindow,Expose,(XEvent *)&event));
    _exposure=true;
    _showPos=false;
    redraw();
    break;
  case EnterNotify:
    _inside=true;
    _exposure=false;
    _showPos=false;
    redraw();
    break;
  case LeaveNotify:
    if(event.xcrossing.detail!=NotifyInferior)
      {
      _inside=false;
      _exposure=false;
      _showPos=false;
      redraw();
      }
    break;
  case ButtonPress:
    switch(event.xbutton.button)
      {
      case Button1:
        if(event.xbutton.window==_textWindow)
          {
          _posY=(event.xbutton.y-_offsetY)/getXGuiManager()->getCharHeight();
          if(_posY<0) _posY=0;
          else if(_posY>=(int)_lines.getSize()) _posY=_lines.getSize()-1;
          _posX=getXGuiManager()->getTextPosition(_lines[_posY]->first,
                                                  event.xbutton.x-_offsetX);
          _selectMouse=true;
          _selectKey=false;
          if((_startSelX!=_endSelX)||(_startSelY!=_endSelY)) _hideSelection();
          _endSelX=_startSelX=_posX;
          _endSelY=_startSelY=_posY;
          _exposure=false;
          _showPos=true;
          redraw();
          }
        break;
      case Button2:
        if(_inside&&_editable&&!_selectMouse&&!_selectKey)
          {
          getXGuiManager()->convertSelection(_textWindow);
          _exposure=false;
          _showPos=true;
          redraw();
          }
        break;
      case Button4: // wheel up
        if(event.xbutton.x*_height>=event.xbutton.y*_width)
          _scrollV->setValue(_scrollV->getValue()-
                    ((double)getXGuiManager()->getCharHeight())/_totalHeight);
        else if(_lines[_maxLine]->second)
          _scrollH->setValue(_scrollH->getValue()-
                    ((double)getXGuiManager()->getTextWidth("M"))/
                    _lines[_maxLine]->second);
        break;
      case Button5: // wheel down
        if(event.xbutton.x*_height>=event.xbutton.y*_width)
          _scrollV->setValue(_scrollV->getValue()+
                    ((double)getXGuiManager()->getCharHeight())/_totalHeight);
        else if(_lines[_maxLine]->second)
          _scrollH->setValue(_scrollH->getValue()+
                    ((double)getXGuiManager()->getTextWidth("M"))/
                    _lines[_maxLine]->second);
        break;
      }
    break;
  case ButtonRelease:
    if(_selectMouse&&
       (event.xbutton.window==_textWindow)&&
       (event.xbutton.button==Button1))
      {
      _posY=(event.xbutton.y-_offsetY)/getXGuiManager()->getCharHeight();
      if(_posY<0) _posY=0;
      else if(_posY>=(int)_lines.getSize()) _posY=_lines.getSize()-1;
      _posX=getXGuiManager()->getTextPosition(_lines[_posY]->first,
                                              event.xbutton.x-_offsetX);
      if((_startSelX!=_endSelX)||(_startSelY!=_endSelY)) _hideSelection();
      _endSelX=_posX;
      _endSelY=_posY;
      if((_startSelX!=_endSelX)||(_startSelY!=_endSelY))
        {
        _drawSelection();
        int x1,y1,x2,y2;
        _getSelectPos(x1,y1,x2,y2);
        Strings text;
        if(y1==y2)
          {
          text=_lines[y1]->first.subString(x1,x2-x1);
          }
        else
          {
          text=_lines[y1]->first.subString(x1,_lines[y1]->first.len()-x1);
          text+='\n';
          for(int i=y1+1;i<y2;i++)
            {
            text+=_lines[i]->first;
            text+='\n';
            }
          text+=_lines[y2]->first.subString(0,x2);
          }
        getXGuiManager()->setSelectionOwner(_textWindow,text);
        }
      _selectMouse=false;
      _exposure=false;
      _showPos=true;
      redraw();
      }
    break;
  case MotionNotify:
    while(XCheckTypedWindowEvent(getXGuiManager()->getDisplay(),
                                 _textWindow,MotionNotify,
                                 (XEvent *)&event));
    if(_selectMouse)
      {
      _exposure=false;
      _showPos=true;
      _posY=(event.xmotion.y-_offsetY)/getXGuiManager()->getCharHeight();
      if(_posY<0) _posY=0;
      else if(_posY>=(int)_lines.getSize()) _posY=_lines.getSize()-1;
      _posX=getXGuiManager()->getTextPosition(_lines[_posY]->first,
                                              event.xmotion.x-_offsetX);
      if((_posX!=_endSelX)||(_posY!=_endSelY))
        {
        if((_startSelX!=_endSelX)||(_startSelY!=_endSelY)) _hideSelection();
        _endSelX=_posX;
        _endSelY=_posY;
        if((_startSelX!=_endSelX)||(_startSelY!=_endSelY)) _drawSelection();
        redraw();
        }
      }
    break;
  case SelectionNotify:
    getXGuiManager()->selectionNotify(event.xselection);
    addText(getXGuiManager()->getSelectedText());
    _showPos=true;
    _exposure=false;
    redraw();
    break;
  case KeyPress:
    {
    bool hideSel=false;
    _exposure=false;
    _showPos=true;
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
      if(_editable) addChar(buffer[0]);
      }
    else if((nb==1)&&(event.xkey.state&ControlMask))
      {
      switch(buffer[0]+'@')
        {
        case 'C':
          if((_startSelX!=_endSelX)||(_startSelY!=_endSelY))
            {
            int x1,y1,x2,y2;
            _getSelectPos(x1,y1,x2,y2);
            Strings text;
            if(y1==y2)
              {
              text=_lines[y1]->first.subString(x1,x2-x1);
              }
            else
              {
              text=_lines[y1]->first.subString(x1,_lines[y1]->first.len()-x1);
              text+='\n';
              for(int i=y1+1;i<y2;i++)
                {
                text+=_lines[i]->first;
                text+='\n';
                }
              text+=_lines[y2]->first.subString(0,x2);
              }
            getXGuiManager()->setSelectionOwner(_textWindow,text);
            }
          break;
        case 'V':
          if(_editable) getXGuiManager()->convertSelection(_textWindow);
          break;
        case 'X':
          if(_editable&&
             ((_startSelX!=_endSelX)||(_startSelY!=_endSelY)))
            {
            int x1,y1,x2,y2;
            _getSelectPos(x1,y1,x2,y2);
            Strings text;
            if(y1==y2)
              {
              text=_lines[y1]->first.subString(x1,x2-x1);
              }
            else
              {
              text=_lines[y1]->first.subString(x1,_lines[y1]->first.len()-x1);
              text+='\n';
              for(int i=y1+1;i<y2;i++)
                {
                text+=_lines[i]->first;
                text+='\n';
                }
              text+=_lines[y2]->first.subString(0,x2);
              }
            getXGuiManager()->setSelectionOwner(_textWindow,text);
            delSelection();
            }
          break;
        }
      }
    else switch(keysym)
      {
      case XK_Return:
      case XK_KP_Enter:
        if(_editable) addChar('\n');
        break;
      case XK_BackSpace:
        if(_editable)
          {
          if((_startSelX!=_endSelX)||(_startSelY!=_endSelY)) delSelection();
          else if(goLeft()) delChar();
          }
        break;
      case XK_Delete:
      case XK_KP_Delete:
        if(_editable)
          {
          if((_startSelX!=_endSelX)||(_startSelY!=_endSelY)) delSelection();
          else delChar();
          }
        break;
      case XK_Left:
      case XK_KP_Left:
        if(event.xkey.state&ShiftMask)
          {
          if((_startSelX!=_endSelX)||(_startSelY!=_endSelY)) _hideSelection();
          if(!_selectKey)
            {
            _startSelX=_posX;
            _startSelY=_posY;
            _selectKey=true;
            }
          goLeft();
          _endSelX=_posX;
          _endSelY=_posY;
          _drawSelection();
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
          if((_startSelX!=_endSelX)||(_startSelY!=_endSelY)) _hideSelection();
          if(!_selectKey)
            {
            _startSelX=_posX;
            _startSelY=_posY;
            _selectKey=true;
            }
          goRight();
          _endSelX=_posX;
          _endSelY=_posY;
          _drawSelection();
          }
        else
          {
          _selectKey=false;
          if(goRight()) hideSel=true;
          }
        break;
      case XK_Up:
      case XK_KP_Up:
        if(event.xkey.state&ShiftMask)
          {
          if((_startSelX!=_endSelX)||(_startSelY!=_endSelY)) _hideSelection();
          if(!_selectKey)
            {
            _startSelX=_posX;
            _startSelY=_posY;
            _selectKey=true;
            }
          goUp();
          _endSelX=_posX;
          _endSelY=_posY;
          _drawSelection();
          }
        else
          {
          _selectKey=false;
          if(goUp()) hideSel=true;
          }
        break;
      case XK_Down:
      case XK_KP_Down:
        if(event.xkey.state&ShiftMask)
          {
          if((_startSelX!=_endSelX)||(_startSelY!=_endSelY)) _hideSelection();
          if(!_selectKey)
            {
            _startSelX=_posX;
            _startSelY=_posY;
            _selectKey=true;
            }
          goDown();
          _endSelX=_posX;
          _endSelY=_posY;
          _drawSelection();
          }
        else
          {
          _selectKey=false;
          if(goDown()) hideSel=true;
          }
        break;
      case XK_Page_Up:
      case XK_KP_Page_Up:
        if(event.xkey.state&ShiftMask)
          {
          if((_startSelX!=_endSelX)||(_startSelY!=_endSelY)) _hideSelection();
          if(!_selectKey)
            {
            _startSelX=_posX;
            _startSelY=_posY;
            _selectKey=true;
            }
          goUp(_textHeight/(2*getXGuiManager()->getCharHeight()));
          _endSelX=_posX;
          _endSelY=_posY;
          _drawSelection();
          }
        else
          {
          _selectKey=false;
          if(goUp(_textHeight/(2*getXGuiManager()->getCharHeight())))
            hideSel=true;
          }
        break;
      case XK_Page_Down:
      case XK_KP_Page_Down:
        if(event.xkey.state&ShiftMask)
          {
          if((_startSelX!=_endSelX)||(_startSelY!=_endSelY)) _hideSelection();
          if(!_selectKey)
            {
            _startSelX=_posX;
            _startSelY=_posY;
            _selectKey=true;
            }
          goDown(_textHeight/(2*getXGuiManager()->getCharHeight()));
          _endSelX=_posX;
          _endSelY=_posY;
          _drawSelection();
          }
        else
          {
          _selectKey=false;
          if(goDown(_textHeight/(2*getXGuiManager()->getCharHeight())))
            hideSel=true;
          }
        break;
      case XK_Home:
      case XK_KP_Home:
        if(event.xkey.state&ShiftMask)
          {
          if((_startSelX!=_endSelX)||(_startSelY!=_endSelY)) _hideSelection();
          if(!_selectKey)
            {
            _startSelX=_posX;
            _startSelY=_posY;
            _selectKey=true;
            }
          if(event.xkey.state&ControlMask) goTop();
          else goStart();
          _endSelX=_posX;
          _endSelY=_posY;
          _drawSelection();
          }
        else
          {
          _selectKey=false;
          if(event.xkey.state&ControlMask)
            {
            if(goTop()) hideSel=true;
            }
          else if(goStart()) hideSel=true;
          }
        break;
      case XK_End:
      case XK_KP_End:
        if(event.xkey.state&ShiftMask)
          {
          if((_startSelX!=_endSelX)||(_startSelY!=_endSelY)) _hideSelection();
          if(!_selectKey)
            {
            _startSelX=_posX;
            _startSelY=_posY;
            _selectKey=true;
            }
          if(event.xkey.state&ControlMask) goBottom();
          else goEnd();
          _endSelX=_posX;
          _endSelY=_posY;
          _drawSelection();
          }
        else
          {
          _selectKey=false;
          if(event.xkey.state&ControlMask)
            {
            if(goBottom()) hideSel=true;
            }
          else if(goEnd()) hideSel=true;
          }
        break;
      }
    if(hideSel)
      {
      if((_startSelX!=_endSelX)||(_startSelY!=_endSelY)) _hideSelection();
      _endSelX=_startSelX=_endSelY=_startSelY=0;
      }
    redraw();
    }
    break;
  }
}

bool XGuiEditor::goLeft(void)
{
if(_posX>0)
  {
  _posX--;
  return(true);
  }
else if(_posY>0)
  {
  _posY--;
  _posX=_lines[_posY]->first.len();
  return(true);
  }
else return(false);
}

bool XGuiEditor::goRight(void)
{
if(_posX<(int)_lines[_posY]->first.len())
  {
  _posX++;
  return(true);
  }
else if(_posY<(int)_lines.getSize()-1)
  {
  _posY++;
  _posX=0;
  return(true);
  }
else return(false);
}

bool XGuiEditor::goStart(void)
{
if(_posX>0)
  {
  _posX=0;
  return(true);
  }
else return(false);
}

bool XGuiEditor::goEnd(void)
{
if(_posX<(int)_lines[_posY]->first.len())
  {
  _posX=_lines[_posY]->first.len();
  return(true);
  }
else return(false);
}

bool XGuiEditor::goUp(int step)
{
if(_posY>0)
  {
  _posY-=step;
  if(_posY<0) _posY=0;
  if(_posX>(int)_lines[_posY]->first.len())
    _posX=_lines[_posY]->first.len();
  return(true);
  }
else return(false);
}

bool XGuiEditor::goDown(int step)
{
if(_posY<(int)_lines.getSize()-1)
  {
  _posY+=step;
  if(_posY>=(int)_lines.getSize()) _posY=_lines.getSize()-1;
  if(_posX>(int)_lines[_posY]->first.len())
    _posX=_lines[_posY]->first.len();
  return(true);
  }
else return(false);
}

bool XGuiEditor::goTop(void)
{
if((_posY>0)||(_posX>0))
  {
  _posY=0;
  _posX=0;
  return(true);
  }
else return(false);
}

bool XGuiEditor::goBottom(void)
{
if((_posY<(int)_lines.getSize()-1)||
   (_posX<(int)_lines.getBack()->first.len()))
  {
  _posY=_lines.getSize()-1;
  _posX=_lines[_posY]->first.len();
  return(true);
  }
else return(false);
}

void XGuiEditor::addChar(char c)
{
if((_startSelX!=_endSelX)||(_startSelY!=_endSelY)) delSelection();
if(c=='\n')
  {
  Strings text=_lines[_posY]->first;
  _lines[_posY]->first=text.subString(0,_posX);
  _lines[_posY]->second=getXGuiManager()->getTextWidth(_lines[_posY]->first);
  _posY++;
  _lines.insert(_posY,new XGuiEditor::EditorLine);
  _lines[_posY]->first=text.subString(_posX,text.len()-_posX);
  _lines[_posY]->second=getXGuiManager()->getTextWidth(_lines[_posY]->first);
  _computeSize();
  _adjustSize();
  _posX=0;
  }
else
  {
  Strings newLine=_lines[_posY]->first.subString(0,_posX);
  int oldWidth=_lines[_maxLine]->second;
  newLine+=c;
  newLine+=(const char *)_lines[_posY]->first+_posX;
  int width=getXGuiManager()->getTextWidth(newLine);
  _lines[_posY]->first=newLine;
  _lines[_posY]->second=width;
  if(width>oldWidth)
    {
    _computeSize();
    if(_lines[_maxLine]->second>_pixWidth)
      _adjustSize();
    else if(_pixmap) _drawLine(_posY);
    }
  else if(_pixmap) _drawLine(_posY);
  _posX++;
  }
}

void XGuiEditor::addText(const Strings & text)
{
if((_startSelX!=_endSelX)||(_startSelY!=_endSelY)) delSelection();
XGuiEditor::EditorLine * current=_lines[_posY];
_lines.erase(_posY);
XGuiEditor::EditorLine * line;
int nbLines=0;
int start=0;
for(int limit=0;limit<=(int)text.len();limit++) // until '\0'
  {
  if((text[limit]=='\n')||(text[limit]=='\0'))
    {
    line=new XGuiEditor::EditorLine;
    line->first=text.subString(start,limit-start);
    line->second=getXGuiManager()->getTextWidth(line->first);
    _lines.insert(_posY+nbLines,line);
    nbLines++;
    start=limit+1; // next line
    }
  }
_lines[_posY]->first=current->first.subString(0,_posX)+_lines[_posY]->first;
_lines[_posY]->second=getXGuiManager()->getTextWidth(_lines[_posY]->first);
_posY+=nbLines-1;
_lines[_posY]->first=_lines[_posY]->first+
              current->first.subString(_posX,current->first.len()-_posX);
_lines[_posY]->second=getXGuiManager()->getTextWidth(_lines[_posY]->first);
_posX=_posX+_lines[_posY]->first.len()-current->first.len();
delete current;
_computeSize();
_adjustSize();
}

void XGuiEditor::delChar(void)
{
_endSelX=_endSelY=_startSelX=_startSelY=0;
_selectMouse=_selectKey=false;
if(_posX<(int)_lines[_posY]->first.len())
  {
  Strings newLine=_lines[_posY]->first.subString(0,_posX);
  newLine+=(const char *)_lines[_posY]->first+_posX+1;
  int width=getXGuiManager()->getTextWidth(newLine);
  _lines[_posY]->first=newLine;
  _lines[_posY]->second=width;
  if(_maxLine==_posY) _computeSize();
  if(_pixmap) _drawLine(_posY);
  }
else if(_posY<(int)_lines.getSize()-1)
  {
  _lines[_posY]->first+=_lines[_posY+1]->first;
  _lines[_posY]->second=getXGuiManager()->getTextWidth(_lines[_posY]->first);
  delete _lines.readErase(_posY+1);
  _computeSize();
  _adjustSize();
  }
}

void XGuiEditor::delSelection(void)
{
_hideSelection();
int x1,y1,x2,y2;
_getSelectPos(x1,y1,x2,y2);
Strings text=_lines[y1]->first.subString(0,x1)+
             _lines[y2]->first.subString(x2,_lines[y2]->first.len()-x2);
for(;y2>=y1;y2--)
  {
  delete _lines.readErase(y2);
  }
_lines.insert(y1,new XGuiEditor::EditorLine);
_lines[y1]->first=text;
_lines[y1]->second=getXGuiManager()->getTextWidth(_lines[y1]->first);
_computeSize();
_adjustSize();
_posY=y1;
_posX=x1;
_selectMouse=_selectKey=false;
_endSelX=_endSelY=_startSelX=_startSelY=0;
}

void XGuiEditor::redraw(void) // virtual
{
if(_window)
  {
  int x=getXGuiManager()->getTextWidth(_lines[_posY]->first
                                                     .subString(0,_posX));
  int y=_posY*getXGuiManager()->getCharHeight();
  char cursorChar=(_posX<(int)_lines[_posY]->first.len() ?
                   _lines[_posY]->first[_posX] : ' ');
  if(_showPos)
    {
    int charWidth=getXGuiManager()->getTextWidth(Strings(cursorChar));
    if(x+charWidth>_textWidth-_offsetX) _offsetX=_textWidth-(x+charWidth);
    else if(x+_offsetX<0) _offsetX=-x;
    if(y+getXGuiManager()->getCharHeight()>_textHeight-_offsetY)
      _offsetY=_textHeight-(y+getXGuiManager()->getCharHeight());
    else if(y+_offsetY<0) _offsetY=-y;
    }
  if(_exposure)
    {
    getXGuiManager()->background(_window,0,0,_width,_height);
    if(_editable)
      {
      getXGuiManager()->drawBorderDown(_window,0,0,_textWidth+2*_textX,
                                                   _textHeight+2*_textY);
      }
    else
      {
      getXGuiManager()->drawBorderLineUp(_window,0,0,_textWidth+2*_textX,
                                                     _textHeight+2*_textY);
      }
    }
  XCopyArea(getXGuiManager()->getDisplay(),_pixmap,_textWindow,
            getXGuiManager()->getGC(),-_offsetX,-_offsetY,
            _textWidth,_textHeight,0,0);
  getXGuiManager()->drawCursor(_textWindow,_inside,
                               x+_offsetX,y+_offsetY,cursorChar);
  _adjustScrollHValue();
  _adjustScrollVValue();
  }
}

void XGuiEditor::_getSelectPos(int & x1,int & y1,int & x2,int & y2)
{
if(_startSelY==_endSelY)
  {
  y1=y2=_endSelY;
  if(_startSelX<_endSelX)
    {x1=_startSelX; x2=_endSelX;}
  else
    {x1=_endSelX; x2=_startSelX;}
  }
else
  {
  if(_startSelY<_endSelY)
    {x1=_startSelX; y1=_startSelY; x2=_endSelX; y2=_endSelY;}
  else
    {x2=_startSelX; y2=_startSelY; x1=_endSelX; y1=_endSelY;}
  }
}

void XGuiEditor::_drawSelection(void)
{
int x1,y1,x2,y2;
_getSelectPos(x1,y1,x2,y2);
if(y1==y2)
  {
  getXGuiManager()->drawSelection(_pixmap,
                                  0,y1*getXGuiManager()->getCharHeight(),
                                  _lines[y1]->first,x1,x2-x1);
  }
else
  {
  int y=y1*getXGuiManager()->getCharHeight();
  getXGuiManager()->drawSelection(_pixmap,0,y,_lines[y1]->first,
                                  x1,_lines[y1]->first.len()-x1);
  y+=getXGuiManager()->getCharHeight();
  for(int i=y1+1;i<y2;i++)
    {
    getXGuiManager()->drawSelection(_pixmap,0,y,_lines[i]->first,
                                    0,_lines[i]->first.len());
    y+=getXGuiManager()->getCharHeight();
    }
  getXGuiManager()->drawSelection(_pixmap,0,y,_lines[y2]->first,0,x2);
  }
}

void XGuiEditor::_hideSelection(void)
{
int first,last;
if(_startSelY<_endSelY) {first=_startSelY; last=_endSelY;}
else {first=_endSelY; last=_startSelY;}
int y=first*getXGuiManager()->getCharHeight();
while(first<=last)
  {
  getXGuiManager()->background(_pixmap,0,y,_pixWidth,
                               getXGuiManager()->getCharHeight());
  getXGuiManager()->drawText(_pixmap,0,y,_lines[first]->first);
  y+=getXGuiManager()->getCharHeight();
  first++;
  }
}

void XGuiEditor::_drawLine(int line)
{
getXGuiManager()->background(_pixmap,0,
                             line*getXGuiManager()->getCharHeight(),
                             _pixWidth,getXGuiManager()->getCharHeight());
getXGuiManager()->drawText(_pixmap,0,
                           line*getXGuiManager()->getCharHeight(),
                           _lines[line]->first);
}

void XGuiEditor::_computeSize(void)
{
_maxLine=0;
for(unsigned int i=0;i<_lines.getSize();i++)
  {
  if(_lines[i]->second>_lines[_maxLine]->second)
    _maxLine=i;
  }
_totalHeight=_lines.getSize()*getXGuiManager()->getCharHeight();
_adjustScrollHRatio();
_adjustScrollVRatio();
}

void XGuiEditor::_adjustSize(void)
{
_pixWidth=2*_lines[_maxLine]->second+2*getXGuiManager()->getMargin();
_pixHeight=2*_totalHeight;
if(_window)
  {
  if(_pixmap) XFreePixmap(getXGuiManager()->getDisplay(),_pixmap);
  _pixmap=getXGuiManager()->getNewPixmap(_window,_pixWidth,_pixHeight);
  getXGuiManager()->background(_pixmap,0,0,_pixWidth,_pixHeight);
  for(unsigned int i=0;i<_lines.getSize();i++)
    {
    getXGuiManager()->drawText(_pixmap,0,i*getXGuiManager()->getCharHeight(),
                               _lines[i]->first);
    }
  }
}

void XGuiEditor::_adjustScrollHRatio(void)
{
if(_lines[_maxLine]->second)
  _scrollH->setRatio(((double)(_textWidth-_spaceWidth))/
                     _lines[_maxLine]->second,true);
else _scrollH->setRatio(1.0,false);
}

void XGuiEditor::_adjustScrollHValue(void)
{
if(_lines[_maxLine]->second)
  _scrollH->setValue(((double)-_offsetX)/_lines[_maxLine]->second,false);
else
  _scrollH->setValue(0.0,false);
}

void XGuiEditor::_adjustScrollVRatio(void)
{
_scrollV->setRatio(((double)_textHeight)/_totalHeight,true);
}

void XGuiEditor::_adjustScrollVValue(void)
{
_scrollV->setValue(((double)-_offsetY)/_totalHeight,false);
}

//-------- Callbacks -------------------------------------------------------//
void XGuiEditor::_scrollHCB(XGuiElement * calling,void *) // static
{
XGuiEditor * editor=(XGuiEditor *)calling->accessParent();
double value=((XGuiScroller *)calling)->getValue();
editor->_offsetX=(int)(-value*editor->_lines[editor->_maxLine]->second);
editor->_showPos=false;
editor->redraw();
}

void XGuiEditor::_scrollVCB(XGuiElement * calling,void *) // static
{
XGuiEditor * editor=(XGuiEditor *)calling->accessParent();
double value=((XGuiScroller *)calling)->getValue();
editor->_offsetY=(int)(-value*editor->_totalHeight);
editor->_showPos=false;
editor->redraw();
}

#endif // X_GUI

