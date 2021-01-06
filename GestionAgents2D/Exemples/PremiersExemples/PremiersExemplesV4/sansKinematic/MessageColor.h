#ifndef _MESSAGECOLOR_H_
#define _MESSAGECOLOR_H_

#include <iostream>

#include "MAS.h"

using namespace std;

class MessageColor : public Message
{
  DEFCLASS(MessageColor)

  friend ostream& operator<<(ostream& os, const MessageColor& aM);

 public :

   // Allocateurs/Desallocateurs

            MessageColor(const char* color);
            MessageColor(const MessageColor& aM);
            MessageColor& operator=(const MessageColor& aM);
   virtual ~MessageColor(void);

            const char* getColor(void);

   // Comparaisons

   friend  bool operator==(const MessageColor& aM1, const MessageColor& aM2);
   friend  bool operator!=(const MessageColor& aM1, const MessageColor& aM2);

   // Inspecteurs/modificateurs

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

   // isEqualTo: a appeler dans une classe derivee (dans operator==)
           bool isEqualTo(const MessageColor& aM) const;

 protected :

             // ###

 private :

             string _color;

 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const MessageColor& aM);
   void _destroy(void);

};

#endif // _MESSAGECOLOR_H_
