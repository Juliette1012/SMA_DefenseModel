#ifdef X_GUI

#include "XGui/xgBtnDlg.h"
#include "XGui/xgLabel.h"
#include "XGui/xgButton.h"
#include "XGui/xgMgr.h"

//--------------------------------------------------------------------------//
// class XGuiButtonDialog                                                   //
//--------------------------------------------------------------------------//

//-------- Allocators ------------------------------------------------------//
XGuiButtonDialog::XGuiButtonDialog(const Strings & title,
                                   const StringsVect & message,
                                   const StringsVect & buttons)
 : XGuiWindow(title), _nbMsg(message.size()), _msgWidth(0),
   _answer(-1), _lineY(0)
{
setCallback(XGuiButtonDialog::_resizeCB);
setCloseCallback(XGuiButtonDialog::_closeCB);
for(int i=0;i<_nbMsg;i++)
  {
  XGuiLabel * label=new XGuiLabel(this,message[i]);
  label->setHeight(getXGuiManager()->getCharHeight());
  if(label->getWidth()>_msgWidth) _msgWidth=label->getWidth();
  }
XGuiButton * button=(XGuiButton *)0;
int width=0;
if(buttons.size())
  {
  unsigned int i;
  int maxWidth=0;
  for(i=0;i<buttons.size();i++)
    {
    button=new XGuiButton(this,buttons[i]);
    button->setCallback(XGuiButtonDialog::_answerCB,this);
    if(button->getWidth()>maxWidth) maxWidth=button->getWidth();
    }
  for(i=0;i<buttons.size();i++)
    {
    _elems[i+_nbMsg]->setWidth(maxWidth);
    if(i) width+=2*getXGuiManager()->getMargin();
    width+=maxWidth;
    }
  }
else
  {
  button=new XGuiButton(this,"  OK  ");
  button->setCallback(XGuiButtonDialog::_answerCB,this);
  width+=button->getWidth();
  }
if(_msgWidth>width) width=_msgWidth;
setInWidth(width+4*getXGuiManager()->getMargin());
setInHeight(_nbMsg*getXGuiManager()->getCharHeight()+button->getHeight()+
            16*getXGuiManager()->getMargin());
setX((getXGuiManager()->getScreenWidth()-_width)/2);
setY((getXGuiManager()->getScreenHeight()-_height)/2);
XGuiButtonDialog::_resizeCB(this,(void *)0);
}

XGuiButtonDialog::~XGuiButtonDialog(void)
{
  // label and buttons are auto-deleted
}

//-------- Inspectors ------------------------------------------------------//
int XGuiButtonDialog::getAnswer(void) const
{
return(_answer);
}

int XGuiButtonDialog::getNbButtons(void) const
{
return(_elems.getSize()-_nbMsg);
}

const Strings & XGuiButtonDialog::getButton(int pos) const
{
return(_elems[pos+_nbMsg]->getTitle());
}

//-------- Modifiers -------------------------------------------------------//
int XGuiButtonDialog::ask(void)
{
_answer=-1;
do
  {
  getXGuiManager()->exclusiveWaitEvent(this);
  } while(_answer<0);
return(_answer);
}

void XGuiButtonDialog::redraw(void) // virtual
{
if(_inWindow)
  {
  getXGuiManager()->background(_inWindow,0,0,_width,_height);
  getXGuiManager()->drawHLineDown(_inWindow,0,_lineY,_width);
  }
}

//-------- Callbacks -------------------------------------------------------//
void XGuiButtonDialog::_resizeCB(XGuiElement * calling,void *) // static
{
XGuiButtonDialog * dialog=(XGuiButtonDialog *)calling;
dialog->_lineY=dialog->getInHeight()-dialog->_elems.getBack()->getHeight()-
               4*getXGuiManager()->getMargin();
int y=(dialog->_lineY-dialog->_nbMsg*getXGuiManager()->getCharHeight())/2;
for(int j=0;j<dialog->_nbMsg;j++)
  {
  dialog->_elems[j]->setX((dialog->getInWidth()-dialog->_msgWidth)/2);
  dialog->_elems[j]->setY(y);
  y+=getXGuiManager()->getCharHeight();
  }
y=dialog->_lineY+2*getXGuiManager()->getMargin();
int width=dialog->getInWidth();
unsigned int i;
for(i=dialog->_nbMsg;i<dialog->_elems.getSize();i++)
  {
  width-=dialog->_elems[i]->getWidth();
  }
width/=1+(int)dialog->_elems.getSize()-dialog->_nbMsg;
int x=width;
for(i=dialog->_nbMsg;i<dialog->_elems.getSize();i++)
  {
  dialog->_elems[i]->setX(x);
  dialog->_elems[i]->setY(y);
  x+=dialog->_elems[i]->getWidth()+width;
  }
}

void XGuiButtonDialog::_closeCB(XGuiElement * calling,void *) // static
{
XGuiButtonDialog * dialog=(XGuiButtonDialog *)calling;
XGuiButtonDialog::_answerCB(dialog->_elems.accessBack(),dialog);
}

void XGuiButtonDialog::_answerCB(XGuiElement * calling,void * data) // static
{
XGuiButtonDialog * dialog=(XGuiButtonDialog *)data;
for(unsigned int i=dialog->_nbMsg;i<dialog->_elems.getSize();i++)
  {
  if(dialog->_elems[i]==calling)
    {
    dialog->_answer=i-dialog->_nbMsg;
    break;
    }
  }
}

#endif // X_GUI

