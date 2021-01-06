#ifdef X_GUI

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "XGui/xgMgr.h"
#include "XGui/xgView2d.h"
#include "XGui/xgGraph.h"

#ifdef OPEN_GL
#include "XGui/xgView3d.h"
#endif

//--------------------------------------------------------------------------//
// class XGuiManager                                                        //
//--------------------------------------------------------------------------//

XGuiManager * XGuiManager::_xGuiManager=(XGuiManager *)0;

XtEventDispatchProc XGuiManager::_oldDispatchProc[LASTEvent];

jmp_buf XGuiManager::_mainLoopBuffer;

// inline XGuiManager * getXGuiManager(void) // friend

//-------- Allocators ------------------------------------------------------//
XGuiManager::XGuiManager(void)
 : _elems(), _showing(false), _fail(false),
   _display((Display *)0), _appContext((XtAppContext)0), _selfBuilt(false),
   _screen(0), _depth(0), _root(0), _font((XFontStruct *)0), _charHeight(0),
   _clickTime(0), _gc(0), _xorGc(0), _colormap(0), _foreground(0),
   _background(0), _highlight(0), _lightside(0), _darkside(0),
   _cursorMove(None), _cursorZoom(None), _cursorZoomXY(None),
   _exclusive(), _selectedText(),
   _running(false), _loopProc((void (*)(void *))0),
   _task((void (*)(void *))0), _taskData((void *)0),
   _timerId((XtIntervalId)0)
{
if(_xGuiManager)
  {
  cerr << "Already connected to X Server" << endl;
  _fail=true;
  }
else
  {
  _xGuiManager=this;
  _display=XOpenDisplay("");
  if(_display)
    {
    int dummy_argc=1;
    const char * dummy_argv[]={"XGui",""}; // Avant pas : const
    XtToolkitInitialize();
    _appContext=XtCreateApplicationContext();
    XtDisplayInitialize(_appContext,_display,
                        dummy_argv[0],dummy_argv[0],
                        (XrmOptionDescRec *)0,0,
                        &dummy_argc,
                        (char**)&dummy_argv); // Avant pas : (char**)&
    _selfBuilt=true;
    _init();
    }
  else _fail=true;
  }
}

XGuiManager::XGuiManager(Display * display,XtAppContext appContext)
 : _elems(), _showing(false), _fail(false),
   _display(display), _appContext(appContext), _selfBuilt(false),
   _screen(0), _depth(0), _root(0), _font((XFontStruct *)0), _charHeight(0),
   _clickTime(0), _gc(0), _xorGc(0), _colormap(0), _foreground(0),
   _background(0), _highlight(0), _lightside(0), _darkside(0),
   _cursorMove(None), _cursorZoom(None), _cursorZoomXY(None), 
   _exclusive(), _selectedText(),
   _running(false), _loopProc((void (*)(void *))0),
   _task((void (*)(void *))0), _taskData((void *)0),
   _timerId((XtIntervalId)0)
{
if(_xGuiManager)
  {
  cerr << "Already connected to X Server" << endl;
  _fail=true;
  }
else
  {
  _xGuiManager=this;
  if(_display&&_appContext) _init();
  else _fail=true;
  }
}

XGuiManager::~XGuiManager(void)
{
while(_elems.getSize()) delete _elems.accessBack();
if(_task) XtRemoveTimeOut(_timerId);
if(!_fail)
  {
  for(int eventType=0;eventType<LASTEvent;eventType++)
    {
    XtSetEventDispatcher(_display,eventType,
                         XGuiManager::_oldDispatchProc[eventType]);
    }
  }
#ifdef OPEN_GL
XGuiViewer3D::destroyGlobalContext();
#endif
if(_display)
  {
  freeColor(_foreground);
  freeColor(_background);
  freeColor(_highlight);
  freeColor(_lightside);
  freeColor(_darkside);
  if(_selfBuilt)
    {
    /* PB with NVIDIA Cards ?
    XtDestroyApplicationContext(_appContext);
    XtCloseDisplay(_display);
    */
    }
  }
if(_xGuiManager==this) _xGuiManager=(XGuiManager *)0;
}

//-------- Inspectors ------------------------------------------------------//
// inline bool XGuiManager::fail(void) const

// inline bool XGuiManager::isShowing(void) const

// inline Display * XGuiManager::getDisplay(void) const

// inline XtAppContext XGuiManager::getContext(void) const

// inline int XGuiManager::getScreen(void) const

// inline int XGuiManager::getDepth(void) const

// inline Window XGuiManager::getRoot(void) const

// inline XFontStruct * XGuiManager::getFont(void) const

int XGuiManager::getTextWidth(const Strings & text) const
{
return(XTextWidth(_font,text,text.len()));
}

int XGuiManager::getTextPosition(const Strings & text,int x) const
{
int len;
for(len=0;len<(int)text.len();len++)
  {
  if(XTextWidth(_font,text,len+1)>x) break;
  }
return(len);
}

// inline int XGuiManager::getCharHeight(void) const

// inline int XGuiManager::getScreenWidth(void) const

// inline int XGuiManager::getScreenHeight(void) const

// inline int XGuiManager::getMargin(void) const

// inline int XGuiManager::getClickTime(void) const

// inline GC XGuiManager::getGC(void) const

// inline GC XGuiManager::getXorGC(void) const

void XGuiManager::queryColor(unsigned long pixel,unsigned short & r,
                             unsigned short & g,unsigned short & b) const
{
XColor color;
color.pixel=pixel;
XQueryColor(_display,_colormap,&color);
r=color.red;
g=color.green;
b=color.blue;
}

// inline unsigned long XGuiManager::getForeground(void) const

// inline unsigned long XGuiManager::getBackground(void) const

// inline unsigned long XGuiManager::getHighlight(void) const

// inline unsigned long XGuiManager::getLightside(void) const

