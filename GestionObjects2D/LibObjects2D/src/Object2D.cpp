#include "Object2D.h"
#include "guiTrans.h"
#include <math.h>

#include <stack>   // Pour la version iterative de _computeConcernObjects
#include <vector>

set<Object2D*> Object2D::allObject2D;

#define OBJECT2D_SEE_CALLBACK_CALL 0 // To debug interface interaction...

/*-------- Static data -----------------------------------------------------*/

static void * _userData=(void *)0;

static GuiWindow * _mainWin=(GuiWindow *)0;

static GuiViewer2D * _viewer=(GuiViewer2D *)0;

/*-------- Hidden Callbacks ------------------------------------------------*/

static
void
_selectCB(GuiShape2D *   /* shape  */,
          XGuiViewer2D * /* viewer */,
          bool           selected,
          void         * userData)
{
 if(!selected) { return; }

#if OBJECT2D_SEE_CALLBACK_CALL
cerr << "------------------------------->" << endl;
cerr << "In Object2D.cpp, begin _selectCB" << endl;
#endif

graphic_selectCallback((Object2D *)userData,_userData);

#if OBJECT2D_SEE_CALLBACK_CALL
cerr << "In Object2D.cpp, end   _selectCB" << endl;
cerr << "<-------------------------------" << endl;
#endif
}

static
void
_keyCB(GuiShape2D * /* shape */,
       const Strings & key,
       void * userData)
{
#if OBJECT2D_SEE_CALLBACK_CALL
cerr << "---------------------------->" << endl;
cerr << "In Object2D.cpp, begin _keyCB" << endl;
#endif

graphic_keyPressCallback((Object2D *)userData,key,_userData);

#if OBJECT2D_SEE_CALLBACK_CALL
cerr << "In Object2D.cpp, end   _keyCB" << endl;
cerr << "<----------------------------" << endl;
#endif
}

static
void
_motionCB(GuiShape2D * /* shape */,
          double dx,
          double dy,
          void * userData)
{
#if OBJECT2D_SEE_CALLBACK_CALL
cerr << "------------------------------->" << endl;
cerr << "In Object2D.cpp, begin _motionCB" << endl;
#endif

graphic_mouseDragCallback((Object2D *)userData,dx,dy,_userData);

#if OBJECT2D_SEE_CALLBACK_CALL
cerr << "In Object2D.cpp, end   _motionCB" << endl;
cerr << "<-------------------------------" << endl;
#endif
}

static
void
_viewerKeyCB(GuiViewer2D * /* viewer */,
             const Strings & key,
             void * /* userData */)
{
#if OBJECT2D_SEE_CALLBACK_CALL
cerr << "---------------------------------->" << endl;
cerr << "In Object2D.cpp, begin _viewerKeyCB" << endl;
#endif

graphic_keyPressCallback((Object2D *)0,key,_userData);

#if OBJECT2D_SEE_CALLBACK_CALL
cerr << "In Object2D.cpp, end   _viewerKeyCB" << endl;
cerr << "<----------------------------------" << endl;
#endif
}

static
void
_viewerResizeCB(GuiElement * calling,
                void * viewer)
{
GuiWindow * win=(GuiWindow *)calling;
GuiViewer2D * v2d=(GuiViewer2D *)viewer;
v2d->setX(0);
v2d->setY(0);
v2d->setWidth(win->getInWidth());
v2d->setHeight(win->getInHeight());
}

static
void
_viewerCloseCB(GuiElement *,
               void *)
{
exit(0);
}

/*-------- class Object2D ------------------------------------------------*/

/*-------- Constructor/Destructor ----------------------------------------*/

Object2D::Object2D(void)
{
 Object2D * obj2d = this;

 obj2d->_shape=NULL;
 setLocation(0.0,0.0,0.0);
 setLayer(0);
 setColor("white");

 point(); /* Doit etre appele uniquement lorsque :
            _shape,_x,_y,_theta,_color,_layer initialises */

 allObject2D.insert(this);
}

Object2D::Object2D(const Object2D& object2D)
{
 _copy(object2D);
 allObject2D.insert(this);
}

Object2D& Object2D::operator=(const Object2D& object2D)
{
 if (this != &object2D)
 {
  _destroy();
  _copy(object2D);
 }
 return *this;
}

Object2D::~Object2D(void)
{
 _destroy();
 _removeAllAttachments();      // Ne mettre que dans le destructeur ???
 allObject2D.erase(this);
}

