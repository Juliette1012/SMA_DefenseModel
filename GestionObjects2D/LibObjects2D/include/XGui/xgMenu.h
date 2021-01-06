#ifndef XGMENU_H
#define XGMENU_H

#include "XGui/xgElem.h"

//--------------------------------------------------------------------------//
// class XGuiMenu                                                           //
//--------------------------------------------------------------------------//

class XGuiMenuItem;
class XGuiArea;

class XGuiMenu : public XGuiElement
{
public:
// Allocators
  XGuiMenu(XGuiMenuItem * parent,bool horizontal=false);
  virtual ~XGuiMenu(void);
// Inspectors
// Modifiers
  virtual void setWidth(int width);
  virtual void setHeight(int height);
  virtual void show(void);
  virtual void hide(void);
//---- Specific ----
// Allocators
// Inspectors
  virtual XGuiElement::Type getElemType(void) const;
  virtual bool isA(XGuiElement::Type type) const;
  bool isHorizontal(void) const;
// Modifiers
  void setActiveItem(XGuiMenuItem * item);
  virtual void usingMenu(XGuiMenu * menu);
  virtual void addElement(XGuiElement * element);
  virtual void removeElement(XGuiElement * element);
  virtual void processEvent(const XEvent & event);
  virtual void redraw(void);
protected:
  friend class XGuiOptionMenu;
  XGuiMenu(XGuiElement * parent, // used by XGuiMenuBar and XGuiOptionMenu
           bool horizontal);
// Attributes
  bool _horizontal;
  XGuiMenuItem * _activeItem;
};

#endif // XGMENU_H

