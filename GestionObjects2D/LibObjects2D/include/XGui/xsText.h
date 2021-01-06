#ifndef XSTEXT_H
#define XSTEXT_H

#include "XGui/xgShap2d.h"
#include "XGui/xgView2d.h"
#include "XGui/xgMgr.h"

//--------------------------------------------------------------------------//
// class XGuiText                                                           //
//--------------------------------------------------------------------------//

class XGuiText : public XGuiShape2D
{
public:
// Allocators
  XGuiText(double x,double y,double theta,const Strings & color,
           const Strings & text);
  XGuiText(const XGuiText & s);
  virtual ~XGuiText(void);
  virtual XGuiShape2D * duplicate(void) const;
// Inspectors
  inline virtual bool isScalable(void) const;
  inline virtual void getLocalBoundingBox(double & xmin,double & ymin,
                                          double & xmax,double & ymax) const;
  inline virtual void getBoundingBox(double & xmin,double & ymin,
                                     double & xmax,double & ymax,
                                     const XGuiViewer2D * viewer) const;
  virtual bool isInside(double x,double y) const;
  virtual bool intersectRay(double xRay,double yRay,double xDir,double yDir,
                            double & x,double & y) const;
// Input/Output
  virtual Strings print(void) const;
// Modifiers
//---- Specific ---
// Allocators
// Inspectors
  inline const Strings & getText(void) const;
  inline virtual double distanceTo(double x,double y,
                                   const XGuiViewer2D * viewer) const;
// Modifiers
  void setText(const Strings & text);
  virtual void drawInViewer(XGuiViewer2D * viewer);
  inline virtual void computePosition(void);
// Attributes
protected:
  Strings _text;
  int _textWidth;
};

#include "XGui/xsText.Ci"

#endif // XSTEXT_H

