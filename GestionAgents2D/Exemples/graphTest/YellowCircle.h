#ifndef _YELLOWCIRCLE_H_
#define _YELLOWCIRCLE_H_

#include <iostream>

#include "MAS.h"
#include "Agent2D.h"

using namespace std;

class YellowCircle : public Agent2D
{
  DEFCLASS(YellowCircle)

  friend ostream& operator<<(ostream& os, const YellowCircle& aC);

 public :

   // Allocateurs/Desallocateurs

            YellowCircle(double rayon,double x,double y);
            YellowCircle(const YellowCircle& aC);
            YellowCircle& operator=(const YellowCircle& aC);
   virtual ~YellowCircle(void);

   virtual  void live(double dt);

   // Comparaisons

   friend  bool operator==(const YellowCircle& aC1, const YellowCircle& aC2);
   friend  bool operator!=(const YellowCircle& aC1, const YellowCircle& aC2);

   // Inspecteurs/modificateurs

   virtual void onKeyPress(const char * key);

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

   // isEqualTo: a appeler dans une classe derivee (dans operator==)
           bool isEqualTo(const YellowCircle& aC) const;

 protected :

             // ###

 private :

             double _rayon;

 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const YellowCircle& aC);
   void _destroy(void);

};

#endif // _YELLOWCIRCLE_H_
