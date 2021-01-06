#ifndef XGSHAP2D_H
#define XGSHAP2D_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <math.h>

#include "Utility/strings.h"

//--------------------------------------------------------------------------//
// class XGuiShape2D                                                        //
//--------------------------------------------------------------------------//

class XGuiShape2D;

class XGuiViewer2D;

class XGuiShape2D
{
public:
// Allocators
  XGuiShape2D(double x,double y,double theta,const Strings & color);
  XGuiShape2D(const XGuiShape2D & s);
  virtual ~XGuiShape2D(void);
  virtual XGuiShape2D * duplicate(void) const=0;
// Inspectors
  inline double getX(void) const;
  inline double getY(void) const;
  inline double getTheta(void) const;
  inline const Strings & getColor(void) const;
  inline int getLayer(void) const;
  inline virtual bool isScalable(void) const;
  virtual void getLocalBoundingBox(double & xmin,double & ymin,
                                   double & xmax,double & ymax) const=0;
  virtual void getBoundingBox(double & xmin,double & ymin,
                              double & xmax,double & ymax,
                              const XGuiViewer2D * viewer) const=0;
  virtual bool isInside(double x,double y) const=0;
  virtual bool intersectRay(double xRay,double yRay,double xDir,double yDir,
                            double & x,double & y) const=0;
// Input/Output
  friend ostream & operator<<(ostream & stream,const XGuiShape2D & shape);
  virtual Strings print(void) const=0;
// Modifiers
  void move(double x,double y,double theta);
  void setColor(const Strings & color);
  void setLayer(int layer);
  inline void setKeyCallback(void (*keyCallback)(XGuiShape2D *,
                                                 const Strings &,
                                                 void *),
                             void * keyData=(void *)0);
  inline void setMotionCallback(void (*motionCallback)(XGuiShape2D *,
                                                       double,double,
                                                       void *),
                                void * motionData=(void *)0);
  inline void setSelectCallback(void (*selectCallback)(XGuiShape2D *,
                                                       XGuiViewer2D *,
                                                       bool,
                                                       void *),
                                void * selectData=(void *)0);
//---- Specific ----
// Allocators
// Inspectors
  virtual double distanceTo(double x,double y,
                            const XGuiViewer2D * viewer) const=0;
  inline bool hasMoved(void) const;
// Modifiers
  inline virtual void addViewer(XGuiViewer2D * viewer);
  inline virtual void removeViewer(XGuiViewer2D * viewer);
  inline virtual void changedViewerBackground(XGuiViewer2D * viewer);
  virtual void drawInViewer(XGuiViewer2D * viewer)=0;
  inline virtual void computePosition(void);
  inline virtual void savePosition(void);
  inline void notifyKey(const Strings & key);
  inline void notifyMotion(double dx,double dy);
  inline void notifySelection(XGuiViewer2D * viewer,bool selected);
protected:
// Private Methods
  static double _distanceToSegment(double x,double y,
                                   double x1,double y1,double x2,double y2);
  inline static bool _equationLine(double x1,double y1,double x2,double y2,
                                   double & a,double & b,double & c);
  inline static bool _intersectLines(double a1,double b1,double c1,
                                     double a2,double b2,double c2,
                                     double & x,double & y);
// Attributes 
  double _x0;
  double _y0;
  double _theta0;
  Strings _color;
  unsigned long _pixel;
  int _layer;
  bool _hasMoved;
  void (*_keyCallback)(XGuiShape2D *,const Strings &,void  *);
  void * _keyData;
  void (*_motionCallback)(XGuiShape2D *,double,double,void *);
  void * _motionData;
  void (*_selectCallback)(XGuiShape2D *,XGuiViewer2D *,bool,void *);
  void * _selectData;
};

#include "XGui/xgShap2d.Ci"

#endif // XGSHAP2D_H

