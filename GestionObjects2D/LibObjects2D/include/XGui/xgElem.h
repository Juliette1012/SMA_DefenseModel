#ifndef XGELEM_H
#define XGELEM_H

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/cursorfont.h>
#include <X11/keysym.h>
#include <X11/Xutil.h>

#include "Utility/strings.h"

//--------------------------------------------------------------------------//
// class XGuiElement                                                        //
//--------------------------------------------------------------------------//

class XGuiElement;

typedef SimpleVector<XGuiElement *> XGuiElemVect;

class XGuiManager;
class XGuiMenu;

class XGuiElement
{
public:
// Allocators
  XGuiElement(int minWidth,int minHeight);
  virtual ~XGuiElement(void);
// Inspectors
  inline virtual int getX(void) const;
  inline virtual int getY(void) const;
  inline virtual int getWidth(void) const;
  inline virtual int getHeight(void) const;
  inline const Strings & getTitle(void) const;
  inline bool isVisible(void) const;
// Modifiers
  virtual void setX(int x);
  virtual void setY(int y);
  virtual void setWidth(int width);
  virtual void setHeight(int height);
  virtual void setTitle(const Strings & title);
  inline void setCallback(void (*callback)(XGuiElement *,void *),
                          void * data=(void *)0);
  inline void setDestroyCallback(void (*callback)(XGuiElement *,void *),
                                 void * data=(void *)0);
  virtual void show(void);
  virtual void hide(void);
  bool dump(const Strings & fileName);
//---- Specific ----
  enum Type {AREA, SCROLLED_AREA, SCROLLED_H_AREA, SCROLLED_V_AREA,
             COLOR_AREA, WINDOW, FRAME, TAB, TAB_GROUP,
             LABEL, BUTTON, TOGGLE, TOGGLE_GROUP,
             MENU_ITEM, MENU, MENU_BAR, MENU_SEPAR, OPTION_MENU,
             CURSOR, SCROLLER, LIST, EDITOR,
             VIEWER3D, VIEWER2D, GRAPHER};
// Allocators
// Inspectors
  virtual XGuiElement::Type getElemType(void) const=0;
  virtual bool isA(XGuiElement::Type type) const=0;
  inline const XGuiElement * getParent(void) const;
  inline Window getWindow(void) const;
  inline bool isMapped(void) const;
// Modifiers
  virtual void setMinSize(int minWidth,int minHeight);
  inline void setParent(XGuiElement * parent);
  inline XGuiElement * accessParent(void);
  void setMapped(bool mapped);
  virtual void addElement(XGuiElement * element);
  virtual void removeElement(XGuiElement * element);
  virtual bool dispatchEvent(const XEvent & event);
  virtual void processEvent(const XEvent & event)=0;
  virtual void usingMenu(XGuiMenu * menu);
  virtual void usingSelection(Window owner);
  virtual void redraw(void)=0;
protected:
// Attributes
  XGuiElement * _parent;
  XGuiElemVect _elems;
  void (*_callback)(XGuiElement *,void *);
  void * _data;
  void (*_destroyCallback)(XGuiElement *,void *);
  void * _destroyData;
  int _x;
  int _y;
  int _width;
  int _height;
  int _minWidth;
  int _minHeight;
  Strings _title;
  Window _window;
  bool _mapped;
};

#include "XGui/xgElem.Ci"

#endif // XGELEM_H

