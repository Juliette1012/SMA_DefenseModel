#ifdef X_GUI
#ifdef OPEN_GL

#include "XGui/xgShap3d.h"
#include "XGui/xgView3d.h"
#include "XGui/xgMgr.h"

#include <math.h>

//--------------------------------------------------------------------------//
// class XGuiShape3D                                                        //
//--------------------------------------------------------------------------//

StlMap<Strings,unsigned int> XGuiShape3D::_textureMap;

const double XGuiShape3D::PRECISION_SIN=1.0-1.0e-9;

//-------- Static methods --------------------------------------------------//
void XGuiShape3D::buildCube(XGui3DPointVect & points,
                            XGui3DTriangleVect & faces) // static
{
int o=points.size();
points.push_back(XGui3DPoint(-0.5,-0.5,-0.5));   // points
points.push_back(XGui3DPoint(+0.5,-0.5,-0.5));
points.push_back(XGui3DPoint(+0.5,-0.5,+0.5));
points.push_back(XGui3DPoint(-0.5,-0.5,+0.5));
points.push_back(XGui3DPoint(-0.5,+0.5,-0.5));
points.push_back(XGui3DPoint(+0.5,+0.5,-0.5));
points.push_back(XGui3DPoint(+0.5,+0.5,+0.5));
points.push_back(XGui3DPoint(-0.5,+0.5,+0.5));
faces.push_back(XGui3DTriangle(o+4,o+0,o+3));    // x neg
faces.push_back(XGui3DTriangle(o+4,o+3,o+7));
faces.push_back(XGui3DTriangle(o+1,o+5,o+6));    // x pos
faces.push_back(XGui3DTriangle(o+1,o+6,o+2));
faces.push_back(XGui3DTriangle(o+0,o+1,o+2));    // y neg
faces.push_back(XGui3DTriangle(o+0,o+2,o+3));
faces.push_back(XGui3DTriangle(o+5,o+4,o+7));    // y pos
faces.push_back(XGui3DTriangle(o+5,o+7,o+6));
faces.push_back(XGui3DTriangle(o+0,o+4,o+5));    // z neg
faces.push_back(XGui3DTriangle(o+0,o+5,o+1));
faces.push_back(XGui3DTriangle(o+3,o+2,o+6));    // z pos
faces.push_back(XGui3DTriangle(o+3,o+6,o+7));
}

void XGuiShape3D::buildCone(XGui3DPointVect & points,
                            XGui3DTriangleVect & faces,
                            int precision) // static
{
int o=points.size();
if(precision<3) precision=3;
double angle=2.0*M_PI/precision;
points.push_back(XGui3DPoint(0.0,0.0,1.0));
points.push_back(XGui3DPoint(0.0,0.0,0.0));
int i;
for(i=0;i<precision;i++)                                 // points
  {
  double alpha=angle*i;
  points.push_back(XGui3DPoint(0.5*::cos(alpha),0.5*::sin(alpha),0.0));
  }
int p1=2+(precision-1);
int p2=2;
for(i=0;i<precision;i++)
  {
  faces.push_back(XGui3DTriangle(o,o+p1,o+p2));          // side
  faces.push_back(XGui3DTriangle(o+1,o+p2,o+p1));        // bottom
  p1=p2;
  p2++;
  }
}

void XGuiShape3D::buildCylinder(XGui3DPointVect & points,
                                XGui3DTriangleVect & faces,
                                int precision) // static
{
int o=points.size();
if(precision<3) precision=3;
double angle=2.0*M_PI/precision;
points.push_back(XGui3DPoint(0.0,0.0,+0.5));
points.push_back(XGui3DPoint(0.0,0.0,-0.5));
int i;
for(i=0;i<precision;i++)                                 // points
  {
  double alpha=angle*i;
  points.push_back(XGui3DPoint(0.5*::cos(alpha),0.5*::sin(alpha),+0.5));
  alpha=angle*(i+0.5);
  points.push_back(XGui3DPoint(0.5*::cos(alpha),0.5*::sin(alpha),-0.5));
  }
int p1,p2;
p1=2+(precision-1)*2;                                    // z pos
p2=2;
for(i=0;i<precision;i++)
  {
  faces.push_back(XGui3DTriangle(o,o+p1,o+p2));
  p1=p2;
  p2+=2;
  }
p1=3;                                                    // z neg
p2=3+(precision-1)*2;
for(i=0;i<precision;i++)
  {
  faces.push_back(XGui3DTriangle(o+1,o+p1,o+p2));
  p2=p1;
  p1+=2;
  }
p1=2+(precision-1)*2;                                    // side
p2=2;
for(i=0;i<precision;i++)
  {
  faces.push_back(XGui3DTriangle(o+p1,o+1+p1,o+p2));
  faces.push_back(XGui3DTriangle(o+1+p1,o+1+p2,o+p2));
  p1=p2;
  p2+=2;
  }
}

void XGuiShape3D::buildTube(XGui3DPointVect & points,
                            XGui3DTriangleVect & faces,
                            int precision, double rate) // static
{
int o=points.size();
if(precision<3) precision=3;
double angle=2.0*M_PI/precision;
points.push_back(XGui3DPoint(0.0,0.0,+0.5));
points.push_back(XGui3DPoint(0.0,0.0,-0.5));
int i;
for(i=0;i<precision;i++)                                 // points
  {
  double alpha1=angle*i;
  points.push_back(XGui3DPoint(0.5*::cos(alpha1),0.5*::sin(alpha1),+0.5));
  alpha1=angle*(i+0.5);
  points.push_back(XGui3DPoint(0.5*::cos(alpha1),0.5*::sin(alpha1),-0.5));
  }
for(i=0;i<precision;i++)                                 // points
  {
  double alpha2=angle*i;
  points.push_back(XGui3DPoint(rate*0.5*::cos(alpha2),
                               rate*0.5*::sin(alpha2),+0.5));
  alpha2=angle*(i+0.5);
  points.push_back(XGui3DPoint(rate*0.5*::cos(alpha2),
                               rate*0.5*::sin(alpha2),-0.5));
  }
int p1,p2,p3;
p1=2+precision*2;                                    // z pos 1
p2=precision*4;
p3=precision*2;
for(i=0;i<precision;i++)
  {
  faces.push_back(XGui3DTriangle(o+p1,o+p2,o+p3));
  p1=p2;
  p2-=2;
  p3-=2;
  }
p1=2+(precision-1)*2;                                // z pos 2
p2=2;
p3=p1+2;
for(i=0;i<precision;i++)
  {
  faces.push_back(XGui3DTriangle(o+p1,o+p2,o+p3));
  p1=p2;
  p2+=2;
  p3+=2;
  }
p1=3+precision*2;                                    // z neg 1
p2=1+precision*4;
p3=1+precision*2;
for(i=0;i<precision;i++)
  {
  faces.push_back(XGui3DTriangle(o+p3,o+p2,o+p1));
  p1=p2;
  p2-=2;
  p3-=2;
  }
p1=3+(precision-1)*2;                                // z neg 2
p2=3;
p3=p1+2;
for(i=0;i<precision;i++)
  {
  faces.push_back(XGui3DTriangle(o+p3,o+p2,o+p1));
  p1=p2;
  p2+=2;
  p3+=2;
  }
p1=2+(precision-1)*2;                                // side out
p2=2;
for(i=0;i<precision;i++)
  {
  faces.push_back(XGui3DTriangle(o+p1,o+1+p1,o+p2));
  faces.push_back(XGui3DTriangle(o+1+p1,o+1+p2,o+p2));
  p1=p2;
  p2+=2;
  }
p1=precision*4;                                    // side in
p2=precision*2+2;
for(i=0;i<precision;i++)
  {
  faces.push_back(XGui3DTriangle(o+p2,o+1+p1,o+p1));
  faces.push_back(XGui3DTriangle(o+p2,o+1+p2,o+1+p1));
  p1=p2;
  p2+=2;
  }
}