void  Object2D::_copy(const Object2D& object2D)
{
 Object2D * obj2d = this;

 if (strcmp(object2D._type,"noShape")==0)
 {
  obj2d->_shape             = NULL;
 }
 else
 if (strcmp(object2D._type,"point")==0)
 {
  const XGuiPoint * sh      = (const XGuiPoint *)object2D._shape;
  obj2d->_shape             = new GuiPoint(*sh);
 }
 else
 if (strcmp(object2D._type,"text")==0)
 {
  const XGuiText * sh       = (const XGuiText *)object2D._shape;
  obj2d->_shape             = new GuiText(*sh);
 }
 else
 if (strcmp(object2D._type,"line")==0)
 {
  const XGuiLine * sh      = (const XGuiLine *)object2D._shape;
  obj2d->_shape            = new GuiLine(*sh);
 }
 else
 if (strcmp(object2D._type,"square")==0)
 {
  const XGuiSquare * sh    = (const XGuiSquare *)object2D._shape;
  obj2d->_shape            = new GuiSquare(*sh);
 }
 else
 if (strcmp(object2D._type,"rectangle")==0)
 {
  const XGuiRectangle * sh = (const XGuiRectangle *)object2D._shape;
  obj2d->_shape            = new GuiRectangle(*sh);
 }
 else
 if (strcmp(object2D._type,"polyline")==0)
 {
  const XGuiPolyline * sh  = (const XGuiPolyline *)object2D._shape;
  obj2d->_shape            = new GuiPolyline(*sh);
 }
 else
 if (strcmp(object2D._type,"polygon")==0)
 {
  const XGuiPolygon * sh   = (const XGuiPolygon *)object2D._shape;
  obj2d->_shape            = new GuiPolygon(*sh);
 }
 else
 if (strcmp(object2D._type,"circle")==0)
 {
  const XGuiCircle * sh    = (const XGuiCircle *)object2D._shape;
  obj2d->_shape            = new GuiCircle(*sh);
 }
 else
 if (strcmp(object2D._type,"image")==0)
 {
  const XGuiImage * sh     = (const XGuiImage *)object2D._shape;
  obj2d->_shape            = new GuiImage(*sh);
 }
 else cerr << "Error Object2D::_copy, unknown type " << object2D._type << endl;

 setLocation(object2D._x,object2D._y,object2D._theta);
 setLayer(object2D._layer);
 setColor(object2D._color.c_str());

 if (obj2d->_shape)
 {
  obj2d->_shape->setKeyCallback(_keyCB,obj2d);
  obj2d->_shape->setMotionCallback(_motionCB,obj2d);
  obj2d->_shape->setSelectCallback(_selectCB,obj2d);
 }
 obj2d->_isImage  = object2D._isImage;
 obj2d->_type     = object2D._type;
}

void  Object2D::_destroy(void)
{
 Object2D * obj2d = this;
 if (obj2d->_shape) delete obj2d->_shape;
}

//--
ostream& operator<<(ostream& os, const Object2D& object2D)
{
 object2D.display(os);
 return os;
}

void Object2D::display(ostream& os) const
{
 os << "type: " << _type << ", ";
 if (strcmp(_type,"image")==0)
 {
  os << "fileName: " << _fileName;
 }
 else
 {
  os << "color: " << _color;
 }

 os << ", position(x,y,theta): " << _x << " " << _y << " " << _theta << endl;
} 

bool operator==(const Object2D& obj1, const Object2D& obj2)
{
 return obj1.isEqualTo(obj2);
}

bool operator!=(const Object2D& obj1, const Object2D& obj2)
{
 return !(obj1==obj2);
}

bool Object2D::isEqualTo(const Object2D& obj) const
{
 if (strcmp(_type,obj._type)!=0) return false;
 if (strcmp(_type,"image")==0) 
 {
  if (_fileName==obj._fileName) return true;
  else return false;
 }
 else
 {
  if (_color==obj._color) return true;
  else return false;
 }
}

/*-------- Location -------------------------------------------------------*/

void Object2D::setLocation(double x, double y, double theta)
{
 _beforeMove();

 _x = x; _y = y; _theta = betweenPi(theta);

 Object2D * obj2d = this;
 if (obj2d->_shape) obj2d->_shape->move(_x,_y,_theta);

 _afterMove();
}

void Object2D::getLocation(double& xOut, double& yOut, double& thetaOut) const
{
 xOut     = _x;
 yOut     = _y;
 thetaOut = _theta;
}

void Object2D::setX(double x)
{
 _beforeMove();

 _x = x;

 Object2D * obj2d = this;
 if (obj2d->_shape) obj2d->_shape->move(_x,_y,_theta);

 _afterMove();
}

