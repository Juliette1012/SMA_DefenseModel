#ifndef XGMNUBAR_H
#define XGMNUBAR_H

#include "XGui/xgMenu.h"

//--------------------------------------------------------------------------//
// class XGuiMenuBar                                                        //
//--------------------------------------------------------------------------//

class XGuiArea;

class XGuiMenuBar : public XGuiMenu
{
public:
// Allocators
  XGuiMenuBar(XGuiArea * parent,bool horizontal=true,bool pushLast=true);
  virtual ~XGuiMenuBar(void);
// Inspectors
// Modifiers
  virtual void setWidth(int width);
  virtual void setHeight(int height);
//---- Specific ----
// Allocators
// Inspectors
  virtual XGuiElement::Type getElemType(void) const;
  virtual bool isA(XGuiElement::Type type) const;
// Modifiers
  virtual void addElement(XGuiElement * element);
  virtual void removeElement(XGuiElement * element);
protected:
// Attributes
  bool _pushLast;
};

#endif // XGMNUBAR_H

