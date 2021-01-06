/*----------------------------------------------------------------------------
  graphTest.cpp
----------------------------------------------------------------------------*/

#include "Object2D.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/time.h>

/*-------- Utilities -------------------------------------------------------*/

unsigned long /* current time in milliseconds */
getTime(void)
{
struct timeval tv;
gettimeofday(&tv,(struct timezone *)0);
return(tv.tv_sec*1000+tv.tv_usec/1000);
}

void initRand(void)
{
srand(getTime());
}

unsigned int /* random value in [ 0 ; n-1 ]   */
integerRand(int n)
{
return(rand()%n);
}

double       /* random value in [ 0.0 ; 1.0 ] */
realRand(void)
{
return(rand()/(double)RAND_MAX);
}

/*-------- Application -----------------------------------------------------*/

/*---- application specific data ----*/
typedef struct
{
unsigned int nbShapes;
unsigned int nbColors;
const char ** colors;
unsigned int nbObj;
Object2D ** obj;
double     viewRadius;
Object2D * yellowCircle;
Object2D * redCircle;
Object2D * target;
Object2D * message;
Object2D * cursor;
Object2D * back;
Object2D * frame;
Object2D * frame2;
double speed;
double maxSpeed;
double maxCursor;
int    autoscale;
int    pause;
unsigned long time;
} AppliData;

void
changeColor(Object2D * obj2d,
            AppliData * data,
            int colorNumber)
{
obj2d->setColor(data->colors[colorNumber%data->nbColors]);
}

void
changeShape(Object2D * obj2d,
            AppliData * data,
            int shapeNumber)
{
switch(shapeNumber%data->nbShapes)
  {
  case 0:
    {
    obj2d->point();
    }
    break;
  case 1:
    {
    obj2d->text("Text");
    }
    break;
  case 2:
    {
    obj2d->line(0.2);
    }
    break;
  case 3:
    {
    obj2d->square(0.2,0);
    }
    break;
  case 4:
    {
    obj2d->square(0.2,1);
    }
    break;
  case 5:
    {
    obj2d->rectangle(0.2,0.1,0);
    }
    break;
  case 6:
    {
    obj2d->rectangle(0.2,0.1,1);
    }
    break;
  case 7:
    {
    double x[]={-0.15,0.1,-0.15};
    double y[]={-0.1,0.0,0.1};
    obj2d->polyline(3,x,y);
    }
    break;
  case 8:
    {
    double x[]={-0.15,0.1,-0.15,-0.05};
    double y[]={-0.1,0.0,0.1,0.0};
    obj2d->polygon(4,x,y,0);
    }
    break;
  case 9:
    {
    double x[]={-0.15,0.1,-0.15,-0.05};
    double y[]={-0.1,0.0,0.1,0.0};
    obj2d->polygon(4,x,y,1);
    }
    break;
  case 10:
    {
    obj2d->circle(0.1,0);
    }
    break;
  case 11:
    {
    obj2d->circle(0.1,1);
    }
    break;
  case 12:
    {
    if(!obj2d->image("fish.bmp",0.02))
      {
      fprintf(stderr,"Can't load image !!!\n");
      }
    }
    break;
  case 13:
    {
    obj2d->noShape();
    }
    break;
  }
}

void testAttachTo(void)
{
static Object2D *o1 = NULL;
static Object2D *o2 = NULL;
static Object2D *o3 = NULL;
static Object2D *o4 = NULL;

if (o1!=NULL) delete o1;
if (o2!=NULL) delete o2;
if (o3!=NULL) delete o3;
if (o4!=NULL) delete o4;

//-------------------------------

o1 = new Object2D();
o2 = new Object2D();
o3 = new Object2D();
o4 = new Object2D();

o1->translate(1,1);
o2->translate(2,2);
o3->translate(3,3);
o4->translate(4,4);

o1->attachTo(*o2);
o2->attachTo(*o3);
o3->attachTo(*o4);
o4->attachTo(*o1);

o1->square(1,1); o1->setColor("red");
o2->square(1,1); o2->setColor("green");
o3->square(1,1); o3->setColor("cyan");
o4->square(1,1); o4->setColor("yellow");

//-------------------------------
}

