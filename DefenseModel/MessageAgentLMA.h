#ifndef _MessageAgentLMA_H_
#define _MessageAgentLMA_H_
#include <iostream>

#include "MAS.h"

using namespace std;

class MessageAgentLMA : public Message
{
  DEFCLASS(MessageAgentLMA)

  friend ostream& operator<<(ostream& os, const MessageAgentLMA& aM);

 public :

   // Allocateurs/Desallocateurs

            MessageAgentLMA(int i);
            MessageAgentLMA(const MessageAgentLMA& aM);
            MessageAgentLMA& operator=(const MessageAgentLMA& aM);
   virtual ~MessageAgentLMA(void);

   // Comparaisons

   friend  bool operator==(const MessageAgentLMA& aM1, const MessageAgentLMA& aM2);
   friend  bool operator!=(const MessageAgentLMA& aM1, const MessageAgentLMA& aM2);

   // Inspecteurs/modificateurs

           void setInt(int i);
           int  getInt(void) const;

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

   // isEqualTo: a appeler dans une classe derivee (dans operator==)
           bool isEqualTo(const MessageAgentLMA& aM) const;

 protected :

      // Pas d'attribut protege

 private :

      // Attribut prive

      int _i;

 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const MessageAgentLMA& aM);
   void _destroy(void);

};

#endif // _MESSAGEINT_H_