// inline unsigned long XGuiManager::getDarkside(void) const

Window XGuiManager::getNewWindow(Window parent,int x,int y,
                                 int width,int height) const
{
return(XCreateSimpleWindow(_display,parent,x,y,width,height,0,
                           _foreground,_background));
}

Pixmap XGuiManager::getNewPixmap(Window parent,int width,int height) const
{
return(XCreatePixmap(_display,parent,width,height,_depth));
}

void XGuiManager::getRootPosition(Window win,int & x,int & y) const
{
Window root,child;
int rootX,rootY,winX,winY;
unsigned int mask;
XQueryPointer(_display,win,&root,&child,
              &rootX,&rootY,&winX,&winY,&mask);
x=rootX-winX;
y=rootY-winY;
}

// inline const Strings & XGuiManager::getSelectedText(void) const

// inline bool XGuiManager::isExclusive(void) const

// inline void XGuiManager::getTask(void (* & task)(void *),
//                                  void * & data) const

//-------- Modifiers -------------------------------------------------------//
// inline void XGuiManager::setDefaultCursor(Window win)

// inline void XGuiManager::setMoveCursor(Window win)

// inline void XGuiManager::setZoomCursor(Window win)

// inline void XGuiManager::setZoomXYCursor(Window win)

bool XGuiManager::allocNamedColor(const Strings & name,unsigned long & pixel)
{
XColor color;
if(XParseColor(_display,_colormap,name,&color)&&
   XAllocColor(_display,_colormap,&color))
  {
  pixel=color.pixel;
  return(true);
  }
else return(false);
}

bool XGuiManager::allocColor(int r,int g,int b,unsigned long & pixel)
{
XColor color;
color.red=r;
color.green=g;
color.blue=b;
if(XAllocColor(_display,_colormap,&color))
  {
  pixel=color.pixel;
  return(true);
  }
else return(false);
}

void XGuiManager::freeColor(unsigned long pixel)
{
XFreeColors(_display,_colormap,&pixel,1,0LU);
}

// inline void XGuiManager::chooseColor(unsigned long pixel)

void XGuiManager::drawText(Drawable draw,int x,int y,const Strings & text)
{
chooseColor(_foreground);
XDrawString(_display,draw,_gc,x,y+_font->ascent,text,text.len());
}

void XGuiManager::drawCursor(Drawable draw,bool inside,int x,int y,char c)
{
int width=XTextWidth(_font,&c,1);
if(inside)
  {
  chooseColor(_foreground);
  XFillRectangle(_display,draw,_gc,x,y,width,_charHeight);
  chooseColor(_lightside);
  XDrawString(_display,draw,_gc,x,y+_font->ascent,&c,1);
  }
else
  {
  chooseColor(_background);
  XFillRectangle(_display,draw,_gc,x,y,width,_charHeight);
  chooseColor(_lightside);
  XDrawRectangle(_display,draw,_gc,x,y,width-1,_charHeight-1);
  chooseColor(_foreground);
  XDrawString(_display,draw,_gc,x,y+_font->ascent,&c,1);
  }
}

void XGuiManager::drawSelection(Drawable draw,int x,int y,
                                const Strings & text,int start,int len)
{
x+=XTextWidth(_font,text,start);
chooseColor(_darkside);
XFillRectangle(_display,draw,_gc,x,y,
               XTextWidth(_font,(const char *)text+start,len),
               _charHeight);
chooseColor(_lightside);
XDrawString(_display,draw,_gc,x,y+_font->ascent,(const char *)text+start,len);
}

void XGuiManager::background(Drawable draw,
                             int x,int y,int width,int height)
{
chooseColor(_background);
XFillRectangle(_display,draw,_gc,x,y,width,height);
}

void XGuiManager::highlight(Drawable draw,
                            int x,int y,int width,int height)
{
chooseColor(_highlight);
XFillRectangle(_display,draw,_gc,x,y,width,height);
}

void XGuiManager::drawBorderUp(Drawable draw,
                               int x,int y,int width,int height)
{
chooseColor(_lightside);
XDrawLine(_display,draw,_gc,x,y,x+width-1,y);
XDrawLine(_display,draw,_gc,x,y+1,x+width-2,y+1);
XDrawLine(_display,draw,_gc,x,y,x,y+height-1);
XDrawLine(_display,draw,_gc,x+1,y,x+1,y+height-2);
chooseColor(_darkside);
XDrawLine(_display,draw,_gc,x,y+height-1,x+width-1,y+height-1);
XDrawLine(_display,draw,_gc,x+1,y+height-2,x+width-1,y+height-2);
XDrawLine(_display,draw,_gc,x+width-1,y,x+width-1,y+height-1);
XDrawLine(_display,draw,_gc,x+width-2,y+1,x+width-2,y+height-1);
}

void XGuiManager::drawBorderDown(Drawable draw,
                                 int x,int y,int width,int height)
{
chooseColor(_darkside);
XDrawLine(_display,draw,_gc,x,y,x+width-1,y);
XDrawLine(_display,draw,_gc,x,y+1,x+width-2,y+1);
XDrawLine(_display,draw,_gc,x,y,x,y+height-1);
XDrawLine(_display,draw,_gc,x+1,y,x+1,y+height-2);
chooseColor(_lightside);
XDrawLine(_display,draw,_gc,x,y+height-1,x+width-1,y+height-1);
XDrawLine(_display,draw,_gc,x+1,y+height-2,x+width-1,y+height-2);
XDrawLine(_display,draw,_gc,x+width-1,y,x+width-1,y+height-1);
XDrawLine(_display,draw,_gc,x+width-2,y+1,x+width-2,y+height-1);
}

