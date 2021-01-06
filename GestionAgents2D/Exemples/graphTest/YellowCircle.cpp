#include "YellowCircle.h"
#include "Petit.h"

#include <math.h>    /* Pour M_PI */

//--
YellowCircle::YellowCircle(double rayon,double x,double y) : Agent2D()
{
 newAgent();

 _rayon = rayon;
 circle(rayon,0);
 setLocation(x,y,0.0);
 setColor("yellow");
}

//--
YellowCircle::YellowCircle(const YellowCircle& aC) : Agent2D(aC)
{
 newAgent();
 _copy(aC);
}

//--
YellowCircle& YellowCircle::operator=(const YellowCircle& aC)
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
YellowCircle::~YellowCircle(void)
{
 _destroy();
}

//--
void YellowCircle::live(double dt)
{
 (void)dt; // Pour eviter un warning si pas utilise

 // "Comportement" d'un Agent de la classe YellowCircle

 vector<Agent2D*> v;
 int i, nbPetits;

 nbPetits = view("Petit",v,2*M_PI,_rayon);

 for(i=0;i<nbPetits;i++)
 {
  v[i]->setColor("yellow");
 }
}

//--
bool operator==(const YellowCircle& aC1, const YellowCircle& aC2)
{
 return aC1.isEqualTo(aC2);
}

//--
bool operator!=(const YellowCircle& aC1, const YellowCircle& aC2)
{
 return !(aC1==aC2);
}

//--
ostream& operator<<(ostream& os, const YellowCircle& aC)
{
 aC.display(os);
 return os;
}

//--
void YellowCircle::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 Agent2D::display(os);

 // ### : Affichage des attributs de la classe YellowCircle
 // Exemple : os << _at;
}

//--
bool YellowCircle::isEqualTo(const YellowCircle& aC) const
{
 (void)aC; // Pour eviter un warning si pas utilise

 // ### : Test des attributs de la classe YellowCircle
 // Exemple : if (_at != aC._at) return false;

 if (!(Agent2D::isEqualTo(aC))) return false;
 return true;
}

//--
void YellowCircle::_copy(const YellowCircle& aC)
{
 (void)aC; // Pour eviter un warning si pas utilise

 // ### : Affectation des attributs de la classe YellowCircle
 // Exemple : _at = aC._at;
}

//--
void YellowCircle::_destroy(void)
{
 // ### : Destruction des attributs de la classe YellowCircle
 // Exemple : delete _at;
}

void YellowCircle::onKeyPress(const char * key)
{
 if (strcmp(key,"n")==0 || strcmp(key,"N")==0) cout << getName() << endl;
}
