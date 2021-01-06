#ifndef XGSHAP3D_H
#define XGSHAP3D_H

#include "XGui/xgMgr.h"

#include "Utility/strings.h"
#include "Utility/stlVect.h"
#include "Utility/stlMap.h"

#include <GL/gl.h>

//--------------------------------------------------------------------------//
// class XGuiShape3D                                                        //
//--------------------------------------------------------------------------//

class XGui3DPoint
{
public:
  inline XGui3DPoint(void);
  inline XGui3DPoint(double x0,double y0,double z0);
  inline XGui3DPoint(const XGui3DPoint & p);
  inline virtual ~XGui3DPoint(void);
  inline XGui3DPoint & operator=(const XGui3DPoint & p);
  double x,y,z;
};

typedef StlVector<XGui3DPoint> XGui3DPointVect;

class XGui3DTriangle
{
public:
  inline XGui3DTriangle(void);
  inline XGui3DTriangle(int pt1,int pt2,int pt3);
  inline XGui3DTriangle(const XGui3DTriangle & t);
  inline virtual ~XGui3DTriangle(void);
  inline XGui3DTriangle & operator=(const XGui3DTriangle & t);
  int p1,p2,p3;
  double dx1,dy1,dz1;
  double dx2,dy2,dz2;
  double dx3,dy3,dz3;
};

typedef StlVector<XGui3DTriangle> XGui3DTriangleVect;

class XGui3DColor
{
public:
  inline XGui3DColor(void);
  inline XGui3DColor(float red,float green,float blue,int colRange);
  inline XGui3DColor(Strings color,int range);
  inline XGui3DColor(const XGui3DColor & c);
  inline virtual ~XGui3DColor(void);
  inline XGui3DColor & operator=(const XGui3DColor & c);
  float r,g,b;
  int range;
};

typedef StlVector<XGui3DColor> XGui3DColorVect;

class XGui3DTexture
{
public:
  inline XGui3DTexture(void);
  inline XGui3DTexture(Strings fileName,int faceNumber,
                       float px1,float py1,
                       float px2,float py2,
                       float px3,float py3);
  inline XGui3DTexture(const XGui3DTexture & t);
  inline virtual ~XGui3DTexture(void);
  inline XGui3DTexture & operator=(const XGui3DTexture & t);
  Strings name;
  int face;
  float x1,y1,x2,y2,x3,y3;
};
 
typedef StlVector<XGui3DTexture> XGui3DTextureVect;

class XGuiShape3D;

class XGuiViewer3D;

