#include "RedCircle.h"
#include "Petit.h"

//--
RedCircle::RedCircle(double rayon,double x,double y) : Agent2D()
{
 newAgent();

 _rayon = rayon;
 circle(rayon,0);
 setLocation(x,y,0.0);
 setColor("red");
}

//--
RedCircle::RedCircle(const RedCircle& aC) : Agent2D(aC)
{
 newAgent();
 _copy(aC);
}

//--
RedCircle& RedCircle::operator=(const RedCircle& aC)
{
 if (this != &aC)
 {
  Agent2D::operator=(aC);
  _destroy();
  _copy(aC);
 }
 return *this;
}

//--
RedCircle::~RedCircle(void)
{
 _destroy();
}

//--
void RedCircle::live(double dt)
{
 (void)dt; // Pour eviter un warning si pas utilise

 // "Comportement" d'un Agent de la classe RedCircle

 Petit* first;

 first = (Petit*)viewFirst("Petit",2*M_PI,_rayon);

 if (first)
 {
  first->setColor("red");
 }
}

//--
bool operator==(const RedCircle& aC1, const RedCircle& aC2)
{
 return aC1.isEqualTo(aC2);
}

//--
bool operator!=(const RedCircle& aC1, const RedCircle& aC2)
{
 return !(aC1==aC2);
}

//--
ostream& operator<<(ostream& os, const RedCircle& aC)
{
 aC.display(os);
 return os;
}

//--
void RedCircle::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 Agent2D::display(os);

 // ### : Affichage des attributs de la classe RedCircle
 // Exemple : os << _at;
}

//--
bool RedCircle::isEqualTo(const RedCircle& aC) const
{
 (void)aC; // Pour eviter un warning si pas utilise

 // ### : Test des attributs de la classe RedCircle
 // Exemple : if (_at != aC._at) return false;

 if (!(Agent2D::isEqualTo(aC))) return false;
 return true;
}

//--
void RedCircle::_copy(const RedCircle& aC)
{
 (void)aC; // Pour eviter un warning si pas utilise

 // ### : Affectation des attributs de la classe RedCircle
 // Exemple : _at = aC._at;
}

//--
void RedCircle::_destroy(void)
{
 // ### : Destruction des attributs de la classe RedCircle
 // Exemple : delete _at;
}

void RedCircle::onKeyPress(const char * key)
{
 if (strcmp(key,"n")==0 || strcmp(key,"N")==0) cout << getName() << endl;
}
