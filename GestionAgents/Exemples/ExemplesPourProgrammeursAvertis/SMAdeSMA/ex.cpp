#include <iostream>
#include <unistd.h>

#include "MAS.h"

#include "SMA.h"    // Description de la class SMA

using namespace std;

int main(void)
{
 Scheduler sched;
 sched.setRandomMode(false);       // Passage en ordonnancement sequentiel

 // Creation de 2 Agents SMA : "SMA.1", "SMA.2"
 for(size_t i=0; i<2 ;i++) { Agent* a = new SMA(5);
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
