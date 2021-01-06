#ifndef _AGENT2D_H_
#define _AGENT2D_H_

#include <iostream>
#include <vector>

#include "MAS.h"
#include "Object2D.h"

using namespace std;

class Agent2D : public Agent,
                public Object2D
{
  DEFCLASS(Agent2D)

  friend ostream& operator<<(ostream& os, const Agent2D& anA);

 public :

   // Allocateurs/Desallocateurs

            Agent2D(void);
            Agent2D(const Agent2D& anA);
            Agent2D& operator=(const Agent2D& anA);
   virtual ~Agent2D(void);

   virtual  void live(double dt);

   virtual  void onSelection(void);                 // Par defaut :
   virtual  void onKeyPress(const char * key);      // si p : affiche le nom
   virtual  void onMouseDrag(double dx, double dy); // deplacement a la souris

   // Comparaisons

   friend  bool operator==(const Agent2D& anA1, const Agent2D& anA2);
   friend  bool operator!=(const Agent2D& anA1, const Agent2D& anA2);

   // Inspecteurs/modificateurs

      // En plus, ... Voir Agent.h et Object2D.h ...!

      // Gestion de la cinematique :
      // ---------------------------

      void   Kinematic(double dt);  // Modification de la position/orientation

      // Velocity: xVelocity, yVelocity, thetaVelocity
      // ---------------------------------------------

      double getLinearVelocityX(void) const;
      double getLinearVelocityY(void) const;
      double getAngularVelocity(void) const;
      void   getVelocity(double& xVelocity,double& yVelocity,
                         double& thetaVelocity) const;

      void   setLinearVelocityX(double xVelocity);
      void   setLinearVelocityY(double yVelocity);
      void   setAngularVelocity(double thetaVelocity);
      void   setVelocity(double xVelocity,double yVelocity,
                         double thetaVelocity);

      // Acceleration xAcceleration, yAcceleration, thetaAcceleration
      // ------------------------------------------------------------

      double getLinearAccelerationX(void) const;
      double getLinearAccelerationY(void) const;
      double getAngularAcceleration(void) const;
      void   getAcceleration(double& xAcceleration,double& yAcceleration,
                             double& thetaAcceleration) const;

      void   setLinearAccelerationX(double xAcceleration);
      void   setLinearAccelerationY(double yAcceleration);
      void   setAngularAcceleration(double thetaAcceleration);
      void   setAcceleration(double xAcceleration,double yAcceleration,
                             double thetaAcceleration);

   // Perception/Detection

   bool   isInside(double x, double y) const;
   bool   intersectRay(double xRay, double yRay, double thetaRay,
                       double& xOut, double& yOut) const;
   Agent2D * throwRay(double& xOut, double& yOut,
                      const vector<Agent2D*>& vectAgent2D) const;

   Agent2D * viewFirst(string aClass,
                       double vision,
                       double range,
                       double turn=0.0) const;

   int       view(string aClass, vector<Agent2D*>& vectAgent2D,
                  double vision,
                  double range,
                  double turn=0.0) const;

   Agent2D * viewFirstAgent2D(double vision,
                              double range,
                              double turn=0.0) const;

   int       viewAgent2D(vector<Agent2D*>& vectAgent2D,
                         double vision,
                         double range,
                         double turn=0.0) const;

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

   // isEqualTo: a appeler dans une classe derivee (dans operator==)
           bool isEqualTo(const Agent2D& anA) const;

 protected :

 private :

     double _linearVelocityX,    _linearVelocityY,    _angularVelocity;
     double _linearAccelerationX,_linearAccelerationY,_angularAcceleration;

 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const Agent2D& anA);
   void _destroy(void);

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

extern void graphic_selectCallback(Agent2D * agt2d,
                                   void * userData);

extern void graphic_keyPressCallback(Agent2D * agt2d,
                                     const char * key,
                                     void * userData);

extern void graphic_mouseDragCallback(Agent2D * agt2d,
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
   graphic_selectCallback(Agent2D * agt2d,
                          void * userData)
   {
   ...
   }

   void
   graphic_keyPressCallback(Agent2D * agt2d,
                            const char * key,
                            void * userData)
   {
   ...
   }

   void
   graphic_mouseDragCallback(Agent2D * agt2d,
                             double dx,
                             double dy,
                             void * userData)
   {
   ...
   }
*/

#endif // _AGENT2D_H_
