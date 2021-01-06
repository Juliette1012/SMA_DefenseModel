#ifndef XGBTNDLG_H
#define XGBTNDLG_H

#include "XGui/xgWin.h"

//--------------------------------------------------------------------------//
// class XGuiButtonDialog                                                   //
//--------------------------------------------------------------------------//

class XGuiButtonDialog : public XGuiWindow
{
public:
// Allocators
  XGuiButtonDialog(const Strings & title,const StringsVect & message,
                   const StringsVect & buttons);
  virtual ~XGuiButtonDialog(void);
// Inspectors
  int getAnswer(void) const;
  int getNbButtons(void) const;
  const Strings & getButton(int pos) const;
// Modifiers
  int ask(void);
//---- Specific ----
// Allocators
// Inspectors
// Modifiers
  virtual void redraw(void);
protected:
  static void _resizeCB(XGuiElement * calling,void * data);
  static void _closeCB(XGuiElement * calling,void * data);
  static void _answerCB(XGuiElement * calling,void * data);
// Attributes
  int _nbMsg;
  int _msgWidth;
  int _answer;
  int _lineY;
};

#endif // XGBTNDLG_H

