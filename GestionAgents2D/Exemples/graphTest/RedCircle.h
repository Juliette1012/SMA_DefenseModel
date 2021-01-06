#ifndef _REDCIRCLE_H_
#define _REDCIRCLE_H_

#include <iostream>

#include "MAS.h"
#include "Agent2D.h"

using namespace std;

class RedCircle : public Agent2D
{
  DEFCLASS(RedCircle)

  friend ostream& operator<<(ostream& os, const RedCircle& aC);

 public :

   // Allocateurs/Desallocateurs

            RedCircle(double rayon,double x,double y);
            RedCircle(const RedCircle& aC);
            RedCircle& operator=(const RedCircle& aC);
   virtual ~RedCircle(void);

   virtual  void live(double dt);

   // Comparaisons

   friend  bool operator==(const RedCircle& aC1, const RedCircle& aC2);
   friend  bool operator!=(const RedCircle& aC1, const RedCircle& aC2);

   // Inspecteurs/modificateurs

   virtual void onKeyPress(const char * key);

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

   // isEqualTo: a appeler dans une classe derivee (dans operator==)
           bool isEqualTo(const RedCircle& aC) const;

 protected :

             // ###

 private :

             double _rayon;

 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const RedCircle& aC);
   void _destroy(void);

};

#endif // _REDCIRCLE_H_
