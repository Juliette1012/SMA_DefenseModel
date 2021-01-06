#ifdef X_GUI

#include "XGui/xgTxtDlg.h"
#include "XGui/xgLabel.h"
#include "XGui/xgButton.h"
#include "XGui/xgMgr.h"

//--------------------------------------------------------------------------//
// class XGuiTextDialog                                                     //
//--------------------------------------------------------------------------//

//-------- Allocators ------------------------------------------------------//
XGuiTextDialog::XGuiTextDialog(const Strings & title,
                               const StringsVect & message)
 : XGuiWindow(title), _done(false), _cancel(false),
   _nbMsg(message.size()), _msgWidth(0),
   _text((XGuiLabel *)0),
   _cancelBtn((XGuiButton *)0),
   _lineY(0)
{
setCallback(XGuiTextDialog::_resizeCB);
setCloseCallback(XGuiTextDialog::_closeCB);
for(int i=0;i<_nbMsg;i++)
  {
  XGuiLabel * label=new XGuiLabel(this,message[i]);
  label->setHeight(getXGuiManager()->getCharHeight());
  if(label->getWidth()>_msgWidth) _msgWidth=label->getWidth();
  }
_text=new XGuiLabel(this,"",true,true);
_text->setCallback(XGuiTextDialog::_enterCB,this);
_cancelBtn=new XGuiButton(this," Cancel ");
_cancelBtn->setCallback(XGuiTextDialog::_cancelCB,this);
int width=4*_cancelBtn->getWidth()+2*getXGuiManager()->getMargin();
if(_msgWidth>width) width=_msgWidth;
setInWidth(width+4*getXGuiManager()->getMargin());
setInHeight(_nbMsg*getXGuiManager()->getCharHeight()+_text->getHeight()+
            16*getXGuiManager()->getMargin());
setX((getXGuiManager()->getScreenWidth()-_width)/2);
setY((getXGuiManager()->getScreenHeight()-_height)/2);
XGuiTextDialog::_resizeCB(this,(void *)0);
}

XGuiTextDialog::~XGuiTextDialog(void)
{
  // _cancelBtn, _text and labels are auto-deleted
}

//-------- Inspectors ------------------------------------------------------//
bool XGuiTextDialog::isEntered(void) const
{
return(_done);
}

bool XGuiTextDialog::isCanceled(void) const
{
return(_cancel);
}

const Strings & XGuiTextDialog::getText(void) const
{
return(_text->getTitle());
}

//-------- Modifiers -------------------------------------------------------//
bool XGuiTextDialog::ask(Strings & answer)
{
_done=false;
_cancel=false;
do
  {
  getXGuiManager()->exclusiveWaitEvent(this);
  } while(!_done&&!_cancel);
if(_cancel)
  {
  answer=Strings("");
  return(false);
  }
else
  {
  answer=_text->getTitle();
  return(true);
  }
}

void XGuiTextDialog::setInitText(const Strings & text)
{
_text->setTitle(text);
}

void XGuiTextDialog::redraw(void) // virtual
{
if(_inWindow)
  {
  getXGuiManager()->background(_inWindow,0,0,_width,_height);
  getXGuiManager()->drawHLineDown(_inWindow,0,_lineY,_width);
  }
}

//-------- Callbacks -------------------------------------------------------//
void XGuiTextDialog::_resizeCB(XGuiElement * calling,void *) // static
{
XGuiTextDialog * dialog=(XGuiTextDialog *)calling;
dialog->_lineY=dialog->getInHeight()-dialog->_text->getHeight()-
               4*getXGuiManager()->getMargin();
int y=(dialog->_lineY-dialog->_nbMsg*getXGuiManager()->getCharHeight())/2;
for(int i=0;i<dialog->_nbMsg;i++)
  {
  dialog->_elems[i]->setX((dialog->getInWidth()-dialog->_msgWidth)/2);
  dialog->_elems[i]->setY(y);
  y+=getXGuiManager()->getCharHeight();
  }
y=dialog->_lineY+2*getXGuiManager()->getMargin();
dialog->_text->setX(2*getXGuiManager()->getMargin());
dialog->_cancelBtn->setX(dialog->getInWidth()-
                         dialog->_cancelBtn->getWidth()-
                         2*getXGuiManager()->getMargin());
dialog->_text->setY(y);
dialog->_cancelBtn->setY(y);
dialog->_text->setWidth(dialog->_cancelBtn->getX()-
                        4*getXGuiManager()->getMargin());
}

void XGuiTextDialog::_closeCB(XGuiElement * calling,void *) // static
{
XGuiTextDialog * dialog=(XGuiTextDialog *)calling;
XGuiTextDialog::_cancelCB(dialog->_cancelBtn,dialog);
}

void XGuiTextDialog::_enterCB(XGuiElement *,void * data) // static
{
XGuiTextDialog * dialog=(XGuiTextDialog *)data;
dialog->_done=true;
dialog->_cancel=false;
}

void XGuiTextDialog::_cancelCB(XGuiElement *,void * data) // static
{
XGuiTextDialog * dialog=(XGuiTextDialog *)data;
dialog->_done=false;
dialog->_cancel=true;
}

#endif // X_GUI

