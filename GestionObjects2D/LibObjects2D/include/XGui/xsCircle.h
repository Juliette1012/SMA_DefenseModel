#ifndef XSCIRCLE_H
#define XSCIRCLE_H

#include "XGui/xgShap2d.h"

//--------------------------------------------------------------------------//
// class XGuiCircle                                                         //
//--------------------------------------------------------------------------//

class XGuiCircle : public XGuiShape2D
{
public:
// Allocators
  XGuiCircle(double x,double y,double theta,const Strings & color,
             double radius,bool filled);
  XGuiCircle(const XGuiCircle & s);
  virtual ~XGuiCircle(void);
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
//---- Specific ----
// Allocators
// Inspectors
  inline virtual double distanceTo(double x,double y,
                                   const XGuiViewer2D * viewer) const;
// Modifiers
  virtual void drawInViewer(XGuiViewer2D * viewer);
  inline virtual void computePosition(void);
// Attributes
protected:
  double _radius;
  bool _filled;
};

#include "XGui/xsCircle.Ci"

#endif // XSCIRCLE_H

