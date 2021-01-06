#ifndef _AGT_H_
#define _AGT_H_

#include <iostream>

#include "MAS.h"

using namespace std;

class Agt : public Agent
{
  DEFCLASS(Agt)

  friend ostream& operator<<(ostream& os, const Agt& anA);

 public :

   // Allocateurs/Desallocateurs

            Agt(size_t v);
            Agt(const Agt& anA);
            Agt& operator=(const Agt& anA);
   virtual ~Agt(void);

   virtual  void live(double dt);

   // Comparaisons

   friend  bool operator==(const Agt& anA1, const Agt& anA2);
   friend  bool operator!=(const Agt& anA1, const Agt& anA2);

   // Inspecteurs/modificateurs

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

   // isEqualTo: a appeler dans une classe derivee (dans operator==)
           bool isEqualTo(const Agt& anA) const;

 protected :

 private :

          size_t _v;

 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const Agt& anA);
   void _destroy(void);

};

#endif // _AGT_H_
