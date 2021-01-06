#ifdef X_GUI

#include <stdio.h>

#include "XGui/xgColCh.h"
#include "XGui/xgLabel.h"
#include "XGui/xgFrame.h"
#include "XGui/xgCursor.h"
#include "XGui/xgCArea.h"
#include "XGui/xgList.h"
#include "XGui/xgButton.h"
#include "XGui/xgMgr.h"

//--------------------------------------------------------------------------//
// class XGuiColorChooser                                                   //
//--------------------------------------------------------------------------//

//-------- Allocators ------------------------------------------------------//
XGuiColorChooser::XGuiColorChooser(const Strings & title,
                                   const Strings & message)
 : XGuiWindow(title),
   _done(false), _cancel(false),
   _message(new XGuiLabel(this,message)),
   _rgbFrame(new XGuiFrame(this,"RGB")),
   _rCursor(new XGuiCursor(_rgbFrame,false)),
   _gCursor(new XGuiCursor(_rgbFrame,false)),
   _bCursor(new XGuiCursor(_rgbFrame,false)),
   _colArea(new XGuiColorArea(_rgbFrame,"")),
   _nameFrame(new XGuiFrame(this,"Name")),
   _names(new XGuiList(_nameFrame,StringsVect())),
   _text(new XGuiLabel(_nameFrame,"",true,true)),
   _okBtn(new XGuiButton(this,"  OK  ")),
   _cancelBtn(new XGuiButton(this," Cancel "))
{
if(_okBtn->getWidth()>_cancelBtn->getWidth())
  _cancelBtn->setWidth(_okBtn->getWidth());
else
  _okBtn->setWidth(_cancelBtn->getWidth());
setCallback(XGuiColorChooser::_resizeCB);
setCloseCallback(XGuiColorChooser::_closeCB);
_rCursor->setCallback(XGuiColorChooser::_cursorCB,this);
_gCursor->setCallback(XGuiColorChooser::_cursorCB,this);
_bCursor->setCallback(XGuiColorChooser::_cursorCB,this);
_names->setCallback(XGuiColorChooser::_nameCB,this);
_text->setCallback(XGuiColorChooser::_enterCB,this);
_okBtn->setCallback(XGuiColorChooser::_enterCB,this);
_cancelBtn->setCallback(XGuiColorChooser::_cancelCB,this);
setWidth(getXGuiManager()->getScreenWidth()/3);
setHeight(getXGuiManager()->getScreenHeight()/2);
setX((getXGuiManager()->getScreenWidth()-_width)/2);
setY((getXGuiManager()->getScreenHeight()-_height)/2);
XGuiColorChooser::_resizeCB(this,(void *)0);
_readDataBase();
setInitColor(_names->getEntry(0));
}

XGuiColorChooser::~XGuiColorChooser(void)
{
  // _message, _rgbFrame, _rCursor, _gCursor, _bCursor,
  // _colArea, _nameFrame, _names, _text,
  // _okBtn and _cancelBtn are auto-deleted
}

//-------- Inspectors ------------------------------------------------------//
bool XGuiColorChooser::isEntered(void) const
{
return(_done);
}

bool XGuiColorChooser::isCanceled(void) const
{
return(_cancel);
}

const Strings & XGuiColorChooser::getColor(void) const
{
return(_text->getTitle());
}

//-------- Modifiers -------------------------------------------------------//
bool XGuiColorChooser::ask(Strings & answer)
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

void XGuiColorChooser::setInitColor(const Strings & color,bool propagate)
{
_text->setTitle(color);
_text->goEnd();
_text->redraw();
_colArea->setColor(color);
if(propagate)
  {
  unsigned long pixel=_colArea->getPixel();
  unsigned short r,g,b;
  getXGuiManager()->queryColor(pixel,r,g,b);
  _setRGB(r>>8,g>>8,b>>8);
  }
}

void XGuiColorChooser::show(void) // virtual
{
XGuiWindow::show();
setInitColor(_text->getTitle());
}

