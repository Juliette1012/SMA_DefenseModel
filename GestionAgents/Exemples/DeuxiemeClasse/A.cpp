#include "A.h"

//--
A::A(void) : Agent()
{
 newAgent();
}

//--
A::A(const A& anA) : Agent(anA)
{
 newAgent();
 _copy(anA);
}

//--
A& A::operator=(const A& anA)
{
 if (this != &anA)
 {
  Agent::operator=(anA);
  _destroy();
  _copy(anA);
 }
 return *this;
}

//--
A::~A(void)
{
 _destroy();
}

//--
void A::live(double dt)
{
 (void)dt; // Pour eviter un warning si pas utilise

 // "Comportement" d'un Agent de la classe A
 cout << "My name is " << getName() << " and dt is "<< dt << endl;

 int alea = randomMinMax(1,10);

 if (alea==5) { cout << "Destruction de " << getName() << endl;
                delete this;
 }
}

//--
bool operator==(const A& anA1, const A& anA2)
{
 return anA1.isEqualTo(anA2);
}

//--
bool operator!=(const A& anA1, const A& anA2)
{
 return !(anA1==anA2);
}

//--
ostream& operator<<(ostream& os, const A& anA)
{
 anA.display(os);
 return os;
}

//--
void A::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 Agent::display(os);
}

//--
bool A::isEqualTo(const A& anA) const
{
 (void)anA; // Pour eviter un warning si pas utilise

 if (!(Agent::isEqualTo(anA))) return false;
 return true;
}

//--
void A::_copy(const A& anA)
{
 (void)anA; // Pour eviter un warning si pas utilise
}

//--
void A::_destroy(void)
{
}

