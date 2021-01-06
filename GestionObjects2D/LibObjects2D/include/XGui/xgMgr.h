#ifndef XGMGR_H
#define XGMGR_H

#include <iostream>
#include <stdio.h>
#include <setjmp.h>

#include <X11/Intrinsic.h>

#include "XGui/xgElem.h"

//--------------------------------------------------------------------------//
// class XGuiManager                                                        //
//--------------------------------------------------------------------------//

class XGuiManager
{
public:
  inline friend XGuiManager * getXGuiManager(void);
// Allocators
  XGuiManager(void);
  virtual ~XGuiManager(void);
// Inspectors
  inline bool fail(void) const;
  inline bool isShowing(void) const;
  int getTextWidth(const Strings & text) const;
  inline int getCharHeight(void) const;
  inline int getScreenWidth(void) const;
  inline int getScreenHeight(void) const;
  inline int getMargin(void) const;
  inline void getTask(void (* & task)(void *),void * & data) const;
// Modifiers
  void bell(void);
  void show(void);
  void hide(void);
  void setTask(void (*task)(void *),void * data);
  static void loopProc(void * data);
  void mainLoop(void (*loopProc)(void *)=(void (*)(void *))0,
                void * data=(void *)0);
  void exitMainLoop(void);
//---- Specific ---
// Allocators
  XGuiManager(Display * display,XtAppContext appContext);
// Inspectors
  inline Display * getDisplay(void) const;
  inline XtAppContext getContext(void) const;
  inline int getScreen(void) const;
  inline int getDepth(void) const;
  inline Window getRoot(void) const;
  inline XFontStruct * getFont(void) const;
  int getTextPosition(const Strings & text,int x) const;
  inline int getClickTime(void) const;
  inline GC getGC(void) const;
  inline GC getXorGC(void) const;
  void queryColor(unsigned long pixel,unsigned short & r,
                  unsigned short & g,unsigned short & b) const;
  inline unsigned long getForeground(void) const;
  inline unsigned long getBackground(void) const;
  inline unsigned long getHighlight(void) const;
  inline unsigned long getLightside(void) const;
  inline unsigned long getDarkside(void) const;
  Window getNewWindow(Window parent,int x,int y,int width,int height) const;
  Pixmap getNewPixmap(Window parent,int width,int height) const;
  void getRootPosition(Window win,int & x,int & y) const;
  inline const Strings & getSelectedText(void) const;
  inline bool isExclusive(void) const;
// Modifiers
  inline void setDefaultCursor(Window win);
  inline void setMoveCursor(Window win);
  inline void setZoomCursor(Window win);
  inline void setZoomXYCursor(Window win);
  inline void setRollCursor(Window win);
  bool allocNamedColor(const Strings & name,unsigned long & pixel);
  bool allocColor(int r,int g,int b,unsigned long & pixel);
  void freeColor(unsigned long pixel);
  inline void chooseColor(unsigned long pixel);
  void drawText(Drawable draw,int x,int y,const Strings & text);
  void drawCursor(Drawable draw,bool inside,int x,int y,char c);
  void drawSelection(Drawable draw,int x,int y,
                     const Strings & text,int start,int len);
  void background(Drawable draw,int x,int y,int width,int height);
  void highlight(Drawable draw,int x,int y,int width,int height);
  void drawBorderUp(Drawable draw,int x,int y,int width,int height);
  void drawBorderDown(Drawable draw,int x,int y,int width,int height);
  void drawBorderLineUp(Drawable draw,int x,int y,int width,int height);
  void drawBorderLineDown(Drawable draw,int x,int y,int width,int height);
  void drawHLineUp(Drawable draw,int x,int y,int width);
  void drawHLineDown(Drawable draw,int x,int y,int width);
  void drawVLineUp(Drawable draw,int x,int y,int height);
  void drawVLineDown(Drawable draw,int x,int y,int height);
  void exclusiveWaitEvent(XGuiElement * target);
  void selectionClear(void);
  void setSelectionOwner(Window owner,const Strings & text);
  void convertSelection(Window requestor);
  void selectionRequest(const XSelectionRequestEvent & evt);
  void selectionNotify(const XSelectionEvent & evt);
  void usingMenu(XGuiMenu * menu);
  void addElement(XGuiElement * element);
  void removeElement(XGuiElement * element);
  void chooseFont(void);
  bool dumpWindow(Window win,unsigned char * & red,
                             unsigned char * & green,
                             unsigned char * & blue,
                             int & nbColors,
                             unsigned long * & points,
                             int & width,int & height);
  bool readRAS(FILE * file,unsigned char * & red,
                           unsigned char * & green,
                           unsigned char * & blue,
                           int & nbColors,
                           unsigned long * & points,
                           int & width,int & height);
  bool writeRAS(FILE * file,const unsigned char * red,
                            const unsigned char * green,
                            const unsigned char * blue,
                            int nbColors,
                            const unsigned long * points,
                            int width,int height);
  bool readBMP(FILE * file,unsigned char * & red,
                           unsigned char * & green,
                           unsigned char * & blue,
                           int & nbColors,
                           unsigned long * & points,
                           int & width,int & height);
  bool writeBMP(FILE * file,const unsigned char * red,
                            const unsigned char * green,
                            const unsigned char * blue,
                            int nbColors,
                            const unsigned long * points,
                            int width,int height);
protected:
  void _init(void);
  static Boolean _dispatchProc(XEvent * event);
  static void _timerProc(XtPointer,XtIntervalId *);
  static void _invertShort(short & s);
  static void _invertLong(long & l);
// Attributes
  XGuiElemVect _elems;
  bool _showing;
  bool _fail;
  Display * _display;
  XtAppContext _appContext;
  bool _selfBuilt;
  int _screen;
  int _depth;
  Window _root;
  XFontStruct * _font;
  int _charHeight;
  int _clickTime;
  GC _gc, _xorGc;
  Colormap _colormap;
  unsigned long _foreground;
  unsigned long _background;
  unsigned long _highlight;
  unsigned long _lightside;
  unsigned long _darkside;
  Cursor _cursorMove;
  Cursor _cursorZoom;
  Cursor _cursorZoomXY;
  Cursor _cursorRoll;
  XGuiElemVect _exclusive;
  Strings _selectedText;
  bool _running;
  void (*_loopProc)(void *);
  void (*_task)(void *);
  void * _taskData;
  XtIntervalId _timerId;
  static jmp_buf _mainLoopBuffer;
  static XGuiManager * _xGuiManager;
  static XtEventDispatchProc _oldDispatchProc[LASTEvent];
};

#include "XGui/xgMgr.Ci"

#endif // XGMGR_H

