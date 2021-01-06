#ifndef   _OBJECT2D_H_
#define   _OBJECT2D_H_

#include <vector>
#include <set>
#include <string>
#include <iostream>

#include "guiTrans.h"

#include "UtilObject2D.h"

using namespace std;

class Object2D
{
 friend ostream& operator<<(ostream& os, const Object2D& object2D);

 public :

/*-------- Constructor/Destructor -----------------------------------------*/

         Object2D(void);
         Object2D(const Object2D& object2D);
virtual ~Object2D(void);

         Object2D& operator=(const Object2D& object2D);

 // Test d'egalite uniquement sur la couleur et le type de forme:
 // noShape, point, text, 
 friend   bool operator==(const Object2D& obj1, const Object2D& obj2);
 friend   bool operator!=(const Object2D& obj1, const Object2D& obj2);

/*-------- Location -------------------------------------------------------*/

 virtual void   setLocation(double x, double y, double theta);
 virtual void   getLocation(double& xOut, double& yOut, double& thetaOut) const;

 virtual void   setX(double x);
 virtual double getX(void) const;
 virtual void   setY(double y);
 virtual double getY(void) const;
 virtual void   setTheta(double theta);
 virtual double getTheta(void) const;

/*-------- Motion ---------------------------------------------------------*/

  virtual void   translate(double dx, double dy);
  virtual void   rotate(double dTheta);

/*-------- Interaction ----------------------------------------------------*/

virtual void onSelection(void);
virtual void onKeyPress(const char * key);
virtual void onMouseDrag(double dx, double dy);

/*-------- Attachment -----------------------------------------------------*/

        void  attachTo(Object2D& object2D);
        bool  isAttachedTo(const Object2D& object2D) const;
        void  detachFrom(Object2D& object2D);
        void  detachFromAll(void);

/*-------- Detection -------------------------------------------------------*/

      bool   isInside(double x, double y) const;
      bool   intersectRay(double xRay, double yRay, double thetaRay,
                          double& xOut, double& yOut) const;
      Object2D * throwRay(double& xOut, double& yOut,
                          Object2D *tabObject2D[],
                          unsigned int nbObject2D) const;

      Object2D * viewFirstObject2D(double vision,
                                   double range,
                                   double turn=0.0) const;
      int        viewObject2D(Object2D*** tabObject2D,         // Version C
                              double vision,
                              double range,
                              double turn=0.0) const;
      int        viewObject2D(vector<Object2D*>& vectObject2D, // Version C++
                              double vision,
                              double range,
                              double turn=0.0) const;

/*-------- Transformation --------------------------------------------------*/

      void   globalToLocalPosition(double& xInOut, double& yInOut) const;
      void   localToGlobalPosition(double& xInOut, double& yInOut) const;

      double globalToLocalOrientation(double orientation) const;
      double localToGlobalOrientation(double orientation) const;

/*-------- Representation --------------------------------------------------*/

      void   setColor(const char * colorName);
      const  char * getColor(void) const;// Retourne NULL si invisible(noShape)

      void   setLayer(int layer);
      int    getLayer(void) const;

      void   getBoundingBox(double & xmin,double & ymin,
                            double & xmax,double & ymax);
      void   noShape(void);
      void   point(void);
      void   text(const char * text,
                  double * textHeight=NULL, double * textWidth=NULL);
      void   line(double length);
      void   square(double side, int filled);
      void   rectangle(double length, double width, int filled);
      void   polyline(unsigned int nbPoints, const double * xPoints,
                                             const double * yPoints);
      void   polygon(unsigned int nbPoints,  const double * xPoints,
                                             const double * yPoints,
                                             int filled);
      void   circle(double radius, int filled);

      int    image(const char * fileName,        // 0: failure, !=0: success
                   double pixelScale);
      int    getImagePixelAt(double x, double y, // 0: failure, !=0: success
                             int& redOut,
                             int& greenOut,
                             int& blueOut);
      int    getImagePixelNumberAt(double x,     //  >=0: pixel number 
                                   double y);    //  <0: failure 
      int    setImagePixelNumberAt(int pixel,    // 0: failure, !=0: success
                                   double x,
                                   double y);
      int    getImageNbColors(void);             // number of colors
      int    getImageRGB(int pixel,              // 0: failure, !=0: success
                         int& redOut,
                         int& greenOut,
                         int& blueOut);

/*-------- Data types ------------------------------------------------------*/

 private :

  static set<Object2D*> allObject2D;

 private :

  double _x, _y, _theta;
  int    _layer;
  string _color;

  GuiShape2D * _shape;
  bool         _isImage;
  string       _fileName;

  const char* _type; // "point", "text", "line", "square", "rectangle",
                     // "polyline", "polygon", "circle", "image"

/*-------- Private method --------------------------------------------------*/

  void         _changeShape(GuiShape2D * sh);

  void         _copy(const Object2D& object2D);
  void         _destroy(void);

 protected:

  virtual void display(ostream& os) const;
          bool isEqualTo(const Object2D& object2D) const;

 private:

/*-------- Private attributs/methods ... attachedTo ------------------------*/

  void _removeAllAttachments(void);

  set<Object2D*> _attachedObjects;
  set<Object2D*> _isAttachedTo;

  double         _old_x, _old_y, _old_theta;

  void _beforeMove(void); // Sauvegarde position courante:
                          //  (_old_x,_old_y,_old_theta)
  void _afterMove(void);  // Calcul Dx, Dy et Dtheta + propagation mouvement

  void _computeConcernObjects(Object2D * object2D);

};

/*-------- Graphical application template ----------------------------------*/

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

#endif // _OBJECT2D_H_
