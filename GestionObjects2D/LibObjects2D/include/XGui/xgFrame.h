#ifndef XGFRAME_H
#define XGFRAME_H

#include "XGui/xgArea.h"

//--------------------------------------------------------------------------//
// class XGuiFrame                                                          //
//--------------------------------------------------------------------------//

class XGuiLabel;

class XGuiFrame : public XGuiArea
{
public:
// Allocators
  XGuiFrame(XGuiArea * parent,const Strings & title);
  virtual ~XGuiFrame(void);
// Inspectors
  virtual int getInWidth(void) const;
  virtual int getInHeight(void) const;
// Modifiers
  virtual void setWidth(int width);
  virtual void setHeight(int height);
  virtual void setTitle(const Strings & title);
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
// Attributes
protected:
  XGuiLabel * _titleLabel;
  Window _inWindow;
};

#endif // XGFRAME_H

