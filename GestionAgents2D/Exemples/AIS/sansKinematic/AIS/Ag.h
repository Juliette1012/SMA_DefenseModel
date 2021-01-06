#ifndef _AG_H_
#define _AG_H_

#include <iostream>

#include "MAS.h"

#include "ImAgent.h"

using namespace std;

class Ag : public ImAgent
{
  DEFCLASS(Ag)

  friend ostream& operator<<(ostream& os, const Ag& anA);

 public :

   // Allocateurs/Desallocateurs

            Ag( /* ### */ );
            Ag(const Ag& anA);
            Ag& operator=(const Ag& anA);
   virtual ~Ag(void);

   virtual  void onKeyPress(const char * key);

            void event_H(void);

   virtual  void live(double dt);

   // Comparaisons

   friend  bool operator==(const Ag& anA1, const Ag& anA2);
   friend  bool operator!=(const Ag& anA1, const Ag& anA2);

   // Inspecteurs/modificateurs

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

   // isEqualTo: a appeler dans une classe derivee (dans operator==)
           bool isEqualTo(const Ag& anA) const;

 protected :

             // ###

 private :

             // ###

 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const Ag& anA);
   void _destroy(void);

};

#endif // _AG_H_
