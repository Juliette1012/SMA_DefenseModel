#ifndef XGVIEW2D_H
#define XGVIEW2D_H

#include "Utility/stlList.h"

#include "XGui/xgElem.h"

//--------------------------------------------------------------------------//
// class XGuiViewer2D                                                       //
//--------------------------------------------------------------------------//

class XGuiArea;

class XGuiShape2D;
typedef StlList<XGuiShape2D *> XGuiShapeList;

class XGuiViewer2D;
typedef StlList<XGuiViewer2D *> XGuiViewerList;

class XGuiViewer2D : public XGuiElement
{
public:
// Allocators
  XGuiViewer2D(XGuiArea * parent);
  virtual ~XGuiViewer2D(void);
// Inspectors
  inline double getScale(void) const;
  inline void getViewPoint(double & x,double & y,double & scale) const;
  inline const Strings & getBackground(void) const;
  inline const XGuiShapeList & getSelection(void) const;
  bool isSelected(const XGuiShape2D * shape) const;
// Modifiers
  void select(XGuiShape2D * shape,bool propagate);
  void unselect(XGuiShape2D * shape,bool propagate);
  void setBackground(const Strings & color);
  void setViewPoint(double x,double y,double scale);
  void autoScale(void);
  virtual void setWidth(int width);
  virtual void setHeight(int height);
  virtual void show(void);
  virtual void hide(void);
  inline void setKeyCallback(void (*keyCallback)(XGuiViewer2D*,
                                                 const Strings &,
                                                 void *),
                             void * keyData=(void *)0);
//---- Specific ----
// Static methods
  static void addShape(XGuiShape2D * shape);
  static void removeShape(XGuiShape2D * shape);
  inline static void forceRedraw(void);
  static void drawAll(void);
// Allocators
// Inspectors
  inline virtual XGuiElement::Type getElemType(void) const;
  inline virtual bool isA(XGuiElement::Type type) const;
  inline Pixmap getPixmap(void) const;
  inline double getXmin(void) const;
  inline double getYmin(void) const;
  inline double getXmax(void) const;
  inline double getYmax(void) const;
  inline int getColumn(double x) const;
  inline int getLine(double y) const;
  inline unsigned long getBackgroundPixel(void) const;
// Modifiers
  virtual void processEvent(const XEvent & event);
  virtual void redraw(void);
  void drawBoundingBox(const XGuiShape2D * shape);
protected:
  void _chooseCursor(void);
// Attributes
  Pixmap _pixmap;
  double _scale;
  double _xmin,_ymin,_xmax,_ymax;
  Strings _color;
  unsigned long _pixel;
  XGuiShapeList _select;
  bool _ctrlPressed;
  unsigned int _pressed;
  bool _canMoveSelection;
  int _mouseX;
  int _mouseY;
  void (*_keyCallback)(XGuiViewer2D *,const Strings &,void *);
  void * _keyData;
  static XGuiViewerList _viewers;
  static XGuiShapeList _shapes;
  static bool _mustDraw;
};

#include "XGui/xgView2d.Ci"

#endif // XGVIEW2D_H

