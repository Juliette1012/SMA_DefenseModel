#include "AgSMA.h"

#include "Ag.h"

//--
AgSMA::AgSMA(size_t nb) : Agent()
{
 newAgent();

 _sched = new Scheduler;
 _sched->setRandomMode(true);
 _sched->setRealTimeMode(true);

 for(size_t i=0;i<nb;i++)
 {
  newAg();
 }
}

//--
AgSMA::AgSMA(const AgSMA& anA) : Agent(anA)
{
 newAgent();
 _copy(anA);
}

//--
AgSMA& AgSMA::operator=(const AgSMA& anA)
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
AgSMA::~AgSMA(void)
{
 _destroy();
}

//--
Ag* AgSMA::newAg(void)
{
 Scheduler *oldSched=Scheduler::getCurrentSched(); //-- sauvegarde ancien

 Scheduler::setCurrentSched(_sched);

 Ag* agPtr = new Ag;

 Scheduler::setCurrentSched(oldSched);            //-- restauration ancien

 return agPtr;
}

//--
Ag* AgSMA::newAg(const Ag& anA)
{
 Scheduler *oldSched=Scheduler::getCurrentSched(); //-- sauvegarde ancien

 Scheduler::setCurrentSched(_sched);

 Ag* agPtr = new Ag(anA);

 Scheduler::setCurrentSched(oldSched);            //-- restauration ancien

 return agPtr;
}

//--
void AgSMA::live(double dt)
{
 (void)dt; // Pour eviter un warning si pas utilise

 // "Comportement" d'un Agent de la classe AgSMA

 _sched->cycle();
}

//--
bool operator==(const AgSMA& anA1, const AgSMA& anA2)
{
 return anA1.isEqualTo(anA2);
}

//--
bool operator!=(const AgSMA& anA1, const AgSMA& anA2)
{
 return !(anA1==anA2);
}

//--
ostream& operator<<(ostream& os, const AgSMA& anA)
{
 anA.display(os);
 return os;
}

//--
void AgSMA::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 Agent::display(os);

 // Affichage des attributs de la classe AgSMA
 // Exemple : os << _at;
}

//--
bool AgSMA::isEqualTo(const AgSMA& anA) const
{
 (void)anA; // Pour eviter un warning si pas utilise

 // ### : Test des attributs de la classe AgSMA
 // Exemple : if (_at != anA._at) return false;

 if (!(Agent::isEqualTo(anA))) return false;
 return true;
}

//--
void AgSMA::_copy(const AgSMA& anA)
{
 (void)anA; // Pour eviter un warning si pas utilise

 // Affectation des attributs de la classe AgSMA
 // Exemple : _at = anA._at;

 _sched = new Scheduler;
 *_sched = *(anA._sched);  // Copie de l'ordonnanceur et des agents
}

//--
void AgSMA::_destroy(void)
{
 // Destruction des attributs de la classe AgSMA
 // Exemple : delete _at;

 delete _sched;
}

