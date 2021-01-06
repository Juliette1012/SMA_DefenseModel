#include "Rond.h"

#include <math.h>

#define EPS 0.5

static
int eq(double x, double y)   // equal  => not equal: !eq(x,y)  
{
 double epsilon=EPS;

 if (fabs(x-y)<epsilon) return 1;
 else return 0;
}

static
int gt(double x, double y)   // greater than
{
 double epsilon=EPS;

 if (x-y>epsilon) return 1;
 else return 0;
}

static
int ge(double x, double y)   // greater or equal
{
 return gt(x,y) || eq(x,y);
}

static
int lt(double x, double y)   // less than
{
 return gt(y,x);
}

static
int le(double x, double y)   // less or equal
{
 return lt(x,y) || eq(x,y);
}

static
double distance(double x1, double y1, double x2, double y2)
{
 double dx=x1-x2;
 double dy=y1-y2;

 return sqrt(dx*dx+dy*dy);
}

//--
Rond::Rond(double radius, Environnement* env) : Agent2D()
{
 newAgent();

 _radius = radius;
 _env    = env;
 attachTo(*env);  // Si on deplace l'environnement ...

 circle(_radius,0);

 setTheta(random01()*2*M_PI);

 setLinearVelocityX(100);
}

//--
Rond::Rond(const Rond& aR) : Agent2D(aR)
{
 newAgent();
 _copy(aR);
}

//--
Rond& Rond::operator=(const Rond& aR)
{
 if (this != &aR)
 {
  Agent2D::operator=(aR);
  _destroy();
  _copy(aR);
 }
 return *this;
}

//--
Rond::~Rond(void)
{
 _destroy();
}

//--
double Rond::getRadius(void)
{
 return _radius;
}

//--
void Rond::onKeyPress(const char * key)
{
 Agent2D::onKeyPress(key);
 if (strcmp(key,"d")==0) delete this;
} 

//--
void Rond::mettreDedans(void)
{
 double side = _env->getSize();
 bool   chgt = false;
 double x,y,theta;
 double xE,yE,tE;

 _env->getLocation(xE,yE,tE);

 getLocation(x,y,theta);
 if (lt(x,xE-side/2+_radius)) { x=xE-side/2+_radius; chgt=true; }
 if (gt(x,xE+side/2-_radius)) { x=xE+side/2-_radius; chgt=true; }
 if (lt(y,yE-side/2+_radius)) { y=yE-side/2+_radius; chgt=true; }
 if (gt(y,yE+side/2-_radius)) { y=yE+side/2-_radius; chgt=true; }
 setLocation(x,y,theta);


 if (chgt) { 
#if 0
 cout << "***************" << endl;
 cout << "* Mise dedans *" << endl;
 cout << "***************" << endl;
#endif
 }
}

//--
void Rond::avancer(double dt)
{
 (void)dt;

 Kinematic(dt);
 mettreDedans(); // Si l'objet vient de sortir ...
}

//--
void Rond::live(double dt)
{
 (void)dt; // Pour eviter un warning si pas utilise

 // "Comportement" d'un Agent de la classe Rond

 mettreDedans(); // Si l'objet etait sorti ...

 vector<Agent2D*> v;
 v.push_back(_env);

#if 1
 vector<Agent*> vRond; getAllAgents("Rond",vRond);
 for(unsigned int i=0;i<vRond.size();i++)
 {
  v.push_back((Agent2D*)vRond[i]);
 }
#endif

 double xInter,yInter;
 Agent2D* agt=throwRay(xInter,yInter,v);

 double x, y, t;  this->getLocation(x,y,t);

 if (agt==_env)
 {
  double xE,yE,tE; _env->getLocation(xE,yE,tE);
  double    size = _env->getSize();

  if (eq(xInter,xE+size/2)) // rayon intersecte a droite
  {
   if (ge(x+_radius,xE+size/2))
   {                             // angle rebond entre PI/2 et 3PI/2
    setTheta(random01()*M_PI + M_PI_2);
   }
  }

  else

  if (eq(xInter,xE-size/2)) // rayon intersecte a gauche
  {
   if (le(x-_radius,xE-size/2))
   {                             // angle rebond entre -PI/2 et PI/2
    setTheta(random01()*M_PI - M_PI_2);
   }
  }

  else

  if (eq(yInter,yE+size/2)) // rayon intersecte en haut
  {
   if (ge(y+_radius,yE+size/2))
   {                             // angle rebond entre 0 et -PI
    setTheta(-random01()*M_PI);
   }
  }

  else

  if (eq(yInter,yE-size/2)) // rayon intersecte en bas
  {
   if (le(y-_radius,yE-size/2))
   {                             // angle rebond entre 0 et PI
    setTheta(random01()*M_PI);
   }
  }

  else cout << "Rond::live, there is a problem !" << endl;

 }
 else { 

   if (agt->isA("Rond")) // Un rond a ete detecte ?
   {
    Rond* rAgt=(Rond*)agt;
    double xA, yA, tA; rAgt->getLocation(xA,yA,tA);
    double rA = rAgt->getRadius();

    if (le(distance(x,y,xA,yA),_radius+rA)) { 
      setTheta(random01()*2*M_PI);  // Gestion de la collision tres simpliste !
    }
   }

 }

 avancer(dt);
}

//--
bool operator==(const Rond& aR1, const Rond& aR2)
{
 return aR1.isEqualTo(aR2);
}

//--
bool operator!=(const Rond& aR1, const Rond& aR2)
{
 return !(aR1==aR2);
}

//--
ostream& operator<<(ostream& os, const Rond& aR)
{
 cout << "<-----------------------------";
 aR.display(os);
 cout << "----------------------------->";
 return os;
}

//--
void Rond::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 Agent2D::display(os);

 // ### : Affichage des attributs de la classe Rond
 // Exemple : os << _at;
 os << "Rond de Radius: " << _radius << endl;
}

//--
bool Rond::isEqualTo(const Rond& aR) const
{
 (void)aR; // Pour eviter un warning si pas utilise

 // ### : Test des attributs de la classe Rond
 // Exemple : if (_at != aR._at) return false;

 if (!(Agent2D::isEqualTo(aR))) return false;
 if (_radius != aR._radius)     return false;
 if (_env != aR._env)           return false;
 return true;
}

//--
void Rond::_copy(const Rond& aR)
{
 (void)aR; // Pour eviter un warning si pas utilise

 // ### : Affectation des attributs de la classe Rond
 // Exemple : _at = aR._at;

 _radius = aR._radius;
 _env    = aR._env;
}

//--
void Rond::_destroy(void)
{
 // ### : Destruction des attributs de la classe Rond
 // Exemple : delete _at;
}

