#ifdef X_GUI
#ifdef OPEN_GL

#include "XGui/xgView3d.h"
#include "XGui/xgShap3d.h"
#include "XGui/xgArea.h"
#include "XGui/xgMgr.h"

#include <math.h>

//--------------------------------------------------------------------------//
// class XGuiViewer3D                                                       //
//--------------------------------------------------------------------------//

const double XGuiViewer3D::PRECISION_SIN=1.0-1.0e-9;

XtIntervalId XGuiViewer3D::_motionTimerId=(XtIntervalId)0;

unsigned long XGuiViewer3D::_motionTimerDt=50; // 20 frames per second

XGuiViewer3DList XGuiViewer3D::_viewers;

XGuiShape3DList XGuiViewer3D::_shapes;

bool XGuiViewer3D::_mustDraw=true;

GLXContext XGuiViewer3D::_globalContext=(GLXContext)0;

Window XGuiViewer3D::_globalWindow=None;

XVisualInfo * XGuiViewer3D::_globalVisualInfo=(XVisualInfo *)0;

//-------- Static methods --------------------------------------------------//
void XGuiViewer3D::addShape(XGuiShape3D * shape) // static
{
_shapes.push_back(shape);
XGuiViewer3D::_mustDraw=true;
}

void XGuiViewer3D::removeShape(XGuiShape3D * shape) // static
{
XGuiShape3DList::iterator itS=_shapes.begin();
while((*itS)!=shape) itS++;
_shapes.erase(itS);
XGuiViewer3DList::iterator itV=_viewers.begin();
for(;itV!=_viewers.end();itV++)
  {
  XGuiShape3DList::iterator itS=(*itV)->_select.begin(); // unselect
  for(;itS!=(*itV)->_select.end();itS++)
    {
    if(*itS==shape)
      {
      (*itV)->_select.erase(itS);
      (*itS)->notifySelection(*itV,false);
      break;
      }
    }
  }
XGuiViewer3D::_mustDraw=true;
}

// inline void XGuiViewer3D::forceRedraw(void) // static

void XGuiViewer3D::drawAll(void) // static
{
if(XGuiViewer3D::_mustDraw)
  {
  XGuiViewer3DList::iterator itV=_viewers.begin();
  for(;itV!=_viewers.end();itV++)
    (*itV)->redraw();
  XGuiViewer3D::_mustDraw=false;
  }
}

bool XGuiViewer3D::createGlobalContext(void) // static
{
if(!XGuiViewer3D::_globalContext)
  {
  SimpleVector<int> attrib;
  attrib.pushBack(GLX_RGBA);
  attrib.pushBack(GLX_RED_SIZE);
  attrib.pushBack(1);
  attrib.pushBack(GLX_GREEN_SIZE);
  attrib.pushBack(1);
  attrib.pushBack(GLX_BLUE_SIZE);
  attrib.pushBack(1);
  attrib.pushBack(GLX_DOUBLEBUFFER);
  attrib.pushBack(GLX_DEPTH_SIZE);
  attrib.pushBack(1);
  attrib.pushBack(None);
  XGuiViewer3D::_globalVisualInfo=glXChooseVisual(
                                  getXGuiManager()->getDisplay(),
                                  getXGuiManager()->getScreen(),
                                  &attrib.accessFront());
  if(!XGuiViewer3D::_globalVisualInfo) return(false);
  XGuiViewer3D::_globalWindow=XGuiViewer3D::_createWindow(
                              getXGuiManager()->getRoot(),
                              0,0,100,100);
  if(!XGuiViewer3D::_globalWindow) return(false);
  XGuiViewer3D::_globalContext=glXCreateContext(
                               getXGuiManager()->getDisplay(),
                               XGuiViewer3D::_globalVisualInfo,
                               (GLXContext)0,true);
  if(XGuiViewer3D::_globalContext)
    {
    glXMakeCurrent(getXGuiManager()->getDisplay(),
                   XGuiViewer3D::_globalWindow,
                   XGuiViewer3D::_globalContext);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    // glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    // glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    // glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_FASTEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    float lightColor[]={1.0,1.0,1.0,1.0};
    glLightfv(GL_LIGHT0,GL_DIFFUSE,lightColor);
    glLightfv(GL_LIGHT0,GL_SPECULAR,lightColor);
    glLightfv(GL_LIGHT0,GL_AMBIENT,lightColor);
    }
  else return(false);
  }
return(true);
}