void testViewObject2D(AppliData * data)
{
 double range = data->viewRadius;

 vector<Object2D*> v;
 int i, nbObj2D;

 nbObj2D = data->yellowCircle->viewObject2D(v,2*M_PI,range);

 for(i=0;i<nbObj2D;i++)
 {
  if (v[i]!=data->frame && v[i]!=data->frame2)
  {
   v[i]->setColor("yellow");
  }
 }
}

void testViewFirstObject2D(AppliData * data)
{
 double range = data->viewRadius;

 Object2D* first;

 first = data->redCircle->viewFirstObject2D(2*M_PI,range);

 if (first && first!=data->frame && first!=data->frame2)
 {
  first->setColor("red");
 }
}

void deleteAppliData(AppliData * data)
{
 unsigned int i;

 delete(data->frame2);
 delete(data->frame);
 delete(data->back);
 delete(data->cursor);
 delete(data->message);
 delete(data->target);

 delete(data->redCircle);
 delete(data->yellowCircle);

 for(i=0;i<data->nbObj;i++)
 {
  delete(data->obj[i]);
 }

 delete[](data->obj);
 delete[](data->colors);

 delete(data);
}

void help(void)
{
 cout << "******************************************"<< endl;
 cout << "help"                                      << endl;
 cout << "----"                                      << endl;
 cout << "Actions clavier SANS objet selectionne:"   << endl;
 cout << "- h : help"                                << endl;
 cout << "- a : autoscale (oui/non)"                 << endl;
 cout << "-' ': pause     (oui/non)"                 << endl;
 cout << "- q : quitter"                             << endl;
 cout << "- t : test de attachTo"                    << endl;
 cout << "- v : rendre visible des objets invisibles"<< endl;
 cout << "Actions clavier AVEC objet selectionne:"   << endl;
 cout << "- c : changer la couleur d'un objet"       << endl;
 cout << "- s : changer la forme (shape) d'un objet" << endl;
 cout << "- k : kopier un objet"                     << endl;
 cout << "******************************************"<< endl;
}

