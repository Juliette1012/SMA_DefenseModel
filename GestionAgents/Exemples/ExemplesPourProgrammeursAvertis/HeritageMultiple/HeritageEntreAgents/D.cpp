#include "D.h"

//--
D::D(void) : C()
{
 newAgent();
}

//--
D::D(const D& aD) : C(aD)
{
 newAgent();
 _copy(aD);
}

//--
D& D::operator=(const D& aD)
{
 if (this != &aD)
 {
  C::operator=(aD);
  _destroy();
  _copy(aD);
 }
 return *this;
}

//--
D::~D(void)
{
 _destroy();
}

//--
void D::live(double dt)
{
 (void)dt;

 // "Comportement" d'un Agent de la classe D
 cout << "D::My name is " << getName() << endl;
}

//--
bool operator==(const D& aD1, const D& aD2)
{
 return aD1.isEqualTo(aD2);
}

//--
bool operator!=(const D& aD1, const D& aD2)
{
 return !(aD1==aD2);
}

//--
ostream& operator<<(ostream& os, const D& aD)
{
 aD.display(os);
 return os;
}

//--
void D::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 C::display(os);

 // ### : Affichage des attributs de la classe D
 // Exemple : os << _at;
}

//--
bool D::isEqualTo(const D& aD) const
{
 (void)aD; // Pour eviter un warning si pas utilise

 // ### : Test des attributs de la classe D
 // Exemple : if (_at != aD._at) return false;

 if (!(C::isEqualTo(aD))) return false;
 return true;
}

//--
void D::_copy(const D& aD)
{
 (void)aD; // Pour eviter un warning si pas utilise

 // ### : Affectation des attributs de la classe D
 // Exemple : _at = aD._at;
}

//--
void D::_destroy(void)
{
 // ### : Destruction des attributs de la classe D
 // Exemple : delete _at;
}

