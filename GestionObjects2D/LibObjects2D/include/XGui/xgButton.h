#ifndef XGBUTTON_H
#define XGBUTTON_H

#include "XGui/xgElem.h"

//--------------------------------------------------------------------------//
// class XGuiButton                                                         //
//--------------------------------------------------------------------------//

class XGuiArea;

class XGuiButton : public XGuiElement
{
public:
// Allocators
  XGuiButton(XGuiArea * parent,const Strings & title);
  virtual ~XGuiButton(void);
// Inspectors
// Modifiers
  virtual void setWidth(int width);
  virtual void setHeight(int height);
  virtual void setTitle(const Strings & title);
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
  int _textX;
  int _textY;
  int _textWidth;
  int _textHeight;
  bool _pressed;
  bool _inside;
};

#endif // XGBUTTON_H

