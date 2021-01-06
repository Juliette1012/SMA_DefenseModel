#ifndef _AgentIA_H_
#define _AgentIA_H_

#include <iostream>

#include "MAS.h"

#include "Agent2D.h"
#include "Environnement.h"
#include "Eprouvette.h"

using namespace std;

 class Ag; class Ac; class Eprouvette;

class AgentIA : public Agent2D
{
  DEFCLASS(AgentIA)

  friend ostream& operator<<(ostream& os, const AgentIA& anI);

 public :

   // Allocateurs/Desallocateurs

            AgentIA(void);
            AgentIA(int x, int y, Environnement* env, Eprouvette* eprouvette);
            AgentIA(const AgentIA& anI);
            AgentIA& operator=(const AgentIA& anI);
   virtual ~AgentIA(void);

   virtual  void onKeyPress(const char * key);

   virtual  void live(double dt);

   Environnement* getEnv(void);
   Eprouvette* getEprouvette(void);

   vector<Ag*> getAg(void);
   vector<Ac*> getAcImmatures(void);

   void setPosition(int x, int y);

   void setAg(Ag* ag);
   void setAc(Ac* ac);

   void clearAgAc();

   // Comparaisons

   friend  bool operator==(const AgentIA& anI1, const AgentIA& anI2);
   friend  bool operator!=(const AgentIA& anI1, const AgentIA& anI2);

 protected :

   // Methodes a appeler par une classe derivee

   // display: a appeler dans une classe derivee      // display est une
   virtual void display(ostream& os) const;           // methode appelee
                                                      // dans operator<<

 protected :
            double _squareSize;
            int _x;
            int _y;
            class Environnement* _env;
            class Eprouvette* _eprouvette;
            const char* _name;

            int _nbAcImmatures;
            //int _AcMatures;
            //int _AcMemoires;
            
            vector<Ag*> _Ag; 
            vector<Ac*> _AcImmatures;
 private :




 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const AgentIA& anI);
   void _destroy(void);

};

#endif // _AgentIA_H_
