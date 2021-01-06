/*----------------------------------------------------------------------------
  CObject2D.h
----------------------------------------------------------------------------*/

#ifndef _COBJECT2D_H_
#define _COBJECT2D_H_

#include "Object2D.h"

#include "UtilObject2D.h"

#ifdef __cplusplus
extern "C" {
#endif

/*-------- Construction/Affectation/Destruction ---------------------------*/

Object2D *
Object2D_new(void);

Object2D *
Object2D_newCopy(const Object2D * anObj2d);

void
Object2D_copy(Object2D * obj2d, const Object2D * anObj2d);

void
Object2D_delete(Object2D * obj2d);

/*-------- Location -------------------------------------------------------*/

void
Object2D_setLocation(Object2D * obj2d,
		     double x,
                     double y,
                     double theta);

void
Object2D_getLocation(const Object2D * obj2d,
		     double * xOut,
                     double * yOut,
                     double * thetaOut);

void
Object2D_setX(Object2D * obj2d,
              double x);

double
Object2D_getX(const Object2D * obj2d);

void
Object2D_setY(Object2D * obj2d,
              double y);

double
Object2D_getY(const Object2D * obj2d);

void
Object2D_setTheta(Object2D * obj2d,
                  double theta);

double
Object2D_getTheta(const Object2D * obj2d);

/*-------- Motion ---------------------------------------------------------*/

void
Object2D_translate(Object2D * obj2d,
                   double dx,
                   double dy);

void
Object2D_rotate(Object2D * obj2d,
                double dTheta);

/*-------- Interaction ----------------------------------------------------*/

void
Object2D_onKeyPress(Object2D * obj2d, const char * key);

void
Object2D_onMouseDrag(Object2D * obj2d, double dx, double dy);

/*-------- Attachment -----------------------------------------------------*/

void
Object2D_attachTo(Object2D * obj2d, const Object2D * anObj2d);

int /* 0: no    1: yes */
Object2D_isAttachedTo(const Object2D * obj2d, const Object2D * anObj2d);

void
Object2D_detachFrom(Object2D * obj2d, const Object2D * anObj2d);

void
Object2D_detachFromAll(Object2D * obj2d);

/*-------- Detection -------------------------------------------------------*/

int /* 0: outside    !=0: inside */
Object2D_isInside(const Object2D * obj2d,
                  double x,
                  double y);

/* Object2D_intersectRay : Lance un rayon (a partir de xRay, yRay et
   dans la direction thetaRay), et indique s'il y a intersection avec
   l'objet obj2d.
   On obtient egalement le point intersection.
*/
int /* 0: no intersection found   !=0: intersection found */
Object2D_intersectRay(const Object2D * obj2d,
                      double xRay,
                      double yRay,
                      double thetaRay,
                      double * xOut,
                      double * yOut);

/* Object2D_throwRay : Lance un rayon devant l'objet obj2d
   (via les coordonnees et l'axe de l'objet2D obj2d)
   et retourne l'objet le plus proche (contenu dans tabObject2D)
   On obtient egalement le point intersection.
*/
Object2D * /* NULL: no intersection found, !=NULL intersection found */
Object2D_throwRay(const Object2D * obj2d,
                  double * xOut, double * yOut,
                  Object2D *tabObject2D[], unsigned int nbObject2D);

Object2D *
Object2D_viewFirstObject2D(const Object2D * obj2d,
                           double vision,
                           double range,
                           double turn);

int
Object2D_viewObject2D(const Object2D * obj2d,
                      Object2D*** tabObject2D,
                      double vision,
                      double range,
                      double turn);

/*-------- Transformation --------------------------------------------------*/

void
Object2D_globalToLocalPosition(const Object2D * obj2d,
                               double * xInOut,
                               double * yInOut);

void
Object2D_localToGlobalPosition(const Object2D * obj2d,
                               double * xInOut,
                               double * yInOut);

double
Object2D_globalToLocalOrientation(const Object2D * obj2d,
                                  double orientation);

double
Object2D_localToGlobalOrientation(const Object2D * obj2d,
                                  double orientation);

/*-------- Representation --------------------------------------------------*/

void
Object2D_setColor(Object2D * obj2d,
                  const char * colorName);

const char *
Object2D_getColor(const Object2D * obj2d);

void
Object2D_setLayer(Object2D * obj2d,
                  int layer);

int
Object2D_getLayer(const Object2D * obj2d);

void
Object2D_getBoundingBox(Object2D* obj2d,
                        double * xmin,double * ymin,
                        double * xmax,double * ymax);

void
Object2D_noShape(Object2D * obj2d);

void
Object2D_point(Object2D * obj2d);

void
Object2D_text(Object2D* obj2d,
              const char * text,
              double * textHeight = NULL,
              double * textWidth  = NULL);

void
Object2D_line(Object2D * obj2d,
              double length);

void
Object2D_square(Object2D * obj2d,
                double side,
                int filled);

void
Object2D_rectangle(Object2D * obj2d,
                   double length,
                   double width,
                   int filled);
void
Object2D_polyline(Object2D * obj2d,
                  unsigned int nbPoints,
                  const double * xPoints,
                  const double * yPoints);

void
Object2D_polygon(Object2D * obj2d,
                 unsigned int nbPoints,
                 const double * xPoints,
                 const double * yPoints,
                 int filled);

void
Object2D_circle(Object2D * obj2d,
                double radius,
                int filled);

int /* 0: failure    !=0: success */
Object2D_image(Object2D * obj2d,
               const char * fileName,
               double pixelScale);

int /* 0: failure    !=0: success */
Object2D_getImagePixelAt(Object2D * obj2d,
                         double x,
                         double y,
                         int * redOut,
                         int * greenOut,
                         int * blueOut);

int /* >=0: pixel number    <0: failure */
Object2D_getImagePixelNumberAt(Object2D * obj2d,
                               double x,
                               double y);

int /* 0: failure    !=0: success */
Object2D_setImagePixelNumberAt(Object2D * obj2d,
                               int pixel,
                               double x,
                               double y);

int /* number of colors */
Object2D_getImageNbColors(Object2D * obj2d);
     
int /* 0: failure    !=0: success */
Object2D_getImageRGB(Object2D * obj2d,
                     int pixel,
                     int * redOut,
                     int * greenOut,
                     int * blueOut);

/*-------- Graphical application template ----------------------------------*/

/*
extern void graphic_init(const char * windowName, const char * fontName);

extern void graphic_setWidth(int width);

extern void graphic_setHeight(int height);

extern void graphic_setBackground(const char * colorName);

extern void graphic_setViewPoint(double x, double y, double scale);

extern void graphic_getViewPoint(double * xOut, double * yOut,
                                 double *scaleOut);

extern void graphic_autoscale(void);

extern void graphic_run(void * userData);

extern void graphic_mainLoop(void * userData);

extern void graphic_selectCallback(Object2D * obj2d,
                                   void * userData);

extern void graphic_keyPressCallback(Object2D * obj2d,
                                     const char * key,
                                     void * userData);

extern void graphic_mouseDragCallback(Object2D * obj2d,
                                      double dx, double dy,
                                      void * userData);
*/

/*-------- Graphical application template --------*/
/*
   int
   main(void)
   {
   graphic_init("My Window","-*-helvetica-*-r-normal--14-*");
   graphic_setWidth(640);
   graphic_setHeight(480);
   ... application specific initializations ...
   graphic_run(myDataPointer);
   return(0);
   }

   void
   graphic_mainLoop(void * userData)
   {
   ...
   }

   void
   graphic_selectCallback(Object2D * obj2d,
                          void * userData)
   {
   ...
   }

   void
   graphic_keyPressCallback(Object2D * obj2d,
                            const char * key,
                            void * userData)
   {
   ...
   }

   void
   graphic_mouseDragCallback(Object2D * obj2d,
                             double dx,
                             double dy,
                             void * userData)
   {
   ...
   }
*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _COBJECT2D_H_ */

/*--------------------------------------------------------------------------*/
