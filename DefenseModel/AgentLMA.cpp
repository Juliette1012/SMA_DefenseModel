#include "AgentLMA.h"

#include <math.h>

//--
AgentLMA::AgentLMA(void) : Agent2D()
{
 newAgent();

 _squareSize = 10.0;                             // Taille du AgentLMA

 square(_squareSize,2);
 setColor("blue");

 int posX = randomMinMax(0, 100);
 int posY = randomMinMax(0, 100);

 setPosition(posX, posY);

}

AgentLMA::AgentLMA(int x, int y, Environnement* env) : Agent2D()
{
 newAgent();

 _squareSize = 10.0;  // Taille du AgentLMA
 _env = env;                           
 attachTo(*env);

 square(_squareSize,2);
 setColor("blue");

 setPosition(x, y);

}

//--
AgentLMA::AgentLMA(const AgentLMA& anI) : Agent2D(anI)
{
 newAgent();
 _copy(anI);
}

//--
AgentLMA& AgentLMA::operator=(const AgentLMA& anI)
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
AgentLMA::~AgentLMA(void)
{
 _destroy();
}

void AgentLMA::onKeyPress(const char * key)
{
 if (strcmp(key,"d")==0 || strcmp(key,"D")==0) delete this;
 if (strcmp(key,"p")==0 || strcmp(key,"P")==0) {
     cout << getName() << " from " << getEnv()->getName() << endl;
 }
 else
 Agent2D::onKeyPress(key);
}

//--
void AgentLMA::live(double dt)
{
 (void)dt; // Pour eviter un warning si pas utilise

 // "Comportement" d'un Agent de la classe AgentLMA
}

Environnement* AgentLMA::getEnv(void)
{
 return _env;
}

//--
void AgentLMA::setPosition(int x, int y)
{
 _x = x;
 _y = y;
 setLocation(_x, _y, 0);
}

//--
bool operator==(const AgentLMA& anI1, const AgentLMA& anI2)
{
 return anI1.isEqualTo(anI2);
}

//--
bool operator!=(const AgentLMA& anI1, const AgentLMA& anI2)
{
 return !(anI1==anI2);
}

//--
ostream& operator<<(ostream& os, const AgentLMA& anI)
{
 anI.display(os);
 return os;
}

//--
void AgentLMA::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 Agent2D::display(os);

 // ### : Affichage des attributs de la classe AgentLMA
 // Exemple : os << _at;
}

//--
void AgentLMA::_copy(const AgentLMA& anI)
{
 (void)anI; // Pour eviter un warning si pas utilise

 // Affectation des attributs de la classe AgentLMA
 // Exemple : _at = anI._at;

 _squareSize = anI._squareSize;
}

//--
void AgentLMA::_destroy(void)
{
 // Destruction des attributs de la classe AgentLMA
 // Exemple : delete _at;
}
