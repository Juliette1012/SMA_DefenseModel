#ifndef XGCURVE_H
#define XGCURVE_H

#include "Utility/strings.h"

#include <X11/Xlib.h>

//--------------------------------------------------------------------------//
// class XGuiCurve                                                          //
//--------------------------------------------------------------------------//

class XGuiGrapher;

class XGuiCurve
{
public:
// Allocators
// Inspectors
// Modifiers
//---- Specific ----
// Allocators
  XGuiCurve(const Strings & color);
  virtual ~XGuiCurve(void);
// Inspectors
  inline const Strings & getColor(void) const;
  inline int getNbPoints(void) const;
  inline virtual void getBoundingBox(double & xmin,double & ymin,
                                     double & xmax,double & ymax) const;
// Input/Output
  friend ostream & operator<<(ostream & stream,const XGuiCurve & curve);
  virtual Strings print(void) const;
// Modifiers
  virtual void addPoint(double x,double y);
  virtual void accumulatePoint(double x,double y);
  virtual void drawInGrapher(XGuiGrapher * grapher);
// Attributes 
protected:
  Strings _color;
  unsigned long _pixel;
  SimpleVector<double> _x;
  SimpleVector<double> _y;
  bool _accumulate;
  double _xmin,_ymin,_xmax,_ymax;
};

#include "XGui/xgCurve.Ci"

#endif // XGCURVE_H

