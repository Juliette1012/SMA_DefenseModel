#ifndef XGLABEL_H
#define XGLABEL_H

#include "XGui/xgElem.h"

//--------------------------------------------------------------------------//
// class XGuiLabel                                                          //
//--------------------------------------------------------------------------//

class XGuiArea;

class XGuiLabel : public XGuiElement
{
public:
// Allocators
  XGuiLabel(XGuiArea * parent,const Strings & title,
            bool editable=false,bool deep=false);
  virtual ~XGuiLabel(void);
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
  virtual void usingSelection(Window owner);
  virtual bool dispatchEvent(const XEvent & event);
  virtual void processEvent(const XEvent & event);
  bool goLeft(void);
  bool goRight(void);
  bool goStart(void);
  bool goEnd(void);
  void addChar(char c);
  void addSelection(void);
  void delChar(void);
  void delSelection(void);
  virtual void redraw(void);
protected:
// Attributes
  Window _textWindow;
  bool _deep;
  bool _editable;
  int _textX;
  int _textY;
  int _textWidth;
  int _textHeight;
  bool _selectMouse;
  bool _selectKey;
  int _startSel;
  int _endSel;
  bool _inside;
  int _pos;
  int _offset;
  Pixmap _textPixmap;
  Pixmap _pixmap;
};

#endif // XGLABEL_H

