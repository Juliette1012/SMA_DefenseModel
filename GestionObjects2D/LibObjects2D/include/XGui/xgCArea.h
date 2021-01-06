#ifndef XGCAREA_H
#define XGCAREA_H

#include "XGui/xgArea.h"

//--------------------------------------------------------------------------//
// class XGuiColorArea                                                      //
//--------------------------------------------------------------------------//

class XGuiColorArea : public XGuiArea
{
public:
// Allocators
  XGuiColorArea(XGuiArea * parent,const Strings & color);
  virtual ~XGuiColorArea(void);
// Inspectors
  const Strings & getColor(void) const;
// Modifiers
  void setColor(const Strings & color);
  virtual void show(void);
//---- Specific ----
// Inspectors
  virtual XGuiElement::Type getElemType(void) const;
  virtual bool isA(XGuiElement::Type type) const;
  unsigned long getPixel(void) const;
protected:
// Attributes
  Strings _color;
  bool _allocated;
  unsigned long _pixel;
};

#endif // XGCAREA_H

