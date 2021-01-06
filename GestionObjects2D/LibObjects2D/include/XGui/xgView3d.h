#ifndef XGVIEW3D_H
#define XGVIEW3D_H

#include "Utility/stlList.h"

#include "XGui/xgElem.h"

#include <X11/Intrinsic.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>

//--------------------------------------------------------------------------//
// class XGuiViewer3D                                                       //
//--------------------------------------------------------------------------//

class XGuiArea;

class XGuiShape3D;
typedef StlList<XGuiShape3D *> XGuiShape3DList;

class XGuiViewer3D;
typedef StlList<XGuiViewer3D *> XGuiViewer3DList;

class XGuiViewer3D : public XGuiElement
{
public:
// Allocators
  XGuiViewer3D(XGuiArea * parent);
  virtual ~XGuiViewer3D(void);
// Inspectors
  inline const Strings & getBackground(void) const;
  inline void getPosition(double & px,double & py,double & pz) const;
  void globalToLocalPosition(double & x,double & y,double & z) const;
  void localToGlobalPosition(double & x,double & y,double & z) const;
  void getOrientation(double & roll,double & pitch,double & yaw) const;
  void globalToLocalOrientation(double & roll,
                                double & pitch,double & yaw) const;
  void localToGlobalOrientation(double & roll,
                                double & pitch,double & yaw) const;
  inline void getLocation(double & px,double & py,double & pz,
                          double & roll,double & pitch,double & yaw) const;
  inline const XGuiShape3DList & getSelection(void) const;
  bool isSelected(const XGuiShape3D * shape) const;
// Modifiers
  void select(XGuiShape3D * shape,bool propagate);
  void unselect(XGuiShape3D * shape,bool propagate);
  void setBackground(const Strings & color);
  void setPosition(double px,double py,double pz);
  void cancelRotation(void);
  void setOrientation(double roll,double pitch,double yaw);
  void setLocation(double px,double py,double pz,
                   double roll,double pitch,double yaw);
  void translate(double dx,double dy,double dz);
  void roll(double dRoll);
  void pitch(double dPitch);
  void yaw(double dYaw);
  virtual void setWidth(int width);
  virtual void setHeight(int height);
  virtual void show(void);
  virtual void hide(void);
  inline void setKeyCallback(void (*keyCallback)(XGuiViewer3D*,
                                                 const Strings &,
                                                 void *),
                             void * keyData=(void *)0);
//---- Specific ----
// Static methods
  static void addShape(XGuiShape3D * shape);
  static void removeShape(XGuiShape3D * shape);
  inline static void forceRedraw(void);
  static void drawAll(void);
  static bool createGlobalContext(void);
  static void destroyGlobalContext(void);
// Allocators
// Inspectors
  inline virtual XGuiElement::Type getElemType(void) const;
  inline virtual bool isA(XGuiElement::Type type) const;
  inline unsigned long getBackgroundPixel(void) const;
// Modifiers
  virtual void processEvent(const XEvent & event);
  virtual void redraw(void);
protected:
  void _adjustLimits(void);
  void _chooseCursor(void);
  static void _motionProc(XtPointer,XtIntervalId *);
  static Window _createWindow(Window parentWin,int x,int y,int w,int h);
// Attributes
  double _px,_py,_pz;
  double _r00,_r01,_r02;
  double _r10,_r11,_r12;
  double _r20,_r21,_r22;
  Strings _color;
  unsigned long _pixel;
  float _r,_g,_b;
  float _rInv,_gInv,_bInv;
  XGuiShape3DList _select;
  bool _ctrlPressed;
  bool _shiftPressed;
  unsigned int _pressed;
  bool _canMoveSelection;
  int _mouseX;
  int _mouseY;
  double _viewAngle;
  double _limitY,_limitZ;
  double _limitMinX,_limitMaxX;
  double _aspectRatio;
  void (*_keyCallback)(XGuiViewer3D *,const Strings &,void *);
  void * _keyData;
  struct
    {
    bool move;
    Time lastMotion;
    double dx;
    double yaw;
    double pitch;
    } _motionData;
  static const double PRECISION_SIN;
  static XtIntervalId _motionTimerId;
  static unsigned long _motionTimerDt;
  static XGuiViewer3DList _viewers;
  static XGuiShape3DList _shapes;
  static bool _mustDraw;
  static GLXContext _globalContext;
  static Window _globalWindow;
  static XVisualInfo *_globalVisualInfo;
};

#include "XGui/xgView3d.Ci"

#endif // XGVIEW3D_H

