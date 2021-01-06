/*----------------------------------------------------------------------------
  CObject2D.cpp
----------------------------------------------------------------------------*/

#include "Object2D.h"
#include "CObject2D.h"

#include <math.h>

/*-------- Construction/Destruction ----------------------------------------*/

Object2D *
Object2D_new(void)
{
Object2D * obj2d = new Object2D();
return(obj2d);
}

Object2D *
Object2D_newCopy(const Object2D * anObj2d)
{
Object2D * obj2d = new Object2D(*anObj2d);
return(obj2d);
}

void
Object2D_copy(Object2D * obj2d, const Object2D * anObj2d)
{
 if (obj2d) *obj2d = *anObj2d;
}

void
Object2D_delete(Object2D * obj2d)
{
delete obj2d;
}

/*-------- Location -------------------------------------------------------*/

void
Object2D_setLocation(Object2D * obj2d,
                     double x,
                     double y,
                     double theta)
{
obj2d->setLocation(x,y,theta);
}

void
Object2D_getLocation(const Object2D * obj2d,
                     double * xOut,
                     double * yOut,
                     double * thetaOut)
{
obj2d->getLocation(*xOut,*yOut,*thetaOut);
}

void
Object2D_setX(Object2D * obj2d,
              double x)
{
obj2d->setX(x);
}

double
Object2D_getX(const Object2D * obj2d)
{
return(obj2d->getX());
}

void
Object2D_setY(Object2D * obj2d,
              double y)
{
obj2d->setY(y);
}

double
Object2D_getY(const Object2D * obj2d)
{
return(obj2d->getY());
}

void
Object2D_setTheta(Object2D * obj2d,
                  double theta)
{
obj2d->setTheta(theta);
}

double
Object2D_getTheta(const Object2D * obj2d)
{
return(obj2d->getTheta());
}

/*-------- Motion ---------------------------------------------------------*/

void
Object2D_translate(Object2D * obj2d,
                   double dx,
                   double dy)
{
obj2d->translate(dx,dy);
}

void
Object2D_rotate(Object2D * obj2d,
                double dTheta)
{
obj2d->rotate(dTheta);
}

/*-------- Interaction ----------------------------------------------------*/

void Object2D_onKeyPress(Object2D * obj2d, const char * key)
{
 obj2d->onKeyPress(key);
}
//--
void Object2D_onMouseDrag(Object2D * obj2d, double dx, double dy)
{
 obj2d->onMouseDrag(dx,dy);
}

/*-------- Attachment -----------------------------------------------------*/

void Object2D_attachTo(Object2D * obj2d, const Object2D * anObj2d)
{
 obj2d->attachTo((*(Object2D*)anObj2d));
}

int Object2D_isAttachedTo(const Object2D * obj2d, const Object2D * anObj2d)
{
 return(obj2d->isAttachedTo(*anObj2d) ? 1 : 0);
}

void Object2D_detachFrom(Object2D * obj2d, const Object2D * anObj2d)
{
 obj2d->detachFrom((*(Object2D*)anObj2d));
}

void Object2D_detachFromAll(Object2D * obj2d)
{
 obj2d->detachFromAll();
}

/*-------- Detection -------------------------------------------------------*/

int /* 0: outside    !=0: inside */
Object2D_isInside(const Object2D * obj2d,
                  double x,
                  double y)
{
return(obj2d->isInside(x,y) ? 1 : 0);
}

int /* 0: no intersection found   !=0: intersection found */
Object2D_intersectRay(const Object2D * obj2d,
                      double xRay,
                      double yRay,
                      double thetaRay,
                      double * xOut,
                      double * yOut)
{
return(obj2d->intersectRay(xRay,yRay,thetaRay,*xOut,*yOut) ? 1 : 0);
}

Object2D * /* NULL: no intersection found, !=NULL intersection found */
Object2D_throwRay(const Object2D * obj2d,
                  double * xOut, double * yOut,
                  Object2D *tabObject2D[], unsigned int nbObject2D)
{
return(obj2d->throwRay(*xOut,*yOut,tabObject2D,nbObject2D));
}

Object2D *
Object2D_viewFirstObject2D(const Object2D * obj2d,
                           double vision,
                           double range,
                           double turn)
{
 return obj2d->viewFirstObject2D(vision,range,turn);
}

