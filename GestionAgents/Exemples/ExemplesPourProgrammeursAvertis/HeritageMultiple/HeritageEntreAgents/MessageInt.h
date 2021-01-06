#ifndef _MESSAGEINT_H_
#define _MESSAGEINT_H_

#include <iostream>

#include "MAS.h"

using namespace std;

class MessageInt : public Message
{
  DEFCLASS(MessageInt)

  friend ostream& operator<<(ostream& os, const MessageInt& aM);

 public :

   // Allocateurs/Desallocateurs

            MessageInt(int i);
            MessageInt(const MessageInt& aM);
            MessageInt& operator=(const MessageInt& aM);
   virtual ~MessageInt(void);

   // Comparaisons

   friend  bool operator==(const MessageInt& aM1, const MessageInt& aM2);
   friend  bool operator!=(const MessageInt& aM1, const MessageInt& aM2);

   // Inspecteurs/modificateurs

           void setInt(int i);
           int  getInt(void) const;

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

   // isEqualTo: a appeler dans une classe derivee (dans operator==)
           bool isEqualTo(const MessageInt& aM) const;

 protected :

      // Pas d'attribut protege

 private :

      // Attribut prive

      int _i;

 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const MessageInt& aM);
   void _destroy(void);

};

#endif // _MESSAGEINT_H_
