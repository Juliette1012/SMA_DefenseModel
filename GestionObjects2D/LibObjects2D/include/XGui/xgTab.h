#ifndef XGTAB_H
#define XGTAB_H

#include "XGui/xgArea.h"

//--------------------------------------------------------------------------//
// class XGuiTab                                                            //
//--------------------------------------------------------------------------//

class XGuiTabGroup;

class XGuiTab : public XGuiArea
{
public:
// Allocators
  XGuiTab(XGuiTabGroup * parent,const Strings & title);
  virtual ~XGuiTab(void);
// Inspectors
  virtual int getX(void) const;
  virtual int getY(void) const;
  virtual int getWidth(void) const;
  virtual int getHeight(void) const;
  virtual int getInWidth(void) const;
  virtual int getInHeight(void) const;
// Modifiers
  virtual void setX(int x);
  virtual void setY(int y);
  virtual void setWidth(int width);
  virtual void setHeight(int height);
  virtual void setInWidth(int inWidth);
  virtual void setInHeight(int inHeight);
  virtual void setTitle(const Strings & title);
  virtual void show(void);
//---- Specific ----
// Allocators
// Inspectors
  virtual XGuiElement::Type getElemType(void) const;
  virtual bool isA(XGuiElement::Type type) const;
// Modifiers
  virtual void processEvent(const XEvent &);
  virtual void redraw(void);
};

#endif // XGTAB_H