void XGuiShape3D::buildSquareTube(XGui3DPointVect & points,
                                  XGui3DTriangleVect & faces,
                                  double rate) // static
{
int o=points.size();
points.push_back(XGui3DPoint(0.5,-0.5,0.5));             // point 0
points.push_back(XGui3DPoint(0.5,-0.5,-0.5));            // point 1 
points.push_back(XGui3DPoint(0.5,0.5,0.5));              // point 2
points.push_back(XGui3DPoint(0.5,0.5,-0.5));             // point 3
points.push_back(XGui3DPoint(-0.5,0.5,0.5));             // point 4
points.push_back(XGui3DPoint(-0.5,0.5,-0.5));            // point 5
points.push_back(XGui3DPoint(-0.5,-0.5,0.5));            // point 6
points.push_back(XGui3DPoint(-0.5,-0.5,-0.5));           // point 7
points.push_back(XGui3DPoint(0.5*rate,-0.5*rate,0.5));   // point 8
points.push_back(XGui3DPoint(0.5*rate,-0.5*rate,-0.5));  // point 9 
points.push_back(XGui3DPoint(0.5*rate,0.5*rate,0.5));    // point 10
points.push_back(XGui3DPoint(0.5*rate,0.5*rate,-0.5));   // point 11
points.push_back(XGui3DPoint(-0.5*rate,0.5*rate,0.5));   // point 12
points.push_back(XGui3DPoint(-0.5*rate,0.5*rate,-0.5));  // point 13
points.push_back(XGui3DPoint(-0.5*rate,-0.5*rate,0.5));  // point 14
points.push_back(XGui3DPoint(-0.5*rate,-0.5*rate,-0.5)); // point 15
faces.push_back(XGui3DTriangle(o,o+1,o+2));
faces.push_back(XGui3DTriangle(o+1,o+3,o+2));
faces.push_back(XGui3DTriangle(o+2,o+3,o+4));
faces.push_back(XGui3DTriangle(o+3,o+5,o+4));
faces.push_back(XGui3DTriangle(o+4,o+5,o+6));
faces.push_back(XGui3DTriangle(o+5,o+7,o+6));
faces.push_back(XGui3DTriangle(o+6,o+7,o));
faces.push_back(XGui3DTriangle(o+7,o+1,o));
faces.push_back(XGui3DTriangle(o+10,o+9,o+8));
faces.push_back(XGui3DTriangle(o+10,o+11,o+9));
faces.push_back(XGui3DTriangle(o+12,o+11,o+10));
faces.push_back(XGui3DTriangle(o+12,o+13,o+11));
faces.push_back(XGui3DTriangle(o+14,o+13,o+12));
faces.push_back(XGui3DTriangle(o+14,o+15,o+13));
faces.push_back(XGui3DTriangle(o+8,o+15,o+14));
faces.push_back(XGui3DTriangle(o+8,o+9,o+15));
faces.push_back(XGui3DTriangle(o,o+2,o+8));
faces.push_back(XGui3DTriangle(o+2,o+10,o+8));
faces.push_back(XGui3DTriangle(o+2,o+4,o+10));
faces.push_back(XGui3DTriangle(o+4,o+12,o+10));
faces.push_back(XGui3DTriangle(o+4,o+6,o+12));
faces.push_back(XGui3DTriangle(o+6,o+14,o+12));
faces.push_back(XGui3DTriangle(o+6,o,o+14));
faces.push_back(XGui3DTriangle(o,o+8,o+14));
faces.push_back(XGui3DTriangle(o+9,o+3,o+1));
faces.push_back(XGui3DTriangle(o+9,o+11,o+3));
faces.push_back(XGui3DTriangle(o+11,o+5,o+3));
faces.push_back(XGui3DTriangle(o+11,o+13,o+5));
faces.push_back(XGui3DTriangle(o+13,o+7,o+5));
faces.push_back(XGui3DTriangle(o+13,o+15,o+7));
faces.push_back(XGui3DTriangle(o+15,o+1,o+7));
faces.push_back(XGui3DTriangle(o+15,o+9,o+1));
}

void XGuiShape3D::buildSphere(XGui3DPointVect & points,
                              XGui3DTriangleVect & faces,
                              int zPrecision,int xyPrecision) // static
{
int o=points.size();
if(zPrecision<2) zPrecision=2;
double zAngle=M_PI/zPrecision;
if(xyPrecision<3) xyPrecision=3;
double xyAngle=2.0*M_PI/xyPrecision;
points.push_back(XGui3DPoint(0.0,0.0,+0.5));
points.push_back(XGui3DPoint(0.0,0.0,-0.5));
int i,j;
for(i=0;i<xyPrecision;i++)                               // points
  {
  for(j=1;j<zPrecision;j++)
    {
    double z=0.5*::cos(j*zAngle);
    double r=0.5*::sin(j*zAngle);
    double alpha=xyAngle*(j%2 ? (i-0.25) : (i+0.25));
    points.push_back(XGui3DPoint(r*::cos(alpha),r*::sin(alpha),z));
    }
  }
int p1,p2;
p1=2+(xyPrecision-1)*(zPrecision-1);                     // z pos
p2=2;
for(i=0;i<xyPrecision;i++)
  {
  faces.push_back(XGui3DTriangle(o,o+p1,o+p2));
  p1=p2;
  p2+=zPrecision-1;
  }
p1=zPrecision;                                           // z neg
p2=zPrecision+(xyPrecision-1)*(zPrecision-1);
for(i=0;i<xyPrecision;i++)
  {
  faces.push_back(XGui3DTriangle(o+1,o+p1,o+p2));
  p2=p1;
  p1+=zPrecision-1;
  }
for(j=1;j<zPrecision-1;j++)                              // side
  {
  p1=1+j+(xyPrecision-1)*(zPrecision-1);
  p2=1+j;
  for(i=0;i<xyPrecision;i++)
    {
    if(j%2)
      {
      faces.push_back(XGui3DTriangle(o+p1,o+1+p1,o+p2));
      faces.push_back(XGui3DTriangle(o+1+p1,o+1+p2,o+p2));
      }
    else
      {
      faces.push_back(XGui3DTriangle(o+p1,o+1+p1,o+1+p2));
      faces.push_back(XGui3DTriangle(o+p1,o+1+p2,o+p2));
      }
    p1=p2;
    p2+=zPrecision-1;
    }
  }
}

