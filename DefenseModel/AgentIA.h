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

   int getRiskStatus(void);
   void setRiskStatus(int risk);

   vector<int> getTypeAc(void);
   int getTypeAg(void);
   void setTypeAg(int type);
   void infect(vector<tuple<int, int>> virus);

   int getNbAcImmature(void);
   int getNbAcMature(void);
   int getNbAcMemoire(void);
   int getNbAg(void);
   void setNbAg(int nbAg);
   void setNbAcImmature(int nbAcImmature);
   void setNbAcMature(int nbAcMature);
   void setNbAcMemoire(int nbAcMemoire);

   vector<tuple<double, double>> getAgPos(void);
   void setAgPos(vector<tuple<double, double>> positions);

   vector<tuple<double, double>> getAcImmaturePos(void);
   void setAcImmaturePos(vector<tuple<double, double>> positions);

   vector<tuple<double, double>> getAcMaturePos(void);
   void setAcMaturePos(vector<tuple<double, double>> positions);

   vector<tuple<double, double>> getAcMemoirePos(void);
   void setAcMemoirePos(vector<tuple<double, double>> positions);

   void setPosition(int x, int y);

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

            int _riskStatus;
            int _nbAcImmature;
            int _nbAcMature;
            int _nbAcMemoire;
            int _nbAg;

            vector<int> _typeAc;
            int _typeAg;
            vector<tuple<double, double>> _agPos;

            vector<tuple<double, double>> _acImmaturePos;
            vector<tuple<double, double>> _acMaturePos;
            vector<tuple<double, double>> _acMemoirePos;

 private :

 private :

   // Methodes privees d'allocation/desallocation

   void _copy(const AgentIA& anI);
   void _destroy(void);

};

#endif // _AgentIA_H_
