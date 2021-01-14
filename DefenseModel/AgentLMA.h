#ifndef _AgentLMA_H_
#define _AgentLMA_H_

#include <iostream>

#include "MAS.h"

#include "Agent2D.h"
#include "Environnement.h"
#include "AgentCMA.h"

class AgentCMA;

using namespace std;

class AgentLMA : public Agent2D
{
  DEFCLASS(AgentLMA)

  friend ostream& operator<<(ostream& os, const AgentLMA& anI);

 public :

   // Allocateurs/Desallocateurs

            AgentLMA(void);
            AgentLMA(int x, int y, Environnement* env);
            AgentLMA(const AgentLMA& anI);
            AgentLMA& operator=(const AgentLMA& anI);
   virtual ~AgentLMA(void);

   virtual  void onKeyPress(const char * key);

   virtual  void live(double dt);
   Environnement* getEnv(void);

   void setPosition(int x, int y);

   // Comparaisons

   friend  bool operator==(const AgentLMA& anI1, const AgentLMA& anI2);
   friend  bool operator!=(const AgentLMA& anI1, const AgentLMA& anI2);

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

 protected :
            double _squareSize;
            int _x;
            int _y;
            Environnement* _env;

            vector<int> _riskStatusAgentsIA;
            vector<string> _nameAgentsIA;

            int _riskStatusGlobalLMA = 0;

 private :

 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const AgentLMA& anI);
   void _destroy(void);

};

#endif // _AgentLMA_H_