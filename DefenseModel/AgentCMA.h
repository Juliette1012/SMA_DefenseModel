#ifndef _AgentCMA_H_
#define _AgentCMA_H_

#include <iostream>

#include "MAS.h"

#include "Agent2D.h"

using namespace std;

class AgentCMA : public Agent2D
{
  DEFCLASS(AgentCMA)

  friend ostream& operator<<(ostream& os, const AgentCMA& anI);

 public :

   // Allocateurs/Desallocateurs

            AgentCMA(void);
            AgentCMA(const AgentCMA& anI);
            AgentCMA& operator=(const AgentCMA& anI);
   virtual ~AgentCMA(void);

   virtual  void onKeyPress(const char * key);

   virtual  void live(double dt);
   void event_R(void);
  int getRiskStatus(void);
   // Comparaisons

   friend  bool operator==(const AgentCMA& anI1, const AgentCMA& anI2);
   friend  bool operator!=(const AgentCMA& anI1, const AgentCMA& anI2);

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

 protected :

             double _squareSize;
            vector<int> _riskStatusAgentsLMA;
            vector<string> _nameAgentsLMA;

            int _riskStatusGlobalCMA;


 private :



 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const AgentCMA& anI);
   void _destroy(void);

};

#endif // _AgentCMA_H_