void XGuiManager::drawBorderLineUp(Drawable draw,
                                   int x,int y,int width,int height)
{
chooseColor(_lightside);
XDrawLine(_display,draw,_gc,x,y,x+width-1,y);
XDrawLine(_display,draw,_gc,x,y,x,y+height-1);
XDrawLine(_display,draw,_gc,x+1,y+height-2,x+width-1,y+height-2);
XDrawLine(_display,draw,_gc,x+width-2,y+1,x+width-2,y+height-1);
chooseColor(_darkside);
XDrawLine(_display,draw,_gc,x+1,y+1,x+width-2,y+1);
XDrawLine(_display,draw,_gc,x+1,y+1,x+1,y+height-2);
XDrawLine(_display,draw,_gc,x+1,y+height-1,x+width-1,y+height-1);
XDrawLine(_display,draw,_gc,x+width-1,y+1,x+width-1,y+height-1);
}

void XGuiManager::drawBorderLineDown(Drawable draw,
                                     int x,int y,int width,int height)
{
chooseColor(_darkside);
XDrawLine(_display,draw,_gc,x,y,x+width-1,y);
XDrawLine(_display,draw,_gc,x,y,x,y+height-1);
XDrawLine(_display,draw,_gc,x+1,y+height-2,x+width-1,y+height-2);
XDrawLine(_display,draw,_gc,x+width-2,y+1,x+width-2,y+height-1);
chooseColor(_lightside);
XDrawLine(_display,draw,_gc,x+1,y+1,x+width-2,y+1);
XDrawLine(_display,draw,_gc,x+1,y+1,x+1,y+height-2);
XDrawLine(_display,draw,_gc,x+1,y+height-1,x+width-1,y+height-1);
XDrawLine(_display,draw,_gc,x+width-1,y+1,x+width-1,y+height-1);
}

void XGuiManager::drawHLineUp(Drawable draw,int x,int y,int width)
{
chooseColor(_lightside);
XDrawLine(_display,draw,_gc,x,y,x+width,y);
chooseColor(_darkside);
XDrawLine(_display,draw,_gc,x,y+1,x+width,y+1);
}

void XGuiManager::drawHLineDown(Drawable draw,int x,int y,int width)
{
chooseColor(_darkside);
XDrawLine(_display,draw,_gc,x,y,x+width,y);
chooseColor(_lightside);
XDrawLine(_display,draw,_gc,x,y+1,x+width,y+1);
}

void XGuiManager::drawVLineUp(Drawable draw,int x,int y,int height)
{
chooseColor(_lightside);
XDrawLine(_display,draw,_gc,x,y,x,y+height);
chooseColor(_darkside);
XDrawLine(_display,draw,_gc,x+1,y,x+1,y+height);
}

void XGuiManager::drawVLineDown(Drawable draw,int x,int y,int height)
{
chooseColor(_darkside);
XDrawLine(_display,draw,_gc,x,y,x,y+height);
chooseColor(_lightside);
XDrawLine(_display,draw,_gc,x+1,y,x+1,y+height);
}

void XGuiManager::bell(void)
{
XBell(getXGuiManager()->_display,0);
}

void XGuiManager::show(void)
{
_showing=true;
for(int i=_elems.getSize();i--;)
  _elems[i]->show();
}

void XGuiManager::hide(void)
{
_showing=false;
for(int i=_elems.getSize();i--;)
  _elems[i]->hide();
}

void XGuiManager::exclusiveWaitEvent(XGuiElement * target)
{
XEvent event;
void (*task)(void *)=_task;
if(_task)
  {
  _task=(void (*)(void *))0;
  XtRemoveTimeOut(_timerId);
  }
_exclusive.pushBack(target);
XtAppNextEvent(_appContext,&event);
XtDispatchEvent(&event);
_exclusive.popBack();
if(task)
  {
  _task=task;
  _timerId=XtAppAddTimeOut(_appContext,0,
                           XGuiManager::_timerProc,(XtPointer)0);
  }
}

void XGuiManager::selectionClear(void)
{
for(int i=_elems.getSize();i--;)
  _elems[i]->usingSelection(None);
}

void XGuiManager::setSelectionOwner(Window owner,const Strings & text)
{
_selectedText=text;
XSetSelectionOwner(_display,XA_PRIMARY,_root,CurrentTime); // owner -> _root
for(int i=_elems.getSize();i--;)
  _elems[i]->usingSelection(owner);
}

void XGuiManager::convertSelection(Window requestor)
{
XConvertSelection(_display,XA_PRIMARY,XA_STRING,XA_CUT_BUFFER0,
                  requestor,CurrentTime);
}

void XGuiManager::selectionRequest(const XSelectionRequestEvent & evt)
{
XEvent reply;
reply.type=SelectionNotify;
reply.xselection.display=evt.display;
reply.xselection.requestor=evt.requestor;
reply.xselection.selection=evt.selection;
reply.xselection.target=evt.target;
reply.xselection.property=evt.property;
reply.xselection.time=evt.time;
if(evt.target==XA_STRING)
  {
  XChangeProperty(evt.display,evt.requestor,evt.property,evt.target,
                  8,PropModeReplace,
                  (const unsigned char *)(const char *)_selectedText,
                  _selectedText.len());
  }
else reply.xselection.property=None;
XSendEvent(evt.display,evt.requestor,true,NoEventMask,&reply);
}

void XGuiManager::selectionNotify(const XSelectionEvent & evt)
{
if(evt.property==None) _selectedText=Strings("");
else
  {
  Atom type;
  int format;
  unsigned long nb,rest;
  unsigned char * buffer;
  XGetWindowProperty(evt.display,
                     evt.requestor,
                     evt.property,
                     0,0xffff,
                     false,AnyPropertyType,&type,
                     &format,&nb,&rest,&buffer);
  buffer[nb]='\0';
  _selectedText=Strings((const char *)buffer);
  XFree(buffer);
  }
}

void XGuiManager::usingMenu(XGuiMenu * menu)
{
for(int i=_elems.getSize();i--;)
  _elems[i]->usingMenu(menu);
}

