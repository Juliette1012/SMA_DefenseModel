#include "Petit.h"

//--
Petit::Petit(Poisson* precedent,AppliData* data) : Poisson(data)
{
 newAgent();

 _precedent=precedent;
}

//--
Petit::Petit(const Petit& aP) : Poisson(aP)
{
 newAgent();
 _copy(aP);
}

//--
Petit& Petit::operator=(const Petit& aP)
{
 if (this != &aP)
 {
  Poisson::operator=(aP);
  _destroy();
  _copy(aP);
 }
 return *this;
}

//--
Petit::~Petit(void)
{
 _destroy();
}

//--
void Petit::live(double dt)
{
 (void)dt; // Pour eviter un warning si pas utilise

 // "Comportement" d'un Agent de la classe Petit

 dt=dt*1000.0;  // Pour avoir un temps en millisecondes

 double x=0.0,y=0.0,th=0.0,d=0.0;

 if (_precedent!=NULL)
 {
  _precedent->getLocation(x,y,th);
 }

 globalToLocalPosition(x,y);
 cartesianToPolar(x,y,&d,&th);
 d-=0.25;
 if(d>0.0)
      {
      double step=_data->maxSpeed*dt;
      rotate(th); /* face the preceding object */
      if(d<1.0) step*=d*d; /* slow down */
      if(step>d) step=d;   /* stay behind the preceding object */
      translate(step,0.0);
      }
}

//--
bool operator==(const Petit& aP1, const Petit& aP2)
{
 return aP1.isEqualTo(aP2);
}

//--
bool operator!=(const Petit& aP1, const Petit& aP2)
{
 return !(aP1==aP2);
}

//--
ostream& operator<<(ostream& os, const Petit& aP)
{
 aP.display(os);
 return os;
}

//--
void Petit::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 Poisson::display(os);

 // ### : Affichage des attributs de la classe Petit
 // Exemple : os << _at;
}

//--
bool Petit::isEqualTo(const Petit& aP) const
{
 (void)aP; // Pour eviter un warning si pas utilise

 // ### : Test des attributs de la classe Petit
 // Exemple : if (_at != aP._at) return false;

 if (!(Poisson::isEqualTo(aP))) return false;
 return true;
}

//--
void Petit::_copy(const Petit& aP)
{
 (void)aP; // Pour eviter un warning si pas utilise

 // ### : Affectation des attributs de la classe Petit
 // Exemple : _at = aP._at;

 _precedent=aP._precedent;
}

//--
void Petit::_destroy(void)
{
 // ### : Destruction des attributs de la classe Petit
 // Exemple : delete _at;
}

void Petit::onKeyPress(const char * key)
{
 if (strcmp(key,"n")==0 || strcmp(key,"N")==0) cout << getName() << endl;
}
