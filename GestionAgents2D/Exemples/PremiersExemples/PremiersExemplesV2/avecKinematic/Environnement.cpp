#include "Environnement.h"

//--
Environnement::Environnement(double size) : Agent2D()
{
 newAgent();

 _size = size;
 square(_size,0);
 setColor("white");
 setLayer(2);
}

//--
Environnement::Environnement(const Environnement& anE) : Agent2D(anE)
{
 newAgent();
 _copy(anE);
}

//--
Environnement& Environnement::operator=(const Environnement& anE)
{
 if (this != &anE)
 {
  Agent2D::operator=(anE);
  _destroy();
  _copy(anE);
 }
 return *this;
}

//--
Environnement::~Environnement(void)
{
 _destroy();
}

double Environnement::getSize(void)
{
 return _size;
}

//--
void Environnement::live(double dt)
{
 (void)dt; // Pour eviter un warning si pas utilise

 // ### : "Comportement" d'un Agent de la classe Environnement
}

//-- Interaction
void Environnement::onKeyPress(const char * key)
{
 if (strcmp(key,"p")==0) {
   cout << getName() << ": " << _size << " X " << _size << endl;
 }
}

void Environnement::onMouseDrag(double dx,double dy)
{
 (void)dx; (void)dy;

 // Pas le droit de deplacer l'environnement
}

//--
bool operator==(const Environnement& anE1, const Environnement& anE2)
{
 return anE1.isEqualTo(anE2);
}

//--
bool operator!=(const Environnement& anE1, const Environnement& anE2)
{
 return !(anE1==anE2);
}

//--
ostream& operator<<(ostream& os, const Environnement& anE)
{
 anE.display(os);
 return os;
}

//--
void Environnement::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 Agent2D::display(os);

 // ### : Affichage des attributs de la classe Environnement
 // Exemple : os << _at;

 cout << "Taille environnement: " << _size << " X " << _size << endl;
}

//--
bool Environnement::isEqualTo(const Environnement& anE) const
{
 (void)anE; // Pour eviter un warning si pas utilise

 // ### : Test des attributs de la classe Environnement
 // Exemple : if (_at != anE._at) return false;

 if (!(Agent2D::isEqualTo(anE))) return false;
 if (_size != anE._size) return false;
 return true;
}

//--
void Environnement::_copy(const Environnement& anE)
{
 (void)anE; // Pour eviter un warning si pas utilise

 // ### : Affectation des attributs de la classe Environnement
 // Exemple : _at = anE._at;

 _size = anE._size;
}

//--
void Environnement::_destroy(void)
{
 // ### : Destruction des attributs de la classe Environnement
 // Exemple : delete _at;
}

