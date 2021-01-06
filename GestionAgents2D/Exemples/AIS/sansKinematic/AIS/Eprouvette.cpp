#include "Eprouvette.h"

#include <vector>

#include "Decor.h"

#include "Ac.h"
#include "Ag.h"

//--
Eprouvette::Eprouvette(size_t size) : Object2D()
{
 addDecor(this);

 _size = size;

 setColor("white");
 square(_size,0);

 _start=false;
}

//--
Eprouvette::Eprouvette(const Eprouvette& anE) : Object2D(anE)
{
 addDecor(this);
 _copy(anE);
}

//--
Eprouvette& Eprouvette::operator=(const Eprouvette& anE)
{
 if (this != &anE)
 {
  Object2D::operator=(anE);
  _destroy();
  _copy(anE);
 }
 return *this;
}

//--
Eprouvette::~Eprouvette(void)
{
 _destroy();
 removeDecor(this);
}

//--
void Eprouvette::onKeyPress(const char * key)
{
 if (strcmp(key,"H")==0 || strcmp(key,"h")==0) event_H();
 else
 if (strcmp(key,"S")==0 || strcmp(key,"s")==0) event_S();
 else
 if (strcmp(key,"C")==0 || strcmp(key,"c")==0) event_C();
 else
 if (strcmp(key,"G")==0 || strcmp(key,"g")==0) event_G();
}

void Eprouvette::event_H(void)
{
 cout << endl;
 cout << "---------------------------------------" << endl;
 cout << "Touches disponibles sur une Eprouvette :" << endl;
 cout << "---------------------------------------" << endl;
 cout << "c/C : Creation Ac                      " << endl;
 cout << "g/G : Creation Ag                      " << endl;
 cout << "s/S : start/stop de tous les Ac        " << endl;
 cout << "h/H : Help sur l'eprouvette !          " << endl;
 cout << "---------------------------------------" << endl;
}

void Eprouvette::event_S(void)
{
 vector<Agent*> v;
 getAllAgents("Ac",v);
 size_t i;
 if (_start)
 {
  for(i=0;i<v.size();i++)
  {
   Ac* ac=(Ac*)v[i];
   ac->stop();
  }
  _start=false;
 }
 else
 {
  for(i=0;i<v.size();i++)
  {
   Ac* ac=(Ac*)v[i];
   ac->start();
  }
  _start=true;
 }
}

void Eprouvette::event_C(void)
{
 Ac * agt = new Ac;
 cout << "Creation de " << agt->getName() << endl;
}

void Eprouvette::event_G(void)
{
 Ag * agt = new Ag;
 cout << "Creation de " << agt->getName() << endl;
}

//--
bool operator==(const Eprouvette& anE1, const Eprouvette& anE2)
{
 return anE1.isEqualTo(anE2);
}

//--
bool operator!=(const Eprouvette& anE1, const Eprouvette& anE2)
{
 return !(anE1==anE2);
}

//--
ostream& operator<<(ostream& os, const Eprouvette& anE)
{
 anE.display(os);
 return os;
}

//--
void Eprouvette::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 Object2D::display(os);

 // Affichage des attributs de la classe Eprouvette
 // Exemple : os << _at;

 os << "Taille eprouvette : " << _size;
}

//--
bool Eprouvette::isEqualTo(const Eprouvette& anE) const
{
 (void)anE; // Pour eviter un warning si pas utilise

 // Test des attributs de la classe Eprouvette
 // Exemple : if (_at != anE._at) return false;

 if (!(Object2D::isEqualTo(anE)))        return false;
 if (_size != anE._size)                 return false;
 return true;
}

//--
int Eprouvette::getSize(void) const
{
 return _size;
}

//--
void Eprouvette::_copy(const Eprouvette& anE)
{
 (void)anE; // Pour eviter un warning si pas utilise

 // Affectation des attributs de la classe Eprouvette
 // Exemple : _at = anE._at;

 _size       = anE._size;
}

//--
void Eprouvette::_destroy(void)
{
 // Destruction des attributs de la classe Eprouvette
 // Exemple : delete _at;
}
