#ifndef XGTABGRP_H
#define XGTABGRP_H

#include "XGui/xgElem.h"

//--------------------------------------------------------------------------//
// class XGuiTabGroup                                                       //
//--------------------------------------------------------------------------//

class XGuiArea;

class XGuiTabGroup : public XGuiElement
{
public:
// Allocators
  XGuiTabGroup(XGuiArea * parent);
  virtual ~XGuiTabGroup(void);
// Inspectors
  int getCurrentTab(void) const;
  int getNbTabs(void) const;
  const Strings & getTab(int pos) const;
// Modifiers
  void setCurrentTab(int pos,bool propagate=true);
  virtual void setWidth(int width);
  virtual void setHeight(int height);
  virtual void show(void);
  virtual void hide(void);
//---- Specific ----
// Allocators
// Inspectors
  virtual XGuiElement::Type getElemType(void) const;
  virtual bool isA(XGuiElement::Type type) const;
// Modifiers
  virtual void addElement(XGuiElement * element);
  virtual void removeElement(XGuiElement * element);
  virtual bool dispatchEvent(const XEvent & event);
  virtual void processEvent(const XEvent & event);
  virtual void redraw(void);
protected:
  friend class XGuiTab;
  void _buildHeader(void);
  void _destroyHeader();
// Attributes
  int _xOffset;
  int _yOffset;
  typedef struct
    {
    int width;
    Window window;
    } TabInfo;
  SimpleVector<TabInfo *> _tabs;
  int _current;
  int _inside;
};

#endif // XGTABGRP_H