void XGuiViewer3D::destroyGlobalContext(void) // static
{
if(XGuiViewer3D::_globalContext)
  {
  /* PB with NVIDIA Cards ?
  glXDestroyContext(getXGuiManager()->getDisplay(),
                    XGuiViewer3D::_globalContext);
  */
  XGuiViewer3D::_globalContext=(GLXContext)0;
  }
if(XGuiViewer3D::_globalWindow)
  {
  /* PB with NVIDIA Cards ?
  XDestroyWindow(getXGuiManager()->getDisplay(),XGuiViewer3D::_globalWindow);
  */
  XGuiViewer3D::_globalWindow=None;
  }
if(XGuiViewer3D::_globalVisualInfo)
  {
  /* PB with NVIDIA Cards ?
  XFree(XGuiViewer3D::_globalVisualInfo);
  */
  XGuiViewer3D::_globalVisualInfo=(XVisualInfo *)0;
  }
}

//-------- Allocators ------------------------------------------------------//
XGuiViewer3D::XGuiViewer3D(XGuiArea * parent)
 : XGuiElement(2*getXGuiManager()->getMargin(),
               2*getXGuiManager()->getMargin()),
   _px(0.0), _py(0.0), _pz(0.0),
   _r00(1.0), _r01(0.0), _r02(0.0),
   _r10(0.0), _r11(1.0), _r12(0.0),
   _r20(0.0), _r21(0.0), _r22(1.0),
   _color("black"), _pixel(0), _r(0.0), _g(0.0), _b(0.0),
   _rInv(1.0), _gInv(1.0), _bInv(1.0),
   _select(), _ctrlPressed(false), _shiftPressed(false),
   _pressed(0), _canMoveSelection(false), _mouseX(0), _mouseY(0),
   _viewAngle(M_PI/6.0), _limitY(1.0), _limitZ(1.0),
   _limitMinX(0.1), _limitMaxX(200.0), _aspectRatio(1.0),
   _keyCallback((void (*)(XGuiViewer3D *,const Strings &,void *))0),
   _keyData((void *)0)
{
_motionData.move=false;
_motionData.lastMotion=(Time)-1L;
_motionData.dx=0.0;
_motionData.yaw=0.0;
_motionData.pitch=0.0;
getXGuiManager()->allocNamedColor(_color,_pixel);
parent->addElement(this);
if(!XGuiViewer3D::_viewers.size()) // first
  {
  XGuiViewer3D::_motionTimerId=XtAppAddTimeOut(getXGuiManager()->getContext(),
                                               XGuiViewer3D::_motionTimerDt,
                                               XGuiViewer3D::_motionProc,
                                               (XtPointer)0);
  }
XGuiViewer3D::_viewers.push_back(this);
}

XGuiViewer3D::~XGuiViewer3D(void)
{
glXMakeCurrent(getXGuiManager()->getDisplay(),
               XGuiViewer3D::_globalWindow,
               XGuiViewer3D::_globalContext);
XGuiShape3DList::iterator itS;
XGuiShape3DList tmpList(_select);
while(tmpList.size())
  {
  for(itS=_select.begin();itS!=_select.end();itS++)
    {
    if((*itS)==tmpList.front())
      {
      _select.erase(itS);
      tmpList.front()->notifySelection(this,false);
      break;
      }
    }
  tmpList.pop_front();
  }
getXGuiManager()->freeColor(_pixel);
XGuiViewer3DList::iterator it=_viewers.begin();
while((*it)!=this) it++;
_viewers.erase(it);
if(!XGuiViewer3D::_viewers.size()) // last
  {
  XtRemoveTimeOut(XGuiViewer3D::_motionTimerId);
  }
_window=None; // PB with NVIDIA Cards ?
}

//-------- Inspectors ------------------------------------------------------//
// inline XGuiElement::Type XGuiViewer3D::getElemType(void) const // virtual

// inline bool XGuiViewer3D::isA(XGuiElement::Type type) const // virtual

// inline const Strings & XGuiViewer3D::getBackground(void) const

// inline unsigned long XGuiViewer3D::getBackgroundPixel(void) const

// inline void XGuiViewer3D::getPosition(double & px,double & py,double & pz)
//                                                                      const

void XGuiViewer3D::globalToLocalPosition(double & x,double & y,double & z)
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

