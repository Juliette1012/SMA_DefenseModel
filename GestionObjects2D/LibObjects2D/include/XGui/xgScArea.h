#ifndef XGSCAREA_H
#define XGSCAREA_H

#include "XGui/xgArea.h"

//--------------------------------------------------------------------------//
// class XGuiScrolledArea                                                   //
//--------------------------------------------------------------------------//

class XGuiScroller;

class XGuiScrolledArea : public XGuiArea
{
public:
// Allocators
  XGuiScrolledArea(XGuiArea * parent);
  virtual ~XGuiScrolledArea(void);
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
  static void _moveVCB(XGuiElement *,void * data);
// Attributes
  Window _screenWindow;
  Window _inWindow;
  int _inWidth;
  int _inHeight;
  XGuiScroller * _scrollH;
  XGuiScroller * _scrollV;
};

#endif // XGSCAREA_H

