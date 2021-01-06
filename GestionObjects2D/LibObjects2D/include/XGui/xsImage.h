#ifndef XSIMAGE_H
#define XSIMAGE_H

#include "Utility/stlMap.h"

#include "XGui/xgShap2d.h"

//--------------------------------------------------------------------------//
// class XGuiImage                                                         //
//--------------------------------------------------------------------------//

class XGuiViewer2D;
class XGuiImageDraw
{
public:
  Pixmap pixmap;
  Region region;
  int pixX;
  int pixY;
  int pixWidth;
  int pixHeight;
  double xmin;
  double ymin;
  double scale;
  double xOffset;
  double yOffset;
};
typedef StlMap<XGuiViewer2D *,XGuiImageDraw *> DrawMap;

class XGuiImage : public XGuiShape2D
{
public:
// Allocators
  XGuiImage(double x,double y,double theta,const Strings & color,
            const Strings & fileName,const StringsVect * pathVect,
            double scale);
  XGuiImage(const XGuiImage & s);
  virtual ~XGuiImage(void);
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
  inline int getNbColors(void) const;
  inline unsigned long getPixel(int x,int y) const;
  inline int getNbColumns(void) const;
  inline int getNbLines(void) const;
  inline const Strings & getFileName(void) const;
  inline double getScale(void) const;
  inline bool fail(void) const;
  inline void getRGB(unsigned long pixel,unsigned char & r,
                     unsigned char & g,unsigned char & b) const;
// Input/Output
  virtual Strings print(void) const;
// Modifiers
  void setPixel(int x,int y,unsigned long pixel);
  void sortColors(void);
//---- Specific ----
// Allocators
// Inspectors
  inline virtual double distanceTo(double x,double y,
                                   const XGuiViewer2D * viewer) const;
// Modifiers
  virtual void addViewer(XGuiViewer2D * viewer);
  virtual void removeViewer(XGuiViewer2D * viewer);
  virtual void changedViewerBackground(XGuiViewer2D * viewer);
  virtual void drawInViewer(XGuiViewer2D * viewer);
  inline virtual void computePosition(void);
  inline virtual void savePosition(void);
// Attributes
protected:
  int _nbColumns;
  int _nbLines;
  double _scale;
  Strings _fileName;
  unsigned char * _red;
  unsigned char * _green;
  unsigned char * _blue;
  unsigned long * _colors;
  int _nbColors;
  unsigned long * _pixels;
  bool _fail;
  DrawMap _drawMap;
  double _l_2;  // half length
  double _w_2;  // half width
  double _dx,_dy;
  double _coordX[4];
  double _coordY[4];
  double _oldCoordX[4];
  double _oldCoordY[4];
};

#include "XGui/xsImage.Ci"

#endif // XSIMAGE_H

