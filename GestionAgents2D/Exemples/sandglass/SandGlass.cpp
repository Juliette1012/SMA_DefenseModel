#include "SandGlass.h"

#include "SandGrain.h"
#include "FixedSandGrain.h"

#include <math.h>

//--
SandGlass::SandGlass(int side,int nbGrain) : Agent2D()
{
 newAgent();
 
 double s=sqrt(2)*0.5;
 double dx=DIAM*(side-0.5);
 double dy=DIAM*(side*(1+s)-0.5);
 SandGrain* grain=NULL;

 for(int i=0;i<side;i++)
  {
  grain=new FixedSandGrain();
  grain->setLocation(-dx,i*DIAM-dy,0);
  grain->attachTo(*this);

  grain=new FixedSandGrain();
  grain->setLocation(i*DIAM-dx,-dy,0);
  grain->attachTo(*this);

  grain=new FixedSandGrain();
  grain->setLocation(dx,i*DIAM-dy,0);
  grain->attachTo(*this);
  grain=new FixedSandGrain();
  grain->setLocation(dx-i*DIAM,-dy,0);
  grain->attachTo(*this);

  grain=new FixedSandGrain();
  grain->setLocation(-dx,dy-i*DIAM,0);
  grain->attachTo(*this);
  grain=new FixedSandGrain();
  grain->setLocation(i*DIAM-dx,dy,0);
  grain->attachTo(*this);

  grain=new FixedSandGrain();
  grain->setLocation(dx,dy-i*DIAM,0);
  grain->attachTo(*this);
  grain=new FixedSandGrain();
  grain->setLocation(dx-i*DIAM,dy,0);
  grain->attachTo(*this);

  grain=new FixedSandGrain();
  grain->setLocation(s*(i+1)*DIAM-dx,(side-1)*DIAM+s*(i+1)*DIAM-dy,0);
  grain->attachTo(*this);
  grain=new FixedSandGrain();
  grain->setLocation(dx-s*(i+1)*DIAM,(side-1)*DIAM+s*(i+1)*DIAM-dy,0);
  grain->attachTo(*this);
  grain=new FixedSandGrain();
  grain->setLocation(s*(i+1)*DIAM-dx,dy-(side-1)*DIAM-s*(i+1)*DIAM,0);
  grain->attachTo(*this);
  grain=new FixedSandGrain();
  grain->setLocation(dx-s*(i+1)*DIAM,dy-(side-1)*DIAM-s*(i+1)*DIAM,0);
  grain->attachTo(*this);
  }
SandGrain *other=NULL;
int nb=0;
while(nb<nbGrain)
  {
  grain=new SandGrain();
  grain->attachTo(*this);

  double distance=0.0, angle=0.0;
  int nbEssai=0, maxEssai=9999;
  do
    {
     nbEssai++;
     if (randomMinMax(0,1))
     {
      grain->setLocation(dx*(2*random01()-1),dy*(random01()*0.6-1),0);
     }
     else
     {
      grain->setLocation(dx*(2*random01()-1),-dy*(random01()*0.6-1),0);
     }

     other=(SandGrain*)grain->viewFirst("SandGrain",0.0,0.0);
     if (other)
     {
      // calcul angle et distance
      double xo,yo,to; other->getLocation(xo,yo,to);
      grain->globalToLocalPosition(xo,yo);
      cartesianToPolar(xo,yo,&distance,&angle);
     }
    } while(other&&(distance<=DIAM)&&(nbEssai<maxEssai));

    if (nbEssai==maxEssai)
    {
     delete grain;
     cerr << "--------------------------------------------------" << endl;
     cerr << "Creation de seulement " << nb << " grains de sable" << endl;
     cerr << "--------------------------------------------------" << endl;
     cerr << endl;
     break;
    }
    nb++;
  }
}

//--
SandGlass::SandGlass(const SandGlass& aS) : Agent2D(aS)
{
 newAgent();
 _copy(aS);
}

//--
SandGlass& SandGlass::operator=(const SandGlass& aS)
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
SandGlass::~SandGlass(void)
{
 _destroy();
}

//--
void SandGlass::live(double dt)
{
 (void)dt; // Pour eviter un warning si pas utilise

 // "Comportement" d'un Agent de la classe SandGlass
}

//--
bool operator==(const SandGlass& aS1, const SandGlass& aS2)
{
 return aS1.isEqualTo(aS2);
}

//--
bool operator!=(const SandGlass& aS1, const SandGlass& aS2)
{
 return !(aS1==aS2);
}

//--
ostream& operator<<(ostream& os, const SandGlass& aS)
{
 aS.display(os);
 return os;
}

//--
void SandGlass::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

 Agent2D::display(os);

 // Affichage des attributs de la classe SandGlass
 // Exemple : os << _at;
}

//--
bool SandGlass::isEqualTo(const SandGlass& aS) const
{
 (void)aS; // Pour eviter un warning si pas utilise

 // Test des attributs de la classe SandGlass
 // Exemple : if (_at != aS._at) return false;

 if (!(Agent2D::isEqualTo(aS))) return false;
 return true;
}

//--
void SandGlass::_copy(const SandGlass& aS)
{
 (void)aS; // Pour eviter un warning si pas utilise

 // Affectation des attributs de la classe SandGlass
 // Exemple : _at = aS._at;
}

//--
void SandGlass::_destroy(void)
{
 // Destruction des attributs de la classe SandGlass
 // Exemple : delete _at;
}

