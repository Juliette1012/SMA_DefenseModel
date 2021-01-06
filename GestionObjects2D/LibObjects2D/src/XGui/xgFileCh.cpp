#ifdef X_GUI

#include "XGui/xgFileCh.h"
#include "XGui/xgFrame.h"
#include "XGui/xgList.h"
#include "XGui/xgLabel.h"
#include "XGui/xgButton.h"
#include "XGui/xgMgr.h"

#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

//--------------------------------------------------------------------------//
// class XGuiFileChooser                                                    //
//--------------------------------------------------------------------------//

//-------- Allocators ------------------------------------------------------//
XGuiFileChooser::XGuiFileChooser(const Strings & title,
                                 const Strings & message)
 : XGuiWindow(title), _path(), _done(false), _cancel(false),
   _message(new XGuiLabel(this,message)),
   _dirFrame(new XGuiFrame(this,"Dir.")),
   _dirs(new XGuiList(_dirFrame,StringsVect())),
   _fileFrame(new XGuiFrame(this,"File")),
   _files(new XGuiList(_fileFrame,StringsVect())),
   _text(new XGuiLabel(this,"",true,true)),
   _okBtn(new XGuiButton(this,"  OK  ")),
   _updtBtn(new XGuiButton(this," Update ")),
   _cancelBtn(new XGuiButton(this," Cancel "))
{
int w=_okBtn->getWidth();
if(_updtBtn->getWidth()>w) w=_updtBtn->getWidth();
if(_cancelBtn->getWidth()>w) w=_cancelBtn->getWidth();
_okBtn->setWidth(w);
_updtBtn->setWidth(w);
_cancelBtn->setWidth(w);
setCallback(XGuiFileChooser::_resizeCB);
setCloseCallback(XGuiFileChooser::_closeCB);
_dirs->setCallback(XGuiFileChooser::_dirsCB,this);
_files->setCallback(XGuiFileChooser::_filesCB,this);
_text->setCallback(XGuiFileChooser::_enterCB,this);
_okBtn->setCallback(XGuiFileChooser::_enterCB,this);
_updtBtn->setCallback(XGuiFileChooser::_updateCB,this);
_cancelBtn->setCallback(XGuiFileChooser::_cancelCB,this);
setWidth(getXGuiManager()->getScreenWidth()/3);
setHeight(getXGuiManager()->getScreenHeight()/2);
setX((getXGuiManager()->getScreenWidth()-_width)/2);
setY((getXGuiManager()->getScreenHeight()-_height)/2);
XGuiFileChooser::_resizeCB(this,(void *)0);
char buffer[0x100];
setInitPath(getcwd(buffer,0x100));
}

XGuiFileChooser::~XGuiFileChooser(void)
{
  // _message, _dirFrame, _dirs, _fileFrame, _files, _text,
  // _okBtn and _cancelBtn are auto-deleted
}

//-------- Inspectors ------------------------------------------------------//
bool XGuiFileChooser::isEntered(void) const
{
return(_done);
}

bool XGuiFileChooser::isCanceled(void) const
{
return(_cancel);
}

const Strings & XGuiFileChooser::getPath(void) const
{
return(_path);
}

const Strings & XGuiFileChooser::getFileName(void) const
{
return(_text->getTitle());
}

//-------- Modifiers -------------------------------------------------------//
bool XGuiFileChooser::ask(Strings & answer)
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

void XGuiFileChooser::setInitPath(const Strings & path)
{
if(&path!=&_path)
  {
  StringsVect dirEntries;
  StringsVect fileEntries;
  DIR * dirp;
  if(path.len()) dirp=::opendir(path);
  else dirp=::opendir(".");
  if(dirp)
    {
    _path=path;
    if(path.len()&&(path[path.len()-1]!='/')) _path+='/';
    _text->setTitle(_path);
    _text->goEnd();
    _text->redraw();
    unsigned int pos;
    struct stat entStat;
    struct dirent * entry=::readdir(dirp);
    while(entry)
      {
      if(!::stat(_path+entry->d_name,&entStat))
        {
        if(S_ISREG(entStat.st_mode))
          {
          for(pos=0;(pos<fileEntries.size())&&
                    (fileEntries[pos]<Strings(entry->d_name));pos++);
          fileEntries.insert(fileEntries.begin()+pos,entry->d_name);
          }
        else if(S_ISDIR(entStat.st_mode)&&
                (Strings(entry->d_name)!=Strings(".")))
          {
          for(pos=0;(pos<dirEntries.size())&&
                    (dirEntries[pos]<Strings(entry->d_name));pos++);
          dirEntries.insert(dirEntries.begin()+pos,entry->d_name);
          }
        }
      entry=::readdir(dirp);
      }
    ::closedir(dirp);
    }
  else getXGuiManager()->bell();
  _dirs->setEntries(dirEntries);
  _files->setEntries(fileEntries);
  }
}