void XGuiShape3D::buildGeode(XGui3DPointVect & points,
                             XGui3DTriangleVect & faces,
                             int slices,int precision) // static
{
if(slices<3) slices=3;
int p=precision/slices;
if((precision%slices)||(p<1)) p++; // ensure precision is a multiple of slices
int o=points.size();
points.push_back(XGui3DPoint(0.0,0.0,0.5));
points.push_back(XGui3DPoint(0.0,0.0,-0.5));
int p1=o+2;
int p2=o;
double dzAngle=0.5*M_PI/(double)p;
for(int raw=1;raw<=p;raw++)
  {
  int nb=slices*raw;
  double zAngle=dzAngle*(double)raw;
  double z=0.5*cos(zAngle);
  double radius=0.5*sin(zAngle);
  double dxyAngle=2.0*M_PI/(double)nb;
  for(int col=0;col<nb;col++)
    {
    double xyAngle=dxyAngle*(double)col;
    points.push_back(XGui3DPoint(radius*cos(xyAngle),radius*sin(xyAngle),z));
    points.push_back(XGui3DPoint(radius*cos(xyAngle),-radius*sin(xyAngle),-z));
    }
  int startP1=p1;
  int startP2=p2;
  for(int i=slices;i--;)
    {
    for(int j=raw-1;j--;)
      {
      faces.push_back(XGui3DTriangle(p1,p1+2,p2));
      faces.push_back(XGui3DTriangle(p1+1,p1+3,p2+1));
      if(i||j)
        {
        faces.push_back(XGui3DTriangle(p2,p1+2,p2+2));
        faces.push_back(XGui3DTriangle(p2+1,p1+3,p2+3));
        }
      else
        {
        faces.push_back(XGui3DTriangle(p2,p1+2,startP2));
        faces.push_back(XGui3DTriangle(p2+1,p1+3,startP2+1));
        }
      p1+=2;
      p2+=2;
      }
    if(i)
      {
      faces.push_back(XGui3DTriangle(p1,p1+2,p2));
      faces.push_back(XGui3DTriangle(p1+1,p1+3,p2+1));
      }
    else
      {
      faces.push_back(XGui3DTriangle(p1,startP1,startP2));
      faces.push_back(XGui3DTriangle(p1+1,startP1+1,startP2+1));
      }
    p1+=2;
    }
  p2=startP1;
  p1=p2+2*nb;
  }
}

void XGuiShape3D::buildText(XGui3DPointVect & points,
                            XGui3DTriangleVect & faces,
                            const Strings & text,
                            double spacing) // static
{
double advance;
double shift=0.0;
for(size_t i=0;i<text.len();i++)
  {
  advance=spacing+XGuiShape3D::buildLetter(points,faces,text[i]);
  XGuiShape3D::translatePoints(points,-advance,0.0,0.0);
  shift+=advance;
  }
XGuiShape3D::translatePoints(points,shift,0.0,0.0);
}

double XGuiShape3D::buildLetter(XGui3DPointVect & points,
                                XGui3DTriangleVect & faces,
                                char letter) // static
{
double * pointArray;
int * faceArray;
int nbPoints,nbFaces;
double advance;
switch(letter)
  {
#include "XGui/Font3d/font3d.h"
  }
int o=points.size();
int i;
for(i=0;i<nbPoints;i++)
  {
  points.push_back(XGui3DPoint(pointArray[3*i],
                               pointArray[3*i+1],
                               pointArray[3*i+2]));
  }
for(i=0;i<nbFaces;i++)
  {
  faces.push_back(XGui3DTriangle(o+faceArray[3*i],
                                 o+faceArray[3*i+1],
                                 o+faceArray[3*i+2]));
  }
return(advance);
}

void XGuiShape3D::reverseFaces(XGui3DTriangleVect & faces) // static
{
int tmp;
for(int i=faces.size();i--;)
  {
  tmp=faces[i].p1;
  faces[i].p1=faces[i].p3;
  faces[i].p3=tmp;
  }
}

void XGuiShape3D::translatePoints(XGui3DPointVect & points,
                                  double dx,double dy,double dz) // static
{
for(int i=points.size();i--;)
  {
  points[i].x+=dx;
  points[i].y+=dy;
  points[i].z+=dz;
  }
}

void XGuiShape3D::scalePoints(XGui3DPointVect & points,
                              double sx,double sy,double sz) // static
{
for(int i=points.size();i--;)
  {
  points[i].x*=sx;
  points[i].y*=sy;
  points[i].z*=sz;
  }
}

void XGuiShape3D::rollPoints(XGui3DPointVect & points,double roll) // static
{
double c=::cos(roll);
double s=::sin(roll);
double y,z;
for(int i=points.size();i--;)
  {
  y=points[i].y;
  z=points[i].z;
  points[i].y=+y*c-z*s;
  points[i].z=+y*s+z*c;
  }
}

void XGuiShape3D::pitchPoints(XGui3DPointVect & points,double pitch) // static
{                            
double c=::cos(pitch);
double s=::sin(pitch);
double x,z;
for(int i=points.size();i--;)
  {
  x=points[i].x;
  z=points[i].z;
  points[i].x=+x*c+z*s;
  points[i].z=-x*s+z*c;
  }
}

void XGuiShape3D::yawPoints(XGui3DPointVect & points,double yaw) // static
{
double c=::cos(yaw);
double s=::sin(yaw);
double x,y;
for(int i=points.size();i--;)
  {
  x=points[i].x;
  y=points[i].y;
  points[i].x=+x*c-y*s;
  points[i].y=+x*s+y*c;
  }
}

