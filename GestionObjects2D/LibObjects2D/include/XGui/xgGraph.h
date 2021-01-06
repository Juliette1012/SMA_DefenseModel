#ifndef XGGRAPH_H
#define XGGRAPH_H

#include "Utility/stlList.h"
#include "Utility/stlMap.h"

#include "XGui/xgElem.h"

//--------------------------------------------------------------------------//
// class XGuiGrapher                                                        //
//--------------------------------------------------------------------------//

class XGuiArea;

class XGuiCurve;
typedef StlMap<Strings,XGuiCurve *> XGuiCurveMap;

class XGuiGrapher;
typedef StlList<XGuiGrapher *> XGuiGrapherList;

class XGuiGrapher : public XGuiElement
{
public:
// Allocators
  XGuiGrapher(XGuiArea * parent);
  virtual ~XGuiGrapher(void);
// Inspectors
  inline double getXmin(void) const;
  inline double getYmin(void) const;
  inline double getXmax(void) const;
  inline double getYmax(void) const;
  inline const Strings & getBackground(void) const;
// Modifiers
  void setBackground(const Strings & color);
  void setViewPoint(double xmin,double ymin,double xmax,double ymax);
  void autoScale(void);
  void autoScaleX(void);
  void autoScaleY(void);
  void addPoint(const Strings & color,double x,double y);
  void accumulatePoint(const Strings & color,double x,double y);
  void clear(const Strings & color);
  virtual void setWidth(int width);
  virtual void setHeight(int height);
  virtual void show(void);
  virtual void hide(void);
//---- Specific ----
// Static methods
  inline static void forceRedraw(void);
  static void drawAll(void);
// Allocators
// Inspectors
  inline virtual XGuiElement::Type getElemType(void) const;
  inline virtual bool isA(XGuiElement::Type type) const;
  inline double getXScale(void) const;
  inline double getYScale(void) const;
  inline int getColumn(double x) const;
  inline int getLine(double y) const;
  inline unsigned long getBackgroundPixel(void) const;
  inline Pixmap getPixmap(void) const;
// Modifiers
  virtual void processEvent(const XEvent & event);
  virtual void redraw(void);
protected:
  void _drawAxis(void);
  void _chooseCursor(void);
// Attributes
  double _xScale,_yScale;
  double _xmin,_ymin,_xmax,_ymax;
  Strings _color;
  unsigned long _pixel;
  unsigned long _textPixel;
  XGuiCurveMap _curveMap;
  int _drawX,_drawY;
  int _drawWidth,_drawHeight;
  bool _ctrlPressed;
  unsigned int _pressed;
  int _mouseX;
  int _mouseY;
  Pixmap _pixmap;
  Region _region;
  static XGuiGrapherList _graphers;
  static bool _mustDraw;
};

#include "XGui/xgGraph.Ci"

#endif // XGGRAPH_H

