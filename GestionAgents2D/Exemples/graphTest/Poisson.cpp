#include "Poisson.h"

//--
Poisson::Poisson(AppliData* data) : Agent2D()
{
 newAgent();

 _data=data;
}

//--
Poisson::Poisson(const Poisson& aP) : Agent2D(aP)
{
 newAgent();
 _copy(aP);
}

//--
Poisson& Poisson::operator=(const Poisson& aP)
{
 if (this != &aP)
 {
  Agent2D::operator=(aP);
  _destroy();
  _copy(aP);
 }
 return *this;
}

//--
Poisson::~Poisson(void)
{
 _destroy();
}

//--
void Poisson::live(double dt)
{
 (void)dt; // Pour eviter un warning si pas utilise

 // "Comportement" d'un Agent de la classe Poisson

  dt=dt*1000.0;  // Pour avoir un temps en millisecondes

  int r,g,b;
  double x,y,th;
  double xInter,yInter;
  int message=0;
  rotate(-5e-3*dt*_data->cursor->getX()/_data->maxCursor);
  getLocation(x,y,th);
  if(_data->frame->intersectRay(x,y,th,xInter,yInter))
    {
    translate(_data->speed*dt,0.0);
    _data->target->circle(0.1,1);
    _data->target->setLocation(xInter,yInter,0.0);
    }
  else /* stop when not facing the aquarium */
    {
    _data->target->point();
    _data->message->text("Boom !!!");
    _data->message->setColor("red");
    message=1;
    }
  getLocation(x,y,th);
  if(_data->back->getImagePixelAt(x,y,r,g,b)&& /* can read pixel */
     ((r!=0)||(g!=0)||(b!=255)))               /* but not blue   */
    {
    char buffer[0x100];
    sprintf(buffer,"Ouch ... my scales !!! (%d/%d/%d)",r,g,b);
    _data->message->text(buffer);
    _data->message->setColor("orange");
    message=1;
    }
  if(!message)
    {
    _data->message->text("OK ...");
    _data->message->setColor("green");
    }
}

//--
bool operator==(const Poisson& aP1, const Poisson& aP2)
{
 return aP1.isEqualTo(aP2);
}

//--
bool operator!=(const Poisson& aP1, const Poisson& aP2)
{
 return !(aP1==aP2);
}

//--
ostream& operator<<(ostream& os, const Poisson& aP)
{
 aP.display(os);
 return os;
}

//--
void Poisson::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 Agent2D::display(os);

 // ### : Affichage des attributs de la classe Poisson
 // Exemple : os << _at;
}

//--
bool Poisson::isEqualTo(const Poisson& aP) const
{
 (void)aP; // Pour eviter un warning si pas utilise

 // ### : Test des attributs de la classe Poisson
 // Exemple : if (_at != aP._at) return false;

 if (!(Agent2D::isEqualTo(aP))) return false;
 return true;
}

//--
void Poisson::_copy(const Poisson& aP)
{
 (void)aP; // Pour eviter un warning si pas utilise

 // ### : Affectation des attributs de la classe Poisson
 // Exemple : _at = aP._at;

 _data = aP._data;
}

//--
void Poisson::_destroy(void)
{
 // ### : Destruction des attributs de la classe Poisson
 // Exemple : delete _at;
}

void Poisson::onKeyPress(const char * key)
{
 if (strcmp(key,"n")==0 || strcmp(key,"N")==0) cout << getName() << endl;
}