//-------- Allocators ------------------------------------------------------//
XGuiShape3D::XGuiShape3D(void)
 : _px(0.0), _py(0.0), _pz(0.0),
   _r00(1.0), _r01(0.0), _r02(0.0),
   _r10(0.0), _r11(1.0), _r12(0.0),
   _r20(0.0), _r21(0.0), _r22(1.0),
   _xmin(0.0), _xmax(0.0),
   _ymin(0.0), _ymax(0.0),
   _zmin(0.0), _zmax(0.0),
   _shapeList(0), _geomList(0), _boundingBoxList(0),
   _points(), _faces(), _colors(), _textures(),
   _keyCallback((void (*)(XGuiShape3D *,const Strings &,void *))0),
   _keyData((void *)0),
   _motionCallback((void (*)(XGuiShape3D *,double,double,double,void *))0),
   _motionData((void *)0),
   _selectCallback((void (*)(XGuiShape3D *,XGuiViewer3D *,bool,void *))0),
   _selectData((void *)0)
{
_shapeList=glGenLists(1);
_geomList=glGenLists(1);
_boundingBoxList=glGenLists(1);
if(!_shapeList||!_geomList||!_boundingBoxList) cerr << "PB LIST" << endl;
_buildShape();
_buildGeom();
XGuiViewer3D::addShape(this);
}

XGuiShape3D::XGuiShape3D(const XGuiShape3D & s)
 : _px(s._px), _py(s._py), _pz(s._pz),
   _r00(s._r00), _r01(s._r01), _r02(s._r02),
   _r10(s._r10), _r11(s._r11), _r12(s._r12),
   _r20(s._r20), _r21(s._r21), _r22(s._r22),
   _xmin(s._xmin), _xmax(s._xmax),
   _ymin(s._ymin), _ymax(s._ymax),
   _zmin(s._zmin), _zmax(s._zmax),
   _shapeList(0), _geomList(0), _boundingBoxList(0),
   _points(s._points), _faces(s._faces),
   _colors(s._colors), _textures(s._textures),
   _keyCallback(s._keyCallback), _keyData(s._keyData),
   _motionCallback(s._motionCallback), _motionData(s._motionData),
   _selectCallback(s._selectCallback), _selectData(s._selectData)
{
_shapeList=glGenLists(1);
_geomList=glGenLists(1);
_boundingBoxList=glGenLists(1);
_buildShape();
_buildGeom();
XGuiViewer3D::addShape(this);
}

XGuiShape3D::~XGuiShape3D(void)
{
glDeleteLists(_boundingBoxList,1);
glDeleteLists(_geomList,1);
glDeleteLists(_shapeList,1);
XGuiViewer3D::removeShape(this);
}

XGuiShape3D * XGuiShape3D::duplicate(void) const // virtual
{
return(new XGuiShape3D(*this));
}

//-------- Inspectors ------------------------------------------------------//
// inline void XGuiShape3D::getPosition(double & px,double & py,double & pz)
//                                                                     const

void XGuiShape3D::globalToLocalPosition(double & x,double & y,double & z)
                                                                    const
{
x-=_px;
y-=_py;
z-=_pz;
double xl=_r00*x+_r10*y+_r20*z;
double yl=_r01*x+_r11*y+_r21*z;
double zl=_r02*x+_r12*y+_r22*z;
x=xl;
y=yl;
z=zl;
}

void XGuiShape3D::localToGlobalPosition(double & x,double & y,double & z)
                                                                    const
{
double xg=_r00*x+_r01*y+_r02*z;
double yg=_r10*x+_r11*y+_r12*z;
double zg=_r20*x+_r21*y+_r22*z;
x=xg+_px;
y=yg+_py;
z=zg+_pz;
}

void XGuiShape3D::getOrientation(double & roll,double & pitch,double & yaw)
                                                                      const
{
//      _                                _
//     |  c2c3  s1s2c3-c1s3  s1s3+c1s2c3  |  s1,c1 : roll
//     |  c2s3  c1c3+s1s2s3  c1s2s3-s1c3  |  s2,c2 : pitch
//     |_ -s2   s1c2         c1c2        _|  s3,c3 : yaw
//
if(_r20<=-PRECISION_SIN)
  {
  pitch=M_PI_2;
  yaw=0.0; // make a choice
  roll=::atan2(-_r12,_r11);
  }
else if(_r20>=PRECISION_SIN)
  {
  pitch=-M_PI_2;
  yaw=0.0; // make a choice
  roll=::atan2(-_r12,_r11);
  }
else
  {
  roll=::atan2(_r21,_r22);
  pitch=::asin(-_r20);
  yaw=::atan2(_r10,_r00);
  }
}

void XGuiShape3D::globalToLocalOrientation(double & roll,
                                           double & pitch,double & yaw) const
{
double c1=::cos(roll);
double s1=::sin(roll);
double c2=::cos(pitch);
double s2=::sin(pitch);
double c3=::cos(yaw);
double s3=::sin(yaw);
double g00=c2*c3, g01=s1*s2*c3-c1*s3, g02=s1*s3+c1*s2*c3; // [ global ]
double g10=c2*s3, g11=c1*c3+s1*s2*s3, g12=c1*s2*s3-s1*c3;
double g20=-s2,   g21=s1*c2,          g22=c1*c2;
double r00=_r00*g00+_r10*g10+_r20*g20; // [ invert self ] * [ global ]
// double r01=_r00*g01+_r10*g11+_r20*g21;
// double r02=_r00*g02+_r10*g12+_r20*g22;
double r10=_r01*g00+_r11*g10+_r21*g20;
// double r11=_r01*g01+_r11*g11+_r21*g21;
// double r12=_r01*g02+_r11*g12+_r21*g22;
double r20=_r02*g00+_r12*g10+_r22*g20;
double r21=_r02*g01+_r12*g11+_r22*g21;
double r22=_r02*g02+_r12*g12+_r22*g22;
if(r20<=-PRECISION_SIN)
  {
  double r11=_r01*g01+_r11*g11+_r21*g21;
  double r12=_r01*g02+_r11*g12+_r21*g22;
  pitch=M_PI_2;
  yaw=0.0; // make a choice
  roll=::atan2(-r12,r11);
  }
else if(r20>=PRECISION_SIN)
  {
  double r11=_r01*g01+_r11*g11+_r21*g21;
  double r12=_r01*g02+_r11*g12+_r21*g22;
  pitch=-M_PI_2;
  yaw=0.0; // make a choice
  roll=::atan2(-r12,r11);
  }
else
  {
  roll=::atan2(r21,r22);
  pitch=::asin(-r20);
  yaw=::atan2(r10,r00);
  }
}

