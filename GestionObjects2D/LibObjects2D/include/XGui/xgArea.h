#ifndef XGAREA_H
#define XGAREA_H

#include "XGui/xgElem.h"

//--------------------------------------------------------------------------//
// class XGuiArea                                                           //
//--------------------------------------------------------------------------//

class XGuiTabGroup;

class XGuiArea : public XGuiElement
{
public:
// Allocators
  XGuiArea(XGuiArea * parent=(XGuiArea *)0);
  virtual ~XGuiArea(void);
// Inspectors
  unsigned long getWindowID(void) const;
  virtual int getInWidth(void) const;
  virtual int getInHeight(void) const;
// Modifiers
  virtual void setWidth(int width);
  virtual void setHeight(int height);
  virtual void setInWidth(int inWidth);
  virtual void setInHeight(int inHeight);
  virtual void show(void);
//---- Specific ----
// Allocators
protected:
  friend class XGuiTab;
  XGuiArea(XGuiTabGroup * parent);
public:
// Inspectors
  virtual XGuiElement::Type getElemType(void) const;
  virtual bool isA(XGuiElement::Type type) const;
  virtual Window getInWindow(void) const;
// Modifiers
  virtual bool dispatchEvent(const XEvent & event);
  virtual void processEvent(const XEvent & event);
  virtual void redraw(void);
  void adjustMenu(int width,int height);
};

#endif // XGAREA_H

