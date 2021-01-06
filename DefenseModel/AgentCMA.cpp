#include "AgentCMA.h"

#include <math.h>

//--
AgentCMA::AgentCMA(void) : Agent2D()
{
 newAgent();

 _squareSize = 15.0;                             // Taille du AgentCMA

 square(_squareSize,2);
 setColor("red");

}

//--
AgentCMA::AgentCMA(const AgentCMA& anI) : Agent2D(anI)
{
 newAgent();
 _copy(anI);
}

//--
AgentCMA& AgentCMA::operator=(const AgentCMA& anI)
{
 if (this != &anI)
 {
  Agent2D::operator=(anI);
  _destroy();
  _copy(anI);
 }
 return *this;
}

//--
AgentCMA::~AgentCMA(void)
{
 _destroy();
}

void AgentCMA::onKeyPress(const char * key)
{
 if (strcmp(key,"d")==0 || strcmp(key,"D")==0) delete this;
 else
 Agent2D::onKeyPress(key);
}

//--
void AgentCMA::live(double dt)
{
 (void)dt; // Pour eviter un warning si pas utilise

 // "Comportement" d'un Agent de la classe AgentCMA
}

//--
bool operator==(const AgentCMA& anI1, const AgentCMA& anI2)
{
 return anI1.isEqualTo(anI2);
}

//--
bool operator!=(const AgentCMA& anI1, const AgentCMA& anI2)
{
 return !(anI1==anI2);
}

//--
ostream& operator<<(ostream& os, const AgentCMA& anI)
{
 anI.display(os);
 return os;
}

//--
void AgentCMA::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 Agent2D::display(os);

 // ### : Affichage des attributs de la classe AgentCMA
 // Exemple : os << _at;
}

//--
void AgentCMA::_copy(const AgentCMA& anI)
{
 (void)anI; // Pour eviter un warning si pas utilise

 // Affectation des attributs de la classe AgentCMA
 // Exemple : _at = anI._at;

 _squareSize = anI._squareSize;
}

//--
void AgentCMA::_destroy(void)
{
 // Destruction des attributs de la classe AgentCMA
 // Exemple : delete _at;
}
