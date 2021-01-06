#include "SMA.h"

#include "Agt.h"

//--
SMA::SMA(size_t nbAgents) : Agent()
{
 newAgent();

 _sched=new Scheduler;
 _sched->setRandomMode(true);

 Scheduler *oldSched=Scheduler::getCurrentSched(); //-- sauvegarde ancien

 Scheduler::setCurrentSched(_sched);

 for(size_t i=0;i<nbAgents;i++)
 {
  new Agt(i);
 }

 Scheduler::setCurrentSched(oldSched);            //-- restauration ancien
}

//--
SMA::SMA(const SMA& aS) : Agent(aS)
{
 newAgent();
 _copy(aS);
}

//--
SMA& SMA::operator=(const SMA& aS)
{
 if (this != &aS)
 {
  Agent::operator=(aS);
  _destroy();
  _copy(aS);
 }
 return *this;
}

//--
SMA::~SMA(void)
{
 _destroy();
}

//--
void SMA::live(double dt)
{
 (void)dt; // Pour eviter un warning si pas utilise

 // "Comportement" d'un Agent de la classe SMA

 cout << "Activation de " << getName() << endl;
 cout << ">********************" << endl;
 _sched->cycle();
 cout << "<********************" << endl;
}

//--
bool operator==(const SMA& aS1, const SMA& aS2)
{
 return aS1.isEqualTo(aS2);
}

//--
bool operator!=(const SMA& aS1, const SMA& aS2)
{
 return !(aS1==aS2);
}

//--
ostream& operator<<(ostream& os, const SMA& aS)
{
 aS.display(os);
 return os;
}

//--
void SMA::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 Agent::display(os);

 // ### : Affichage des attributs de la classe SMA
 // Exemple : os << _at;
}

//--
bool SMA::isEqualTo(const SMA& aS) const
{
 (void)aS; // Pour eviter un warning si pas utilise

 // ### : Test des attributs de la classe SMA
 // Exemple : if (_at != aS._at) return false;

 if (!(Agent::isEqualTo(aS))) return false;
 return true;
}

//--
void SMA::_copy(const SMA& aS)
{
 (void)aS; // Pour eviter un warning si pas utilise

 // ### : Affectation des attributs de la classe SMA
 // Exemple : _at = aS._at;

 _sched=new Scheduler;
 *_sched = *(aS._sched);  // Copie de l'ordonnanceur et des agents associes
}

//--
void SMA::_destroy(void)
{
 // ### : Destruction des attributs de la classe SMA
 // Exemple : delete _at;

 delete _sched;         // Destruction de l'ordonnanceur et des agents associes
}
