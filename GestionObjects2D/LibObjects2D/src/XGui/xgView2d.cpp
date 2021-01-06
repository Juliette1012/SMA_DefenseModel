#ifdef X_GUI

#include "XGui/xgView2d.h"
#include "XGui/xgShap2d.h"
#include "XGui/xgArea.h"
#include "XGui/xgMgr.h"

//--------------------------------------------------------------------------//
// class XGuiViewer2D                                                       //
//--------------------------------------------------------------------------//

XGuiViewerList XGuiViewer2D::_viewers;

XGuiShapeList XGuiViewer2D::_shapes;

bool XGuiViewer2D::_mustDraw=true;

//-------- Static methods --------------------------------------------------//
void XGuiViewer2D::addShape(XGuiShape2D * shape) // static
{
XGuiShapeList::iterator itS=_shapes.begin();
while((itS!=_shapes.end())&&((*itS)->getLayer()<shape->getLayer())) itS++;
_shapes.insert(itS,shape);
XGuiViewerList::iterator itV=_viewers.begin();
for(;itV!=_viewers.end();itV++) shape->addViewer(*itV);
XGuiViewer2D::_mustDraw=true;
}

void XGuiViewer2D::removeShape(XGuiShape2D * shape) // static
{
XGuiShapeList::iterator itS=_shapes.begin();
while((*itS)!=shape) itS++;
_shapes.erase(itS);
XGuiViewerList::iterator itV=_viewers.begin();
for(;itV!=_viewers.end();itV++)
  {
  XGuiShapeList::iterator itS=(*itV)->_select.begin(); // unselect
  for(;itS!=(*itV)->_select.end();itS++)
    {
    if(*itS==shape)
      {
#if 0                                               // Avant
      (*itV)->_select.erase(itS);            
      (*itS)->notifySelection(*itV,false);
#else                                               // Apres modification VR
      (*itS)->notifySelection(*itV,false);
      (*itV)->_select.erase(itS);
#endif
      break;
      }
    }
  }
XGuiViewer2D::_mustDraw=true;
}

// inline void XGuiViewer2D::forceRedraw(void) // static

void XGuiViewer2D::drawAll(void) // static
{
if(XGuiViewer2D::_mustDraw)
  {
  XGuiShapeList::iterator itS=_shapes.begin();
  for(;itS!=_shapes.end();itS++) 
    if((*itS)->hasMoved()) (*itS)->computePosition();
  XGuiViewerList::iterator itV=_viewers.begin();
  for(;itV!=_viewers.end();itV++)
    (*itV)->redraw();
  for(itS=_shapes.begin();itS!=_shapes.end();itS++)
    (*itS)->savePosition();
  XGuiViewer2D::_mustDraw=false;
  }
}

//-------- Allocators ------------------------------------------------------//
XGuiViewer2D::XGuiViewer2D(XGuiArea * parent)
 : XGuiElement(2*getXGuiManager()->getMargin(),
               2*getXGuiManager()->getMargin()),
   _pixmap(None), _scale(1.0),
   _xmin(0.0), _ymin(0.0), _xmax(0.0), _ymax(0.0),
   _color("black"), _pixel(0),
   _select(), _ctrlPressed(false), _pressed(0), _canMoveSelection(false),
   _mouseX(0), _mouseY(0),
   _keyCallback((void (*)(XGuiViewer2D *,const Strings &,void *))0),
   _keyData((void *)0)
{
getXGuiManager()->allocNamedColor(_color,_pixel);
parent->addElement(this);
XGuiViewer2D::_viewers.push_back(this);
XGuiShapeList::iterator itS=_shapes.begin();
for(;itS!=_shapes.end();itS++) 
  (*itS)->addViewer(this);
autoScale();
}

