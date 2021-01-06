#include "Label.h"

#include "MessageColor.h"

//--
Label::Label(Environnement* env) : Agent2D()
{
 newAgent();
 text(env->getName());

 attachTo(*env);

 double xEnv, yEnv, thetaEnv;
 double widthEnv = env->getWidth();
 double lengthEnv = env->getLength();
 env->getLocation(xEnv,yEnv,thetaEnv);

 double x = env-> getPosX();
 double y = env -> getPosY();

 setLocation(x - lengthEnv/2, y - widthEnv/2 ,thetaEnv);
 setColor("black");
}

//--
Label::Label(const Label& aL) : Agent2D(aL)
{
 newAgent();
 _copy(aL);
}

//--
Label& Label::operator=(const Label& aL)
{
 if (this != &aL)
 {
  Agent2D::operator=(aL);
  _destroy();
  _copy(aL);
 }
 return *this;
}

//--
Label::~Label(void)
{
 _destroy();
}

void Label::setText(const char* name, Environnement* env){
    text(name);
    attachTo(*env);
}

//--
void Label::live(double dt)
{
 (void)dt; // Pour eviter un warning si pas utilise

 // "Comportement" d'un Agent de la classe Label

 while (getNbMessages())
 {
  MessageColor* mes = (MessageColor*)getNextMessage(); 

  text(mes->getColor());
  setColor(mes->getColor());

  delete mes;
 }
}

//--
bool operator==(const Label& aL1, const Label& aL2)
{
 return aL1.isEqualTo(aL2);
}

//--
bool operator!=(const Label& aL1, const Label& aL2)
{
 return !(aL1==aL2);
}

//--
ostream& operator<<(ostream& os, const Label& aL)
{
 aL.display(os);
 return os;
}

//--
void Label::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 Agent2D::display(os);

 // ### : Affichage des attributs de la classe Label
 // Exemple : os << _at;
}

//--
bool Label::isEqualTo(const Label& aL) const
{
 (void)aL; // Pour eviter un warning si pas utilise

 // ### : Test des attributs de la classe Label
 // Exemple : if (_at != aL._at) return false;

 if (!(Agent2D::isEqualTo(aL))) return false;
 return true;
}

//--
void Label::_copy(const Label& aL)
{
 (void)aL; // Pour eviter un warning si pas utilise

 // ### : Affectation des attributs de la classe Label
 // Exemple : _at = aL._at;
}

//--
void Label::_destroy(void)
{
 // ### : Destruction des attributs de la classe Label
 // Exemple : delete _at;
}