void XGuiViewer3D::localToGlobalPosition(double & x,double & y,double & z)
                                                                     const
{
double xg=_r00*x+_r01*y+_r02*z;
double yg=_r10*x+_r11*y+_r12*z;
double zg=_r20*x+_r21*y+_r22*z;
x=xg+_px;
y=yg+_py;
z=zg+_pz;
}

void XGuiViewer3D::getOrientation(double & roll,double & pitch,double & yaw)
                                                                       const
{
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

void XGuiViewer3D::globalToLocalOrientation(double & roll,
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

void XGuiViewer3D::localToGlobalOrientation(double & roll,
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

// inline void XGuiViewer3D::getLocation(double & px,double & py,
//                                       double & pz,double & roll,
//                                       double & pitch,double & yaw) const

// inline const XGuiShape3DList & XGuiViewer3D::getSelection(void) const

bool XGuiViewer3D::isSelected(const XGuiShape3D * shape) const
{
XGuiShape3DList::const_iterator it;
for(it=_select.begin();it!=_select.end();it++)
  if(*it==shape) return(true);
return(false);
}

//-------- Modifiers -------------------------------------------------------//
void XGuiViewer3D::select(XGuiShape3D * shape,bool propagate)
{
XGuiShape3DList::iterator it;
for(it=_select.begin();it!=_select.end();it++)
  if(*it==shape) return;
_select.push_back(shape);
XGuiViewer3D::_mustDraw=true;
if(propagate) shape->notifySelection(this,true);
}

void XGuiViewer3D::unselect(XGuiShape3D * shape,bool propagate)
{
XGuiShape3DList::iterator it;
for(it=_select.begin();it!=_select.end();it++)
  {
  if(*it==shape)
    {
    _select.erase(it);
    XGuiViewer3D::_mustDraw=true;
    if(propagate) shape->notifySelection(this,false);
    break;
    }
  }
}

void XGuiViewer3D::setBackground(const Strings & color)
{
unsigned long pixel;
if(getXGuiManager()->allocNamedColor(color,pixel))
  {
  unsigned short r,g,b;
  getXGuiManager()->queryColor(pixel,r,g,b);
  _r=((float)r)/65535.0;
  _g=((float)g)/65535.0;
  _b=((float)b)/65535.0;
  int nbDark=(r<0x8000)+(g<0x8000)+(b<0x8000);
  if(nbDark>=2)
    getXGuiManager()->queryColor(getXGuiManager()->getLightside(),r,g,b);
  else
    getXGuiManager()->queryColor(getXGuiManager()->getForeground(),r,g,b);
  _rInv=((float)r)/65535.0;
  _gInv=((float)g)/65535.0;
  _bInv=((float)b)/65535.0;
  getXGuiManager()->freeColor(_pixel);
  _pixel=pixel;
  _color=color;
  if(_window)
    {
    XSetWindowBackground(getXGuiManager()->getDisplay(),_window,_pixel);
    }
  XGuiViewer3D::_mustDraw=true;
  }
}

void XGuiViewer3D::setPosition(double px,double py,double pz)
{
_px=px;   _py=py;   _pz=pz;
XGuiViewer3D::_mustDraw=true;
if(_callback) (*_callback)(this,_data);
}

void XGuiViewer3D::cancelRotation(void)
{
_r00=_r11=_r22=1.0;
_r01=_r02=_r10=_r12=_r20=_r21=0.0;
XGuiViewer3D::_mustDraw=true;
if(_callback) (*_callback)(this,_data);
}

void XGuiViewer3D::setOrientation(double roll,double pitch,double yaw)
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
XGuiViewer3D::_mustDraw=true;
if(_callback) (*_callback)(this,_data);
}

void XGuiViewer3D::setLocation(double px,double py,double pz,
                               double roll,double pitch,double yaw)
{
_px=px;   _py=py;   _pz=pz;
double c1=::cos(roll);
double s1=::sin(roll);
double c2=::cos(pitch);
double s2=::sin(pitch);
double c3=::cos(yaw);
double s3=::sin(yaw);
_r00=c2*c3; _r01=s1*s2*c3-c1*s3; _r02=s1*s3+c1*s2*c3;
_r10=c2*s3; _r11=c1*c3+s1*s2*s3; _r12=c1*s2*s3-s1*c3;
_r20=-s2;   _r21=s1*c2;          _r22=c1*c2;
XGuiViewer3D::_mustDraw=true;
if(_callback) (*_callback)(this,_data);
}

void XGuiViewer3D::translate(double dx,double dy,double dz)
{
_px+=dx*_r00+dy*_r01+dz*_r02;
_py+=dx*_r10+dy*_r11+dz*_r12;
_pz+=dx*_r20+dy*_r21+dz*_r22;
XGuiViewer3D::_mustDraw=true;
if(_callback) (*_callback)(this,_data);
}
                                               //  1  0  0
void XGuiViewer3D::roll(double dRoll)          //  0  c -s
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
XGuiViewer3D::_mustDraw=true;
if(_callback) (*_callback)(this,_data);
}
                                               //  c  0  s
void XGuiViewer3D::pitch(double dPitch)        //  0  1  0
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
XGuiViewer3D::_mustDraw=true;
if(_callback) (*_callback)(this,_data);
}
                                               //  c -s  0