double Object2D::getX(void) const
{
 return (_x);
}

void Object2D::setY(double y)
{
 _beforeMove();

 _y = y;

 Object2D * obj2d = this;
 if (obj2d->_shape) obj2d->_shape->move(_x,_y,_theta);

 _afterMove();
}

double Object2D::getY(void) const
{
 return (_y);
}

void Object2D::setTheta(double theta)
{
 _beforeMove();

 _theta = betweenPi(theta);

 Object2D * obj2d = this;
 if (obj2d->_shape) obj2d->_shape->move(_x,_y,_theta);

 _afterMove();
}

double Object2D::getTheta(void) const
{
 return (_theta);
}

/*-------- Motion ---------------------------------------------------------*/

void Object2D::translate(double dx, double dy)   // ^y     ^ x     
{                                                //  \    /
_beforeMove();                                   //   \  /)theta
                                                 //    \.------
double c=cos(_theta);                            //    obj
double s=sin(_theta);

 _x = _x+dx*c-dy*s;
 _y = _y+dx*s+dy*c;

 Object2D * obj2d = this;
 if (obj2d->_shape) obj2d->_shape->move(_x,_y,_theta);

_afterMove();
}

void Object2D::rotate(double dTheta)
{
 _beforeMove();

 _theta=betweenPi(_theta+dTheta);

 Object2D * obj2d = this;
 if (obj2d->_shape) obj2d->_shape->move(_x,_y,_theta);

 _afterMove();
}

/*-------- Interaction ----------------------------------------------------*/

void Object2D::onSelection(void)
{
#if OBJECT2D_SEE_CALLBACK_CALL
 fprintf(stderr,"Object 0x%p: button Press\n",(void*)this);
#endif
}

void Object2D::onKeyPress(const char *key)
{
 (void)key;
#if OBJECT2D_SEE_CALLBACK_CALL
 fprintf(stderr,"Object 0x%p: key Press <%s>\n",(void*)this,key);
#endif
}
//--
void Object2D::onMouseDrag(double dx, double dy)
{
#if OBJECT2D_SEE_CALLBACK_CALL
 fprintf(stderr,"Object 0x%p: mouse Drag <%f,%f>\n",(void*)this,dx,dy);
#endif

  double x,y,theta;

  getLocation(x,y,theta);
  x+=dx;
  y+=dy;
  setLocation(x,y,theta);
}

/*-------- Detection -------------------------------------------------------*/

bool Object2D::isInside(double x, double y) const
{
const Object2D * obj2d = this;
if (obj2d->_shape) return(obj2d->_shape->isInside(x,y) ? true : false);
else return false;   // Ou (_x==x && _y==y); ??
}



/* Object2D::intersectRay : Lance un rayon (a partir de xRay, yRay et
   dans la direction thetaRay), et indique s'il y a intersection avec
   l'objet *this.
   On obtient egalement le point intersection.
*/
bool Object2D::intersectRay(double xRay, double yRay, double thetaRay,
                            double& xOut,
                            double& yOut) const
{
const Object2D * obj2d = this;
double xDir=cos(thetaRay);
double yDir=sin(thetaRay);
if (obj2d->_shape)
     return(obj2d->_shape->intersectRay(xRay,yRay,xDir,yDir,xOut,yOut) ?
            true : false);
else return false; // Pas d'intersection avec un objet invisible
}

/* Object2D::throwRay : Lance un rayon devant l'objet *this
   (via les coordonnees et l'axe de l'objet2D *this)
   et retourne l'objet le plus proche (contenu dans tabObject2D)
   On obtient egalement le point intersection.
*/
Object2D * Object2D::throwRay(double& xOut, double& yOut,
                              Object2D *tabObject2D[],
                              unsigned int nbObject2D) const
{
 double xThis,yThis,thetaThis;

 unsigned int i;
 Object2D *other, *found=NULL;

 double x,y,dx,dy,d,dmin=0.0;

 getLocation(xThis,yThis,thetaThis);

 for(i=0;i<nbObject2D;i++)
 {
  other=tabObject2D[i];

  if (other==this) continue;

  if (other->intersectRay(xThis,yThis,thetaThis,x,y))
  {
   dx=x-xThis;
   dy=y-yThis;
   d=dx*dx+dy*dy;
   if(!found||(d<dmin))
   {
    dmin=d;
    xOut=x;
    yOut=y;
    found=other;
   }
  }
 }
 return (found);
}

