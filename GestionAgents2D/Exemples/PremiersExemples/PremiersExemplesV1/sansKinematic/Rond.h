#ifndef _ROND_H_
#define _ROND_H_

#include <iostream>

#include "MAS.h"

#include "Agent2D.h"
#include "AppliData.h"

using namespace std;

class Rond : public Agent2D
{
  DEFCLASS(Rond)

  friend ostream& operator<<(ostream& os, const Rond& aR);

 public :

   // Allocateurs/Desallocateurs

            Rond(double radius, AppliData* data);
            Rond(const Rond& aR);
            Rond& operator=(const Rond& aR);
   virtual ~Rond(void);

            double getRadius(void);
   virtual  void onKeyPress(const char*);

            void mettreDedans(void);
            void avancer(double dt);
   virtual  void live(double dt);

   // Comparaisons

   friend  bool operator==(const Rond& aR1, const Rond& aR2);
   friend  bool operator!=(const Rond& aR1, const Rond& aR2);

   // Inspecteurs/modificateurs

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

   // isEqualTo: a appeler dans une classe derivee (dans operator==)
           bool isEqualTo(const Rond& aR) const;

 protected :

             // ###

 private :

             double     _radius;
             AppliData* _data;

 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const Rond& aR);
   void _destroy(void);

};

#endif // _ROND_H_
