#ifndef XGMNUSEP_H
#define XGMNUSEP_H

#include "XGui/xgElem.h"

//--------------------------------------------------------------------------//
// class XGuiMenuSepar                                                      //
//--------------------------------------------------------------------------//

class XGuiMenu;

class XGuiMenuSepar : public XGuiElement
{
public:
// Allocators
  XGuiMenuSepar(XGuiMenu * parent);
  virtual ~XGuiMenuSepar(void);
// Inspectors
// Modifiers
  virtual void setWidth(int width);
  virtual void setHeight(int height);
  virtual void show(void);
//---- Specific ----
// Allocators
// Inspectors
  virtual XGuiElement::Type getElemType(void) const;
  virtual bool isA(XGuiElement::Type type) const;
// Modifiers
  virtual void processEvent(const XEvent & event);
  virtual void redraw(void);
protected:
// Attributes
  bool _horizontal;
};

#endif // XGMNUSEP_H