/*
// Dans Object2D.h:
// ----------------
// Object2D * throwRay(double& xOut, double& yOut,
//                     const vector<Object2D*>& vectObject2D) const;

Object2D * Object2D::throwRay(double& xOut, double& yOut,
                              const vector<Object2D*>& vectObject2D) const
{
 double xThis,yThis,thetaThis;

 unsigned int i, nbObject2D=vectObject2D.size();
 Object2D *other, *found=NULL;

 double x,y,dx,dy,d,dmin=0.0;

 getLocation(xThis,yThis,thetaThis);

 for(i=0;i<nbObject2D;i++)
 {
  other=vectObject2D[i];

  if (other==this) continue;

  if (other->intersectRay(xThis,yThis,thetaThis,x,y))
  {
   dx=x-xThis;
   dy=y-yThis;
   d=dx*dx+dy*dy;
   if(!found||(d<dmin))
   {
    dmin=d;
    xOut=x;
    yOut=y;
    found=other;
   }
  }
 }
 return (found);
}
*/

/*
  Determine l'Object2D le plus proche et situe dans un cone de visibilite.

  Parametres
  E vision - l'angle d'ouverture du cone du champ de perception
  E range - la portee du cone du champ de perception
  E turn - l'orientation du champ par rapport a celui de l'Object2D *this

  Valeur de retour
  S L'Object2D le plus proche present dans le cone de perception ou NULL
    s'il n'y en a pas

*/
Object2D * Object2D::viewFirstObject2D(double vision,
                                       double range,
                                       double turn) const
{
 double v2=vision;
 v2=(v2 ? v2/2.0 : M_PI);
 range *= range;
 double x0,y0,theta0;
 getLocation(x0,y0,theta0);
 double a0=theta0+turn;
 double x,y;
 double d,a;
 const Object2D * obj=(const Object2D *)NULL;
 bool firstTime=true;
 double dMin=0.0;
 double aMin=0.0; (void)aMin;
 const Object2D * objMin=(const Object2D *)NULL;
 set<Object2D*>::const_iterator iter = allObject2D.begin();
 for(;!(iter==allObject2D.end());iter++)
    {
    obj=*iter;
    if(obj!=this)  // if(obj!=this && obj->_shape)
      {
      x = obj->getX() - x0;
      y = obj->getY() - y0;
      d=x*x+y*y;
      if((!range||d<range)&&(firstTime||d<dMin))
        {
        a=betweenPi(cartToAngle(x,y)-a0);
        if(::fabs(a)<=v2)
          {
          dMin=d;
          aMin=a;
          objMin=obj;
          firstTime=false;
          }
        }
      }
    }
 if(firstTime) // no Object2D found
    {
    // angle = 0.0;
    // distance = 0.0;
    return (Object2D*)NULL;
    }
  else
    {
    // angle = betweenPi(aMin-turn);
    // distance = ::sqrt(dMin);
    return (Object2D*)objMin;
    }
}

/* 
  Retourne le nombre d'Object2D presents dans le cone de vision et ...
  place les Object2D presents dans le cone de vision dans tabObject2D
  Comme dans Object2D::viewObject2D, il y a un malloc, il faudra penser
  a faire un free !
*/
int Object2D::viewObject2D(Object2D*** tabObject2D,          // Version C
                              double vision,
                              double range,
                              double turn) const
{
 vector<Object2D*> v;

 int nbObject2D = this->viewObject2D(v,vision,range,turn);

 Object2D** tab = (Object2D**)malloc(nbObject2D*sizeof(Object2D*));

 for(int i=0;i<nbObject2D;i++)
 {
  tab[i]=v[i];
 }

 *tabObject2D = tab;

 return nbObject2D;
}

/* 
  Retourne le nombre d'Object2D presents dans le cone de vision et ...
  place les Object2D presents dans le cone de vision dans vectObject2D
*/
int Object2D::viewObject2D(vector<Object2D*>& vectObject2D, // Version C++
                           double vision,
                           double range,
                           double turn) const
{
vectObject2D.clear();
double v2=vision;
v2=(v2 ? v2/2.0 : M_PI);
range *= range;
double x0,y0,theta0;
getLocation(x0,y0,theta0);
double a0=theta0+turn;
double x,y;
double d,a;
const Object2D * obj = (const Object2D *)NULL;
set<Object2D*>::const_iterator iter = allObject2D.begin();

for(;!(iter==allObject2D.end());iter++)
   {
    obj=*iter;
    if(obj!=this)  // if(obj!=this && obj->_shape)
    {
     x = obj->getX() - x0;
     y = obj->getY() - y0;
     d=x*x+y*y;
     if(!range||d<range)
       {
       a=betweenPi(cartToAngle(x,y)-a0);
       if(::fabs(a)<=v2)
         {
          vectObject2D.push_back((Object2D *)obj);
         }
       }
    }
   }
 return vectObject2D.size();
}

