#include "Agent2D.h"

#define AGENT2D_SEE_CALLBACK_CALL 0 // To debug interface interaction...

#include <math.h> // Pour M_PI

//-- A mettre ??? pas s^ur !
#if 0 
void getAllAgents(string aClass, vector<Agent2D*>& anAgent2DVector)
{
 getAllAgents(aClass,(vector<Agent*>&)anAgent2DVector);
}

Agent2D* getAgent2D(string aName)
{
 Agent* agt=getAgent(aName);

 if (agt==NULL) return NULL;

 if (agt->isA("Agent2D")) return (Agent2D*)agt;

 cerr << "Can't get a Agent2D from " << aName << " !" << endl;
 return NULL;
} 
#endif

//--
Agent2D::Agent2D(void) : Agent(),
                         Object2D()
{
 newAgent();

 _linearVelocityX=_linearVelocityY=_angularVelocity=0.0;
 _linearAccelerationX=_linearAccelerationY=_angularAcceleration=0.0;
}

//--
Agent2D::Agent2D(const Agent2D& anA) : Agent(anA),
                                       Object2D(anA)
{
 newAgent();
 _copy(anA);
}

//--
Agent2D& Agent2D::operator=(const Agent2D& anA)
{
 if (this != &anA)
 {
  Agent::operator=(anA);
  Object2D::operator=(anA);
  _destroy();
  _copy(anA);
 }
 return *this;
}

//--
Agent2D::~Agent2D(void)
{
 _destroy();
}

//--
void Agent2D::live(double dt)
{
 (void)dt; // Pour eviter un warning si pas utilise

 // "Comportement" d'un Agent de la classe Agent2D

 if (dt!=0.0) Kinematic(dt);
}

void Agent2D::Kinematic(double dt)
{
 if (_linearVelocityX==0 &&
     _linearVelocityY==0 &&
     _angularVelocity==0 &&
     _linearAccelerationX==0 &&
     _linearAccelerationY==0 &&
     _angularAcceleration==0)   return;

 double dt2=dt*dt;
 double xold,yold,thetaold;
 double xnew,ynew,thetanew;

 xold=yold=thetaold=0.0;

 xnew = 0.5*_linearAccelerationX*dt2 + _linearVelocityX*dt + xold;
 ynew = 0.5*_linearAccelerationY*dt2 + _linearVelocityY*dt + yold;
 thetanew = 0.5*_angularAcceleration*dt2 + _angularVelocity*dt + thetaold;

 _linearVelocityX += _linearAccelerationX*dt;
 _linearVelocityY += _linearAccelerationY*dt;
 _angularVelocity += _angularAcceleration*dt;

 localToGlobalPosition(xnew,ynew);
 thetanew = localToGlobalOrientation(thetanew);

 setLocation(xnew,ynew,thetanew);
}

//---------------------------------------------------------------------------
//     VELOCITY .... _linearVelocityX,_linearVelocityY,
//                   _angularVelocity
//---------------------------------------------------------------------------
void Agent2D::setLinearVelocityX(double xVelocity)
{
 _linearVelocityX = xVelocity;
}
void Agent2D::setLinearVelocityY(double yVelocity)
{
 _linearVelocityY = yVelocity;
}
void Agent2D::setAngularVelocity(double thetaVelocity)
{
 _angularVelocity = thetaVelocity;
}
void Agent2D::setVelocity(double xVelocity,double yVelocity,
                          double thetaVelocity)
{
 _linearVelocityX = xVelocity;
 _linearVelocityY = yVelocity;
 _angularVelocity = thetaVelocity;
}
//--
double Agent2D::getLinearVelocityX(void) const
{
 return _linearVelocityX;
}
double Agent2D::getLinearVelocityY(void) const
{
 return _linearVelocityY;
}
double Agent2D::getAngularVelocity(void) const
{
 return _angularVelocity;
}
void   Agent2D::getVelocity(double& xVelocity,double& yVelocity,
                            double& thetaVelocity) const
{
 xVelocity     = _linearVelocityX;
 yVelocity     = _linearVelocityY;
 thetaVelocity = _angularVelocity;
}

//---------------------------------------------------------------------------
//     ACCELERATION .... _linearAccelerationX,_linearAccelerationY,
//                       _angularAcceleration
//---------------------------------------------------------------------------

