#include "AcSMA.h"

#include "Ac.h"

//--
AcSMA::AcSMA(size_t nb) : Agent()
{
 newAgent();

 _sched = new Scheduler;
 _sched->setRandomMode(true);
 _sched->setRealTimeMode(false);

 for(size_t i=0;i<nb;i++)
 {
  newAc();
 }
}

//--
AcSMA::AcSMA(const AcSMA& anA) : Agent(anA)
{
 newAgent();
 _copy(anA);
}

//--
AcSMA& AcSMA::operator=(const AcSMA& anA)
{
 if (this != &anA)
 {
  Agent::operator=(anA);
  _destroy();
  _copy(anA);
 }
 return *this;
}

//--
AcSMA::~AcSMA(void)
{
 _destroy();
}

//--
Ac* AcSMA::newAc(void)
{
 Scheduler *oldSched=Scheduler::getCurrentSched(); //-- sauvegarde ancien

 Scheduler::setCurrentSched(_sched);

 Ac* acPtr = new Ac;

 Scheduler::setCurrentSched(oldSched);            //-- restauration ancien

 return acPtr;
}

Ac* AcSMA::newAc(const Ac& anA)
{
 Scheduler *oldSched=Scheduler::getCurrentSched(); //-- sauvegarde ancien

 Scheduler::setCurrentSched(_sched);

 Ac* acPtr = new Ac(anA);

 Scheduler::setCurrentSched(oldSched);            //-- restauration ancien

 return acPtr;
}

//--
void AcSMA::live(double dt)
{
 (void)dt; // Pour eviter un warning si pas utilise

 // "Comportement" d'un Agent de la classe AcSMA

 _sched->cycle();
}

//--
bool operator==(const AcSMA& anA1, const AcSMA& anA2)
{
 return anA1.isEqualTo(anA2);
}

//--
bool operator!=(const AcSMA& anA1, const AcSMA& anA2)
{
 return !(anA1==anA2);
}

//--
ostream& operator<<(ostream& os, const AcSMA& anA)
{
 anA.display(os);
 return os;
}

//--
void AcSMA::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 Agent::display(os);

 // Affichage des attributs de la classe AcSMA
 // Exemple : os << _at;
}

//--
bool AcSMA::isEqualTo(const AcSMA& anA) const
{
 (void)anA; // Pour eviter un warning si pas utilise

 // ### : Test des attributs de la classe AcSMA
 // Exemple : if (_at != anA._at) return false;

 if (!(Agent::isEqualTo(anA))) return false;
 return true;
}

//--
void AcSMA::_copy(const AcSMA& anA)
{
 (void)anA; // Pour eviter un warning si pas utilise

 // Affectation des attributs de la classe AcSMA
 // Exemple : _at = anA._at;

 _sched = new Scheduler;
 *_sched = *(anA._sched);  // Copie de l'ordonnanceur et des agents
}

//--
void AcSMA::_destroy(void)
{
 // Destruction des attributs de la classe AcSMA
 // Exemple : delete _at;

 delete _sched;
}

