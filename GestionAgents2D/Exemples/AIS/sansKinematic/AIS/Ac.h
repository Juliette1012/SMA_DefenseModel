#ifndef _AC_H_
#define _AC_H_

#include <iostream>

#include "MAS.h"

#include "ImAgent.h"

using namespace std;

class Ac : public ImAgent
{
  DEFCLASS(Ac)

  friend ostream& operator<<(ostream& os, const Ac& anA);

 public :

   // Allocateurs/Desallocateurs

            Ac( /* ### */ );
            Ac(const Ac& anA);
            Ac& operator=(const Ac& anA);
   virtual ~Ac(void);

   virtual  void onKeyPress(const char * key);

            void event_H(void);
            void event_S(void);

   virtual  void live(double dt);

            void start(void);
            void stop(void);

   // Comparaisons

   friend  bool operator==(const Ac& anA1, const Ac& anA2);
   friend  bool operator!=(const Ac& anA1, const Ac& anA2);

   // Inspecteurs/modificateurs

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

   // isEqualTo: a appeler dans une classe derivee (dans operator==)
           bool isEqualTo(const Ac& anA) const;

 protected :

             double _vision;

 private :

             Object2D *_cercle;

             bool _start;
 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const Ac& anA);
   void _destroy(void);

};

#endif // _AC_H_