void  Agent2D::setLinearAccelerationX(double xAcceleration)
{
 _linearAccelerationX = xAcceleration;
}
void  Agent2D::setLinearAccelerationY(double yAcceleration)
{
 _linearAccelerationY = yAcceleration;
}
void  Agent2D::setAngularAcceleration(double thetaAcceleration)
{
 _angularAcceleration = thetaAcceleration;
}
void  Agent2D::setAcceleration(double xAcceleration,double yAcceleration,
                               double thetaAcceleration)
{
 _linearAccelerationX = xAcceleration;
 _linearAccelerationY = yAcceleration;
 _angularAcceleration = thetaAcceleration;
}

double Agent2D::getLinearAccelerationX(void) const
{
 return _linearAccelerationX;
}
double Agent2D::getLinearAccelerationY(void) const
{
 return _linearAccelerationY;
}
double Agent2D::getAngularAcceleration(void) const
{
 return _angularAcceleration;
}
void  Agent2D::getAcceleration(double& xAcceleration,double& yAcceleration,
                               double& thetaAcceleration) const
{
 xAcceleration     = _linearAccelerationX;
 yAcceleration     = _linearAccelerationY;
 thetaAcceleration = _angularAcceleration;
}

//--
bool operator==(const Agent2D& anA1, const Agent2D& anA2)
{
 return anA1.isEqualTo(anA2);
}

//--
bool operator!=(const Agent2D& anA1, const Agent2D& anA2)
{
 return !(anA1==anA2);
}

//--
ostream& operator<<(ostream& os, const Agent2D& anA)
{
 anA.display(os);
 return os;
}

//--
void Agent2D::display(ostream& os) const
{
 (void)os; // Pour eviter un warning si pas utilise

  Agent::display(os);
  Object2D::display(os);

 // ### : Affichage des attributs de la classe Agent2D
 // Exemple : os << _at;

 cout << "Velocity(x,y,theta): ("<< _linearVelocityX << "," <<
                                    _linearVelocityY << "," <<
                                    _angularVelocity << ")" << endl;
 cout << "Acceleration(x,y,theta): ("<< _linearAccelerationX << "," <<
                                        _linearAccelerationY << "," <<
                                        _angularAcceleration << ")" << endl;
}

//--
bool Agent2D::isEqualTo(const Agent2D& anA) const
{
 (void)anA; // Pour eviter un warning si pas utilise

 // ### : Test des attributs de la classe Agent2D
 // Exemple : if (_at != anA._at) return false;

  if (!(Agent::isEqualTo(anA))) return false;
  if (!(Object2D::isEqualTo(anA))) return false;

  if (_linearVelocityX != anA._linearVelocityX) return false;
  if (_linearVelocityY != anA._linearVelocityY) return false;
  if (_angularVelocity != anA._angularVelocity) return false;
  if (_linearAccelerationX != anA._linearAccelerationX) return false;
  if (_linearAccelerationY != anA._linearAccelerationY) return false;
  if (_angularAcceleration != anA._angularAcceleration) return false;
 return true;
}

//--
void Agent2D::_copy(const Agent2D& anA)
{
 (void)anA; // Pour eviter un warning si pas utilise

 // ### : Affectation des attributs de la classe Agent2D
 // Exemple : _at = anA._at;

 _linearVelocityX = anA._linearVelocityX;
 _linearVelocityY = anA._linearVelocityY;
 _angularVelocity = anA._angularVelocity;

 _linearAccelerationX = anA._linearAccelerationX;
 _linearAccelerationY = anA._linearAccelerationY;
 _angularAcceleration = anA._angularAcceleration;
}

//--
void Agent2D::_destroy(void)
{
 // ### : Destruction des attributs de la classe Agent2D
 // Exemple : delete _at;
}

//-- Interaction

void Agent2D::onSelection(void)
{
#if AGENT2D_SEE_CALLBACK_CALL
 cerr << getName() << ": button Press" << endl;
#endif
}

void Agent2D::onKeyPress(const char * key)
{
 (void)key;
#if AGENT2D_SEE_CALLBACK_CALL
 cerr << getName() << ": key Press <" << key << ">" << endl;
#endif
}

void Agent2D::onMouseDrag(double dx, double dy)
{
#if AGENT2D_SEE_CALLBACK_CALL
 cerr << getName() << ": mouse Drag <" << dx << "," << dy << ">" << endl,
#endif
 Object2D::onMouseDrag(dx,dy);
}