void XGuiViewer3D::yaw(double dYaw)            //  s  c  0
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
XGuiViewer3D::_mustDraw=true;
if(_callback) (*_callback)(this,_data);
}

void XGuiViewer3D::setWidth(int width) // virtual
{
XGuiElement::setWidth(width);
_adjustLimits();
XGuiViewer3D::_mustDraw=true;
if(_callback) (*_callback)(this,_data);
}

void XGuiViewer3D::setHeight(int height) // virtual
{
XGuiElement::setHeight(height);
_adjustLimits();
XGuiViewer3D::_mustDraw=true;
if(_callback) (*_callback)(this,_data);
}

void XGuiViewer3D::show(void) // virtual
{
if(!_window)
  {
  _window=XGuiViewer3D::_createWindow(((XGuiArea *)_parent)->getInWindow(),
                                      _x,_y,_width,_height);
  XSetWindowBackground(getXGuiManager()->getDisplay(),_window,_pixel);
  XSelectInput(getXGuiManager()->getDisplay(),_window,
               ExposureMask | EnterWindowMask |
               KeyPressMask | KeyReleaseMask |
               ButtonPressMask | ButtonMotionMask | ButtonReleaseMask);
  XMapWindow(getXGuiManager()->getDisplay(),_window);
  _adjustLimits();
  XGuiViewer3D::_mustDraw=true;
  }
XGuiElement::show();
}

void XGuiViewer3D::hide(void) // virtual
{
glXMakeCurrent(getXGuiManager()->getDisplay(),
               XGuiViewer3D::_globalWindow,
               XGuiViewer3D::_globalContext);
_window=None; // PB with NVIDIA Cards ?
XGuiElement::hide();
}

// inline void XGuiViewer3D::setKeyCallback(
//                           void (*keyCallback)(XGuiViewer3D*,
//                                               const Strings &,
//                                               void *),
//                           void * keyData)

