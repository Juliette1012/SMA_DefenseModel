#ifndef XGOPTMNU_H
#define XGOPTMNU_H

#include "XGui/xgElem.h"

//--------------------------------------------------------------------------//
// class XGuiOptionMenu                                                     //
//--------------------------------------------------------------------------//

class XGuiArea;

class XGuiOptionMenu : public XGuiElement
{
public:
// Allocators
  XGuiOptionMenu(XGuiArea * parent,const StringsVect & entries);
  virtual ~XGuiOptionMenu(void);
// Inspectors
  int getResult(void) const;
  int getNbEntries(void) const;
  const Strings & getEntry(int pos) const;
// Modifiers
  void setActiveEntry(int pos,bool propagate=true);
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
  virtual void addElement(XGuiElement * element);
  virtual void removeElement(XGuiElement * element);
  virtual void usingMenu(XGuiMenu * menu);
  virtual bool dispatchEvent(const XEvent & event);
  virtual void processEvent(const XEvent & event);
  virtual void redraw(void);
protected:
  static void _itemCB(XGuiElement * calling,void * data);
// Attributes
  StringsVect _entries;
  int _result;
  int _textX;
  int _textY;
  int _textWidth;
  int _textHeight;
  bool _inside;
  XGuiMenu * _menu;
};

#endif // XGOPTMNU_H