int
main(void)
{
unsigned int i;
AppliData * data;

/*---- initialize random generator ----*/

initRand();

/*---- initialize graphic window ----*/

graphic_init("My Window","-*-helvetica-*-r-normal--14-*");
graphic_setWidth(640);
graphic_setHeight(480);
graphic_setBackground("cyan4");

/*---- initialize application specific data ----*/

data= new AppliData;
data->nbShapes=14;
data->nbColors=12;
data->colors= new const char* [data->nbColors];
data->colors[0]="white";
data->colors[1]="red";
data->colors[2]="green";
data->colors[3]="blue";
data->colors[4]="yellow";
data->colors[5]="magenta";
data->colors[6]="orange";
data->colors[7]="brown";
data->colors[8]="light grey";
data->colors[9]="dark grey";
data->colors[10]="black";
data->colors[11]="pink";

data->nbObj=30;
data->obj= new Object2D* [data->nbObj];
for(i=0;i<data->nbObj;i++)
  {
  data->obj[i]= new Object2D();
  if(i)
    {
    changeShape(data->obj[i],data,9);
    data->obj[i]->setLayer(1);
    changeColor(data->obj[i],data,integerRand(data->nbColors));
    }
  else
    {
    changeShape(data->obj[i],data,12);  /* Le 1er, c'est le poisson */
    }
  data->obj[i]->rotate(0.25*i);
  data->obj[i]->translate(0.25*i,0.0);
  }

data->viewRadius   = 1.0;
data->yellowCircle = new Object2D();
  {
  data->yellowCircle->circle(data->viewRadius,0);
  data->yellowCircle->setColor("yellow");
  data->yellowCircle->setLocation(-6.9,-5.0,0.0);
  }
data->redCircle    = new Object2D();
  {
  data->redCircle->circle(data->viewRadius,0);
  data->redCircle->setColor("red");
  data->redCircle->setLocation(-6.9,-3.0,0.0);
  }

data->target = new Object2D();
  {
  data->target->setColor("red");
  data->target->setLayer(2);
  }

data->message = new Object2D();
  {
  data->message->setLayer(-1);
  data->message->setLocation(-7.9,6.75,0.0);
  }

data->cursor = new Object2D();
  {
  double x[]={0.0,0.15,0.0,-0.15};
  double y[]={-0.5,0.0,0.5,0.0};
  data->cursor->setLayer(-1);
  data->cursor->setColor("yellow");
  data->cursor->polygon(4,x,y,1);
  data->cursor->setLocation(0,-6.5,0.0);
  }

data->back = new Object2D();
  {
  if(!data->back->image("back.bmp",0.1))
    {
    fprintf(stderr,"Can't load image !!!\n");
    }
  data->back->setLayer(-1);
  data->back->setY(-0.5*(12-7.9));
  }

data->frame = new Object2D();
  {
  data->frame->rectangle(15.8,12,1);
  data->frame->setColor("blue");
  data->frame->setLayer(-2);
  }

data->frame2 = new Object2D();
  {
  data->frame2->rectangle(17.8,14,1);
  data->frame2->setColor("black");
  data->frame2->setLayer(-3);
  }

/*----- initialize specific data -----*/
  
data->speed=1e-3;
data->maxSpeed=1e-2;
data->maxCursor=7.9;
data->autoscale=1;
data->pause=0;
data->time=getTime();

/*---- run the graphic application ----*/

help();

graphic_run(data);
return(0);
}

void
graphic_mainLoop(void * userData)
{
unsigned int i;
int r,g,b;
AppliData * data=(AppliData *)userData;
unsigned long dt=getTime()-data->time;
data->time+=dt;
if(!data->pause)
  {
  double x,y,th,d;
  double xInter,yInter;
  int message=0;
  data->obj[0]->rotate(-5e-3*dt*data->cursor->getX()/data->maxCursor);
  data->obj[0]->getLocation(x,y,th);
  if(data->frame->intersectRay(x,y,th,xInter,yInter))
    {
    data->obj[0]->translate(data->speed*dt,0.0);
    data->target->circle(0.1,1);
    data->target->setLocation(xInter,yInter,0.0);
    }
  else /* stop when not facing the aquarium */
    {
    data->target->point();
    data->message->text("Boom !!!");
    data->message->setColor("red");
    message=1;
    }
  data->obj[0]->getLocation(x,y,th);
  if(data->back->getImagePixelAt(x,y,r,g,b)&& /* can read pixel */
     ((r!=0)||(g!=0)||(b!=255)))              /* but not blue   */
    {
    char buffer[0x100];
    sprintf(buffer,"Ouch ... my scales !!! (%d/%d/%d)",r,g,b);
    data->message->text(buffer);
    data->message->setColor("orange");
    message=1;
    }
  if(!message)
    {
    data->message->text("OK ...");
    data->message->setColor("green");
    }
  for(i=1;i<data->nbObj;i++)
    {
    data->obj[i-1]->getLocation(x,y,th);
    data->obj[i]->globalToLocalPosition(x,y);
    cartesianToPolar(x,y,&d,&th);
    d-=0.25; /* distance between objects */
    if(d>0.0)
      {
      double step=data->maxSpeed*dt;
      data->obj[i]->rotate(th); /* face the preceding object */
      if(d<1.0) step*=d*d; /* slow down */
      if(step>d) step=d; /* stay behind the preceding object */
      data->obj[i]->translate(step,0.0);
      }
    }
  }
if(data->autoscale)
  {
  graphic_autoscale();
  }

  testViewObject2D(data);
  testViewFirstObject2D(data);
}

