#ifndef XGHSCARE_H
#define XGHSCARE_H

#include "XGui/xgArea.h"

//--------------------------------------------------------------------------//
// class XGuiHScrolledArea                                                  //
//--------------------------------------------------------------------------//

class XGuiScroller;

class XGuiHScrolledArea : public XGuiArea
{
public:
// Allocators
  XGuiHScrolledArea(XGuiArea * parent);
  virtual ~XGuiHScrolledArea(void);
// Inspectors
  virtual int getInWidth(void) const;
  virtual int getInHeight(void) const;
// Modifiers
  virtual void setWidth(int width);
  virtual void setHeight(int height);
  virtual void setInWidth(int inWidth);
  virtual void setInHeight(int inHeight);
  virtual void show(void);
  virtual void hide(void);
//---- Specific ----
// Allocators
// Inspectors
  virtual XGuiElement::Type getElemType(void) const;
  virtual bool isA(XGuiElement::Type type) const;
  virtual Window getInWindow(void) const;
// Modifiers
  virtual void processEvent(const XEvent & event);
  virtual void redraw(void);
protected:
  void _adjustRatio(void);
  static void _moveHCB(XGuiElement *,void * data);
// Attributes
  Window _screenWindow;
  Window _inWindow;
  int _inWidth;
  XGuiScroller * _scrollH;
};

#endif // XGHSCARE_H

