#ifndef XGVSCARE_H
#define XGVSCARE_H

#include "XGui/xgArea.h"

//--------------------------------------------------------------------------//
// class XGuiVScrolledArea                                                  //
//--------------------------------------------------------------------------//

class XGuiScroller;

class XGuiVScrolledArea : public XGuiArea
{
public:
// Allocators
  XGuiVScrolledArea(XGuiArea * parent);
  virtual ~XGuiVScrolledArea(void);
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
  static void _moveVCB(XGuiElement *,void * data);
// Attributes
  Window _screenWindow;
  Window _inWindow;
  int _inHeight;
  XGuiScroller * _scrollV;
};

#endif // XGVSCARE_H