XGuiViewer2D::~XGuiViewer2D(void)
{
XGuiShapeList::iterator itS;
XGuiShapeList tmpList(_select);
while(tmpList.size())
  {
  for(itS=_select.begin();itS!=_select.end();itS++)
    {
    if((*itS)==tmpList.front())
      {
      _select.erase(itS);
      tmpList.front()->notifySelection(this,false);
      break;
      }
    }
  tmpList.pop_front();
  }
for(itS=_shapes.begin();itS!=_shapes.end();itS++) 
  (*itS)->removeViewer(this);
getXGuiManager()->freeColor(_pixel);
if(_pixmap) XFreePixmap(getXGuiManager()->getDisplay(),_pixmap);
XGuiViewerList::iterator it=_viewers.begin();
while((*it)!=this) it++;
_viewers.erase(it);
}

//-------- Inspectors ------------------------------------------------------//
// inline XGuiElement::Type XGuiViewer2D::getElemType(void) const // virtual

// inline bool XGuiViewer2D::isA(XGuiElement::Type type) const // virtual

// inline Pixmap XGuiViewer2D::getPixmap(void) const;

// inline double XGuiViewer2D::getScale(void) const

// inline double XGuiViewer2D::getXmin(void) const

// inline double XGuiViewer2D::getYmin(void) const

// inline double XGuiViewer2D::getXmax(void) const

// inline double XGuiViewer2D::getYmax(void) const

// inline void XGuiViewer2D::getViewPoint(double & x,double & y,
//                                        double & scale) const;

// inline int XGuiViewer2D::getColumn(double x) const

// inline int XGuiViewer2D::getLine(double y) const

// inline const Strings & XGuiViewer2D::getBackground(void) const

// inline unsigned long XGuiViewer2D::getBackgroundPixel(void) const

// inline const XGuiShapeList & XGuiViewer2D::getSelection(void) const

bool XGuiViewer2D::isSelected(const XGuiShape2D * shape) const
{
XGuiShapeList::const_iterator it;
for(it=_select.begin();it!=_select.end();it++)
  if(*it==shape) return(true);
return(false);
}

//-------- Modifiers -------------------------------------------------------//
void XGuiViewer2D::select(XGuiShape2D * shape,bool propagate)
{
XGuiShapeList::iterator it;
for(it=_select.begin();it!=_select.end();it++)
  if(*it==shape) return;
_select.push_back(shape);
XGuiViewer2D::_mustDraw=true;
if(propagate) shape->notifySelection(this,true);
}

void XGuiViewer2D::unselect(XGuiShape2D * shape,bool propagate)
{
XGuiShapeList::iterator it;
for(it=_select.begin();it!=_select.end();it++)
  {
  if(*it==shape)
    {
    _select.erase(it);
    XGuiViewer2D::_mustDraw=true;
    if(propagate) shape->notifySelection(this,false);
    break;
    }
  }
}

void XGuiViewer2D::setBackground(const Strings & color)
{
unsigned long pixel;
if(getXGuiManager()->allocNamedColor(color,pixel))
  {
  getXGuiManager()->freeColor(_pixel);
  _pixel=pixel;
  _color=color;
  XGuiShapeList::iterator it=_shapes.begin();
  for(;it!=_shapes.end();it++) (*it)->changedViewerBackground(this);
  if(_window)
    {
    XSetWindowBackground(getXGuiManager()->getDisplay(),_window,_pixel);
    }
  XGuiViewer2D::_mustDraw=true;
  }
}

void XGuiViewer2D::setViewPoint(double x,double y,double scale)
{
double xmin,ymin,xmax,ymax;
xmin=x-_width*0.5/scale;
ymin=y-_height*0.5/scale;
xmax=xmin+_width/scale;
ymax=ymin+_height/scale;
if((getColumn(_xmin)!=getColumn(xmin))||
   (getLine(_ymin)!=getLine(ymin))||
   (getColumn(_xmax)!=getColumn(xmax))||
   (getLine(_ymax)!=getLine(ymax)))
  {                                        // really new view point ?
  _scale=scale;
  _xmin=xmin;
  _ymin=ymin;
  _xmax=xmax;
  _ymax=ymax;
  XGuiViewer2D::_mustDraw=true;
  if(_callback) (*_callback)(this,_data);
  }
}