//-- Algos de perception...

bool Agent2D::isInside(double x, double y) const
{
 return Object2D::isInside(x,y);
}

bool Agent2D::intersectRay(double xRay, double yRay, double thetaRay,
                           double& xOut, double& yOut) const
{
 return Object2D::intersectRay(xRay,yRay,thetaRay,xOut,yOut);
}

/* throwRay : Lance un rayon devant l'objet *this
   (via les coordonnees et l'axe de l'objet2D *this)
    et retourne l'objet le plus proche (contenu dans vectAgent2D)
    On obtient egalement le point intersection.
*/
Agent2D * Agent2D::throwRay(double& xOut, double& yOut,
                            const vector<Agent2D*>& vectAgent2D) const
{
#if 1
 double xThis,yThis,thetaThis;

 unsigned int i, nbAgent2D=vectAgent2D.size();
 Agent2D *other, *found=NULL;

 double x,y,dx,dy,d,dmin=0.0;

 getLocation(xThis,yThis,thetaThis);

 for(i=0;i<nbAgent2D;i++)
 {
  other=vectAgent2D[i];

  if (other==this) continue;

  if (other->intersectRay(xThis,yThis,thetaThis,x,y))
  {
   dx=x-xThis;
   dy=y-yThis;
   d=dx*dx+dy*dy;
   if(!found||(d<dmin))
   {
    dmin=d;
    xOut=x;
    yOut=y;
    found=other;
   }
  }
 }
 return (found);
#else
 Object2D **tabObject2D;
 Object2D *found;
 unsigned int i, nbAgent2D=vectAgent2D.size();

 tabObject2D=(Object2D**)malloc(nbAgent2D*sizeof(Object2D*));
 if (tabObject2D==NULL)
 {
  cerr << "Agent2D::throwRay: Can't allocate memory... return NULL" << endl;
  return NULL;
 }

 for(i=0;i<nbAgent2D;i++)
 {
  tabObject2D[i]=(Object2D*)vectAgent2D[i];
 }

 found = Object2D::throwRay(xOut,yOut,tabObject2D,nbAgent2D);

 free(tabObject2D);

 return (Agent2D*)found;
#endif
}

/*
  Determine l'Agent2D d'un certain type (aClass) le plus proche et
  situe dans un cone de visibilite.

  Parametres
  E vision - l'angle d'ouverture du cone du champ de perception
  E range - la portee du cone du champ de perception
  E turn - l'orientation du champ par rapport a celui de l'Agent2D *this

  Valeur de retour
  S L'Agent2D le plus proche present dans le cone de perception ou NULL
    s'il n'y en a pas
*/
Agent2D * Agent2D::viewFirst(string aClass,
                             double vision,
                             double range,
                             double turn) const
{
 double v2=vision;
 v2=(v2 ? v2/2.0 : M_PI);
 range *= range;
 double x0,y0,theta0;
 getLocation(x0,y0,theta0);
 double a0=theta0+turn;
 double x,y;
 double d,a;
 const Agent2D * obj=(const Agent2D *)NULL;
 bool firstTime=true;
 double dMin=0.0;
 double aMin=0.0; (void)aMin;
 const Agent2D * objMin=(const Agent2D *)NULL;

 const set<Agent*> all_aClassObject = Scheduler::getAllAgents(aClass);
 set<Agent*>::const_iterator iter = all_aClassObject.begin();

 if (!(iter==all_aClassObject.end()))
 {
  if (!((*iter)->isA("Agent2D")))
  { cerr << "Agent2D::viewFirst" << ", class " << aClass
         << " is not a derived from Agent2D !" << endl;
    return 0;
  }
 }

 for(;!(iter==all_aClassObject.end());iter++)
   {
    obj=(const Agent2D *)(*iter);
    if(obj!=this)  // if(obj!=this && obj->_shape)
      {
      x = obj->getX() - x0;
      y = obj->getY() - y0;
      d=x*x+y*y;
      if((!range||d<range)&&(firstTime||d<dMin))
        {
        a=betweenPi(cartToAngle(x,y)-a0);
        if(::fabs(a)<=v2)
          {
          dMin=d;
          aMin=a;
          objMin=obj;
          firstTime=false;
          }
        }
      }
   }
 if(firstTime) // no Agent2D found
    {
    // angle = 0.0;
    // distance = 0.0;
    return (Agent2D*)NULL;
    }
  else
    {
    // angle = betweenPi(aMin-turn);
    // distance = ::sqrt(dMin);
    return (Agent2D*)objMin;
    }
}

