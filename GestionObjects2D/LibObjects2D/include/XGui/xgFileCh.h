#ifndef XGFILECH_H
#define XGFILECH_H

#include "XGui/xgWin.h"

//--------------------------------------------------------------------------//
// class XGuiFileChooser                                                    //
//--------------------------------------------------------------------------//

class XGuiFrame;
class XGuiLabel;
class XGuiList;
class XGuiButton;

class XGuiFileChooser : public XGuiWindow
{
public:
// Allocators
  XGuiFileChooser(const Strings & title,const Strings & message);
  virtual ~XGuiFileChooser(void);
// Inspectors
  bool isEntered(void) const;
  bool isCanceled(void) const;
  const Strings & getPath(void) const;
  const Strings & getFileName(void) const;
// Modifiers
  bool ask(Strings & answer);
  void setInitPath(const Strings & path);
//---- Specific ----
// Allocators
// Inspectors
// Modifiers
protected:
  static void _resizeCB(XGuiElement * calling,void * data);
  static void _closeCB(XGuiElement * calling,void * data);
  static void _dirsCB(XGuiElement * calling,void * data);
  static void _filesCB(XGuiElement * calling,void * data);
  static void _enterCB(XGuiElement * calling,void * data);
  static void _updateCB(XGuiElement * calling,void * data);
  static void _cancelCB(XGuiElement * calling,void * data);
// Attributes
  Strings _path;
  bool _done;
  bool _cancel;
  XGuiLabel * _message;
  XGuiFrame * _dirFrame;
  XGuiList * _dirs;
  XGuiFrame * _fileFrame;
  XGuiList * _files;
  XGuiLabel * _text;
  XGuiButton * _okBtn;
  XGuiButton * _updtBtn;
  XGuiButton * _cancelBtn;
};

#endif // XGFILECH_H

