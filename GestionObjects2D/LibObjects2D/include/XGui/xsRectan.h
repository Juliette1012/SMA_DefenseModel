#ifndef XSRECTAN_H
#define XSRECTAN_H

#include "XGui/xgShap2d.h"

//--------------------------------------------------------------------------//
// class XGuiRectangle                                                      //
//--------------------------------------------------------------------------//

class XGuiRectangle : public XGuiShape2D
{
public:
// Allocators
  XGuiRectangle(double x,double y,double theta,const Strings & color,
                 double length,double width,bool filled);
  XGuiRectangle(const XGuiRectangle & s);
  virtual ~XGuiRectangle(void);
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
  double _l_2;      // half length
  double _w_2;      // half width
  bool _filled;
  double _coordX[4];
  double _coordY[4];
};

#include "XGui/xsRectan.Ci"

#endif // XSRECTAN_H

