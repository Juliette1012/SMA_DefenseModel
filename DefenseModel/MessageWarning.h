#ifndef _MessageAgentCMA_H_
#define _MessageAgentCMA_H_

#include <iostream>

#include "MAS.h"

using namespace std;

class MessageAgentCMA : public Message
{
  DEFCLASS(MessageAgentCMA)

  friend ostream& operator<<(ostream& os, const MessageAgentCMA& aM);

 public :

   // Allocateurs/Desallocateurs

            MessageAgentCMA();
            MessageAgentCMA(const MessageAgentCMA& aM);
            MessageAgentCMA& operator=(const MessageAgentCMA& aM);
   virtual ~MessageAgentCMA(void);

   // Comparaisons

   friend  bool operator==(const MessageAgentCMA& aM1, const MessageAgentCMA& aM2);
   friend  bool operator!=(const MessageAgentCMA& aM1, const MessageAgentCMA& aM2);

   // Inspecteurs/modificateurs

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

   // isEqualTo: a appeler dans une classe derivee (dans operator==)
           bool isEqualTo(const MessageAgentCMA& aM) const;

 protected :

             // ###

 private :

 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const MessageAgentCMA& aM);
   void _destroy(void);

};

#endif // _MessageAgentCMA_H_
