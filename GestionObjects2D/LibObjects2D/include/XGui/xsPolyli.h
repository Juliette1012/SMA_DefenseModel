#ifndef XSPOLYLI_H
#define XSPOLYLI_H

#include "XGui/xgShap2d.h"

//--------------------------------------------------------------------------//
// class XGuiPolyline                                                       //
//--------------------------------------------------------------------------//

class XGuiPolyline : public XGuiShape2D
{
public:
// Allocators
  XGuiPolyline(double x,double y,double theta,const Strings & color,
                int nbPoints,const double * xPoints,const double * yPoints);
  XGuiPolyline(const XGuiPolyline & s);
  virtual ~XGuiPolyline(void);
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
  double * _x;
  double * _y;
  double * _coordX;
  double * _coordY;
  XPoint * _points;
};

#include "XGui/xsPolyli.Ci"

#endif // XSPOLYLI_H

