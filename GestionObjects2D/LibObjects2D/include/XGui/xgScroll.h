#ifndef XGSCROLL_H
#define XGSCROLL_H

#include "XGui/xgElem.h"

//--------------------------------------------------------------------------//
// class XGuiScroller                                                       //
//--------------------------------------------------------------------------//

class XGuiArea;

class XGuiScroller : public XGuiElement
{
public:
// Allocators
  XGuiScroller(XGuiArea * parent,bool horizontal);
  virtual ~XGuiScroller(void);
// Inspectors
  double getValue(void) const;
  double getRatio(void) const;
// Modifiers
  virtual void setWidth(int width);
  virtual void setHeight(int height);
  void setValue(double value,bool propagate=true);
  void setRatio(double ratio,bool propagate=true);
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
  friend class XGuiList;
  friend class XGuiEditor;
  XGuiScroller(XGuiElement * parent, // used by XGuiList and XGuiEditor
               bool horizontal);
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

#endif // XGSCROLL_H

