#ifndef XGWIN_H
#define XGWIN_H

#include "XGui/xgArea.h"

//--------------------------------------------------------------------------//
// class XGuiWindow                                                         //
//--------------------------------------------------------------------------//

class XGuiWindow : public XGuiArea
{
public:
// Allocators
  XGuiWindow(const Strings & title);
  virtual ~XGuiWindow(void);
// Inspectors
  virtual int getInWidth(void) const;
  virtual int getInHeight(void) const;
// Modifiers
  virtual void setX(int x);
  virtual void setY(int y);
  virtual void setWidth(int width);
  virtual void setHeight(int height);
  virtual void setTitle(const Strings & title);
  virtual void setInWidth(int inWidth);
  virtual void setInHeight(int inHeight);
  void setCloseCallback(void (*callback)(XGuiElement *,void *),
                        void * data=(void *)0);
  virtual void show(void);
  virtual void hide(void);
//---- Specific ----
// Allocators
// Inspectors
  virtual XGuiElement::Type getElemType(void) const;
  virtual bool isA(XGuiElement::Type type) const;
  virtual Window getInWindow(void) const;
// Modifiers
  virtual void setMinSize(int minWidth,int minHeight);
  virtual void processEvent(const XEvent & event);
  virtual void redraw(void);
protected:
  void _computeDelta(void);
// Attributes
  Window _inWindow;
  bool _inWidthGiven;
  bool _inHeightGiven;
  void (*_closeCallback)(XGuiElement *,void *);
  void * _closeData;
  static bool _deltaComputed;
  static int _dx,_dy,_dw,_dh;
};

#endif // XGWIN_H

