#ifndef _MessageVaccin_H_
#define _MessageVaccin_H_

#include <iostream>

#include "MAS.h"

using namespace std;

class MessageVaccin : public Message
{
  DEFCLASS(MessageVaccin)

  friend ostream& operator<<(ostream& os, const MessageVaccin& aM);

 public :

   // Allocateurs/Desallocateurs

            MessageVaccin();
            MessageVaccin(const MessageVaccin& aM);
            MessageVaccin& operator=(const MessageVaccin& aM);
   virtual ~MessageVaccin(void);

   // Comparaisons

   friend  bool operator==(const MessageVaccin& aM1, const MessageVaccin& aM2);
   friend  bool operator!=(const MessageVaccin& aM1, const MessageVaccin& aM2);

   // Inspecteurs/modificateurs

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

   // isEqualTo: a appeler dans une classe derivee (dans operator==)
           bool isEqualTo(const MessageVaccin& aM) const;

 protected :

             // ###

 private :

 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const MessageVaccin& aM);
   void _destroy(void);

};

#endif // _MessageVaccin_H_
