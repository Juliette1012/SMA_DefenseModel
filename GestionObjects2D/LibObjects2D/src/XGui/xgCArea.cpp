#ifdef X_GUI

#include "XGui/xgCArea.h"
#include "XGui/xgMgr.h"

//--------------------------------------------------------------------------//
// class XGuiColorArea                                                      //
//--------------------------------------------------------------------------//

//-------- Allocators ------------------------------------------------------//
XGuiColorArea::XGuiColorArea(XGuiArea * parent,const Strings & color)
 : XGuiArea(parent),
   _color(), _allocated(false), _pixel(0)
{
setColor(color);
}

XGuiColorArea::~XGuiColorArea(void)
{
if(_allocated)
  getXGuiManager()->freeColor(_pixel);
}

//-------- Inspectors ------------------------------------------------------//
XGuiElement::Type XGuiColorArea::getElemType(void) const // virtual
{
return(XGuiElement::COLOR_AREA);
}

bool XGuiColorArea::isA(XGuiElement::Type type) const // virtual
{
return((type==XGuiElement::COLOR_AREA)||XGuiArea::isA(type));
}

const Strings & XGuiColorArea::getColor(void) const
{
return(_color);
}

unsigned long XGuiColorArea::getPixel(void) const
{
return(_pixel);
}

//-------- Modifiers -------------------------------------------------------//
void XGuiColorArea::setColor(const Strings & color)
{
_color=color;
if(_allocated) getXGuiManager()->freeColor(_pixel);
if(getXGuiManager()->allocNamedColor(color,_pixel))
  {
  _allocated=true;
  }
else
  {
  _allocated=false;
  _pixel=getXGuiManager()->getBackground();
  }
if(_window)
  {
  XSetWindowBackground(getXGuiManager()->getDisplay(),_window,_pixel);
  XClearWindow(getXGuiManager()->getDisplay(),_window);
  }
}

void XGuiColorArea::show(void) // virtual
{
if(!_window&&_parent)
  {
  _window=getXGuiManager()->getNewWindow(((XGuiArea *)_parent)->getInWindow(),
                                         _x,_y,_width,_height);
  XSetWindowBackground(getXGuiManager()->getDisplay(),
                       _window,_pixel);
  XMapWindow(getXGuiManager()->getDisplay(),_window);
  }
XGuiElement::show();
}

#endif // X_GUI

