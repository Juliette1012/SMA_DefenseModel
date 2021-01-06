#ifndef XGTXTDLG_H
#define XGTXTDLG_H

#include "XGui/xgWin.h"

//--------------------------------------------------------------------------//
// class XGuiTextDialog                                                     //
//--------------------------------------------------------------------------//

class XGuiLabel;
class XGuiButton;

class XGuiTextDialog : public XGuiWindow
{
public:
// Allocators
  XGuiTextDialog(const Strings & title,const StringsVect & message);
  virtual ~XGuiTextDialog(void);
// Inspectors
  bool isEntered(void) const;
  bool isCanceled(void) const;
  const Strings & getText(void) const;
// Modifiers
  bool ask(Strings & answer);
  void setInitText(const Strings & text);
//---- Specific ----
// Allocators
// Inspectors
// Modifiers
  virtual void redraw(void);
protected:
  static void _resizeCB(XGuiElement * calling,void * data);
  static void _closeCB(XGuiElement * calling,void * data);
  static void _enterCB(XGuiElement * calling,void * data);
  static void _cancelCB(XGuiElement * calling,void * data);
// Attributes
  bool _done;
  bool _cancel;
  int _nbMsg;
  int _msgWidth;
  XGuiLabel * _text;
  XGuiButton * _cancelBtn;
  int _lineY;
};

#endif // XGTXTDLG_H