/*-------- Transformation --------------------------------------------------*/

void Object2D::globalToLocalPosition(double& xInOut, double& yInOut) const
{
double x=xInOut-_x;
double y=yInOut-_y;
double d=sqrt(x*x+y*y);
double a=(d ? atan2(y,x) : 0.0);
a-=_theta;
xInOut=d*cos(a);
yInOut=d*sin(a);
}

void Object2D::localToGlobalPosition(double& xInOut, double& yInOut) const
{
double x=xInOut;
double y=yInOut;
double d=sqrt(x*x+y*y);
double a=(d ? atan2(y,x) : 0.0);
a+=_theta;
xInOut=_x+d*cos(a);
yInOut=_y+d*sin(a);
}

double Object2D::globalToLocalOrientation(double orientation) const
{
orientation-=_theta;
while(orientation>M_PI) orientation-=2*M_PI;
while(orientation<=-M_PI) orientation+=2*M_PI;
return(orientation);
}

double Object2D::localToGlobalOrientation(double orientation) const
{
orientation+=_theta;
while(orientation>M_PI) orientation-=2*M_PI;
while(orientation<=-M_PI) orientation+=2*M_PI;
return(orientation);
}

/*-------- Representation --------------------------------------------------*/

void Object2D::setColor(const char * colorName)
{
 if (colorName==NULL)
 {
  cerr << "setColor(NULL); has no effect" << endl;
  return;
 }

 _color = colorName;

 Object2D * obj2d = this;
 if (obj2d->_shape) obj2d->_shape->setColor(_color.c_str());
}

const char *
Object2D::getColor(void) const
{
 if (strcmp(_type,"noShape")==0) return NULL;
 return (_color.c_str());
}

void
Object2D::setLayer(int layer)
{
 _layer = layer;

 Object2D * obj2d = this;
 if (obj2d->_shape)
 {
  bool select=_viewer->isSelected(obj2d->_shape);
  obj2d->_shape->setLayer(layer);
  if(select)
  { 
   _viewer->select(obj2d->_shape, false); // VR: Before true...
      // If the associated shape is already selected, it means that
      // the callBack notifySelection was already called on it.
      // Then no need to propagate... see XGuiViewer2D::select
  }
 }
}
                  
int
Object2D::getLayer(void) const
{
 return (_layer);
}

void Object2D::_changeShape(GuiShape2D * sh)  // Methode privee
{
Object2D * obj2d = this;

 if (sh==NULL) {
                 if (obj2d->_shape) delete obj2d->_shape;
                 obj2d->_shape=sh;
                 obj2d->_isImage=false;
                 return;
                }

 sh->setKeyCallback(_keyCB,obj2d);
 sh->setMotionCallback(_motionCB,obj2d);
 sh->setSelectCallback(_selectCB,obj2d);
 sh->setLayer(_layer);
 if (obj2d->_shape)
 {
   if (_viewer->isSelected(obj2d->_shape))
   {
    _viewer->select(sh,false); // VR: Before true...
       // If the associated shape is already selected, it means that
       // the callBack notifySelection was already called on it.
       // Then no need to propagate... see XGuiViewer2D::select
   }
   delete obj2d->_shape;
 }
 obj2d->_shape=sh;
 obj2d->_isImage=false;
}

void Object2D::getBoundingBox(double & xmin,double & ymin,
                              double & xmax,double & ymax)
{
 if (!(_viewer && _shape))       { xmin=ymin=xmax=ymax=0; return; }

 _shape->getBoundingBox(xmin,ymin,xmax,ymax,_viewer);
}

void Object2D::noShape(void)
{
 Object2D * obj2d = this;
 _changeShape(NULL);
 obj2d->_type="noShape";
}

void Object2D::point(void)
{
Object2D * obj2d = this;
_changeShape(new GuiPoint(_x,_y,_theta,_color.c_str()));
obj2d->_type="point";
}

