#ifndef XGMNUITM_H
#define XGMNUITM_H

#include "XGui/xgElem.h"

//--------------------------------------------------------------------------//
// class XGuiMenuItem                                                       //
//--------------------------------------------------------------------------//

class XGuiMenu;

class XGuiMenuItem : public XGuiElement
{
public:
// Allocators
  XGuiMenuItem(XGuiMenu * parent,const Strings & title);
  virtual ~XGuiMenuItem(void);
// Inspectors
// Modifiers
  virtual void setWidth(int width);
  virtual void setHeight(int height);
  virtual void setTitle(const Strings & title);
  virtual void show(void);
  virtual void hide(void);
//---- Specific ----
// Allocators
// Inspectors
  virtual XGuiElement::Type getElemType(void) const;
  virtual bool isA(XGuiElement::Type type) const;
// Modifiers
  void press(void);
  void relax(void);
  virtual void addElement(XGuiElement * element);
  virtual void removeElement(XGuiElement * element);
  virtual bool dispatchEvent(const XEvent & event);
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
  XGuiMenu * _menu;
};

#endif // XGMNUITM_H

