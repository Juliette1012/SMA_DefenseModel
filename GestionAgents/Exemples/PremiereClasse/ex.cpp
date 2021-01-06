#include <iostream>
#include <unistd.h>

#include "MAS.h"

#include "A.h"    // Description de la class A

using namespace std;

int main(void)
{
 Scheduler sched;
 sched.setRandomMode(true);       // Passage en ordonnancement aleatoire
 sched.setRealTimeMode(true);     // Passage en mode "temps reel"

 // Creation de 5 Agents A : "A.1", "A.2", "A.3", "A.4", "A.5"
 for(size_t i=0; i<5 ;i++) { Agent* a = new A;
                             cout << "Creation de " << a->getName() << endl;
 }

 sleep(1);

 while (1)         // Execution d'un cycle de simulation :
 {                 // Appel, 1 et 1 seule fois dans le cycle, de la
  sched.cycle();   // methode void live(double dt) de chacun des Agents
  cout << "----------------------------------------------------------" << endl;
 }

 return 0;   // A la fin, lorsque l'ordonnanceur est detruit, tous les agents
}            // connus par l'ordonnanceur sont automatiquement detruits.
