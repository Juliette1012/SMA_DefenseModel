#include "FixedSandGrain.h"

//--
FixedSandGrain::FixedSandGrain(void) : SandGrain()
{
 newAgent();
 setColor("white");
 _fixed=true;
}

//--
FixedSandGrain::FixedSandGrain(const FixedSandGrain& aF) : SandGrain(aF)
{
 newAgent();
 _copy(aF);
}

//--
FixedSandGrain& FixedSandGrain::operator=(const FixedSandGrain& aF)
{
 if (this != &aF)
 {
  SandGrain::operator=(aF);
  _destroy();
  _copy(aF);
 }
 return *this;
}

//--
FixedSandGrain::~FixedSandGrain(void)
{
 _destroy();
}

//--
void FixedSandGrain::live(double dt)
{
 (void)dt; // Pour eviter un warning si pas utilise

 // "Comportement" d'un Agent de la classe FixedSandGrain
}

//--
bool operator==(const FixedSandGrain& aF1, const FixedSandGrain& aF2)
{
 return aF1.isEqualTo(aF2);
}

//--
bool operator!=(const FixedSandGrain& aF1, const FixedSandGrain& aF2)
{
 return !(aF1==aF2);
}

//--
ostream& operator<<(ostream& os, const FixedSandGrain& aF)
{
 aF.display(os);
 return os;
}

//--
void FixedSandGrain::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 SandGrain::display(os);

 // Affichage des attributs de la classe FixedSandGrain
 // Exemple : os << _at;
}

//--
bool FixedSandGrain::isEqualTo(const FixedSandGrain& aF) const
{
 (void)aF; // Pour eviter un warning si pas utilise

 // Test des attributs de la classe FixedSandGrain
 // Exemple : if (_at != aF._at) return false;

 if (!(SandGrain::isEqualTo(aF))) return false;
 return true;
}

//--
void FixedSandGrain::_copy(const FixedSandGrain& aF)
{
 (void)aF; // Pour eviter un warning si pas utilise

 // Affectation des attributs de la classe FixedSandGrain
 // Exemple : _at = aF._at;
}

//--
void FixedSandGrain::_destroy(void)
{
 // Destruction des attributs de la classe FixedSandGrain
 // Exemple : delete _at;
}

void FixedSandGrain::onKeyPress(const char * key)
{
 if (strcmp(key,"n")==0 || strcmp(key,"N")==0) cout << getName() << endl;
}
