#ifndef XGTGLGRP_H
#define XGTGLGRP_H

#include "XGui/xgElem.h"

//--------------------------------------------------------------------------//
// class XGuiToggleGroup                                                    //
//--------------------------------------------------------------------------//

class XGuiToggle;
class XGuiArea;

class XGuiToggleGroup : public XGuiElement
{
public:
// Allocators
  XGuiToggleGroup(XGuiArea * parent,const StringsVect & entries,
                  bool horizontal=false,bool big=false);
  virtual ~XGuiToggleGroup(void);
// Inspectors
  int getResult(void) const;
  int getNbEntries(void) const;
  const Strings & getEntry(int pos) const;
// Modifiers
  void setActiveEntry(int pos,bool propagate=true);
  virtual void setWidth(int width);
  virtual void setHeight(int height);
  virtual void show(void);
//---- Specific ----
// Allocators
// Inspectors
  virtual XGuiElement::Type getElemType(void) const;
  virtual bool isA(XGuiElement::Type type) const;
// Modifiers
  void setActiveToggle(XGuiToggle * toggle,bool propagate=true);
  virtual void processEvent(const XEvent & event);
  virtual void redraw(void);
protected:
  static void _toggleCB(XGuiElement * calling,void * data);
// Attributes
  bool _horizontal;
};

#endif // XGTGLGRP_H