/* 
  Retourne le nombre d'Agent2D d'un type particulier (aClass) presents
  dans le cone de vision

  Les Agent2D* sont places dans vectAgent2D.
*/
int Agent2D::view(string aClass, vector<Agent2D*>& vectAgent2D,
                  double vision,
                  double range,
                  double turn) const
{
 vectAgent2D.clear();
 double v2=vision;
 v2=(v2 ? v2/2.0 : M_PI);
 range *= range;
 double x0,y0,theta0;
 getLocation(x0,y0,theta0);
 double a0=theta0+turn;
 double x,y;
 double d,a;
 const Agent2D * obj = (const Agent2D *)NULL;

 const set<Agent*> all_aClassObject = Scheduler::getAllAgents(aClass);
 set<Agent*>::const_iterator iter = all_aClassObject.begin();

 if (!(iter==all_aClassObject.end()))
 {
  if (!((*iter)->isA("Agent2D")))
  { cerr << "Agent2D::view" << ", class " << aClass
         << " is not a derived from Agent2D !" << endl;
    return 0;
  }
 }

 for(;!(iter==all_aClassObject.end());iter++)
   {
    obj=(const Agent2D *)(*iter);
    if(obj!=this)  // if(obj!=this && obj->_shape)
    {
     x = obj->getX() - x0;
     y = obj->getY() - y0;
     d=x*x+y*y;
     if(!range||d<range)
       {
       a=betweenPi(cartToAngle(x,y)-a0);
       if(::fabs(a)<=v2)
         {
          vectAgent2D.push_back((Agent2D *)obj);
         }
       }
    }
   }
 return vectAgent2D.size();
}

//--
Agent2D * Agent2D::viewFirstAgent2D(double vision,
                                    double range,
                                    double turn) const
{
 return viewFirst("Agent2D",vision,range,turn);
}

//--
int       Agent2D::viewAgent2D(vector<Agent2D*>& vectAgent2D,
                               double vision,
                               double range,
                               double turn) const
{
 return view("Agent2D",vectAgent2D,vision,range,turn);
}

//------------- Interface avec appli graphique -------------

//--
void
graphic_selectCallback(Object2D * obj2d,
                       void * userData)
{
#if AGENT2D_SEE_CALLBACK_CALL
cerr << "------------------------------------------->" << endl;
cerr << "In Agent2D.cpp, begin graphic_selectCallBack" << endl;
#endif

 Agent2D* agt2d = (Agent2D*)obj2d;
 graphic_selectCallback(agt2d,userData);

#if AGENT2D_SEE_CALLBACK_CALL
cerr << "In Agent2D.cpp, end   graphic_selectCallBack" << endl;
cerr << "<-------------------------------------------" << endl;
#endif
}

void
graphic_keyPressCallback(Object2D * obj2d,
                         const char * key,
                         void * userData)
{
#if AGENT2D_SEE_CALLBACK_CALL
cerr << "--------------------------------------------->" << endl;
cerr << "In Agent2D.cpp, begin graphic_keyPressCallBack" << endl;
#endif

 Agent2D* agt2d = (Agent2D*)obj2d;
 graphic_keyPressCallback(agt2d,key,userData);

#if AGENT2D_SEE_CALLBACK_CALL
cerr << "In Agent2D.cpp, end   graphic_keyPressCallBack" << endl;
cerr << "--------------------------------------------->" << endl;
#endif
}
//--
void
graphic_mouseDragCallback(Object2D * obj2d,
                          double dx,
                          double dy,
                          void * userData)
{
#if AGENT2D_SEE_CALLBACK_CALL
cerr << "---------------------------------------------->" << endl;
cerr << "In Agent2D.cpp, begin graphic_mouseDragCallBack" << endl;
#endif

 Agent2D* agt2d = (Agent2D*)obj2d;
 graphic_mouseDragCallback(agt2d,dx,dy,userData);

#if AGENT2D_SEE_CALLBACK_CALL
cerr << "In Agent2D.cpp, end   graphic_mouseDragCallBack" << endl;
cerr << "<----------------------------------------------" << endl;
#endif
}
