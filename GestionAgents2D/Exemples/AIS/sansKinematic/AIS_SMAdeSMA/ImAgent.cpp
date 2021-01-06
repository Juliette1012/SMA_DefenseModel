#include "ImAgent.h"

#include "Eprouvette.h"

#include <math.h>

//--
ImAgent::ImAgent(void) : Agent2D()
{
 newAgent();

 extern Eprouvette* eprouvette;

 if (eprouvette==NULL) {
  cerr << "ImAgent::ImAgent(void): erreur, pas d'eprouvette!" << endl;
  exit(1);
 }

 // Calcul d'une position aleatoire dans l'Eprouvette

 double xE, yE, tE; eprouvette->getLocation(xE,yE,tE); // Position Eprouvette

 int size = eprouvette->getSize();                     // Taille Eprouvette

 _squareSize = size/100.0;                             // Taille du ImAgent

 int sizeZoneCreation = (int)(size - _squareSize);

 int posX = randomMinMax(0,sizeZoneCreation-1) - sizeZoneCreation/2;
 int posY = randomMinMax(0,sizeZoneCreation-1) - sizeZoneCreation/2;

 setLocation(posX+xE,posY+yE,0);

 square(_squareSize,1);
 attachTo(*eprouvette);   // Si on deplace l'eprouvette ... on se deplace

 _speed = 0.0;
}

//--
ImAgent::ImAgent(const ImAgent& anI) : Agent2D(anI)
{
 newAgent();
 _copy(anI);

 extern Eprouvette* eprouvette;

 if (eprouvette==NULL) {
  cerr << "ImAgent::ImAgent(const ImAgent& anI): erreur, pas d'eprouvette!"
       << endl;
  exit(1);
 }

 attachTo(*eprouvette);   // Si on deplace l'eprouvette ... on se deplace
}

//--
ImAgent& ImAgent::operator=(const ImAgent& anI)
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
ImAgent::~ImAgent(void)
{
 _destroy();
}

void ImAgent::onKeyPress(const char * key)
{
 if (strcmp(key,"d")==0 || strcmp(key,"D")==0) delete this;
 else
 Agent2D::onKeyPress(key);
}

//--
void ImAgent::live(double dt)
{
 (void)dt; // Pour eviter un warning si pas utilise

 // "Comportement" d'un Agent de la classe ImAgent

 move();
}

void   ImAgent::move(void)
{
 if (_speed != 0.0) translate(_speed,0);
}

void   ImAgent::setSpeed(double speed)
{
 _speed = speed;
}
double ImAgent::getSpeed(void)
{
 return _speed;
}

//--
bool operator==(const ImAgent& anI1, const ImAgent& anI2)
{
 return anI1.isEqualTo(anI2);
}

//--
bool operator!=(const ImAgent& anI1, const ImAgent& anI2)
{
 return !(anI1==anI2);
}

//-------- distance ----------
double ImAgent::distance(double xP,double yP) const
{
 double x = getX();
 double y = getY();

 double dx = xP - x;
 double dy = yP - y;

 return sqrt(dx*dx + dy*dy);
}

//-------- towards ----------
double ImAgent::towards(double xP,double yP)
{
  double epsilon = 10e-3;

  double speed = 0.1; // A ajuster en fonction de la machine

  double x = getX();
  double y = getY();

  double dx = xP - x;
  double dy = yP - y;

  double r  = distance(xP,yP);

  if (r < epsilon) { r = 0.0;
                     setSpeed( 0.0 );
  }
  else /* (r!=0.0) */
  {
    setTheta( cartToAngle(dx,dy) );
    setSpeed( speed );
  }
  return r;
}

//--
ostream& operator<<(ostream& os, const ImAgent& anI)
{
 anI.display(os);
 return os;
}

//--
void ImAgent::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 Agent2D::display(os);

 // ### : Affichage des attributs de la classe ImAgent
 // Exemple : os << _at;

 os << getName() << " : speed = " << _speed << endl;
}

//--
bool ImAgent::isEqualTo(const ImAgent& anI) const
{
 (void)anI; // Pour eviter un warning si pas utilise

 // Test des attributs de la classe ImAgent
 // Exemple : if (_at != anI._at) return false;

 if (!(Agent2D::isEqualTo(anI)))     return false;
 if (_squareSize != anI._squareSize) return false;
 if (_speed      != anI._speed)      return false;
 return true;
}

//--
void ImAgent::_copy(const ImAgent& anI)
{
 (void)anI; // Pour eviter un warning si pas utilise

 // Affectation des attributs de la classe ImAgent
 // Exemple : _at = anI._at;

 _squareSize = anI._squareSize;
 _speed      = anI._speed;
}

//--
void ImAgent::_destroy(void)
{
 // Destruction des attributs de la classe ImAgent
 // Exemple : delete _at;
}

