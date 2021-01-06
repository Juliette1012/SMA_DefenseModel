#ifndef XSSQUARE_H
#define XSSQUARE_H

#include "XGui/xgShap2d.h"

//--------------------------------------------------------------------------//
// class XGuiSquare                                                         //
//--------------------------------------------------------------------------//

class XGuiSquare : public XGuiShape2D
{
public:
// Allocators
  XGuiSquare(double x,double y,double theta,const Strings & color,
              double side,bool filled);
  XGuiSquare(const XGuiSquare & s);
  virtual ~XGuiSquare(void);
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
// Attributes
protected:
  double _s_2;      // half side
  bool _filled;
  double _coordX[4];
  double _coordY[4];
};

#include "XGui/xsSquare.Ci"

#endif // XSSQUARE_H