void XGuiManager::addElement(XGuiElement * element)
{
_elems.pushBack(element);
}

void XGuiManager::removeElement(XGuiElement * element)
{
for(int i=_elems.getSize();i--;)
  if(_elems[i]==element)
    _elems.erase(i);
}

void XGuiManager::chooseFont(void)
{
char * var=::getenv("ORISFONT");
if(var)
  {
  _font=XLoadQueryFont(_display,var);
  if(!_font)
    {
    cerr << "Font \"" << var << "\" not available"
         << "  - using \"fixed\" instead" << endl;
    _font=XLoadQueryFont(_display,"fixed");
    }
  /*
  if(_font->min_bounds.width!=_font->max_bounds.width)
    {
    cerr << "Font \"" << var << "\" is proportional"
         << "  - using \"fixed\" instead" << endl;
    _font=XLoadQueryFont(_display,"fixed");
    }
  */
  }
else _font=XLoadQueryFont(_display,"fixed");
}

bool XGuiManager::dumpWindow(Window win,
                             unsigned char * & red,
                             unsigned char * & green,
                             unsigned char * & blue,
                             int & nbColors,
                             unsigned long * & points,
                             int & width,int & height)
{
XWindowAttributes winAttr;
XGetWindowAttributes(_display,win,&winAttr);
width=winAttr.width;
height=winAttr.height;
XImage * image=XGetImage(_display,win,0,0,width,height,AllPlanes,ZPixmap);
points=(unsigned long *)malloc(width*height* sizeof(unsigned long));
unsigned long pixel;
SimpleVector<unsigned long> colors;
int x,y,col;
bool found;
for(y=0;y<height;y++)
  {
  for(x=0;x<width;x++)
    {
    pixel=XGetPixel(image,x,y);
    found=false;
    for(col=colors.getSize();!found&&col--;)
      if(colors[col]==pixel) found=true;
    if(found) points[y*width+x]=col;
    else
      {
      points[y*width+x]=colors.getSize();
      colors.pushBack(pixel);
      }
    }
  }
nbColors=colors.getSize();
unsigned int colorSize=nbColors*sizeof(unsigned char);
red=(unsigned char *)malloc(colorSize);
green=(unsigned char *)malloc(colorSize);
blue=(unsigned char *)malloc(colorSize);
XColor color;
for(col=nbColors;col--;)
  {
  color.pixel=colors[col];
  XQueryColor(_display,winAttr.colormap,&color);
  red[col]=color.red>>8;
  green[col]=color.green>>8;
  blue[col]=color.blue>>8;
  }
XDestroyImage(image);
return(true);
}

bool XGuiManager::readRAS(FILE * file,unsigned char * & red,
                                      unsigned char * & green,
                                      unsigned char * & blue,
                                      int & nbColors,
                                      unsigned long * & points,
                                      int & width,int & height)
{
struct
  {
  long magic;
  long width;
  long height;
  long depth;
  long length;
  long type;
  long maptype;
  long maplength;
  } head;
bool fail=false;                                                // read header
if(!fail&&!::fread(&head.magic,sizeof(long),1,file)) fail=true;
if(!fail&&!::fread(&head.width,sizeof(long),1,file)) fail=true;
if(!fail&&!::fread(&head.height,sizeof(long),1,file)) fail=true;
if(!fail&&!::fread(&head.depth,sizeof(long),1,file)) fail=true;
if(!fail&&!::fread(&head.length,sizeof(long),1,file)) fail=true;
if(!fail&&!::fread(&head.type,sizeof(long),1,file)) fail=true;
if(!fail&&!::fread(&head.maptype,sizeof(long),1,file)) fail=true;
if(!fail&&!::fread(&head.maplength,sizeof(long),1,file)) fail=true;
#if defined __i386__ || defined __MSDOS__
_invertLong(head.magic);
_invertLong(head.width);
_invertLong(head.height);
_invertLong(head.depth);
_invertLong(head.length);
_invertLong(head.type);
_invertLong(head.maptype);
_invertLong(head.maplength);
#endif
if(!fail)                                                   // check file type
  {
  if((head.magic!=0x59A66A95L)|| // magic number for RasterFile
     (head.depth!=8))            // 8 bits : 256 colors
    fail=true;
  }
if(!fail)                                            // check image properties
  {
  width=head.width;
  height=head.height;
  nbColors=head.maplength/3;
  if(!width||!height||!nbColors) fail=true;
  }
if(!fail)                                                   // allocate memory
  {
  unsigned int colorSize=nbColors*sizeof(unsigned char);
  red=(unsigned char *)malloc(colorSize);
  green=(unsigned char *)malloc(colorSize);
  blue=(unsigned char *)malloc(colorSize);
  points=(unsigned long *)malloc(width*height* sizeof(unsigned long));
  }
if(!fail&&::fread(red,sizeof(unsigned char),                  // read colormap
                  nbColors,file)!=(unsigned int)nbColors)
  fail=true;
if(!fail&&::fread(green,sizeof(unsigned char),
                  nbColors,file)!=(unsigned int)nbColors)
  fail=true;
if(!fail&&::fread(blue,sizeof(unsigned char),
                  nbColors,file)!=(unsigned int)nbColors)
  fail=true;
if(!fail)                                                 // read image pixels
  {
  unsigned int lineSize=width+width%2;
  unsigned char * line=(unsigned char *)malloc(lineSize*sizeof(unsigned char));
  int x,y;
  for(y=0;!fail&&(y<height);y++)
    {
    if(::fread(line,sizeof(unsigned char),lineSize,file)==lineSize)
      {
      for(x=0;x<width;x++) points[y*width+x]=line[x];
      }
    else fail=true;
    }
  free(line);
  }
return(!fail);
}

