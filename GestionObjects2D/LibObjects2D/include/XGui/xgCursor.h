#ifndef XGCURSOR_H
#define XGCURSOR_H

#include "XGui/xgElem.h"

//--------------------------------------------------------------------------//
// class XGuiCursor                                                         //
//--------------------------------------------------------------------------//

class XGuiArea;

class XGuiCursor : public XGuiElement
{
public:
// Allocators
  XGuiCursor(XGuiArea * parent,bool horizontal);
  virtual ~XGuiCursor(void);
// Inspectors
  double getValue(void) const;
// Modifiers
  virtual void setWidth(int width);
  virtual void setHeight(int height);
  void setValue(double value,bool propagate=true);
  virtual void show(void);
  virtual void hide(void);
//---- Specific ----
// Allocators
// Inspectors
  virtual XGuiElement::Type getElemType(void) const;
  virtual bool isA(XGuiElement::Type type) const;
  bool isHorizontal(void) const;
// Modifiers
  virtual void processEvent(const XEvent & event);
  virtual void redraw(void);
protected:
// Attributes
  bool _horizontal;
  double _value;
  double _ratio;
  int _cursorX;
  int _cursorY;
  int _cursorWidth;
  int _cursorHeight;
  unsigned int _pressed;
  int _offset;
  bool _inside;
  Pixmap _pixmap;
};

#endif // XGCURSOR_H