void XGuiColorChooser::_readDataBase(void)
{
StringsVect colorEntries;
char line[0x100];
FILE * file=fopen("/usr/lib/X11/rgb.txt","r");
if(!file)
  {
  char * var=::getenv("ORISRGB");
  if(var) file=fopen(var,"r");
  }
if(file)
  {
  while(!feof(file))
    {
    if(fgets(line,0x100,file))
      {
      char c=line[0];
      if((c==' ')||(c=='\t')||((c>='0')&&(c<='9')))
        {
        int dummy;
        if(sscanf(line,"%d%d%d",&dummy,&dummy,&dummy)==3)
          {
          int i=0;
          c=line[i];
          while((c==' ')||(c=='\t')) c=line[++i]; // eat blanks
          while((c>='0')&&(c<='9')) c=line[++i];  // eat integer
          while((c==' ')||(c=='\t')) c=line[++i]; // eat blanks
          while((c>='0')&&(c<='9')) c=line[++i];  // eat integer
          while((c==' ')||(c=='\t')) c=line[++i]; // eat blanks
          while((c>='0')&&(c<='9')) c=line[++i];  // eat integer
          while((c==' ')||(c=='\t')) c=line[++i]; // eat blanks
          int start=i;
          while((c!='\n')&&(c!='\0')) c=line[++i]; // replace '\n' by '\0'
          line[i]='\0';
          if(start!=i) colorEntries.push_back(Strings(line+start));
          }
        }
      }
    }
  fclose(file);
  }
else
  {
  colorEntries.push_back("black");
  colorEntries.push_back("white");
  colorEntries.push_back("red");
  colorEntries.push_back("green");
  colorEntries.push_back("blue");
  }
_names->setEntries(colorEntries);
}

void XGuiColorChooser::_readRGB(int & r,int & g,int & b)
{
r=(int)(255.0*_rCursor->getValue());
g=(int)(255.0*_gCursor->getValue());
b=(int)(255.0*_bCursor->getValue());
}

void XGuiColorChooser::_setRGB(int r,int  g,int  b)
{
_rCursor->setValue(r/255.0,false);
_gCursor->setValue(g/255.0,false);
_bCursor->setValue(b/255.0,false);
}

