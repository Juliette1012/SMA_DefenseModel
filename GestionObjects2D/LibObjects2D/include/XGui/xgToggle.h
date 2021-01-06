#ifndef XGTOGGLE_H
#define XGTOGGLE_H

#include "XGui/xgElem.h"

//--------------------------------------------------------------------------//
// class XGuiToggle                                                         //
//--------------------------------------------------------------------------//

class XGuiArea;

class XGuiToggle : public XGuiElement
{
public:
// Allocators
  XGuiToggle(XGuiArea * parent,const Strings & title,bool big=false);
  virtual ~XGuiToggle(void);
// Inspectors
  bool isPressed(void) const;
// Modifiers
  void setPressed(bool isPressed,bool propagate=true);
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
  friend class XGuiToggleGroup;
  XGuiToggle(XGuiElement * parent, // used by XGuiToggleGroup
             const Strings & title,bool big=false);
// Attributes
  int _textX;
  int _textY;
  int _textWidth;
  int _textHeight;
  bool _pressed;
  bool _inside;
  bool _big;
};

#endif // XGTOGGLE_H

