#ifndef _MessageAgentIA_H_
#define _MessageAgentIA_H_

#include <iostream>

#include "MAS.h"

using namespace std;

class MessageAgentIA : public Message
{
  DEFCLASS(MessageAgentIA)

  friend ostream& operator<<(ostream& os, const MessageAgentIA& aM);

 public :

   // Allocateurs/Desallocateurs

            MessageAgentIA(int i);
            MessageAgentIA(const MessageAgentIA& aM);
            MessageAgentIA& operator=(const MessageAgentIA& aM);
   virtual ~MessageAgentIA(void);

   // Comparaisons

   friend  bool operator==(const MessageAgentIA& aM1, const MessageAgentIA& aM2);
   friend  bool operator!=(const MessageAgentIA& aM1, const MessageAgentIA& aM2);

   // Inspecteurs/modificateurs

           void setInt(int i);
           int  getInt(void) const;

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

   // isEqualTo: a appeler dans une classe derivee (dans operator==)
           bool isEqualTo(const MessageAgentIA& aM) const;

 protected :

      // Pas d'attribut protege

 private :

      // Attribut prive

      int _i;

 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const MessageAgentIA& aM);
   void _destroy(void);

};

#endif // _MESSAGEINT_H_