void XGuiViewer3D::processEvent(const XEvent & event) // virtual
{
switch(event.type)
  {
  case Expose:
    while(XCheckTypedWindowEvent(getXGuiManager()->getDisplay(),
                                 _window,Expose,(XEvent *)&event));
    XGuiViewer3D::_mustDraw=true;
    break;
  case EnterNotify:
    if(event.xcrossing.state&ControlMask) _ctrlPressed=true;
    else _ctrlPressed=false;
    if(event.xcrossing.state&ShiftMask) _shiftPressed=true;
    else _shiftPressed=false;
    _chooseCursor();
    break;
  case KeyPress:
    {
    static char buffer[0x20];
    KeySym keysym;
    int nb=XLookupString((XKeyEvent *)&event.xkey,
                         buffer,0x10,&keysym,(XComposeStatus*)0);
    switch(keysym)
      {
      case XK_Control_L:
      case XK_Control_R:
        _ctrlPressed=true;
        _chooseCursor();
        break;
      case XK_Shift_L:
      case XK_Shift_R:
        _shiftPressed=true;
        _chooseCursor();
        break;
      case XK_Delete: // Sometimes BackSpace is converted in Delete
        if(event.xkey.keycode==22) // keycode for BackSpace
          {
          keysym=XK_BackSpace;
          buffer[0]='\b';
          nb=1;
          }
        break;
      }
    char * str;
    if(nb==1)
      {
      buffer[nb]='\0';
      str=buffer;
      }
    else str=XKeysymToString(keysym);
    if(str)
      {
      if(_select.size()) // to selected objects
        {
        XGuiShape3DList::iterator it;
        XGuiShape3DList tmpList(_select);
        while(tmpList.size())
          {
          for(it=_select.begin();it!=_select.end();it++)
            {
            if((*it)==tmpList.front())
              {
              (*it)->notifyKey(str);
              break;
              }
            }
          tmpList.pop_front();
          }
        }
      else // to viewer
        {
        if(_keyCallback) (*_keyCallback)(this,str,_keyData);
        }
      }
    }
    break;
  case KeyRelease:
    {
    static char buffer[0x10];
    KeySym keysym;
    XLookupString((XKeyEvent *)&event.xkey,
                  buffer,0x10,&keysym,(XComposeStatus*)0);
    switch(keysym)
      {
      case XK_Control_L:
      case XK_Control_R:
        _ctrlPressed=false;
        _chooseCursor();
        break;
      case XK_Shift_L:
      case XK_Shift_R:
        _shiftPressed=false;
        _chooseCursor();
        break;
      }
    }
    break;
  case ButtonPress:
    if(!_pressed)
      {
      _motionData.move=false;
      _motionData.lastMotion=(Time)-1L;
      _canMoveSelection=false;
      _pressed=event.xbutton.button;
      _mouseX=event.xbutton.x;
      _mouseY=event.xbutton.y;
      _chooseCursor();
      if(!_ctrlPressed) // Not Ctrl : selection
        {
        double xDir=_limitMinX;
        double yDir=(1.0-(2.0*_mouseX)/(double)_width)*_limitY*_limitMinX;
        double zDir=(1.0-(2.0*_mouseY)/(double)_height)*_limitZ*_limitMinX;
        localToGlobalPosition(xDir,yDir,zDir);
        double x,y,z,d=0.0,dmin=0.0,cutDist=_limitMinX*_limitMinX;
        XGuiShape3D * nearest=(XGuiShape3D *)0;
        XGuiShape3DList::iterator it=_shapes.begin();
        for(;it!=_shapes.end();it++)
          {
          int faceNumber;
          if((*it)->intersectRay(_px,_py,_pz,
                                 xDir-_px,yDir-_py,zDir-_pz,
                                 x,y,z,faceNumber))
            {
            x-=_px; y-=_py; z-=_pz;
            d=x*x+y*y+z*z;
            if((d>cutDist)&&(!nearest||(d<dmin)))
              {
              nearest=(*it);
              dmin=d;
              }
            }
          }
        if(d>=_limitMaxX*_limitMaxX) // not too far
          nearest=(XGuiShape3D *)0;
        if(_shiftPressed) // Shift : (un)select shapes
          {
          if(nearest)
            {
            for(it=_select.begin();it!=_select.end();it++) // unselect
              if(*it==nearest) break;
            if(it==_select.end())
              {
              if(_pressed==Button1)
                {
                _select.push_back(nearest);
                nearest->notifySelection(this,true);
                }
              }
            else
              {
              if(_pressed!=Button1)
                {
                _select.erase(it);
                nearest->notifySelection(this,false);
                }
              }
            XGuiViewer3D::_mustDraw=true;
            }
          }
        else // unselect all shapes and select the nearest
          {
          XGuiShape3DList::iterator it;
          XGuiShape3DList tmpList(_select);
          while(tmpList.size())
            {
            for(it=_select.begin();it!=_select.end();it++)
              {
              if((*it==tmpList.front())&&
                 ((*it!=nearest)||(_pressed!=Button1))) // avoid reselection
                {
                _select.erase(it);
                tmpList.front()->notifySelection(this,false);
                break;
                }
              }
            tmpList.pop_front();
            }
          if(nearest&&(_pressed==Button1))
            {
            for(it=_shapes.begin();it!=_shapes.end();it++)
              if(*it==nearest) break;
            if(it!=_shapes.end()) // nearest not destroyed
              {
              for(it=_select.begin();it!=_select.end();it++)
                if(*it==nearest) break;
              if(it==_select.end()) // not reinserted by previous CB
                {
                _select.push_back(nearest);
                nearest->notifySelection(this,true);
                }
              }
            }
          XGuiViewer3D::_mustDraw=true;
          }
        if(nearest&&(_pressed==Button1)) _canMoveSelection=true;
        }
      }
    break;
  case ButtonRelease:
    if(_pressed==event.xbutton.button)
      {
      if((_pressed==Button1)&&
         _ctrlPressed&&
         (event.xbutton.time-_motionData.lastMotion<
          XGuiViewer3D::_motionTimerDt))
        {
        _motionData.move=true;
        }
      _pressed=0;
      _canMoveSelection=false;
      _chooseCursor();
      }
    break;
  case MotionNotify:
    while(XCheckTypedWindowEvent(getXGuiManager()->getDisplay(),
                                 _window,MotionNotify,(XEvent *)&event));
    if(_pressed)
      {
      _motionData.move=false;
      _motionData.lastMotion=(Time)-1L;
      double dx=((double)(event.xmotion.x-_mouseX))/(double)_width;
      double dy=((double)(event.xmotion.y-_mouseY))/(double)_height;
      _mouseX=event.xbutton.x;
      _mouseY=event.xbutton.y;
      if(_ctrlPressed)
        {
        double xmin,xmax,ymin,ymax,zmin,zmax;
        double x,y,z,xInc,yInc,zInc;
        double xl,yl,zl;
        double xc=0.0;
        int nbSeen=0;
        int i,j,k,precision=3;
        XGuiShape3DList::iterator itS=_shapes.begin();
        for(;itS!=_shapes.end();itS++)
          {
          if((*itS)->getLocalBoundingBox(xmin,ymin,zmin,xmax,ymax,zmax))
            {
            (*itS)->localToGlobalPosition(xmin,ymin,zmin);
            (*itS)->localToGlobalPosition(xmax,ymax,zmax);
            xmin-=_px; ymin-=_py; zmin-=_pz;
            xmax-=_px; ymax-=_py; zmax-=_pz;
            xInc=(xmax-xmin)/precision;
            yInc=(ymax-ymin)/precision;
            zInc=(zmax-zmin)/precision;
            for(i=0;i<=precision;i++)
              {
              for(j=0;j<=precision;j++)
                {
                for(k=0;k<=precision;k++)
                  {
                  x=xmin+xInc*i;
                  y=ymin+yInc*j;
                  z=zmin+zInc*k;
                  xl=_r00*x+_r10*y+_r20*z;
                  yl=_r01*x+_r11*y+_r21*z;
                  zl=_r02*x+_r12*y+_r22*z;
                  if(yl<0) yl=-yl;
                  if(zl<0) zl=-zl;
                  if((xl>_limitMinX)&&(xl<_limitMaxX)&&
                     (yl<_limitY*xl)&&(zl<_limitZ*xl))
                    {
                    nbSeen++;
                    xc+=xl;
                    }
                  }
                }
              }
            }
          }
        if(nbSeen)
          {
          xc/=nbSeen;
          if(xc<_limitMinX) xc=_limitMinX;
          }
        else xc=_limitMinX;
        if(_pressed==Button1) // ---> rotate or translate Y / Z
          {
          if(_shiftPressed) // Ctrl+Shift ---> translate Y / Z
            {
            translate(0.0,xc*dx,xc*dy);
            }
          else // Ctrl ---> rotate
            {
            _motionData.lastMotion=event.xmotion.time;
            _motionData.dx=xc;
            _motionData.yaw=-5.0*dx;
            _motionData.pitch=5.0*dy;
            void (*oldCB)(XGuiElement *,void *)=_callback;
            _callback=(void (*)(XGuiElement *,void *))0;
            translate(_motionData.dx,0,0);
            yaw(_motionData.yaw);
            pitch(_motionData.pitch);
            translate(-_motionData.dx,0,0);
            _callback=oldCB;
            if(_callback) (*_callback)(this,_data);
            }
          }
        else // other button ---> translate X
          {
          translate(xc*2.0*dy,0.0,0.0);
          }
        }
      else if(_canMoveSelection)
        {
        double screenDy=-2.0*dx*_limitMinX*_limitY;
        double screenDz=-2.0*dy*_limitMinX*_limitZ;
        double objX,objY,objZ;
        double objDx,objDy,objDz;
        XGuiShape3DList::iterator it;
        XGuiShape3DList tmpList(_select);
        while(tmpList.size())
          {
          for(it=_select.begin();it!=_select.end();it++)
            {
            if((*it)==tmpList.front())
              {
              (*it)->getPosition(objX,objY,objZ);
              globalToLocalPosition(objX,objY,objZ);
              objDx=0.0;
              objDy=screenDy*objX/_limitMinX;
              objDz=screenDz*objX/_limitMinX;
              localToGlobalPosition(objDx,objDy,objDz);
              (*it)->notifyMotion(objDx-_px,objDy-_py,objDz-_pz);
              break;
              }
            }
          tmpList.pop_front();
          }
        }
      }
    break;
  }
}

