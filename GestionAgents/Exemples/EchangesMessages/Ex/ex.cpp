#include <iostream>
#include <unistd.h>

#include "MAS.h"

#include "E.h"    // Description de la class E
#include "F.h"    // Description de la class F

using namespace std;

const int nbAgents = 5;

int main(void)
{
 Scheduler sched;
 sched.setRandomMode(true);

 for(int i=0; i<nbAgents ;i++)
 { 
  new E(i+1);
 }

 int t = 1;
 while(t<=10)
 {
 sleep(1);
 cout << "**********************************************************" << endl;
 sched.cycle();
 cout << "**********************************************************" << endl;

 if (t == 1) new F(0,10);

 t++;
 }

 cout << endl;

 //////////////////////////////////////////////////////////////////////////

 vector<Agent*> v;

 string aClass = "E";

 getAllAgents(aClass,v);

 cout << "Dans cette simulation, il y avait " << v.size() << " agents"
      << " de la classe " << aClass << endl;

 for(size_t indV=0;indV<v.size();indV++)
 {
  cout << (indV+1) << ") " << v[indV]->getName() << endl;
 }

 cout << endl;

 //////////////////////////////////////////////////////////////////////////

 string aName = "E.1";

 cout << aName << " existe-t-il?" << endl;

 Agent *ag = getAgent(aName);

 if (exist(ag)) {
                  cout << "ok, "+aName+" existe" << endl;
 }
 else {
        cout << "ko, "+aName+" n'existe pas" << endl;
        cout << "stop..." << endl;
        return 1;
 }

 cout << endl;

 //////////////////////////////////////////////////////////////////////////

 aClass = "F";

 cout << aName << " est-il de la classe " << aClass << "?" << endl;

 if (ag->isA(aClass)) {
                        cout << ag->getName() << " est un " << aClass << endl;
 }
 else {
        cout << ag->getName() << " n'est pas un " << aClass << endl;
 }

 if (getAgent(aName)->isA(aClass)) {
                                     cout << getAgent(aName)->getName()
                                          << " est un " << aClass << endl;
 }
 else {
        cout << getAgent(aName)->getName()
             << " n'est pas un " << aClass << endl;
 }


 return 0;
}
