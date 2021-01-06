#ifndef XGCOLCH_H
#define XGCOLCH_H

#include "XGui/xgWin.h"

//--------------------------------------------------------------------------//
// class XGuiColorChooser                                                   //
//--------------------------------------------------------------------------//

class XGuiLabel;
class XGuiFrame;
class XGuiCursor;
class XGuiColorArea;
class XGuiList;
class XGuiButton;

class XGuiColorChooser : public XGuiWindow
{
public:
// Allocators
  XGuiColorChooser(const Strings & title,const Strings & message);
  virtual ~XGuiColorChooser(void);
// Inspectors
  bool isEntered(void) const;
  bool isCanceled(void) const;
  const Strings & getColor(void) const;
// Modifiers
  bool ask(Strings & answer);
  void setInitColor(const Strings & color,bool propagate=true);
  virtual void show(void);
//---- Specific ----
// Allocators
// Inspectors
// Modifiers
protected:
  void _readDataBase(void);
  void _readRGB(int & r,int & g,int & b);
  void _setRGB(int r,int g,int b);
  static void _resizeCB(XGuiElement * calling,void * data);
  static void _closeCB(XGuiElement * calling,void * data);
  static void _cursorCB(XGuiElement * calling,void * data);
  static void _nameCB(XGuiElement * calling,void * data);
  static void _enterCB(XGuiElement * calling,void * data);
  static void _cancelCB(XGuiElement * calling,void * data);
// Attributes
  bool _done;
  bool _cancel;
  XGuiLabel * _message;
  XGuiFrame * _rgbFrame;
  XGuiCursor * _rCursor;
  XGuiCursor * _gCursor;
  XGuiCursor * _bCursor;
  XGuiColorArea * _colArea;
  XGuiFrame * _nameFrame;
  XGuiList * _names;
  XGuiLabel * _text;
  XGuiButton * _okBtn;
  XGuiButton * _cancelBtn;
};

#endif // XGCOLCH_H