bool XGuiManager::writeRAS(FILE * file,const unsigned char * red,
                                       const unsigned char * green,
                                       const unsigned char * blue,
                                       int nbColors,
                                       const unsigned long * points,
                                       int width,int height)
{
struct
  {
  long magic;
  long width;
  long height;
  long depth;
  long length;
  long type;
  long maptype;
  long maplength;
  } head;
head.magic=0x59A66A95L;                         // magic number for RasterFile
head.width=width;
head.height=height;
head.depth=8;                                   // 8 bits : 256 colors
head.length=height*(width%2 ? width+1 : width);
head.type=1;                                    // always 1 !
head.maptype=1;                                 // always 1 !!
head.maplength=3*nbColors;
bool fail=false;                                               // write header
#if defined __i386__ || defined __MSDOS__
_invertLong(head.magic);
_invertLong(head.width);
_invertLong(head.height);
_invertLong(head.depth);
_invertLong(head.length);
_invertLong(head.type);
_invertLong(head.maptype);
_invertLong(head.maplength);
#endif
if(!fail&&!::fwrite(&head.magic,sizeof(long),1,file)) fail=true;
if(!fail&&!::fwrite(&head.width,sizeof(long),1,file)) fail=true;
if(!fail&&!::fwrite(&head.height,sizeof(long),1,file)) fail=true;
if(!fail&&!::fwrite(&head.depth,sizeof(long),1,file)) fail=true;
if(!fail&&!::fwrite(&head.length,sizeof(long),1,file)) fail=true;
if(!fail&&!::fwrite(&head.type,sizeof(long),1,file)) fail=true;
if(!fail&&!::fwrite(&head.maptype,sizeof(long),1,file)) fail=true;
if(!fail&&!::fwrite(&head.maplength,sizeof(long),1,file)) fail=true;
if(!fail)                                                    // write colormap
  fail|=(::fwrite(red,sizeof(unsigned char),
                  nbColors,file)!=(unsigned int)nbColors);
if(!fail)
  fail|=(::fwrite(green,sizeof(unsigned char),
                  nbColors,file)!=(unsigned int)nbColors);
if(!fail)
  fail|=(::fwrite(blue,sizeof(unsigned char),
                  nbColors,file)!=(unsigned int)nbColors);
if(!fail)
  {                                                      // write image pixels
  unsigned int lineSize=width+width%2;
  unsigned char * line=(unsigned char *)malloc(lineSize*sizeof(unsigned char));
  ::memset(line,0,lineSize*sizeof(unsigned char));
  int x,y;
  for(y=0;!fail&&(y<height);y++)
    {
    for(x=0;x<width;x++) line[x]=points[y*width+x];
 // if(!::fwrite(line,sizeof(unsigned char),lineSize,file)==lineSize) AVANT..!
    if(!(::fwrite(line,sizeof(unsigned char),lineSize,file)==lineSize))
      fail=true;
    }
  free(line);
  }
return(!fail);
}

