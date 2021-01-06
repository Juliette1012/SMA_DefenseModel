#ifndef XSPOLYGO_H
#define XSPOLYGO_H

#include "XGui/xgShap2d.h"

//--------------------------------------------------------------------------//
// class XGuiPolygon                                                        //
//--------------------------------------------------------------------------//

class XGuiPolygon : public XGuiShape2D
{
public:
// Allocators
  XGuiPolygon(double x,double y,double theta,const Strings & color,
              int nbPoints,const double * xPoints,const double * yPoints,
              bool filled);
  XGuiPolygon(const XGuiPolygon & s);
  virtual ~XGuiPolygon(void);
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
  int _nb;
  bool _filled;
  double * _x;
  double * _y;
  double * _coordX;
  double * _coordY;
  XPoint * _points;
};

#include "XGui/xsPolygo.Ci"

#endif // XSPOLYGO_H