int
Object2D_viewObject2D(const Object2D * obj2d,
                      Object2D*** tabObject2D,
                      double vision,
                      double range,
                      double turn)
{
 return obj2d->viewObject2D(tabObject2D,vision,range,turn);
}

/*-------- Transformation --------------------------------------------------*/

void
Object2D_globalToLocalPosition(const Object2D * obj2d,
                               double * xInOut,
                               double * yInOut)
{
obj2d->globalToLocalPosition(*xInOut,*yInOut);
}

void
Object2D_localToGlobalPosition(const Object2D * obj2d,
                               double * xInOut,
                               double * yInOut)
{
obj2d->localToGlobalPosition(*xInOut,*yInOut);
}

double
Object2D_globalToLocalOrientation(const Object2D * obj2d,
                                  double orientation)
{
return(obj2d->globalToLocalOrientation(orientation));
}

double
Object2D_localToGlobalOrientation(const Object2D * obj2d,
                                  double orientation)
{
return(obj2d->localToGlobalOrientation(orientation));
}

/*-------- Representation --------------------------------------------------*/

void
Object2D_setColor(Object2D * obj2d,
                  const char * colorName)
{
obj2d->setColor(colorName);
}

const char *
Object2D_getColor(const Object2D * obj2d)
{
return(obj2d->getColor());
}

void
Object2D_setLayer(Object2D * obj2d,
                  int layer)
{
obj2d->setLayer(layer);
}
                  
int
Object2D_getLayer(const Object2D * obj2d)
{
return(obj2d->getLayer());
}

void
Object2D_getBoundingBox(Object2D* obj2d,
                        double * xmin,double * ymin,
                        double * xmax,double * ymax)
{
 obj2d->getBoundingBox(*xmin,*ymin,*xmax,*ymax);
}


void
Object2D_noShape(Object2D * obj2d)
{
obj2d->noShape();
}

void
Object2D_point(Object2D * obj2d)
{
obj2d->point();
}

void
Object2D_text(Object2D* obj2d,
              const char * text,
              double * textHeight, double * textWidth)
{
obj2d->text(text,textHeight,textWidth);
}

void
Object2D_line(Object2D* obj2d,
              double length)
{
obj2d->line(length);
}

void
Object2D_square(Object2D * obj2d,
                double side,
                int filled)
{
obj2d->square(side,filled);
}

void
Object2D_rectangle(Object2D * obj2d,
                   double length,
                   double width,
                   int filled)
{
obj2d->rectangle(length,width,filled);
}

void
Object2D_polyline(Object2D * obj2d,
                  unsigned int nbPoints,
                  const double * xPoints,
                  const double * yPoints)
{
obj2d->polyline(nbPoints,xPoints,yPoints);
}

void
Object2D_polygon(Object2D * obj2d,
                 unsigned int nbPoints,
                 const double * xPoints,
                 const double * yPoints,
                 int filled)
{
obj2d->polygon(nbPoints,xPoints,yPoints,filled);
}

void
Object2D_circle(Object2D * obj2d,
                double radius,
                int filled)
{
obj2d->circle(radius,filled);
}

int /* 0: failure    !=0: success */
Object2D_image(Object2D * obj2d,
               const char * fileName,
               double pixelScale)
{
return(obj2d->image(fileName,pixelScale));
}

int /* 0: failure    !=0: success */
Object2D_getImagePixelAt(Object2D * obj2d,
                         double x,
                         double y,
                         int * redOut,
                         int * greenOut,
                         int * blueOut)
{
return(obj2d->getImagePixelAt(x,y,*redOut,*greenOut,*blueOut));
}

int /* >=0: pixel number    <0: failure */
Object2D_getImagePixelNumberAt(Object2D * obj2d,
                               double x,
                               double y)
{
return(obj2d->getImagePixelNumberAt(x,y));
}

int /* 0: failure    !=0: success */
Object2D_setImagePixelNumberAt(Object2D * obj2d,
		               int pixel,
                               double x,
                               double y)
{
return(obj2d->setImagePixelNumberAt(pixel,x,y));
}

int /* number of colors */
Object2D_getImageNbColors(Object2D * obj2d)
{
return(obj2d->getImageNbColors());
}

int /* 0: failure    !=0: success */
Object2D_getImageRGB(Object2D * obj2d,
		     int pixel,
                     int * redOut,
                     int * greenOut,
                     int * blueOut)
{
return(obj2d->getImageRGB(pixel,*redOut,*greenOut,*blueOut));
}

/*--------------------------------------------------------------------------*/