void XGuiShape3D::localToGlobalOrientation(double & roll,
                                           double & pitch,double & yaw) const
{
double c1=::cos(roll);
double s1=::sin(roll);
double c2=::cos(pitch);
double s2=::sin(pitch);
double c3=::cos(yaw);
double s3=::sin(yaw);
double l00=c2*c3, l01=s1*s2*c3-c1*s3, l02=s1*s3+c1*s2*c3; // [ local ]
double l10=c2*s3, l11=c1*c3+s1*s2*s3, l12=c1*s2*s3-s1*c3;
double l20=-s2,   l21=s1*c2,          l22=c1*c2;
double r00=_r00*l00+_r01*l10+_r02*l20; // [ self ] * [ local ]
// double r01=_r00*l01+_r01*l11+_r02*l21;
// double r02=_r00*l02+_r01*l12+_r02*l22;
double r10=_r10*l00+_r11*l10+_r12*l20;
// double r11=_r10*l01+_r11*l11+_r12*l21;
// double r12=_r10*l02+_r11*l12+_r12*l22;
double r20=_r20*l00+_r21*l10+_r22*l20;
double r21=_r20*l01+_r21*l11+_r22*l21;
double r22=_r20*l02+_r21*l12+_r22*l22;
if(r20<=-PRECISION_SIN)
  {
  double r11=_r10*l01+_r11*l11+_r12*l21;
  double r12=_r10*l02+_r11*l12+_r12*l22;
  pitch=M_PI_2;
  yaw=0.0; // make a choice
  roll=::atan2(-r12,r11);
  }
else if(r20>=PRECISION_SIN)
  {
  double r11=_r10*l01+_r11*l11+_r12*l21;
  double r12=_r10*l02+_r11*l12+_r12*l22;
  pitch=-M_PI_2;
  yaw=0.0; // make a choice
  roll=::atan2(-r12,r11);
  }
else
  {
  roll=::atan2(r21,r22);
  pitch=::asin(-r20);
  yaw=::atan2(r10,r00);
  }
}

// inline const XGui3DPointVect & XGuiShape3D::getPoints(void) const

// inline const XGui3DTriangleVect & XGuiShape3D::getFaces(void) const

// inline const XGui3DColorVect & XGuiShape3D::getColors(void) const

// inline const XGui3DTextureVect & XGuiShape3D::getTextures(void) const

// inline bool XGuiShape3D::getLocalBoundingBox(
//             double & xmin,double & ymin,double & zmin,
//             double & xmax,double & ymax,double & zmax) const

// inline bool XGuiShape3D::getGlobalBoundingBox(
//             double & xmin,double & ymin,double & zmin,
//             double & xmax,double & ymax,double & zmax) const

bool XGuiShape3D::isInside(double x,double y,double z) const
{
int nbFound=0;
double k;
for(int face=_faces.size();face--;)
  {
  if(_intersectFace(face,x,y,z,x+1.0,y,z,k))
    nbFound++;
  }
return(nbFound%2);
}

bool XGuiShape3D::intersectRay(double xRay,double yRay,double zRay,
                               double xDir,double yDir,double zDir,
                               double & x,double & y,double & z,
                               int & faceNumber) const
{
double xmin,ymin,zmin,xmax,ymax,zmax;
if(getLocalBoundingBox(xmin,ymin,zmin,xmax,ymax,zmax))
  {
  xDir+=xRay; yDir+=yRay; zDir+=zRay;
  globalToLocalPosition(xDir,yDir,zDir);
  globalToLocalPosition(xRay,yRay,zRay);
  xDir-=xRay; yDir-=yRay; zDir-=zRay;
  bool found=false;
  double xi,yi,zi,ki,k=-1.0;
  if(xDir)
    {
    ki=(xmin-xRay)/xDir;
    if(ki>=0.0)
      {
      yi=yRay+ki*yDir;
      if((yi>=ymin)&&(yi<=ymax))
        {
        zi=zRay+ki*zDir;
        if((zi>=zmin)&&(zi<=zmax))
          {
          k=ki;
          found=true;
          goto foundInBoundingBox;
          }
        }
      }
    ki=(xmax-xRay)/xDir;
    if(ki>=0.0)
      {
      yi=yRay+ki*yDir;
      if((yi>=ymin)&&(yi<=ymax))
        {
        zi=zRay+ki*zDir;
        if((zi>=zmin)&&(zi<=zmax))
          {
          k=ki;
          found=true;
          goto foundInBoundingBox;
          }
        }
      }
    }
  if(yDir)
    {
    ki=(ymin-yRay)/yDir;
    if(ki>=0.0)
      {
      xi=xRay+ki*xDir;
      if((xi>=xmin)&&(xi<=xmax))
        {
        zi=zRay+ki*zDir;
        if((zi>=zmin)&&(zi<=zmax))
          {
          k=ki;
          found=true;
          goto foundInBoundingBox;
          }
        }
      }
    ki=(ymax-yRay)/yDir;
    if(ki>=0.0)
      {
      xi=xRay+ki*xDir;
      if((xi>=xmin)&&(xi<=xmax))
        {
        zi=zRay+ki*zDir;
        if((zi>=zmin)&&(zi<=zmax))
          {
          k=ki;
          found=true;
          goto foundInBoundingBox;
          }
        }
      }
    }
  if(zDir)
    {
    ki=(zmin-zRay)/zDir;
    if(ki>=0.0)
      {
      yi=yRay+ki*yDir;
      if((yi>=ymin)&&(yi<=ymax))
        {
        xi=xRay+ki*xDir;
        if((xi>=xmin)&&(xi<=xmax))
          {
          k=ki;
          found=true;
          goto foundInBoundingBox;
          }
        }
      }
    ki=(zmax-zRay)/zDir;
    if(ki>=0.0)
      {
      yi=yRay+ki*yDir;
      if((yi>=ymin)&&(yi<=ymax))
        {
        xi=xRay+ki*xDir;
        if((xi>=xmin)&&(xi<=xmax))
          {
          k=ki;
          found=true;
          goto foundInBoundingBox;
          }
        }
      }
    }
  foundInBoundingBox:
  if(found)
    {
    found=false;
    for(int face=_faces.size();face--;)
      {
      if(_intersectFace(face,xRay,yRay,zRay,xDir,yDir,zDir,ki))
        {
        if(!found||(ki<k))
          {
          k=ki;
          faceNumber=face;
          found=true;
          }
        }
      }
    if(found)
      {
      x=xRay+k*xDir;
      y=yRay+k*yDir;
      z=zRay+k*zDir;
      localToGlobalPosition(x,y,z);
      return(true);
      }
    }
  }
return(false);
}

//-------- Input/Output ----------------------------------------------------//
ostream & operator<<(ostream & stream,const XGuiShape3D & shape)
{
return(stream << shape.print());
}

Strings XGuiShape3D::print(void) const // virtual
{
Strings str("XGuiShape3D");
return(str);
}

//-------- Modifiers -------------------------------------------------------//
// inline void XGuiShape3D::draw(void)