void XGuiViewer3D::redraw(void) // virtual
{
if(_window&&_mapped)
  {
  glXMakeCurrent(getXGuiManager()->getDisplay(),_window,
                 XGuiViewer3D::_globalContext);
  glViewport(0,0,_width,_height);
  glClearColor(_r,_g,_b,1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(_viewAngle*360.0/M_PI,_aspectRatio,_limitMinX,_limitMaxX);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(_px,_py,_pz,                // local origin
            _px+_r00,_py+_r10,_pz+_r20, // local x direction
            _r02,_r12,_r22);            // local z
  float lightDir[]={-_r00,-_r10,-_r20,0.0};
  glLightfv(GL_LIGHT0,GL_POSITION,lightDir);
  XGuiShape3DList::iterator it=_shapes.begin();
  for(;it!=_shapes.end();it++)
    {
    (*it)->draw();
    }
  if(_select.size())
    {
    for(it=_select.begin();it!=_select.end();it++) // draw selection
      (*it)->drawBoundingBox(_rInv,_gInv,_bInv);
    }
  glXSwapBuffers(getXGuiManager()->getDisplay(),_window);
  }
}

void XGuiViewer3D::_adjustLimits(void)
{
_aspectRatio=((double)_width)/((double)_height);
_limitZ=::tan(_viewAngle);
_limitY=_limitZ*_aspectRatio;
}

void XGuiViewer3D::_chooseCursor(void)
{
if(_ctrlPressed)
  {
  if(_pressed&&(_pressed!=Button1))
    getXGuiManager()->setZoomCursor(_window);
  else
    {
    if(_shiftPressed)
      getXGuiManager()->setMoveCursor(_window);
    else
      getXGuiManager()->setRollCursor(_window);
    }
  }
else getXGuiManager()->setDefaultCursor(_window);
}

void XGuiViewer3D::_motionProc(XtPointer,XtIntervalId *) // static
{
if(!getXGuiManager()->isExclusive()&&
   !XPending(getXGuiManager()->getDisplay()))
  {
  bool moved=false;
  XGuiViewer3D * viewer;
  XGuiViewer3DList::iterator itV=XGuiViewer3D::_viewers.begin();
  for(;itV!=XGuiViewer3D::_viewers.end();itV++)
    {
    viewer=(*itV);
    if(viewer->_motionData.move)
      {
      moved=true;
      void (*oldCB)(XGuiElement *,void *)=viewer->_callback;
      viewer->_callback=(void (*)(XGuiElement *,void *))0;
      viewer->translate(viewer->_motionData.dx,0,0);
      viewer->yaw(viewer->_motionData.yaw);
      viewer->pitch(viewer->_motionData.pitch);
      viewer->translate(-viewer->_motionData.dx,0,0);
      viewer->_callback=oldCB;
      if(viewer->_callback) (*viewer->_callback)(viewer,viewer->_data);
      }
    }
  if(moved)
    {
    void (*task)(void *);
    void * data;
    getXGuiManager()->getTask(task,data);
    if(!task) XGuiViewer3D::drawAll();
    }
  }
XGuiViewer3D::_motionTimerId=XtAppAddTimeOut(getXGuiManager()->getContext(),
                                             XGuiViewer3D::_motionTimerDt,
                                             XGuiViewer3D::_motionProc,
                                             (XtPointer)0);
}

Window XGuiViewer3D::_createWindow(Window parentWin,int x,int y,int w,int h)
{                                                                  // static
XSetWindowAttributes attr;
attr.background_pixel=getXGuiManager()->getBackground();
attr.border_pixel=getXGuiManager()->getForeground();
attr.colormap=XCreateColormap(getXGuiManager()->getDisplay(),
                              getXGuiManager()->getRoot(),
                              XGuiViewer3D::_globalVisualInfo->visual,
                              AllocNone);
return(XCreateWindow(getXGuiManager()->getDisplay(),
                     parentWin,x,y,w,h,0,
                     XGuiViewer3D::_globalVisualInfo->depth,
                     InputOutput,
                     XGuiViewer3D::_globalVisualInfo->visual,
                     CWBackPixel | CWBorderPixel | CWColormap,
                     &attr));
}

#endif // OPEN_GL
#endif // X_GUI

