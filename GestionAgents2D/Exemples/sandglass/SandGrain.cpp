#include "SandGrain.h"

#include <math.h>

static
double signedSquare(double arg)
{
 return (arg>=0.0 ? arg*arg : -arg*arg);
}

static
double signedSqrt(double arg)
{
 return (arg>=0.0 ? sqrt(arg) : -sqrt(-arg));
}

//--
SandGrain::SandGrain(void) : Agent2D()
{
 newAgent();

 _fixed   = false;
 _sx      = 0.0;
 _sy      = 0.0;
 _g       = GRAV;
 _contact = 0;

 const char* _colors[11];
 _colors[0]="pink";
 _colors[1]="red";
 _colors[2]="green";
 _colors[3]="blue";
 _colors[4]="yellow";
 _colors[5]="magenta";
 _colors[6]="orange";
 _colors[7]="brown";
 _colors[8]="light grey";
 _colors[9]="dark grey";
 _colors[10]="black";
 int nbColors = 11;
 setColor(_colors[randomMinMax(0,nbColors-1)]);

 setLayer(5);
 circle(DIAM*0.5,true);
}

//--
SandGrain::SandGrain(const SandGrain& aS) : Agent2D(aS)
{
 newAgent();
 _copy(aS);
}

//--
SandGrain& SandGrain::operator=(const SandGrain& aS)
{
 if (this != &aS)
 {
  Agent2D::operator=(aS);
  _destroy();
  _copy(aS);
 }
 return *this;
}

//--
SandGrain::~SandGrain(void)
{
 _destroy();
}

//--
void SandGrain::live(double dt)
{
 (void)dt; // Pour eviter un warning si pas utilise

 // "Comportement" d'un Agent de la classe SandGrain

 double coef1=sqrt((1.0-TRANSFERT)*RENDEMENT);
 double coef2=sqrt(TRANSFERT*RENDEMENT);
 double angle=0.0,distance=0.0;
 double oldLocation0,oldLocation1,oldLocation2;
 getLocation(oldLocation0,oldLocation1,oldLocation2);
 if(_contact>3)
    {
    _sx*=coef1;
    _sy*=coef1;
    }
 else if(!_contact) _sy-=_g*DT;
 setLocation(oldLocation0+_sx*DT,oldLocation1+_sy*DT,0.0);
 SandGrain* other=(SandGrain*)viewFirst("SandGrain",0.0,0.0,0.0);
 
 if (other)
 {
  // calcul angle et distance
  double xo,yo,to; other->getLocation(xo,yo,to);
  globalToLocalPosition(xo,yo);
  cartesianToPolar(xo,yo,&distance,&angle);
 }
 if(other&&(distance<=DIAM))
    {
    double c=cos(angle);
    double s=sin(angle);
    double sxa=_sx*c+_sy*s;
    double sya=_sy*c-_sx*s;
    if(other->_fixed) sxa=-sxa*coef1;
    else
      {
      double sxb=other->_sx*c+other->_sy*s;
      double syb=other->_sy*c-other->_sx*s;
      double sxa2=signedSquare(sxa);
      double sxb2=signedSquare(sxb);
      sxa=signedSqrt(sxb2*coef2*coef2-sxa2*coef1*coef1);
      sxb=signedSqrt(sxa2*coef2*coef2-sxb2*coef1*coef1);
      other->_sx=sxb*c-syb*s;
      other->_sy=syb*c+sxb*s;
      }
    _sx=sxa*c-sya*s;
    _sy=sya*c+sxa*s;
    _contact++;
    setLocation(oldLocation0,oldLocation1,oldLocation2);
    }
  else _contact=0;
}

//--
bool operator==(const SandGrain& aS1, const SandGrain& aS2)
{
 return aS1.isEqualTo(aS2);
}

//--
bool operator!=(const SandGrain& aS1, const SandGrain& aS2)
{
 return !(aS1==aS2);
}

//--
ostream& operator<<(ostream& os, const SandGrain& aS)
{
 aS.display(os);
 return os;
}

//--
void SandGrain::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 Agent2D::display(os);

 // Affichage des attributs de la classe SandGrain
 // Exemple : os << _at;
}

//--
bool SandGrain::isEqualTo(const SandGrain& aS) const
{
 (void)aS; // Pour eviter un warning si pas utilise

 // Test des attributs de la classe SandGrain
 // Exemple : if (_at != aS._at) return false;

 if (!(Agent2D::isEqualTo(aS))) return false;
 if (_fixed != aS._fixed)       return false;
 if (_sx != aS._sx)             return false;
 if (_sy != aS._sy)             return false;
 if (_g != aS._g)               return false;
 if (_contact != aS._contact)   return false;
 return true;
}

//--
void SandGrain::_copy(const SandGrain& aS)
{
 (void)aS; // Pour eviter un warning si pas utilise

 // Affectation des attributs de la classe SandGrain
 // Exemple : _at = aS._at;

 _fixed   = aS._fixed;
 _sx      = aS._sx;
 _sy      = aS._sy;
 _g       = aS._g;
 _contact = aS._contact;
}

//--
void SandGrain::_destroy(void)
{
 // Destruction des attributs de la classe SandGrain
 // Exemple : delete _at;
}

void SandGrain::onKeyPress(const char * key)
{
 if (strcmp(key,"n")==0 || strcmp(key,"N")==0) cout << getName() << endl;
}