void
graphic_selectCallback(Object2D * obj2d,
                       void * userData)
{
 AppliData * data=(AppliData *)userData;
 (void)obj2d;(void)data;

 if (obj2d==NULL) return; // No sens !


 obj2d->onSelection();
}

void
graphic_keyPressCallback(Object2D * obj2d,
                         const char * key,
                         void * userData)
{
AppliData * data=(AppliData *)userData;

if((obj2d==data->target)||
   (obj2d==data->message)||
   (obj2d==data->back)||
   (obj2d==data->frame)||
   (obj2d==data->frame2))
  {
  return; /* avoid interaction with these objects */
  }

if (obj2d==NULL)         /* Interaction clavier SANS objet selectionne */
{
 if(!strcmp(key,"Left"))
  {
  graphic_mouseDragCallback(data->cursor,
                            -0.5,0.0,userData); /* simulate mouse drag */
  }
 else if(!strcmp(key,"Right"))
  {
  graphic_mouseDragCallback(data->cursor,
                            0.5,0.0,userData); /* simulate mouse drag */
  }
 else if(!strcmp(key,"Up"))
  {
  data->speed+=1e-4;
  if(data->speed>data->maxSpeed) data->speed=data->maxSpeed;
  }
 else if(!strcmp(key,"Down"))
  {
  data->speed-=1e-4;
  if(data->speed<0.0) data->speed=0.0;
  }
 else if(!strcmp(key,"h")||!strcmp(key,"H"))
  {
  help();
  }
 else if(!strcmp(key,"a")||!strcmp(key,"A"))
  {
  data->autoscale=1-data->autoscale;
  }
 else if(!strcmp(key," "))
  {
  data->pause=1-data->pause;
  }
 else if(!strcmp(key,"q")||!strcmp(key,"Q")||!strcmp(key,"\x1b")) /* Esc */
  {
  deleteAppliData(data);
  exit(0);
  }
 else if(!strcmp(key,"t")||!strcmp(key,"T"))
  {
  testAttachTo();                       /* test de attachTo     */
  }
 else if(!strcmp(key,"v")||!strcmp(key,"V"))
  {
   unsigned int i;
   for(i=0;i<data->nbObj;i++)
   {
    if (data->obj[i]->getColor()==NULL) 
    {                                   /* Object invisible     */
     changeShape(data->obj[i],data,3);  /* => Le rendre visible */
    }
   }
  }
 else { fprintf(stderr,"Viewer key <%s>\n",key); }
 return;
}

        /*  ET donc ici, interaction clavier AVEC un objet selectionne */

if(!strcmp(key,"c")||!strcmp(key,"C"))
  {
   changeColor(obj2d,data,integerRand(data->nbColors));
   return;
  }
if(!strcmp(key,"s")||!strcmp(key,"S"))
  {
   changeShape(obj2d,data,integerRand(data->nbShapes));
   return;
  }
if(!strcmp(key,"k")||!strcmp(key,"K"))
  {
   new Object2D(*obj2d);  /* Test de la copie... ici, pointeur non stocke */
   return;
  }

obj2d->onKeyPress(key);
}

void
graphic_mouseDragCallback(Object2D * obj2d,
                          double dx,
                          double dy,
                          void * userData)
{
double x,y,theta;
AppliData * data=(AppliData *)userData;

if((obj2d==data->target)||
   (obj2d==data->message)||
   (obj2d==data->back)||
   (obj2d==data->frame)||
   (obj2d==data->frame2))
  {
  return; /* avoid interaction with these objects */
  }

if(obj2d==data->cursor)   /* Cas particulier: interaction avec le curseur */
  {
   obj2d->getLocation(x,y,theta);
   x+=dx;
   if(x>data->maxCursor) x=data->maxCursor;
   else if(x<-data->maxCursor) x=-data->maxCursor;
   obj2d->setLocation(x,y,theta);
   return;
  }

obj2d->onMouseDrag(dx,dy);
}

/*--------------------------------------------------------------------------*/