void Object2D::text(const char * text, double * textHeight, double * textWidth)
{
Object2D * obj2d = this;
_changeShape(new GuiText(_x,_y,_theta,_color.c_str(),
                         text));
obj2d->_type="text";

#if 1
if (textHeight) *textHeight = getXGuiManager()->getCharHeight();
if (textWidth)  *textWidth  = getXGuiManager()->getTextWidth(text);
#else
if (!(_viewer && _shape)) { if (textHeight) *textHeight = 0;
                            if (textWidth)  *textWidth  = 0;
                            return;
                          }
double xmin,ymin,xmax,ymax;
getBoundingBox(xmin,ymin,xmax,ymax);

xmin = _viewer->getColumn(xmin);
xmax = _viewer->getColumn(xmax);
ymin = _viewer->getLine(ymin);
ymax = _viewer->getLine(ymax);

if (textHeight) *textHeight = ymin - ymax; // Not ymax - ymin ....!
if (textWidth)  *textWidth  = xmax - xmin;
#endif
}

void Object2D::line(double length)
{
Object2D * obj2d = this;
_changeShape(new GuiLine(_x,_y,_theta,_color.c_str(),
                         length));
obj2d->_type="line";
}

void Object2D::square(double side, int filled)
{
Object2D * obj2d = this;
_changeShape(new GuiSquare(_x,_y,_theta,_color.c_str(),
                           side,
                           filled));
obj2d->_type="square";
}

void Object2D::rectangle(double length, double width, int filled)
{
Object2D * obj2d = this;
_changeShape(new GuiRectangle(_x,_y,_theta,_color.c_str(),
                              length,
                              width,
                              filled));
obj2d->_type="rectangle";
}

void Object2D::polyline(unsigned int nbPoints,
                        const double * xPoints,
                        const double * yPoints)
{
Object2D * obj2d = this;
_changeShape(new GuiPolyline(_x,_y,_theta,_color.c_str(),
                             nbPoints,
                             xPoints,
                             yPoints));
obj2d->_type="polyline";
}

void Object2D::polygon(unsigned int nbPoints,
                       const double * xPoints,
                       const double * yPoints,
                       int filled)
{
Object2D * obj2d = this;
_changeShape(new GuiPolygon(_x,_y,_theta,_color.c_str(),
                            nbPoints,
                            xPoints,
                            yPoints,
                            filled));
obj2d->_type="polygon";
}

void Object2D::circle(double radius, int filled)
{
Object2D * obj2d = this;
_changeShape(new GuiCircle(_x,_y,_theta,_color.c_str(),
                           radius,
                           filled));
obj2d->_type="circle";
}

int Object2D::image(const char * fileName, double pixelScale)
{
Object2D * obj2d = this;
GuiImage * sh=new GuiImage(_x,_y,_theta,_color.c_str(),
                           fileName,
                           (const StringsVect *)0,
                           pixelScale);
if(sh->fail())
  {
  delete sh;
  return(0);
  }
else
  {
  _changeShape(sh);
  obj2d->_isImage=true;
  obj2d->_fileName=fileName;
  obj2d->_type="image";
  return(1);
  }
}

int Object2D::getImagePixelAt(double x, double y,
                              int& redOut,
                              int& greenOut,
                              int& blueOut)
{
Object2D * obj2d = this;
if(!obj2d->_isImage)
  {
  redOut=-1;
  greenOut=-1;
  blueOut=-1;
  return(0);
  }
GuiImage * sh=(GuiImage *)obj2d->_shape;
double xx=x-_x;
double yy=y-_y;
double sinTh=sin(_theta);
double cosTh=cos(_theta);
int xi=(int)::floor(sh->getNbColumns()*0.5+(xx*cosTh+yy*sinTh)/sh->getScale());
int yi=(int)::floor(sh->getNbLines()*0.5+(yy*cosTh-xx*sinTh)/sh->getScale());
if((xi>=0)&&(xi<sh->getNbColumns())&&
   (yi>=0)&&(yi<sh->getNbLines()))
  {
  unsigned char r,g,b;
  sh->getRGB(sh->getPixel(xi,yi),r,g,b);
  redOut=r;
  greenOut=g;
  blueOut=b;
  return(1);
  }
else
  {
  redOut=-1;
  greenOut=-1;
  blueOut=-1;
  return(0);
  }
}

int Object2D::getImagePixelNumberAt(double x, double y)
{
Object2D * obj2d = this;
if(!obj2d->_isImage)
  {
  return(-1);
  }
GuiImage * sh=(GuiImage *)obj2d->_shape;
double xx=x-_x;
double yy=y-_y;
double sinTh=sin(_theta);
double cosTh=cos(_theta);
int xi=(int)::floor(sh->getNbColumns()*0.5+(xx*cosTh+yy*sinTh)/sh->getScale());
int yi=(int)::floor(sh->getNbLines()*0.5+(yy*cosTh-xx*sinTh)/sh->getScale());
if((xi>=0)&&(xi<sh->getNbColumns())&&
   (yi>=0)&&(yi<sh->getNbLines()))
  {
  return(sh->getPixel(xi,yi));
  }
else
  {
  return(-1);
  }
}

