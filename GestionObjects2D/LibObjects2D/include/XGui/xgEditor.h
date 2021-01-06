#ifndef XGEDITOR_H
#define XGEDITOR_H

#include "XGui/xgElem.h"
#include "Utility/stlUtil.h"

//--------------------------------------------------------------------------//
// class XGuiEditor                                                         //
//--------------------------------------------------------------------------//

class XGuiScroller;
class XGuiArea;

class XGuiEditor : public XGuiElement
{
public:
// Allocators
  XGuiEditor(XGuiArea * parent,const Strings & content,bool readOnly=false);
  virtual ~XGuiEditor(void);
// Inspectors
  virtual Strings getContent(void) const;
// Modifiers
  virtual void setWidth(int width);
  virtual void setHeight(int height);
  virtual void setContent(const Strings & content);
  virtual void show(void);
  virtual void hide(void);
//---- Specific ----
// Allocators
// Inspectors
  virtual XGuiElement::Type getElemType(void) const;
  virtual bool isA(XGuiElement::Type type) const;
// Modifiers
  virtual bool dispatchEvent(const XEvent & event);
  virtual void usingSelection(Window owner);
  virtual void processEvent(const XEvent & event);
  bool goLeft(void);
  bool goRight(void);
  bool goStart(void);
  bool goEnd(void);
  bool goUp(int step=1);
  bool goDown(int step=1);
  bool goTop(void);
  bool goBottom(void);
  void addChar(char c);
  void addText(const Strings & text);
  void delChar(void);
  void delSelection(void);
  virtual void redraw(void);
protected:
  void _getSelectPos(int & x1,int & y1,int & x2,int & y2);
  void _drawSelection(void);
  void _hideSelection(void);
  void _drawLine(int line);
  void _computeSize(void);
  void _adjustSize(void);
  void _adjustScrollHRatio(void);
  void _adjustScrollHValue(void);
  void _adjustScrollVRatio(void);
  void _adjustScrollVValue(void);
  static void _scrollHCB(XGuiElement * calling,void * data);
  static void _scrollVCB(XGuiElement * calling,void * data);
// Attributes
  Window _textWindow;
  int _textX;
  int _textY;
  int _textWidth;
  int _textHeight;
  Pixmap _pixmap;
  int _pixWidth;
  int _pixHeight;
  bool _editable;
  class EditorLine : public StlPair<Strings,int>
    {
    public:
    inline EditorLine(void)
            : StlPair<Strings,int>() {}
    inline EditorLine(const Strings & s,int i)
            : StlPair<Strings,int>(s,i) {}
    inline virtual ~EditorLine(void) {}
    };
  SimpleVector<EditorLine *> _lines;
  int _maxLine;
  int _totalHeight;
  int _spaceWidth;
  XGuiScroller * _scrollH;
  XGuiScroller * _scrollV;
  bool _inside;
  bool _showPos;
  bool _exposure;
  int _posX;
  int _posY;
  int _offsetX;
  int _offsetY;
  bool _selectMouse;
  bool _selectKey;
  int _startSelX;
  int _startSelY;
  int _endSelX;
  int _endSelY;
};

#endif // XGEDITOR_H