//-------- Callbacks -------------------------------------------------------//
void XGuiColorChooser::_resizeCB(XGuiElement * calling,void *) // static
{
XGuiColorChooser * chooser=(XGuiColorChooser *)calling;
chooser->_message->setX((chooser->getInWidth()-
                         chooser->_message->getWidth())/2);
chooser->_message->setY(2*getXGuiManager()->getMargin());
chooser->_okBtn->setY(chooser->getInHeight()-
                      chooser->_okBtn->getHeight()-
                      2*getXGuiManager()->getMargin());
chooser->_cancelBtn->setY(chooser->getInHeight()-
                          chooser->_cancelBtn->getHeight()-
                          2*getXGuiManager()->getMargin());
chooser->_rgbFrame->setX(2*getXGuiManager()->getMargin());
chooser->_rgbFrame->setY(chooser->_message->getY()+
                         chooser->_message->getHeight()+
                         2*getXGuiManager()->getMargin());
chooser->_rgbFrame->setInWidth(3*chooser->_rCursor->getWidth()+
                               6*getXGuiManager()->getMargin());
chooser->_rgbFrame->setHeight(chooser->_okBtn->getY()-
                              chooser->_rgbFrame->getY()-
                              2*getXGuiManager()->getMargin());
chooser->_nameFrame->setWidth(chooser->getInWidth()-
                              chooser->_rgbFrame->getWidth()-
                              6*getXGuiManager()->getMargin());
chooser->_nameFrame->setHeight(chooser->_rgbFrame->getHeight());
chooser->_nameFrame->setY(chooser->_rgbFrame->getY());
chooser->_nameFrame->setX(chooser->getInWidth()-
                          chooser->_nameFrame->getWidth()-
                          2*getXGuiManager()->getMargin());
chooser->_text->setX(getXGuiManager()->getMargin());
chooser->_text->setY(chooser->_nameFrame->getInHeight()-
                     chooser->_text->getHeight()-
                     getXGuiManager()->getMargin());
chooser->_text->setWidth(chooser->_nameFrame->getInWidth()-
                         2*getXGuiManager()->getMargin());
chooser->_names->setX(getXGuiManager()->getMargin());
chooser->_names->setY(getXGuiManager()->getMargin());
chooser->_names->setWidth(chooser->_nameFrame->getInWidth()-
                          2*getXGuiManager()->getMargin());
chooser->_names->setHeight(chooser->_text->getY()-
                           chooser->_names->getY()-
                           2*getXGuiManager()->getMargin());
chooser->_colArea->setX(getXGuiManager()->getMargin());
chooser->_colArea->setWidth(chooser->_rgbFrame->getInWidth()-
                            2*getXGuiManager()->getMargin());
chooser->_colArea->setHeight(chooser->_text->getHeight());
chooser->_colArea->setY(chooser->_rgbFrame->getInHeight()-
                        chooser->_colArea->getHeight()-
                        getXGuiManager()->getMargin());
chooser->_rCursor->setX(getXGuiManager()->getMargin());
chooser->_rCursor->setY(getXGuiManager()->getMargin());
chooser->_rCursor->setHeight(chooser->_colArea->getY()-
                             chooser->_rCursor->getY()-
                             2*getXGuiManager()->getMargin());
chooser->_gCursor->setX((chooser->_rgbFrame->getInWidth()-
                         chooser->_gCursor->getWidth())/2);
chooser->_gCursor->setY(chooser->_rCursor->getY());
chooser->_gCursor->setHeight(chooser->_rCursor->getHeight());
chooser->_bCursor->setX(chooser->_rgbFrame->getInWidth()-
                        chooser->_bCursor->getWidth()-
                        getXGuiManager()->getMargin());
chooser->_bCursor->setY(chooser->_rCursor->getY());
chooser->_bCursor->setHeight(chooser->_rCursor->getHeight());
chooser->_okBtn->setX(2*getXGuiManager()->getMargin());
chooser->_cancelBtn->setX(chooser->getInWidth()-
                          2*getXGuiManager()->getMargin()-
                          chooser->_cancelBtn->getWidth());
}

void XGuiColorChooser::_closeCB(XGuiElement * calling,void *) // static
{
XGuiColorChooser * chooser=(XGuiColorChooser *)calling;
XGuiColorChooser::_cancelCB(chooser->_cancelBtn,chooser);
}

void XGuiColorChooser::_cursorCB(XGuiElement *,void * data) // static
{
static char buffer[0x100];
XGuiColorChooser * chooser=(XGuiColorChooser *)data;
int r,g,b;
chooser->_readRGB(r,g,b);
sprintf(buffer,"rgb:%.2x/%.2x/%.2x",r,g,b);
chooser->setInitColor(buffer,false);
}

void XGuiColorChooser::_nameCB(XGuiElement *,void * data) // static
{
XGuiColorChooser * chooser=(XGuiColorChooser *)data;
int result=chooser->_names->getResult();
if(result>=0)
  {
  chooser->setInitColor(chooser->_names->getEntry(result));
  if(chooser->_names->isEntered())
    {
    chooser->_done=true;
    chooser->_cancel=false;
    }
  }
}

void XGuiColorChooser::_enterCB(XGuiElement *,void * data) // static
{
XGuiColorChooser * chooser=(XGuiColorChooser *)data;
chooser->setInitColor(chooser->_text->getTitle());
chooser->_done=true;
chooser->_cancel=false;
}

void XGuiColorChooser::_cancelCB(XGuiElement *,void * data) // static
{
XGuiColorChooser * chooser=(XGuiColorChooser *)data;
chooser->_done=false;
chooser->_cancel=true;
}

#endif // X_GUI