class XGuiShape3D
{
public:
// Static methods
  static void buildCube(XGui3DPointVect & points,
                        XGui3DTriangleVect & faces);
  static void buildCone(XGui3DPointVect & points,
                        XGui3DTriangleVect & faces,
                        int precision);
  static void buildCylinder(XGui3DPointVect & points,
                            XGui3DTriangleVect & faces,
                            int precision);
  static void buildTube(XGui3DPointVect & points,
                        XGui3DTriangleVect & faces,
                        int precision, double rate);
  static void buildSquareTube(XGui3DPointVect & points,
                              XGui3DTriangleVect & faces,
                              double rate);
  static void buildSphere(XGui3DPointVect & points,
                          XGui3DTriangleVect & faces,
                          int zPrecision,int xyPrecision);
  static void buildGeode(XGui3DPointVect & points,
                         XGui3DTriangleVect & faces,
                         int slices,int precision);
  static void buildText(XGui3DPointVect & points,
                        XGui3DTriangleVect & faces,
                        const Strings & text,double spacing);
  static double buildLetter(XGui3DPointVect & points,
                            XGui3DTriangleVect & faces,
                            char letter);
  static void reverseFaces(XGui3DTriangleVect & faces);
  static void translatePoints(XGui3DPointVect & points,
                              double dx,double dy,double dz);
  static void scalePoints(XGui3DPointVect & points,
                          double sx,double sy,double sz);
  static void rollPoints(XGui3DPointVect & points,double roll);
  static void pitchPoints(XGui3DPointVect & points,double pitch);
  static void yawPoints(XGui3DPointVect & points,double yaw);
// Allocators
  XGuiShape3D(void);
  XGuiShape3D(const XGuiShape3D & s);
  virtual ~XGuiShape3D(void);
  virtual XGuiShape3D * duplicate(void) const;
// Inspectors
  inline void getPosition(double & px,double & py,double & pz) const;
  void globalToLocalPosition(double & x,double & y,double & z) const;
  void localToGlobalPosition(double & x,double & y,double & z) const;
  void getOrientation(double & roll,double & pitch,double & yaw) const;
  void globalToLocalOrientation(double & roll,
                                double & pitch,double & yaw) const;
  void localToGlobalOrientation(double & roll,
                                double & pitch,double & yaw) const;
  inline bool getLocalBoundingBox(double & xmin,double & ymin,double & zmin,
                                  double & xmax,double & ymax,double & zmax)
                                                                      const;
  inline bool getGlobalBoundingBox(double & xmin,double & ymin,double & zmin,
                                   double & xmax,double & ymax,double & zmax)
                                                                       const;
  bool isInside(double x,double y,double z) const;
  bool intersectRay(double xRay,double yRay,double zRay,
                    double xDir,double yDir,double zDir,
                    double & x,double & y,double & z,
                    int & faceNumber) const;
// Input/Output
  friend ostream & operator<<(ostream & stream,const XGuiShape3D & shape);
  virtual Strings print(void) const;
// Modifiers
  void setPosition(double px,double py,double pz);
  void cancelRotation(void);
  void setOrientation(double roll,double pitch,double yaw);
  void translate(double dx,double dy,double dz);
  void roll(double dRoll);
  void pitch(double dPitch);
  void yaw(double dYaw);
  bool setShape(const XGui3DPointVect & points,
                const XGui3DTriangleVect & faces,
                const XGui3DColorVect & colors,
                const XGui3DTextureVect & textures,
                const StringsVect * pathVect);
  inline void setKeyCallback(void (*keyCallback)(XGuiShape3D *,
                                                 const Strings &,
                                                 void *),
                             void * keyData=(void *)0);
  inline void setMotionCallback(void (*motionCallback)(XGuiShape3D *,
                                                       double,double,double,
                                                       void *),
                                void * motionData=(void *)0);
  inline void setSelectCallback(void (*selectCallback)(XGuiShape3D *,
                                                       XGuiViewer3D *,
                                                       bool,
                                                       void *),
                                void * selectData=(void *)0);
//---- Specific ----
// Allocators
// Inspectors
  inline const XGui3DPointVect & getPoints(void) const;
  inline const XGui3DTriangleVect & getFaces(void) const;
  inline const XGui3DColorVect & getColors(void) const;
  inline const XGui3DTextureVect & getTextures(void) const;
// Modifiers
  inline virtual void draw(void);
  void drawBoundingBox(float r,float g,float b);
  inline void notifyKey(const Strings & key);
  inline void notifyMotion(double x,double y,double z);
  inline void notifySelection(XGuiViewer3D * viewer,bool selected);
protected:
  void _buildGeom(void);
  void _buildShape(void);
  void _buildTriangle(int face);
  void _buildTexture(int face,int numTexture);
  bool _loadTexture(const XGui3DTexture & texture,
                    const StringsVect * pathVect);
  bool _intersectFace(int face,double xRay,double yRay,double zRay,
                      double xDir,double yDir,double zDir,
                      double & k) const;
// Attributes 
  double _px,_py,_pz;
  double _r00,_r01,_r02;
  double _r10,_r11,_r12;
  double _r20,_r21,_r22;
  double _xmin,_xmax;
  double _ymin,_ymax;
  double _zmin,_zmax;
  int _shapeList;
  int _geomList;
  int _boundingBoxList;
  XGui3DPointVect _points;
  XGui3DTriangleVect _faces;
  XGui3DColorVect _colors;
  XGui3DTextureVect _textures;
  void (*_keyCallback)(XGuiShape3D *,const Strings &,void *);
  void * _keyData;
  void (*_motionCallback)(XGuiShape3D *,double,double,double,void *);
  void * _motionData;
  void (*_selectCallback)(XGuiShape3D *,XGuiViewer3D *,bool,void *);
  void * _selectData;
  typedef StlMap<Strings,unsigned int> TextureMap;
  static TextureMap _textureMap;
  static const double PRECISION_SIN;
};

#include "XGui/xgShap3d.Ci"

#endif // XGSHAP3D_H