int Object2D::setImagePixelNumberAt(int pixel, double x, double y)
{
Object2D * obj2d = this;
if(!obj2d->_isImage)
  {
  return(0);
  }
GuiImage * sh=(GuiImage *)obj2d->_shape;
if((pixel<0)||(pixel>=sh->getNbColors()))
  {
  return(0);
  }
double xx=x-_x;
double yy=y-_y;
double sinTh=sin(_theta);
double cosTh=cos(_theta);
int xi=(int)::floor(sh->getNbColumns()*0.5+(xx*cosTh+yy*sinTh)/sh->getScale());
int yi=(int)::floor(sh->getNbLines()*0.5+(yy*cosTh-xx*sinTh)/sh->getScale());
if((xi>=0)&&(xi<sh->getNbColumns())&&
   (yi>=0)&&(yi<sh->getNbLines()))
  {
  sh->setPixel(xi,yi,pixel);
  return(1);
  }
else
  {
  return(0);
  }
}

int Object2D::getImageNbColors(void)
{
Object2D * obj2d = this;
if(!obj2d->_isImage)
  {
  return(0);
  }
GuiImage * sh=(GuiImage *)obj2d->_shape;
return(sh->getNbColors());
}

int Object2D::getImageRGB(int pixel,
                          int& redOut,
                          int& greenOut,
                          int& blueOut)
{
Object2D * obj2d = this;
if(!obj2d->_isImage)
  {
  redOut=-1;
  greenOut=-1;
  blueOut=-1;
  return(0);
  }
GuiImage * sh=(GuiImage *)obj2d->_shape;
if((pixel<0)||(pixel>=sh->getNbColors()))
  {
  redOut=-1;
  greenOut=-1;
  blueOut=-1;
  return(0);
  }
unsigned char r,g,b;
sh->getRGB(pixel,r,g,b);
redOut=r;
greenOut=g;
blueOut=b;
return(1);
}

/*--------------------------------------------------------------------------*/

/*-------- Graphical application template ----------------------------------*/

void
graphic_init(const char * windowName,
             const char * fontName)
{
setenv("ORISFONT",fontName, 1);
GuiManager * manager=getGuiManager();
if(!manager) manager=new GuiManager();
if(manager->fail())
  {
  cerr << "Can't connect to X Server" << endl;
  delete manager;
  exit(1);
  }
if(_viewer) delete _viewer;
if(_mainWin) delete _mainWin;
_mainWin = new GuiWindow(windowName);
_mainWin->setInWidth(200);
_mainWin->setInHeight(200);
_viewer = new GuiViewer2D(_mainWin);
_mainWin->setCallback(_viewerResizeCB,(void *)_viewer);
_mainWin->setCloseCallback(_viewerCloseCB,(void *)0);
getGuiManager()->show();
}

void
graphic_setWidth(int width)
{
if(_mainWin) _mainWin->setInWidth(width);
}

void
graphic_setHeight(int height)
{
if(_mainWin) _mainWin->setInHeight(height);
}

void
graphic_setBackground(const char * colorName)
{
if(_viewer) _viewer->setBackground(colorName);
}

void graphic_setViewPoint(double x,
                          double y,
                          double scale)
{
if(_viewer) _viewer->setViewPoint(x,y,scale);
}

void graphic_getViewPoint(double * xOut,
                          double * yOut,
                          double * scaleOut)
{
if(_viewer) _viewer->getViewPoint(*xOut,*yOut,*scaleOut);
}

void
graphic_autoscale(void)
{
if(_viewer) _viewer->autoScale();
}

void
graphic_run(void * userData)
{
_userData=userData;
GuiManager * manager = getGuiManager();
if(manager)
  {
  if(_viewer) _viewer->setKeyCallback(_viewerKeyCB,(void *)0);
  manager->setTask(graphic_mainLoop,_userData);
  manager->mainLoop();
  }
}

void
graphic_reset(void)
{
if(_viewer)
  {
  delete _viewer;
  _viewer=(GuiViewer2D *)0;
  }
if(_mainWin)
  {
  delete _mainWin;
  _mainWin=(GuiWindow *)0;
  }
GuiManager * manager=getGuiManager();
if(manager) delete manager;
}

/*--------------------------------------------------------------------------*/


