#ifndef XGLIST_H
#define XGLIST_H

#include "XGui/xgElem.h"

//--------------------------------------------------------------------------//
// class XGuiList                                                           //
//--------------------------------------------------------------------------//

class XGuiScroller;
class XGuiArea;

class XGuiList : public XGuiElement
{
public:
// Allocators
  XGuiList(XGuiArea * parent,const StringsVect & entries);
  virtual ~XGuiList(void);
// Inspectors
  int getResult(void) const;
  int getNbEntries(void) const;
  const Strings & getEntry(int pos) const;
  bool isEntered(void) const;
// Modifiers
  void setEntries(const StringsVect & entries);
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
  virtual void processEvent(const XEvent & event);
  virtual void redraw(void);
protected:
  void _buildPixmap(void);
  bool _showResult(void);
  void _keyUp(void);
  void _keyDown(void);
  static void _scrollCB(XGuiElement * calling,void * data);
// Attributes
  StringsVect _entries;
  int _result;
  Time _lastTime;
  bool _isEntered;
  Pixmap _textPixmap;
  int _textX;
  int _textY;
  int _textWidth;
  int _textHeight;
  int _totalHeight;
  int _offset;
  XGuiScroller * _scroll;
  Pixmap _pixmap;
};

#endif // XGLIST_H

