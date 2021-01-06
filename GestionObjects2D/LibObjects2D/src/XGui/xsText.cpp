#ifdef X_GUI

#include "XGui/xsText.h"
#include "XGui/xgView2d.h"
#include "XGui/xgMgr.h"

//--------------------------------------------------------------------------//
// class XGuiText                                                           //
//--------------------------------------------------------------------------//

//-------- Allocators ------------------------------------------------------//
XGuiText::XGuiText(double x,double y,double theta,const Strings & color,
                   const Strings & text)
 : XGuiShape2D(x,y,theta,color),
   _text(text), _textWidth(getXGuiManager()->getTextWidth(text))
{
computePosition();
}

XGuiText::XGuiText(const XGuiText & s)
 : XGuiShape2D(s),
   _text(s._text), _textWidth(s._textWidth)
{}

XGuiText::~XGuiText(void)
{}

XGuiShape2D * XGuiText::duplicate(void) const // virtual
{
return(new XGuiText(*this));
}

//-------- Inspectors ------------------------------------------------------//
// inline bool XGuiText::isScalable(void) const // virtual

// inline const Strings & XGuiText::getText(void) const

// inline void XGuiText::getLocalBoundingBox(double & xmin,double & ymin,
//                                           double & xmax,double & ymax)
//                                           const // virtual

// inline void XGuiText::getBoundingBox(double & xmin,double & ymin,
//                                      double & xmax,double & ymax,
//                                      const XGuiViewer2D * viewer)
//                                                            const // virtual

// inline double XGuiText::distanceTo(double x,double y,
//                                    const XGuiViewer2D * viewer)
//                                                            const // virtual

bool XGuiText::isInside(double,double) const // virtual
{
return(false);
}

bool XGuiText::intersectRay(double,double,double,double,
                            double &,double &) const // virtual
{
return(false);
}

//-------- Input/Output ----------------------------------------------------//
Strings XGuiText::print(void) const // virtual
{
return("text("+_text.dump()+")");
}

//-------- Modifiers -------------------------------------------------------//
void XGuiText::setText(const Strings & text)
{
_text=text;
_textWidth=getXGuiManager()->getTextWidth(text);
XGuiViewer2D::forceRedraw();
}

void XGuiText::drawInViewer(XGuiViewer2D * viewer) // virtual
{
getXGuiManager()->chooseColor(_pixel);
XDrawString(getXGuiManager()->getDisplay(),
            viewer->getPixmap(),getXGuiManager()->getGC(),
            viewer->getColumn(_x0),
            viewer->getLine(_y0)+getXGuiManager()->getFont()->ascent,
            _text,_text.len());
}

// inline void XGuiText::computePosition(void) // virtual

#endif // X_GUI