void XGuiShape3D::drawBoundingBox(float r,float g,float b)
{
if(_faces.size())
  {
  float matrix[16];
  matrix[0]=_r00; matrix[4]=_r01; matrix[8]=_r02;
  matrix[1]=_r10; matrix[5]=_r11; matrix[9]=_r12;
  matrix[2]=_r20; matrix[6]=_r21; matrix[10]=_r22;
  matrix[12]=_px; matrix[13]=_py; matrix[14]=_pz;
  matrix[3]=matrix[7]=matrix[11]=0.0;
  matrix[15]=1.0;
  glPushMatrix(); glMultMatrixf(matrix);
  glDisable(GL_LIGHTING);
  GLfloat lineWidth;
  glGetFloatv(GL_LINE_WIDTH,&lineWidth);
  glLineWidth(2.0);                                   // hack ! does not seem
  glNewList(_boundingBoxList,GL_COMPILE_AND_EXECUTE); // to work outside a
  glBegin(GL_LINES);                                  // display list !!
  glColor3f(r,g,b);
  glVertex3f(_xmin,_ymin,_zmin); glVertex3f(_xmax,_ymin,_zmin);
  glVertex3f(_xmin,_ymin,_zmin); glVertex3f(_xmin,_ymax,_zmin);
  glVertex3f(_xmin,_ymin,_zmin); glVertex3f(_xmin,_ymin,_zmax);
  glVertex3f(_xmax,_ymax,_zmax); glVertex3f(_xmin,_ymax,_zmax);
  glVertex3f(_xmax,_ymax,_zmax); glVertex3f(_xmax,_ymin,_zmax);
  glVertex3f(_xmax,_ymax,_zmax); glVertex3f(_xmax,_ymax,_zmin);
  glVertex3f(_xmin,_ymin,_zmax); glVertex3f(_xmax,_ymin,_zmax);
  glVertex3f(_xmin,_ymin,_zmax); glVertex3f(_xmin,_ymax,_zmax);
  glVertex3f(_xmax,_ymax,_zmin); glVertex3f(_xmax,_ymin,_zmin);
  glVertex3f(_xmax,_ymax,_zmin); glVertex3f(_xmin,_ymax,_zmin);
  glVertex3f(_xmax,_ymin,_zmin); glVertex3f(_xmax,_ymin,_zmax);
  glVertex3f(_xmin,_ymax,_zmin); glVertex3f(_xmin,_ymax,_zmax);
  glEnd();
  glEndList();
  glLineWidth(lineWidth);
  glEnable(GL_LIGHTING);
  glPopMatrix();
  }
}

void XGuiShape3D::setPosition(double px,double py,double pz)
{
_px=px;   _py=py;   _pz=pz;
_buildGeom();
}

void XGuiShape3D::cancelRotation(void)
{
_r00=_r11=_r22=1.0;
_r01=_r02=_r10=_r12=_r20=_r21=0.0;
_buildGeom();
}

void XGuiShape3D::setOrientation(double roll,double pitch,double yaw)
{
double c1=::cos(roll);
double s1=::sin(roll);
double c2=::cos(pitch);
double s2=::sin(pitch);
double c3=::cos(yaw);
double s3=::sin(yaw);
_r00=c2*c3; _r01=s1*s2*c3-c1*s3; _r02=s1*s3+c1*s2*c3;
_r10=c2*s3; _r11=c1*c3+s1*s2*s3; _r12=c1*s2*s3-s1*c3;
_r20=-s2;   _r21=s1*c2;          _r22=c1*c2;
_buildGeom();
}

void XGuiShape3D::translate(double dx,double dy,double dz)
{
_px+=dx*_r00+dy*_r01+dz*_r02;
_py+=dx*_r10+dy*_r11+dz*_r12;
_pz+=dx*_r20+dy*_r21+dz*_r22;
_buildGeom();
}
                                               //  1  0  0
void XGuiShape3D::roll(double dRoll)           //  0  c -s
{                                              //  0  s  c
double c=::cos(dRoll);
double s=::sin(dRoll);
/*
double r10=+c*_r10-s*_r20;       // [ Local ] * [ Global ]
double r20=+s*_r10+c*_r20;
double r11=+c*_r11-s*_r21;
double r21=+s*_r11+c*_r21;
double r12=+c*_r12-s*_r22;
double r22=+s*_r12+c*_r22;
_r10=r10;
_r20=r20;
_r11=r11;
_r21=r21;
_r12=r12;
_r22=r22;
*/
double r01=+c*_r01+s*_r02;       // [ Global ] * [ Local ]
double r02=-s*_r01+c*_r02;
double r11=+c*_r11+s*_r12;
double r12=-s*_r11+c*_r12;
double r21=+c*_r21+s*_r22;
double r22=-s*_r21+c*_r22;
_r01=r01;
_r02=r02;
_r11=r11;
_r12=r12;
_r21=r21;
_r22=r22;
_buildGeom();
}
                                               //  c  0  s
void XGuiShape3D::pitch(double dPitch)         //  0  1  0
{                                              // -s  0  c
double c=::cos(dPitch);
double s=::sin(dPitch);
/*
double r00=+c*_r00+s*_r20;       // [ Local ] * [ Global ]
double r20=-s*_r00+c*_r20;
double r01=+c*_r01+s*_r21;
double r21=-s*_r01+c*_r21;
double r02=+c*_r02+s*_r22;
double r22=-s*_r02+c*_r22;
_r00=r00;
_r20=r20;
_r01=r01;
_r21=r21;
_r02=r02;
_r22=r22;
*/
double r00=+c*_r00-s*_r02;       // [ Global ] * [ Local ]
double r02=+s*_r00+c*_r02;
double r10=+c*_r10-s*_r12;
double r12=+s*_r10+c*_r12;
double r20=+c*_r20-s*_r22;
double r22=+s*_r20+c*_r22;
_r00=r00;
_r02=r02;
_r10=r10;
_r12=r12;
_r20=r20;
_r22=r22;
_buildGeom();
}
                                               //  c -s  0
void XGuiShape3D::yaw(double dYaw)             //  s  c  0
{                                              //  0  0  1
double c=::cos(dYaw);
double s=::sin(dYaw);
/*
double r00=+c*_r00-s*_r10;       // [ Local ] * [ Global ]
double r10=+s*_r00+c*_r10;
double r01=+c*_r01-s*_r11;
double r11=+s*_r01+c*_r11;
double r02=+c*_r02-s*_r12;
double r12=+s*_r02+c*_r12;
_r00=r00;
_r10=r10;
_r01=r01;
_r11=r11;
_r02=r02;
_r12=r12;
*/
double r00=+c*_r00+s*_r01;       // [ Global ] * [ Local ]
double r01=-s*_r00+c*_r01;
double r10=+c*_r10+s*_r11;
double r11=-s*_r10+c*_r11;
double r20=+c*_r20+s*_r21;
double r21=-s*_r20+c*_r21;
_r00=r00;
_r01=r01;
_r10=r10;
_r11=r11;
_r20=r20;
_r21=r21;
_buildGeom();
}