void XGuiViewer2D::autoScale(void)
{
double gxmin=0.0,gymin=0.0,gxmax=0.0,gymax=0.0;
double xmin,ymin,xmax,ymax;
bool firstTime=true;
XGuiShapeList::const_iterator it=_shapes.begin();
for(;it!=_shapes.end();it++)
  {
  if((*it)->isScalable())
    {
    if((*it)->hasMoved()) (*it)->computePosition();
    (*it)->getBoundingBox(xmin,ymin,xmax,ymax,this);
    }
  else
    {
    xmin=xmax=(*it)->getX();
    ymin=ymax=(*it)->getY();
    }
  if(firstTime)
    {
    gxmin=xmin;
    gymin=ymin;
    gxmax=xmax;
    gymax=ymax;
    firstTime=false;
    }
  else
    {
    if(xmin<gxmin) gxmin=xmin;
    if(ymin<gymin) gymin=ymin;
    if(xmax>gxmax) gxmax=xmax;
    if(ymax>gymax) gymax=ymax;
    }
  }
double w=gxmax-gxmin;
double h=gymax-gymin;
double s;
if(!w&&!h) w=h=2.0;
if(h*_width>w*_height) s=_height/h;
else s=_width/w;
setViewPoint(0.5*(gxmin+gxmax),0.5*(gymin+gymax),0.9*s);
}

void XGuiViewer2D::setWidth(int width) // virtual
{
XGuiElement::setWidth(width);
if(_window)
  {
  XFreePixmap(getXGuiManager()->getDisplay(),_pixmap);
  _pixmap=XCreatePixmap(getXGuiManager()->getDisplay(),_window,
                        _width,_height,
                        getXGuiManager()->getDepth());
  }
setViewPoint(0.5*(_xmax+_xmin),0.5*(_ymax+_ymin),_scale);
}

void XGuiViewer2D::setHeight(int height) // virtual
{
XGuiElement::setHeight(height);
if(_window)
  {
  XFreePixmap(getXGuiManager()->getDisplay(),_pixmap);
  _pixmap=XCreatePixmap(getXGuiManager()->getDisplay(),_window,
                        _width,_height,
                        getXGuiManager()->getDepth());
  }
setViewPoint(0.5*(_xmax+_xmin),0.5*(_ymax+_ymin),_scale);
}

void XGuiViewer2D::show(void) // virtual
{
if(!_window)
  {
  _window=getXGuiManager()->getNewWindow(((XGuiArea *)_parent)->getInWindow(),
                                         _x,_y,_width,_height);
  XSetWindowBackground(getXGuiManager()->getDisplay(),_window,_pixel);
  XSelectInput(getXGuiManager()->getDisplay(),_window,
               ExposureMask | EnterWindowMask |
               KeyPressMask | KeyReleaseMask |
               ButtonPressMask | ButtonMotionMask | ButtonReleaseMask);
  _pixmap=XCreatePixmap(getXGuiManager()->getDisplay(),_window,
                        _width,_height,
                        getXGuiManager()->getDepth());
  XMapWindow(getXGuiManager()->getDisplay(),_window);
  XGuiViewer2D::_mustDraw=true;
  }
XGuiElement::show();
}

void XGuiViewer2D::hide(void) // virtual
{
XGuiElement::hide();
if(_pixmap)
  {
  XFreePixmap(getXGuiManager()->getDisplay(),_pixmap);
  _pixmap=None;
  }
}

// inline void XGuiViewer2D::setKeyCallback(
//                           void (*keyCallback)(XGuiViewer2D*,
//                                               const Strings &,
//                                               void *),
//                           void * keyData)

