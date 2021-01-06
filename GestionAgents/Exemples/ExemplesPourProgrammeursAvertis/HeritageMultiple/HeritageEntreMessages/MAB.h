#ifndef _MAB_H_
#define _MAB_H_

#include <iostream>

#include "MAS.h"
#include "MA.h"
#include "MB.h"

using namespace std;

class MAB : public MA,
            public MB
{
  DEFCLASS(MAB)

  friend ostream& operator<<(ostream& os, const MAB& aM);

 public :

   // Allocateurs/Desallocateurs

            MAB( /* ### */ );
            MAB(const MAB& aM);
            MAB& operator=(const MAB& aM);
   virtual ~MAB(void);

           string getClass(void) const;       // Redefinition
           bool   isA(string aClass) const;   // des methodes
           Agent* getEmitter(void) const;     // de Message

   // Comparaisons

   friend  bool operator==(const MAB& aM1, const MAB& aM2);
   friend  bool operator!=(const MAB& aM1, const MAB& aM2);

   // Inspecteurs/modificateurs

           operator Message* ()
           { 
            return reinterpret_cast<Message*>(this);
           }

 protected :

   // Methodes a appeler par une classe derivee

           void newMessage(void); // Pour lever l'ambiguite (heritage multiple)
           void newMessage(Message * This); // Idem...

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

   // isEqualTo: a appeler dans une classe derivee (dans operator==)
           bool isEqualTo(const MAB& aM) const;

 protected :

      // Attribut protege

 private :

      // Attribut prive

          Message* _This;    // Important pour la redefinition des methodes
                             // afin de lever les ambiguites.
 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const MAB& aM);
   void _destroy(void);

};

#endif // _MAB_H_
