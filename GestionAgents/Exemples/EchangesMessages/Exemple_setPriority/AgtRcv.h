#ifndef _AGTRCV_H_
#define _AGTRCV_H_

#include <iostream>

#include "MAS.h"

#include "Agent.h"

using namespace std;

class AgtRcv : public Agent
{
  DEFCLASS(AgtRcv)

  friend ostream& operator<<(ostream& os, const AgtRcv& anA);

 public :

   // Allocateurs/Desallocateurs

            AgtRcv( /* ### */ );
            AgtRcv(const AgtRcv& anA);
            AgtRcv& operator=(const AgtRcv& anA);
   virtual ~AgtRcv(void);

   virtual  void live(double dt);

   // Comparaisons

   friend  bool operator==(const AgtRcv& anA1, const AgtRcv& anA2);
   friend  bool operator!=(const AgtRcv& anA1, const AgtRcv& anA2);

   // Inspecteurs/modificateurs

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

   // isEqualTo: a appeler dans une classe derivee (dans operator==)
           bool isEqualTo(const AgtRcv& anA) const;

 protected :

             // ###

 private :

             // ###

 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const AgtRcv& anA);
   void _destroy(void);

};

#endif // _AGTRCV_H_
