#ifndef XSPOINT_H
#define XSPOINT_H

#include "XGui/xgShap2d.h"

//--------------------------------------------------------------------------//
// class XGuiPoint                                                          //
//--------------------------------------------------------------------------//

class XGuiPoint : public XGuiShape2D
{
public:
// Allocators
  XGuiPoint(double x,double y,double theta,const Strings & color);
  XGuiPoint(const XGuiPoint & s);
  virtual ~XGuiPoint(void);
  virtual XGuiShape2D * duplicate(void) const;
// Inspectors
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
  inline virtual double distanceTo(double x,double y,
                                   const XGuiViewer2D * viewer) const;
// Modifiers
  virtual void drawInViewer(XGuiViewer2D * viewer);
  inline virtual void computePosition(void);
};

#include "XGui/xsPoint.Ci"

#endif // XSPOINT_H