bool XGuiShape3D::setShape(const XGui3DPointVect & points,
                           const XGui3DTriangleVect & faces,
                           const XGui3DColorVect & colors,
                           const XGui3DTextureVect & textures,
                           const StringsVect * pathVect)
{
unsigned int i;
for(i=faces.size();i--;)
  {
  if((faces[i].p1<0)||(faces[i].p1>=(int)points.size())||
     (faces[i].p2<0)||(faces[i].p2>=(int)points.size())||
     (faces[i].p3<0)||(faces[i].p3>=(int)points.size()))
    return(false);
  }
if(colors.size())
  {
  int range=faces.size();
  for(i=colors.size();i--;) range-=colors[i].range;
  if(range) return(false);
  }
for(i=textures.size();i--;)
  {
  if((textures[i].face<0)||(textures[i].face>=(int)faces.size())||
     !_loadTexture(textures[i],pathVect))
    return(false);
  }
_points=points;
_faces=faces;
_colors=colors;
_textures=textures;
if(_points.size())
  {
  _xmin=_xmax=_points.back().x;
  _ymin=_ymax=_points.back().y;
  _zmin=_zmax=_points.back().z;
  for(i=_points.size()-1;i--;)
    {
    if(_points[i].x<_xmin) _xmin=_points[i].x;
    else if(_points[i].x>_xmax) _xmax=_points[i].x;
    if(_points[i].y<_ymin) _ymin=_points[i].y;
    else if(_points[i].y>_ymax) _ymax=_points[i].y;
    if(_points[i].z<_zmin) _zmin=_points[i].z;
    else if(_points[i].z>_zmax) _zmax=_points[i].z;
    }
  }
else _xmin=_xmax=_ymin=_ymax=_zmin=_zmax=0.0;
for(i=_faces.size();i--;)
  {
  _faces[i].dx1=_points[_faces[i].p2].x-_points[_faces[i].p1].x;
  _faces[i].dy1=_points[_faces[i].p2].y-_points[_faces[i].p1].y;
  _faces[i].dz1=_points[_faces[i].p2].z-_points[_faces[i].p1].z;
  _faces[i].dx2=_points[_faces[i].p3].x-_points[_faces[i].p1].x;
  _faces[i].dy2=_points[_faces[i].p3].y-_points[_faces[i].p1].y;
  _faces[i].dz2=_points[_faces[i].p3].z-_points[_faces[i].p1].z;
  _faces[i].dx3=_faces[i].dy1*_faces[i].dz2-_faces[i].dz1*_faces[i].dy2;
  _faces[i].dy3=_faces[i].dx2*_faces[i].dz1-_faces[i].dz2*_faces[i].dx1;
  _faces[i].dz3=_faces[i].dx1*_faces[i].dy2-_faces[i].dy1*_faces[i].dx2;
  }
_buildShape();
return(true);
}

// inline void XGuiShape3D::setKeyCallback(void (*keyCallback)(XGuiShape3D *,
//                                                             const Strings &,
//                                                             void *),
//                                         void * keyData)

// inline void XGuiShape3D::setMotionCallback(
//                          void (*motionCallback)(XGuiShape3D *,
//                                                 double,double,double,
//                                                 void *),
//                          void * motionData)

// inline void XGuiShape3D::setSelectCallback(
//                          void (*selectCallback)(XGuiShape3D *,
//                                                 XGuiViewer3D *,
//                                                 bool,
//                                                 void *),
//                          void * selectData)

// inline void XGuiShape3D::notifyKey(const Strings & key)

// inline void XGuiShape3D::notifyMotion(double dx,double dy,double dz)

// inline void XGuiShape3D::notifySelection(XGuiViewer3D * viewer,
//                                          bool selected)

//-------- Private Methods -------------------------------------------------//
void XGuiShape3D::_buildGeom(void)
{
float matrix[16];
matrix[0]=_r00; matrix[4]=_r01; matrix[8]=_r02;
matrix[1]=_r10; matrix[5]=_r11; matrix[9]=_r12;
matrix[2]=_r20; matrix[6]=_r21; matrix[10]=_r22;
matrix[12]=_px; matrix[13]=_py; matrix[14]=_pz;
matrix[3]=matrix[7]=matrix[11]=0.0;
matrix[15]=1.0;
glNewList(_geomList,GL_COMPILE);
glPushMatrix();
glMultMatrixf(matrix);
glCallList(_shapeList);
glPopMatrix();
glEndList();
XGuiViewer3D::forceRedraw();
}

void XGuiShape3D::_buildShape(void)
{
float emissiveColor[]={0.0,0.0,0.0,1.0};
float ambientColor[]={0.1,0.1,0.1,1.0};
float diffuseColor[]={1.0,1.0,1.0,1.0};
float specularColor[]={0.3,0.3,0.3,1.0};
unsigned int numTexture=0;
bool inside=false;
glNewList(_shapeList,GL_COMPILE);
if(_colors.size())
  {
  glMaterialfv(GL_FRONT,GL_EMISSION,emissiveColor);
  glMaterialfv(GL_FRONT,GL_SPECULAR,specularColor);
  glMaterialf(GL_FRONT,GL_SHININESS,32.0);
  int face=0;
  for(unsigned int col=0;col<_colors.size();col++)
    {
    diffuseColor[0]=_colors[col].r;
    diffuseColor[1]=_colors[col].g;
    diffuseColor[2]=_colors[col].b;
    glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuseColor);
    ambientColor[0]=diffuseColor[0]*0.1;
    ambientColor[1]=diffuseColor[1]*0.1;
    ambientColor[2]=diffuseColor[2]*0.1;
    glMaterialfv(GL_FRONT,GL_AMBIENT,ambientColor);
    for(int range=_colors[col].range;range--;)
      {
      if((numTexture<_textures.size())&&
         (_textures[numTexture].face==face))
        {
        if(inside) {glEnd(); inside=false;}
        _buildTexture(face,numTexture);
        ++numTexture;
        }
      else
        {
        if(!inside) {glBegin(GL_TRIANGLES); inside=true;}
        _buildTriangle(face);
        }
      face++;
      }
    if(inside) {glEnd(); inside=false;}
    }
  }
else
  {
  glMaterialfv(GL_FRONT,GL_EMISSION,emissiveColor);
  glMaterialfv(GL_FRONT,GL_SPECULAR,specularColor);
  glMaterialf(GL_FRONT,GL_SHININESS,32.0);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuseColor);
  glMaterialfv(GL_FRONT,GL_AMBIENT,ambientColor);
  for(unsigned int face=0;face<_faces.size();face++)
    {
    if((numTexture<_textures.size())&&
       (_textures[numTexture].face==(int)face))
      {
      if(inside) {glEnd(); inside=false;}
      _buildTexture(face,numTexture);
      ++numTexture;
      }
    else
      {
      if(!inside) {glBegin(GL_TRIANGLES); inside=true;}
      _buildTriangle(face);
      }
    }
  if(inside) {glEnd(); inside=false;}
  }