void XGuiViewer2D::processEvent(const XEvent & event) // virtual
{
switch(event.type)
  {
  case Expose:
    while(XCheckTypedWindowEvent(getXGuiManager()->getDisplay(),
                                 _window,Expose,(XEvent *)&event)) { ; }
    XGuiViewer2D::_mustDraw=true;
    break;
  case EnterNotify:
    if(event.xcrossing.state&ControlMask) _ctrlPressed=true;
    else _ctrlPressed=false;
    _chooseCursor();
    break;
  case KeyPress:
    {
    static char buffer[0x20];
    KeySym keysym;
    int nb=XLookupString((XKeyEvent *)&event.xkey,
                         buffer,0x10,&keysym,(XComposeStatus*)0);
    switch(keysym)
      {
      case XK_Control_L:
      case XK_Control_R:
        _ctrlPressed=true;
        _chooseCursor();
        break;
      case XK_Delete: // Sometimes BackSpace is converted in Delete
        if(event.xkey.keycode==22) // keycode for BackSpace
          {
          keysym=XK_BackSpace;
          buffer[0]='\b';
          nb=1;
          }
        break;
      }
    char * str;
    if(nb==1)
      {
      buffer[nb]='\0';
      str=buffer;
      }
    else str=XKeysymToString(keysym);
    if(str)
      {
      if(_select.size()) // to selected objects
        {
        XGuiShapeList::iterator it;
        XGuiShapeList tmpList(_select);
        while(tmpList.size())
          {
          for(it=_select.begin();it!=_select.end();it++)
            {
            if((*it)==tmpList.front())
              {
              (*it)->notifyKey(str);
              break;
              }
            }
          tmpList.pop_front();
          }
        }
      else // to viewer
        {
        if(_keyCallback) (*_keyCallback)(this,str,_keyData);
        }
      }
    }
    break;
  case KeyRelease:
    {
    static char buffer[0x10];
    KeySym keysym;
    XLookupString((XKeyEvent *)&event.xkey,
                  buffer,0x10,&keysym,(XComposeStatus*)0);
    switch(keysym)
      {
      case XK_Control_L:
      case XK_Control_R:
        _ctrlPressed=false;
        _chooseCursor();
        break;
      }
    }
    break;
  case ButtonPress:
#if 0                 // Fabrice
{
    if(!_pressed)
      {
      _canMoveSelection=false;
      _pressed=event.xbutton.button;
      _mouseX=event.xbutton.x;
      _mouseY=event.xbutton.y;
      _chooseCursor();
      if(!_ctrlPressed) // Not Ctrl : selection
        {
        double x=(event.xbutton.x/_scale)+_xmin;
        double y=_ymax-(event.xbutton.y/_scale);
        XGuiShape2D * nearest=(XGuiShape2D *)0;
        double d,dmin=0.0;
        XGuiShapeList::iterator it=_shapes.begin();
        for(;it!=_shapes.end();it++)
          {
          d=(*it)->distanceTo(x,y,this);
          if(!nearest||(d<dmin))
            {
            nearest=*it;
            dmin=d;
            }
          }
        if(nearest&&(dmin>5.0/_scale)) // precision = 5 pixels
          nearest=(XGuiShape2D *)0;
        if(event.xbutton.state&ShiftMask) // Shift : (un)select shapes
          {
          if(nearest)
            {
            for(it=_select.begin();it!=_select.end();it++) // unselect
              if(*it==nearest) break;
            if(it==_select.end())
              {
              if(_pressed==Button1)
                {
                _select.push_back(nearest);
                nearest->notifySelection(this,true);
                }
              }
            else
              {
              if(_pressed!=Button1)
                {
                _select.erase(it);
                nearest->notifySelection(this,false);
                }
              }
            XGuiViewer2D::_mustDraw=true;
            }
          }
        else // unselect all shapes and select the nearest
          {
          XGuiShapeList::iterator it;
          XGuiShapeList tmpList(_select);
          while(tmpList.size())
            {
            for(it=_select.begin();it!=_select.end();it++)
              {
              if((*it==tmpList.front())&&
                 ((*it!=nearest)||(_pressed!=Button1))) // avoid reselection
                {
                _select.erase(it);
                tmpList.front()->notifySelection(this,false);
                break;
                }
              }
            tmpList.pop_front();
            }
          if(nearest&&(_pressed==Button1))
            {
            for(it=_shapes.begin();it!=_shapes.end();it++)
              if(*it==nearest) break;
            if(it!=_shapes.end()) // nearest not destroyed
              {
              for(it=_select.begin();it!=_select.end();it++)
                if(*it==nearest) break;
              if(it==_select.end()) // not reinserted by previous CB
                {
                _select.push_back(nearest);
                nearest->notifySelection(this,true);
                }
              }
            }
          XGuiViewer2D::_mustDraw=true;
          }
        if(nearest&&(_pressed==Button1)) _canMoveSelection=true;
        }
      }
    break;
}
#else                 // Vincent
{
    if(!_pressed)
      {
      _canMoveSelection=false;
      _pressed=event.xbutton.button;
      _mouseX=event.xbutton.x;
      _mouseY=event.xbutton.y;
      _chooseCursor();
      if(!_ctrlPressed) // Not Ctrl : selection
        {
        double x=(event.xbutton.x/_scale)+_xmin;
        double y=_ymax-(event.xbutton.y/_scale);
        XGuiShape2D * nearest=(XGuiShape2D *)0;
        double d,dmin=0.0;
        XGuiShapeList::iterator it;
        for(it=_shapes.begin();it!=_shapes.end();it++)
          {
          d=(*it)->distanceTo(x,y,this);
          if(!nearest||(d<dmin))
            {
            nearest=*it;
            dmin=d;
            }
          }

        if(nearest&&(dmin>5.0/_scale)) // precision = 5 pixels
          nearest=(XGuiShape2D *)0;

#if 1
        // And now, to be able to click inside an object...
        for(it=_shapes.begin();it!=_shapes.end();it++) 
          {
           if ((*it)->isInside(x,y))
           {
            d=(*it)->distanceTo(x,y,this);
            if(!nearest||(d<dmin)) { nearest=*it; dmin=d; }
           }
           else
           {
            double xmin,ymin,xmax,ymax;
            (*it)->getBoundingBox(xmin,ymin,xmax,ymax,this);
            if (xmin<=x && x<=xmax && ymin<=y && y<=ymax)
            {
             d=(*it)->distanceTo(x,y,this);
             if(!nearest||(d<dmin)) { nearest=*it; dmin=d; }
            }
           }
          }
#endif

        if(event.xbutton.state&ShiftMask) // Shift : (un)select shapes
          {
          if(nearest)
            {
            for(it=_select.begin();it!=_select.end();it++) // unselect
              if(*it==nearest) break;
            if(it==_select.end()) // nearest,
              {                   // not found in already selected objects
               if(_pressed==Button1)        // The first selection of an object
               { nearest->notifySelection(this,false); // with Button1 do not
                                            // -----  generate a notification
                _select.push_back(nearest);            // true => false //<--
               }                                                        //  !
               else { nearest->notifySelection(this,true); }            //  !
              }                                                         //  !
            else                  // nearest,                           //  !
              {                   // found in already selected objects  //  !
               if(_pressed!=Button1) _select.erase(it);                 //  !
               nearest->notifySelection(this,true);                     //  !
              }                                                         //  !
                                                                        //  !
            XGuiViewer2D::_mustDraw=true;                               //  !
            }                                                           //  !
          }                                                             //  !
        else // unselect all shapes and select the nearest              //  !
          {                                                             //  !
          XGuiShapeList::iterator it;                                   //  !
          bool nearAlreadySelected = false;                             //  !
          for(it=_select.begin();it!=_select.end();it++)                //  !
            {                                                           //  !
             if (*it==nearest) nearAlreadySelected = true;              //  !
             else(*it)->notifySelection(this,false);                    //  !
            }                                                           //  !
          _select.clear();                                              //  !
                                                                        //  !
          if(nearest)                                                   //  !
          {                                                             //  !
           if (_pressed==Button1) _select.push_back(nearest);           //  !
           if (_pressed==Button1 && !nearAlreadySelected)               //  !
                { nearest->notifySelection(this,false); }               //  !
                                             // -----       false >---------!
           else {
#if 1 // VR : to avoid the use of the wheel to select...
             if (_pressed!=Button4 && _pressed!=Button5) 
#endif
                 nearest->notifySelection(this,true);
           }  
          }
          XGuiViewer2D::_mustDraw=true;
          }
        if(nearest&&(_pressed==Button1)) _canMoveSelection=true;
        }
      }
    break;
}
#endif
  case ButtonRelease:
    if(_pressed==event.xbutton.button)
      {
      _pressed=0;
      _canMoveSelection=false;
      _chooseCursor();
      }
    break;
  case MotionNotify:
    while(XCheckTypedWindowEvent(getXGuiManager()->getDisplay(),
                                 _window,MotionNotify,(XEvent *)&event)) { ; }
    if(_pressed)
      {
      int dx=event.xbutton.x-_mouseX;
      int dy=event.xbutton.y-_mouseY;
      _mouseX=event.xbutton.x;
      _mouseY=event.xbutton.y;
      if(_ctrlPressed)
        {
        if(_pressed==Button1) // ---> translate
          {
          setViewPoint((_xmin+_xmax)/2.0-dx/_scale,
                       (_ymin+_ymax)/2.0+dy/_scale,
                       _scale);
          }
        else // other button ---> zoom
          {
          if(dy>0)
            setViewPoint((_xmin+_xmax)/2.0,(_ymin+_ymax)/2.0,
                         _scale*(1.0+2.0*dy/_height));
          else
            setViewPoint((_xmin+_xmax)/2.0,(_ymin+_ymax)/2.0,
                         _scale/(1.0-2.0*dy/_height));
          }
        }
      else if(_canMoveSelection)
        {
        XGuiShapeList::iterator it;
        XGuiShapeList tmpList(_select);
        while(tmpList.size())
          {
          for(it=_select.begin();it!=_select.end();it++)
            {
            if((*it)==tmpList.front())
              {
              (*it)->notifyMotion(dx/_scale,-dy/_scale);
              break;
              }
            }
          tmpList.pop_front();
          }
        }
      }
    break;
  }
}