//-------- Callbacks -------------------------------------------------------//
void XGuiFileChooser::_resizeCB(XGuiElement * calling,void *) // static
{
XGuiFileChooser * chooser=(XGuiFileChooser *)calling;
chooser->_message->setX((chooser->getInWidth()-
                         chooser->_message->getWidth())/2);
chooser->_message->setY(2*getXGuiManager()->getMargin());
chooser->_okBtn->setY(chooser->getInHeight()-
                      chooser->_okBtn->getHeight()-
                      2*getXGuiManager()->getMargin());
chooser->_updtBtn->setY(chooser->getInHeight()-
                        chooser->_updtBtn->getHeight()-
                        2*getXGuiManager()->getMargin());
chooser->_cancelBtn->setY(chooser->getInHeight()-
                          chooser->_cancelBtn->getHeight()-
                          2*getXGuiManager()->getMargin());
chooser->_text->setX(2*getXGuiManager()->getMargin());
chooser->_text->setY(chooser->_okBtn->getY()-
                     chooser->_text->getHeight()-
                     2*getXGuiManager()->getMargin());
chooser->_text->setWidth(chooser->getInWidth()-
                         4*getXGuiManager()->getMargin());
chooser->_dirFrame->setX(2*getXGuiManager()->getMargin());
chooser->_dirFrame->setY(chooser->_message->getY()+
                         chooser->_message->getHeight()+
                         2*getXGuiManager()->getMargin());
chooser->_dirFrame->setWidth((chooser->getInWidth()-
                              6*getXGuiManager()->getMargin())/2);
chooser->_dirFrame->setHeight(chooser->_text->getY()-
                            chooser->_dirFrame->getY()-
                            2*getXGuiManager()->getMargin());
chooser->_fileFrame->setWidth(chooser->_dirFrame->getWidth());
chooser->_fileFrame->setHeight(chooser->_dirFrame->getHeight());
chooser->_fileFrame->setY(chooser->_dirFrame->getY());
chooser->_fileFrame->setX(chooser->getInWidth()-
                          chooser->_fileFrame->getWidth()-
                          2*getXGuiManager()->getMargin());
chooser->_dirs->setX(getXGuiManager()->getMargin());
chooser->_dirs->setY(getXGuiManager()->getMargin());
chooser->_dirs->setWidth(chooser->_dirFrame->getInWidth()-
                         2*getXGuiManager()->getMargin());
chooser->_dirs->setHeight(chooser->_dirFrame->getInHeight()-
                          2*getXGuiManager()->getMargin());
chooser->_files->setX(chooser->_dirs->getX());
chooser->_files->setY(chooser->_dirs->getY());
chooser->_files->setWidth(chooser->_dirs->getWidth());
chooser->_files->setHeight(chooser->_dirs->getHeight());
chooser->_okBtn->setX(2*getXGuiManager()->getMargin());
chooser->_updtBtn->setX((chooser->getInWidth()-
                         chooser->_updtBtn->getWidth())/2);
chooser->_cancelBtn->setX(chooser->getInWidth()-
                          2*getXGuiManager()->getMargin()-
                          chooser->_cancelBtn->getWidth());
}

void XGuiFileChooser::_closeCB(XGuiElement * calling,void *) // static
{
XGuiFileChooser * chooser=(XGuiFileChooser *)calling;
XGuiFileChooser::_cancelCB(chooser->_cancelBtn,chooser);
}

void XGuiFileChooser::_dirsCB(XGuiElement *,void * data) // static
{
XGuiFileChooser * chooser=(XGuiFileChooser *)data;
int result=chooser->_dirs->getResult();
if(result>=0)
  {
  const Strings & entry=chooser->_dirs->getEntry(result);
  if((entry==Strings(".."))&&chooser->_path.len())
    {
    if(chooser->_path!=Strings("/"))
      {
      int limit=chooser->_path.len()-1; // last char is '/'
      while(limit)
        {
        limit--;
        if(chooser->_path[limit]=='/')
          {
          limit++; // on the right of '/'
          break;
          }
        }
      if(chooser->_path.subString(limit,chooser->_path.len()-limit)==
         Strings("../"))
        chooser->setInitPath(chooser->_path+"../");
      else
        chooser->setInitPath(chooser->_path.subString(0,limit));
      }
    }
  else chooser->setInitPath(chooser->_path+entry);
  }
}

void XGuiFileChooser::_filesCB(XGuiElement *,void * data) // static
{
XGuiFileChooser * chooser=(XGuiFileChooser *)data;
int result=chooser->_files->getResult();
if(result>=0)
  {
  chooser->_text->setTitle(chooser->_path+
                           chooser->_files->getEntry(result));
  chooser->_text->goEnd();
  chooser->_text->redraw();
  if(chooser->_files->isEntered())
    {
    chooser->_done=true;
    chooser->_cancel=false;
    }
  }
}

void XGuiFileChooser::_enterCB(XGuiElement *,void * data) // static
{
XGuiFileChooser * chooser=(XGuiFileChooser *)data;
chooser->_done=true;
chooser->_cancel=false;
}

void XGuiFileChooser::_updateCB(XGuiElement *,void * data) // static
{
XGuiFileChooser * chooser=(XGuiFileChooser *)data;
chooser->setInitPath(chooser->_text->getTitle());
}

void XGuiFileChooser::_cancelCB(XGuiElement *,void * data) // static
{
XGuiFileChooser * chooser=(XGuiFileChooser *)data;
chooser->_done=false;
chooser->_cancel=true;
}

#endif // X_GUI