void Object2D::attachTo(Object2D& object2D)
{
 if (this != &object2D) { object2D._attachedObjects.insert(this);
                          (*this)._isAttachedTo.insert(&object2D);
 }
}

bool Object2D::isAttachedTo(const Object2D& object2D) const
{
 set<Object2D*>::const_iterator iter;
 iter = _isAttachedTo.find((Object2D*)(&object2D));
 return (iter!=_isAttachedTo.end());
}

void Object2D::detachFrom(Object2D& object2D)
{
 object2D._attachedObjects.erase(this);
 (*this)._isAttachedTo.erase(&object2D);
}

void Object2D::detachFromAll(void)
{
 set<Object2D*>::iterator iter;

 for(iter=_isAttachedTo.begin();iter!=_isAttachedTo.end();iter++)
 {
  (*iter)->_attachedObjects.erase(this);
 }

 _isAttachedTo.clear();
}

void Object2D::_removeAllAttachments(void)
{
 detachFromAll();

 set<Object2D*>::iterator iter;

 for(iter=_attachedObjects.begin();iter!=_attachedObjects.end();iter++)
 {
  (*iter)->_isAttachedTo.erase(this);
 }

 _attachedObjects.clear();
}

void  Object2D::_beforeMove(void)
{
 //if (_attachedObjects.empty()) return;
 getLocation(_old_x,_old_y,_old_theta);
}

static set<Object2D*> concernObjects;

void Object2D::_computeConcernObjects(Object2D * object2D)
{
#if 1                                               // Iteratif
stack<Object2D*> pile;
pile.push(object2D);
while (!pile.empty())
{
 Object2D* obj = pile.top(); pile.pop();
 set<Object2D*>::iterator iterCO;
 iterCO = concernObjects.find(obj);  // Recherche de obj dans concernObjects
 if (iterCO==concernObjects.end()) { // Pas trouve
                                     concernObjects.insert(obj);
                                     set<Object2D*>::iterator iter;
                                     for(iter =obj->_attachedObjects.begin();
                                         iter!=obj->_attachedObjects.end();
                                         iter++)
                                     {
                                      pile.push(*iter);
                                     }
 }
}
#else                                               // Recursif
 concernObjects.insert(object2D);
 set<Object2D*>::iterator iter;

 for(iter =object2D->_attachedObjects.begin();
     iter!=object2D->_attachedObjects.end();
     iter++)
 {
  set<Object2D*>::iterator iterCO;
  iterCO = concernObjects.find(*iter);// Recherche de *iter dans concernObjects
  if (iterCO==concernObjects.end()) { // Pas trouve
                                      _computeConcernObjects(*iter);
  }
 }
#endif
}

void  Object2D::_afterMove(void)
{
 if (_attachedObjects.empty()) return;

 double new_x, new_y, new_theta;
 getLocation(new_x,new_y,new_theta);

 double Dx, Dy, Dtheta;

 Dx = new_x - _old_x;
 Dy = new_y - _old_y;
 Dtheta = new_theta - _old_theta;

 //concernObjects.clear();

 _computeConcernObjects(this);
 
 set<Object2D*>::iterator iterCO;
 for(iterCO =concernObjects.begin();
     iterCO!=concernObjects.end();
     iterCO++)
 {
  if (*iterCO != this) {

#if 1
                           // Version oRis ....
   (*iterCO)->_x += Dx;     
   (*iterCO)->_y += Dy;

   double dx = (*iterCO)->_x - new_x;
   double dy = (*iterCO)->_y - new_y;
   double dt = Dtheta;
   double d,a;
   cartesianToPolar(dx,dy,&d,&a);
   polarToCartesian(d,a+dt,&dx,&dy);
   (*iterCO)->_x = new_x + dx;
   (*iterCO)->_y = new_y + dy;
   (*iterCO)->_theta = betweenPi((*iterCO)->_theta+dt);
   if ((*iterCO)->_shape)
     (*iterCO)->_shape->move((*iterCO)->_x,(*iterCO)->_y,(*iterCO)->_theta);
#else
                         // Version buggee !
   double x,y,theta;

   (*iterCO)->getLocation(x,y,theta);
      
   (*iterCO)->_x     = x+Dx;
   (*iterCO)->_y     = y+Dy;
   (*iterCO)->_theta = betweenPi(theta+Dtheta);
   if ((*iterCO)->_shape)
     (*iterCO)->_shape->move((*iterCO)->_x,(*iterCO)->_y,(*iterCO)->_theta);
#endif
  }
 }

 concernObjects.clear();
}
