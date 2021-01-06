#include "Environnement.h"

//--

Environnement::Environnement(const char* name, int x, int y, double length, double width, const char* color) : Agent2D()
{
 newAgent();
 _name = name;
 _length = length;
 _width = width;
 rectangle(_length, _width, 0);
 setColor(color);
 setPosition(x,y);
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

const char* Environnement::getName(void)
{
  return _name;
}

double Environnement::getWidth(void)
{
  return _width;
}

double Environnement::getLength(void)
{
  return _length;
}

double Environnement::getPosX(void)
{
  return _x;
}

double Environnement::getPosY(void)
{
  return _y;
}

void Environnement::setPosition(int x, int y){
  _x = x;
  _y = y;
  setLocation(_x, _y, 0);
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
   cout << getName() << ": " << _width << " X " << _length << endl;
 }
}

void Environnement::onMouseDrag(double dx,double dy)
{
 (void)dx; (void)dy;

 // Pas le droit de deplacer l'environnement
 Agent2D::onMouseDrag(dx,dy); // ... Mais on peut maintenant essayer !
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

 cout << "Taille environnement : length = " << _length << "and width = " << _width << endl;
}

//--
bool Environnement::isEqualTo(const Environnement& anE) const
{
 (void)anE; // Pour eviter un warning si pas utilise

 // ### : Test des attributs de la classe Environnement
 // Exemple : if (_at != anE._at) return false;

 if (!(Agent2D::isEqualTo(anE))) return false;
 if (_width != anE._width && _length != anE._length) return false;
 return true;
}

//--
void Environnement::_copy(const Environnement& anE)
{
 (void)anE; // Pour eviter un warning si pas utilise

 // ### : Affectation des attributs de la classe Environnement
 // Exemple : _at = anE._at;

 _width = anE._width;
 _length = anE._length;
}

//--
void Environnement::_destroy(void)
{
 // ### : Destruction des attributs de la classe Environnement
 // Exemple : delete _at;
}

