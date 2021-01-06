#ifndef _MB_H_
#define _MB_H_

#include <iostream>

#include "MAS.h"

using namespace std;

class MB : public Message
{
  DEFCLASS(MB)

  friend ostream& operator<<(ostream& os, const MB& aM);

 public :

   // Allocateurs/Desallocateurs

            MB( /* ### */ );
            MB(const MB& aM);
            MB& operator=(const MB& aM);
   virtual ~MB(void);

   // Comparaisons

   friend  bool operator==(const MB& aM1, const MB& aM2);
   friend  bool operator!=(const MB& aM1, const MB& aM2);

   // Inspecteurs/modificateurs

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

   // isEqualTo: a appeler dans une classe derivee (dans operator==)
           bool isEqualTo(const MB& aM) const;

 protected :

             // ###

 private :

             // ###

 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const MB& aM);
   void _destroy(void);

};

#endif // _MB_H_