bool XGuiManager::readBMP(FILE * file,unsigned char * & red,
                                      unsigned char * & green,
                                      unsigned char * & blue,
                                      int & nbColors,
                                      unsigned long * & points,
                                      int & width,int & height)
{
struct
  {
  short type;          /*  File Type Identifier (4D42h)     */
  long  fileSize;      /*  Size of File                     */
  short reserved1;     /*  Reserved (should be 0)           */
  short reserved2;     /*  Reserved (should be 0)           */
  long  offset;        /*  Offset to bitmap data            */
  long  size;          /*  Size of Remianing Header         */
  long  width;         /*  Width of Bitmap in Points        */
  long  height;        /*  Height of Bitmap in Points       */
  short planes;        /*  Number of Planes                 */
  short bitCount;      /*  Bits Per Point                   */
  long  compression;   /*  Compression Scheme (0=none)      */
  long  sizeImage;     /*  Size of bitmap in bytes          */
  long  xPelsPerMeter; /*  Horz. Resolution in Points/Meter */
  long  yPelsPerMeter; /*  Vert. Resolution in Points/Meter */
  long  clrUsed;       /*  Number of Colors in Color Table  */
  long  clrImportant;  /*  Number of Important Colors       */
  } head;
bool fail=false;                                                // read header
if(!fail&&!::fread(&head.type,sizeof(short),1,file)) fail=true;
if(!fail&&!::fread(&head.fileSize,sizeof(long),1,file)) fail=true;
if(!fail&&!::fread(&head.reserved1,sizeof(short),1,file)) fail=true;
if(!fail&&!::fread(&head.reserved2,sizeof(short),1,file)) fail=true;
if(!fail&&!::fread(&head.offset,sizeof(long),1,file)) fail=true;
if(!fail&&!::fread(&head.size,sizeof(long),1,file)) fail=true;
if(!fail&&!::fread(&head.width,sizeof(long),1,file)) fail=true;
if(!fail&&!::fread(&head.height,sizeof(long),1,file)) fail=true;
if(!fail&&!::fread(&head.planes,sizeof(short),1,file)) fail=true;
if(!fail&&!::fread(&head.bitCount,sizeof(short),1,file)) fail=true;
if(!fail&&!::fread(&head.compression,sizeof(long),1,file)) fail=true;
if(!fail&&!::fread(&head.sizeImage,sizeof(long),1,file)) fail=true;
if(!fail&&!::fread(&head.xPelsPerMeter,sizeof(long),1,file)) fail=true;
if(!fail&&!::fread(&head.yPelsPerMeter,sizeof(long),1,file)) fail=true;
if(!fail&&!::fread(&head.clrUsed,sizeof(long),1,file)) fail=true;
if(!fail&&!::fread(&head.clrImportant,sizeof(long),1,file)) fail=true;
#ifndef __i386__
#ifndef __MSDOS__
_invertShort(head.type);
_invertLong(head.fileSize);
_invertShort(head.reserved1);
_invertShort(head.reserved2);
_invertLong(head.offset);
_invertLong(head.size);
_invertLong(head.width);
_invertLong(head.height);
_invertShort(head.planes);
_invertShort(head.bitCount);
_invertLong(head.compression);
_invertLong(head.sizeImage);
_invertLong(head.xPelsPerMeter);
_invertLong(head.yPelsPerMeter);
_invertLong(head.clrUsed);
_invertLong(head.clrImportant);
#endif
#endif
if(!fail)                                                   // check file type
  {
  if((head.type!=0x4D42)||    // magic number for BMP
     (head.compression!=0) || // not compressed
     ((head.bitCount!=1)&&    // 1 bit  : 2 colors
      (head.bitCount!=4)&&    // 4 bits : 16 colors
      (head.bitCount!=8)))    // 8 bits : 256 colors
    fail=true;
  }
if(!fail)                                            // check image properties
  {
  width=head.width;
  height=head.height;
  nbColors=head.clrUsed;
  if(!width||!height||!nbColors) fail=true;
  }
if(!fail)                                                   // allocate memory
  {
  unsigned int colorSize=nbColors*sizeof(unsigned char);
  red=(unsigned char *)malloc(colorSize);
  green=(unsigned char *)malloc(colorSize);
  blue=(unsigned char *)malloc(colorSize);
  points=(unsigned long *)malloc(width*height*sizeof(unsigned long));
  }
for(int col=0;!fail&&(col<nbColors);col++)                    // read colormap
  {
  unsigned char dummy;
  if(!::fread(blue+col,sizeof(unsigned char),1,file))
    {
    fail=true;
    break;
    }
  if(!::fread(green+col,sizeof(unsigned char),1,file))
    {
    fail=true;
    break;
    }
  if(!::fread(red+col,sizeof(unsigned char),1,file))
    {
    fail=true;
    break;
    }
  if(!::fread(&dummy,sizeof(unsigned char),1,file))
    {
    fail=true;
    break;
    }
  }
if(!fail)                                              // read unused colormap
  {
  unsigned char dummy;
  int nbDummy=head.offset-(54+4*head.clrUsed);
  while(!fail&&nbDummy--)
    if(!::fread(&dummy,sizeof(unsigned char),1,file))
      fail=true;
  }
if(!fail)                                                 // read image pixels
  {
  long lineSize=head.sizeImage/head.height;
  unsigned char * line=(unsigned char *)malloc(lineSize*sizeof(unsigned char));
  int x,y;
  for(y=height;!fail&&y--;)
    {
    if(::fread(line,sizeof(unsigned char),
               lineSize,file)!=(unsigned int)lineSize)
      {
      fail=true;
      break;
      }
    switch(head.bitCount)
      {
      case 1:
        for(x=0;x<width;x++)
          {
          switch(x%8)
            {
            case 0:
              points[y*width+x]=(line[x>>3]>>7)&0x01;
              break;
            case 1:
              points[y*width+x]=(line[x>>3]>>6)&0x01;
              break;
            case 2:
              points[y*width+x]=(line[x>>3]>>5)&0x01;
              break;
            case 3:
              points[y*width+x]=(line[x>>3]>>4)&0x01;
              break;
            case 4:
              points[y*width+x]=(line[x>>3]>>3)&0x01;
              break;
            case 5:
              points[y*width+x]=(line[x>>3]>>2)&0x01;
              break;
            case 6:
              points[y*width+x]=(line[x>>3]>>1)&0x01;
              break;
            case 7:
              points[y*width+x]=line[x>>3]&0x01;
              break;
            }
          }
        break;
      case 4:
        for(x=0;x<width;x++)
          {
          if(x%2)
            points[y*width+x]=line[x>>1]&0x0F;
          else
            points[y*width+x]=(line[x>>1]>>4)&0x0F;
          }
        break;
      case 8:
        for(x=0;x<width;x++)
          points[y*width+x]=line[x];
        break;
      }
    }
  free(line);
  }
return(!fail);
}