glEndList();
XGuiViewer3D::forceRedraw();
}

void XGuiShape3D::_buildTriangle(int face)
{
double dx=_faces[face].dx3;
double dy=_faces[face].dy3;
double dz=_faces[face].dz3;
double l=::sqrt(dx*dx+dy*dy+dz*dz);
if(l) {dx/=l; dy/=l; dz/=l;} // normalize
glNormal3f(dx,dy,dz);
glVertex3f(_points[_faces[face].p1].x,
           _points[_faces[face].p1].y,
           _points[_faces[face].p1].z);
glVertex3f(_points[_faces[face].p2].x,
           _points[_faces[face].p2].y,
           _points[_faces[face].p2].z);
glVertex3f(_points[_faces[face].p3].x,
           _points[_faces[face].p3].y,
           _points[_faces[face].p3].z);
}

void XGuiShape3D::_buildTexture(int face,int numTexture)
{
TextureMap::const_iterator it=_textureMap.find(_textures[numTexture].name);
glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D,(*it).second);
glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
glBegin(GL_TRIANGLES);
double dx=_faces[face].dx3;
double dy=_faces[face].dy3;
double dz=_faces[face].dz3;
double l=::sqrt(dx*dx+dy*dy+dz*dz);
if(l) {dx/=l; dy/=l; dz/=l;} // normalize
glNormal3f(dx,dy,dz);
glTexCoord2f(_textures[numTexture].x1,
             _textures[numTexture].y1);
glVertex3f(_points[_faces[face].p1].x,
           _points[_faces[face].p1].y,
           _points[_faces[face].p1].z);
glTexCoord2f(_textures[numTexture].x2,
             _textures[numTexture].y2);
glVertex3f(_points[_faces[face].p2].x,
           _points[_faces[face].p2].y,
           _points[_faces[face].p2].z);
glTexCoord2f(_textures[numTexture].x3,
             _textures[numTexture].y3);
glVertex3f(_points[_faces[face].p3].x,
           _points[_faces[face].p3].y,
           _points[_faces[face].p3].z);
glEnd();
glDisable(GL_TEXTURE_2D);
}

bool XGuiShape3D::_loadTexture(const XGui3DTexture & texture,
                               const StringsVect * pathVect)
{
TextureMap::const_iterator it=_textureMap.find(texture.name);
if(it==_textureMap.end())
  {
  Strings name(texture.name);
  FILE * file=::fopen(name,"rb");
  if(!file&&pathVect)
    {
    for(unsigned int i=0;!file&&i<pathVect->size();i++)
      {
      name=(*pathVect)[i]+texture.name;
      file=::fopen(name,"rb");
      }
    }
  if(!file) return(false);
  int nbColumns,nbLines,nbColors,posFrom,posTo;
  unsigned char * red, * green, * blue;
  unsigned long * pixels;
  Strings ext(texture.name.extension());
  ext.toLower();
  if(ext==Strings(".bmp"))
    {
    if(!getXGuiManager()->readBMP(file,red,green,blue,nbColors,
                                       pixels,nbColumns,nbLines))
      {
      ::fclose(file);
      return(false);
      }
    }
  else if(ext==Strings(".ras"))
    {
    if(!getXGuiManager()->readRAS(file,red,green,blue,nbColors,
                                       pixels,nbColumns,nbLines))
      {
      ::fclose(file);
      return(false);
      }
    }
  else
    {
    ::fclose(file);
    return(false);
    }
  ::fclose(file);
  int width=1;
  while((width<<1)<=nbColumns) width<<=1;
  unsigned char * textureData=(unsigned char *)
                              malloc(width*nbLines*sizeof(unsigned char)*3);
  for(int y=nbLines;y--;)
    {
    for(int x=width;x--;)
      {
      posFrom=y*nbColumns+x;
      posTo=y*width+x;
      textureData[3*posTo]=red[pixels[posFrom]];
      textureData[3*posTo+1]=green[pixels[posFrom]];
      textureData[3*posTo+2]=blue[pixels[posFrom]];
      }
    }
  free(red);
  free(green);
  free(blue);
  free(pixels);
  unsigned int textureID;
  glGenTextures(1,&textureID);
  glBindTexture(GL_TEXTURE_2D,textureID);
  /*
  glTexImage2D(GL_TEXTURE_2D,0,3,width,nbLines,0,GL_RGB,
               GL_UNSIGNED_BYTE,(void *)textureData);
  */
  gluBuild2DMipmaps(GL_TEXTURE_2D,3,width,nbLines,GL_RGB,
                    GL_UNSIGNED_BYTE,(void *)textureData);
  free(textureData);
  _textureMap.insert(TextureMap::value_type(texture.name,textureID));
  }
return(true);
}

bool XGuiShape3D::_intersectFace(int face,double xRay,double yRay,double zRay,
                                 double xDir,double yDir,double zDir,
                                 double & k) const
{
double m00=_faces[face].dy2*_faces[face].dz3-   // transposed comatrix
           _faces[face].dz2*_faces[face].dy3;
double m10=_faces[face].dz1*_faces[face].dy3-
           _faces[face].dy1*_faces[face].dz3;
double m20=_faces[face].dx3;
double m01=_faces[face].dz2*_faces[face].dx3-
           _faces[face].dz3*_faces[face].dx2;
double m11=_faces[face].dx1*_faces[face].dz3-
           _faces[face].dx3*_faces[face].dz1;
double m21=_faces[face].dy3;
double m02=_faces[face].dx2*_faces[face].dy3-
           _faces[face].dy2*_faces[face].dx3;
double m12=_faces[face].dy1*_faces[face].dx3-
           _faces[face].dy3*_faces[face].dx1;
double m22=_faces[face].dz3;
double delta=m20*m20+m21*m21+m22*m22;           // determinant
double x,y,z;
xRay-=_points[_faces[face].p1].x;               // originin in P1
yRay-=_points[_faces[face].p1].y;
zRay-=_points[_faces[face].p1].z;
x=m00*xRay+m01*yRay+m02*zRay;                   // change coordinate
y=m10*xRay+m11*yRay+m12*zRay;
z=m20*xRay+m21*yRay+m22*zRay;
xRay=x; yRay=y; zRay=z;
x=m00*xDir+m01*yDir+m02*zDir;
y=m10*xDir+m11*yDir+m12*zDir;
z=m20*xDir+m21*yDir+m22*zDir;
xDir=x; yDir=y; zDir=z;
if(zDir)
  {
  k=-zRay/zDir;
  if(k>=0)
    {
    x=xRay+k*xDir;
    if(x>=0.0)
      {
      y=yRay+k*yDir;
      if((y>=0.0)&&(y<=delta-x)) return(true);
      }
    }
  }
return(false);
}

#endif // OPEN_GL
#endif // X_GUI