void XGuiViewer2D::redraw(void) // virtual
{
if(_window&&_mapped)
  {
  XGuiShapeList::iterator it;
  getXGuiManager()->chooseColor(_pixel);
  XFillRectangle(getXGuiManager()->getDisplay(),_pixmap,
                 getXGuiManager()->getGC(),0,0,_width,_height);
  double xmin,ymin,xmax,ymax;
  for(it=_shapes.begin();it!=_shapes.end();it++) // draw shapes
    {
    (*it)->getBoundingBox(xmin,ymin,xmax,ymax,this);
    if((xmin<=_xmax)&&(xmax>=_xmin)&&(ymin<=_ymax)&&(ymax>=_ymin))
      (*it)->drawInViewer(this);
    }
  if(_select.size())
    {
    for(it=_select.begin();it!=_select.end();it++) // draw selection
      drawBoundingBox(*it);
    }
  XCopyArea(getXGuiManager()->getDisplay(),_pixmap,_window,
            getXGuiManager()->getGC(),0,0,_width,_height,0,0);
  }
}

void XGuiViewer2D::drawBoundingBox(const XGuiShape2D * shape)
{
double xmin,ymin,xmax,ymax;
shape->getBoundingBox(xmin,ymin,xmax,ymax,this);
if((xmin<=_xmax)&&(xmax>=_xmin)&&(ymin<=_ymax)&&(ymax>=_ymin))
  {
  int x=getColumn(xmin);
  int y=getLine(ymax);
  int w=getColumn(xmax)-x;
  int h=getLine(ymin)-y;
  XDrawRectangle(getXGuiManager()->getDisplay(),_pixmap,
                 getXGuiManager()->getXorGC(),x-2,y-2,w+4,h+4);
  if((w>4)&&(h>4))
    XDrawRectangle(getXGuiManager()->getDisplay(),_pixmap,
                   getXGuiManager()->getXorGC(),x+2,y+2,w-4,h-4);
  }
}

void XGuiViewer2D::_chooseCursor(void)
{
if(_ctrlPressed)
  {
  if(_pressed&&(_pressed!=Button1))
    getXGuiManager()->setZoomCursor(_window);
  else
    getXGuiManager()->setMoveCursor(_window);
  }
else getXGuiManager()->setDefaultCursor(_window);
}

#endif // X_GUI