bool XGuiManager::writeBMP(FILE * file,const unsigned char * red,
                                       const unsigned char * green,
                                       const unsigned char * blue,
                                       int nbColors,
                                       const unsigned long * points,
                                       int width,int height)
{
struct
  {
  short type;          /*  File Type Identifier (4D42h)     */
  long  fileSize;      /*  Size of File                     */
  short reserved1;     /*  Reserved (should be 0)           */
  short reserved2;     /*  Reserved (should be 0)           */
  long  offset;        /*  Offset to bitmap data            */
  long  size;          /*  Size of Remianing Header         */
  long  width;         /*  Width of Bitmap in Points        */
  long  height;        /*  Height of Bitmap in Points       */
  short planes;        /*  Number of Planes                 */
  short bitCount;      /*  Bits Per Point                   */
  long  compression;   /*  Compression Scheme (0=none)      */
  long  sizeImage;     /*  Size of bitmap in bytes          */
  long  xPelsPerMeter; /*  Horz. Resolution in Points/Meter */
  long  yPelsPerMeter; /*  Vert. Resolution in Points/Meter */
  long  clrUsed;       /*  Number of Colors in Color Table  */
  long  clrImportant;  /*  Number of Important Colors       */
  } head;
int nbBits=(nbColors>256 ? 24 : (nbColors>16 ? 8 : (nbColors>2 ? 4 : 1)));
long lineSize=width*nbBits;
if(lineSize%32)
  lineSize=4*(1+lineSize/32);
else
  lineSize/=8;
head.type=0x4D42;                               // magic number for BMP
head.reserved1=0;
head.reserved2=0;
head.offset=54+(nbBits==24 ? 0 : (1<<(nbBits+2)));
head.size=40;
head.width=width;
head.height=height;
head.planes=1;
head.bitCount=nbBits;
head.compression=0;
head.sizeImage=lineSize*height;
head.xPelsPerMeter=2925;
head.yPelsPerMeter=2925;
head.clrUsed=(nbBits==24 ? 0 : nbColors);
head.clrImportant=head.clrUsed;
head.fileSize=head.offset+head.sizeImage;
int nbDummy=head.offset-(54+4*head.clrUsed);
bool fail=false;                                               // write header
#ifndef __i386__
#ifndef __MSDOS__
_invertShort(head.type);
_invertLong(head.fileSize);
_invertShort(head.reserved1);
_invertShort(head.reserved2);
_invertLong(head.offset);
_invertLong(head.size);
_invertLong(head.width);
_invertLong(head.height);
_invertShort(head.planes);
_invertShort(head.bitCount);
_invertLong(head.compression);
_invertLong(head.sizeImage);
_invertLong(head.xPelsPerMeter);
_invertLong(head.yPelsPerMeter);
_invertLong(head.clrUsed);
_invertLong(head.clrImportant);
#endif
#endif
if(!fail&&!::fwrite(&head.type,sizeof(short),1,file)) fail=true;
if(!fail&&!::fwrite(&head.fileSize,sizeof(long),1,file)) fail=true;
if(!fail&&!::fwrite(&head.reserved1,sizeof(short),1,file)) fail=true;
if(!fail&&!::fwrite(&head.reserved2,sizeof(short),1,file)) fail=true;
if(!fail&&!::fwrite(&head.offset,sizeof(long),1,file)) fail=true;
if(!fail&&!::fwrite(&head.size,sizeof(long),1,file)) fail=true;
if(!fail&&!::fwrite(&head.width,sizeof(long),1,file)) fail=true;
if(!fail&&!::fwrite(&head.height,sizeof(long),1,file)) fail=true;
if(!fail&&!::fwrite(&head.planes,sizeof(short),1,file)) fail=true;
if(!fail&&!::fwrite(&head.bitCount,sizeof(short),1,file)) fail=true;
if(!fail&&!::fwrite(&head.compression,sizeof(long),1,file)) fail=true;
if(!fail&&!::fwrite(&head.sizeImage,sizeof(long),1,file)) fail=true;
if(!fail&&!::fwrite(&head.xPelsPerMeter,sizeof(long),1,file)) fail=true;
if(!fail&&!::fwrite(&head.yPelsPerMeter,sizeof(long),1,file)) fail=true;
if(!fail&&!::fwrite(&head.clrUsed,sizeof(long),1,file)) fail=true;
if(!fail&&!::fwrite(&head.clrImportant,sizeof(long),1,file)) fail=true;
if(nbBits!=24)                                               // write colormap
  {
  for(int col=0;!fail&&(col<nbColors);col++)
    {
    unsigned char dummy=0;
    if(!::fwrite(blue+col,sizeof(unsigned char),1,file))
      {
      fail=true;
      break;
      }
    if(!::fwrite(green+col,sizeof(unsigned char),1,file))
      {
      fail=true;
      break;
      }
    if(!::fwrite(red+col,sizeof(unsigned char),1,file))
      {
      fail=true;
      break;
      }
    if(!::fwrite(&dummy,sizeof(unsigned char),1,file))
      {
      fail=true;
      break;
      }
    }
  if(!fail)                                           // write unused colormap
    {
    unsigned char dummy=0;
    while(!fail&&nbDummy--)
      if(!::fwrite(&dummy,sizeof(unsigned char),1,file))
        fail=true;
    }
  }
if(!fail)                                                // write image pixels
  {
  unsigned char * line=(unsigned char *)malloc(lineSize*sizeof(unsigned char));
  ::memset(line,0,lineSize*sizeof(unsigned char));
  int x,y,col;
  for(y=height;!fail&&y--;)
    {
    switch(nbBits)
      {
      case 1:
        for(x=0;x<width;x++)
          {
          switch(x%8)
            {
            case 0:
              line[x>>3]=points[y*width+x]<<7;
              break;
            case 1:
              line[x>>3]|=points[y*width+x]<<6;
              break;
            case 2:
              line[x>>3]|=points[y*width+x]<<5;
              break;
            case 3:
              line[x>>3]|=points[y*width+x]<<4;
              break;
            case 4:
              line[x>>3]|=points[y*width+x]<<3;
              break;
            case 5:
              line[x>>3]|=points[y*width+x]<<2;
              break;
            case 6:
              line[x>>3]|=points[y*width+x]<<1;
              break;
            case 7:
              line[x>>3]|=points[y*width+x];
              break;
            }
          }
        break;
      case 4:
        for(x=0;x<width;x++)
          {
          if(x%2)
            line[x>>1]|=points[y*width+x];
          else
            line[x>>1]=points[y*width+x]<<4;
          }
        break;
      case 8:
        for(x=0;x<width;x++)
          line[x]=points[y*width+x];
        break;
      case 24:
        for(x=0;x<width;x++)
          {
          col=points[y*width+x];
          line[3*x]=blue[col];
          line[1+3*x]=green[col];
          line[2+3*x]=red[col];
          }
        break;
      }
    if(::fwrite(line,sizeof(unsigned char),
               lineSize,file)!=(unsigned int)lineSize)
      fail=true;
    }
  free(line);
  }
return(!fail);
}

void XGuiManager::setTask(void (*task)(void *),void * data)
{
if(_task&&!task) XtRemoveTimeOut(_timerId);
else if(task&&!_task)
  {
  _timerId=XtAppAddTimeOut(_appContext,0,
                           XGuiManager::_timerProc,(XtPointer)0);
  }
_task=task;
_taskData=data;
}

void XGuiManager::loopProc(void * /* data */) // static
{
XEvent evt;
XtAppNextEvent(_xGuiManager->_appContext,&evt);
XtDispatchEvent(&evt);
}

void XGuiManager::mainLoop(void (*loopProc)(void *),void * data)
{
_running=true;
if(loopProc)
  {
  _loopProc=loopProc;
  while(_running)
    {
    (*_loopProc)(data);
    }
  }
else
  {
  if(!setjmp(XGuiManager::_mainLoopBuffer))
    {
    XtAppMainLoop(_appContext);
    }
  }
_running=false;
}

void XGuiManager::exitMainLoop(void)
{
if(_running)
  {
  _running=false;
  if(!_loopProc) longjmp(XGuiManager::_mainLoopBuffer,1);
  }
}

//-------- Private methods -------------------------------------------------//
void XGuiManager::_init(void)
{
XSetCloseDownMode(_display,DestroyAll);
_screen=DefaultScreen(_display);
_depth=DefaultDepth(_display,_screen);
_root=DefaultRootWindow(_display);
XSelectInput(_display,_root,PropertyChangeMask | ButtonReleaseMask);
chooseFont();
_charHeight=_font->ascent+_font->descent;
_clickTime=XtGetMultiClickTime(_display); // default : 200 ms
_colormap=DefaultColormap(_display,_screen);
allocNamedColor("grey0",_foreground);
allocNamedColor("grey70",_background);
allocNamedColor("grey76",_highlight);
allocNamedColor("grey96",_lightside);
allocNamedColor("grey38",_darkside);
XGCValues gcValues;
gcValues.font=_font->fid;
gcValues.graphics_exposures=false;
gcValues.foreground=_foreground;
gcValues.background=_background;
_gc=XCreateGC(_display,_root,
              GCFont | GCGraphicsExposures | GCForeground | GCBackground,
              &gcValues);
gcValues.foreground=_foreground^_lightside;
gcValues.background=_foreground^_lightside;
gcValues.plane_mask=_foreground^_lightside;
gcValues.function=GXxor;
_xorGc=XCreateGC(_display,_root,
                 GCFont | GCGraphicsExposures | GCForeground | GCBackground |
                 GCPlaneMask | GCFunction,&gcValues);
_cursorMove=XCreateFontCursor(_display,XC_icon);
_cursorZoom=XCreateFontCursor(_display,XC_sb_v_double_arrow);
_cursorZoomXY=XCreateFontCursor(_display,XC_fleur);
_cursorRoll=XCreateFontCursor(_display,XC_exchange);
#ifdef OPEN_GL
if(!XGuiViewer3D::createGlobalContext())
  {
  cerr << "X Server does not support OpenGL" << endl;
  _fail=true;
  }
#endif
if(!_fail)
  {
  XtEventDispatchProc proc;
  for(int eventType=0;eventType<LASTEvent;eventType++)
    {
    proc=XtSetEventDispatcher(_display,eventType,XGuiManager::_dispatchProc);
    XGuiManager::_oldDispatchProc[eventType]=proc;
    }
  }
}

Boolean XGuiManager::_dispatchProc(XEvent * event) // static
{
bool used=false;
if(getXGuiManager()->_exclusive.getSize())
  {
  if(getXGuiManager()->_exclusive.accessBack()->dispatchEvent(*event))
    used=true;
  else
    {
    switch(event->type)
      {
      case ButtonPress:
      case KeyPress:
        getXGuiManager()->bell();
        break;
      case SelectionNotify:
      case Expose:
      case LeaveNotify:
      case ConfigureNotify:
        {
        for(int i=getXGuiManager()->_elems.getSize();i--;)
          {
          if(getXGuiManager()->_elems[i]->dispatchEvent(*event))
            {
            used=true;
            break;
            }
          }
        }
        break;
      }
    }
  }
else
  {
  for(int i=getXGuiManager()->_elems.getSize();i--;)
    {
    if(getXGuiManager()->_elems[i]->dispatchEvent(*event))
      {
      used=true;
      break;
      }
    }
  }
switch(event->type)
  {
  case SelectionClear:
    getXGuiManager()->selectionClear();
    break;
  case SelectionRequest:
    getXGuiManager()->selectionRequest(event->xselectionrequest);
    break;
  case ButtonRelease:
    getXGuiManager()->usingMenu((XGuiMenu *)0);
    break;
  }
#ifdef OPEN_GL
XGuiViewer3D::drawAll();
#endif
XGuiViewer2D::drawAll();
XGuiGrapher::drawAll();
return(used ? true : (*XGuiManager::_oldDispatchProc[event->type])(event));
}

void XGuiManager::_timerProc(XtPointer,XtIntervalId *) // static
{
(*getXGuiManager()->_task)(getXGuiManager()->_taskData);
#ifdef OPEN_GL
XGuiViewer3D::drawAll();
#endif
XGuiViewer2D::drawAll();
XGuiGrapher::drawAll();
XSync(getXGuiManager()->getDisplay(),false);
if(getXGuiManager()->_task)
  {
  if(XPending(getXGuiManager()->_display))
    {
    getXGuiManager()->_timerId=XtAppAddTimeOut(getXGuiManager()->_appContext,
                                               2, // time to proceed
                                               XGuiManager::_timerProc,
                                               (XtPointer)0);
    }
  else
    {
    getXGuiManager()->_timerId=XtAppAddTimeOut(getXGuiManager()->_appContext,
                                               0,
                                               XGuiManager::_timerProc,
                                               (XtPointer)0);
    }
  }
}

void XGuiManager::_invertShort(short & s) // static
{
unsigned char * ptr=(unsigned char *)&s;
unsigned char tmp=ptr[0];
ptr[0]=ptr[1];
ptr[1]=tmp;
}

void XGuiManager::_invertLong(long & l) // static
{
unsigned char * ptr=(unsigned char *)&l;
unsigned char tmp=ptr[0];
ptr[0]=ptr[3];
ptr[3]=tmp;
tmp=ptr[1];
ptr[1]=ptr[2];
ptr[2]=tmp;
}

#endif // X_GUI

