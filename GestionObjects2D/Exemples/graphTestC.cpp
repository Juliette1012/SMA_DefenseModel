/*----------------------------------------------------------------------------
  graphTestC.c
----------------------------------------------------------------------------*/

#include "CObject2D.h"

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
Object2D_setColor(obj2d,data->colors[colorNumber%data->nbColors]);
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
    Object2D_point(obj2d);
    }
    break;
  case 1:
    {
    Object2D_text(obj2d,"Text");
    }
    break;
  case 2:
    {
    Object2D_line(obj2d,0.2);
    }
    break;
  case 3:
    {
    Object2D_square(obj2d,0.2,0);
    }
    break;
  case 4:
    {
    Object2D_square(obj2d,0.2,1);
    }
    break;
  case 5:
    {
    Object2D_rectangle(obj2d,0.2,0.1,0);
    }
    break;
  case 6:
    {
    Object2D_rectangle(obj2d,0.2,0.1,1);
    }
    break;
  case 7:
    {
    double x[]={-0.15,0.1,-0.15};
    double y[]={-0.1,0.0,0.1};
    Object2D_polyline(obj2d,3,x,y);
    }
    break;
  case 8:
    {
    double x[]={-0.15,0.1,-0.15,-0.05};
    double y[]={-0.1,0.0,0.1,0.0};
    Object2D_polygon(obj2d,4,x,y,0);
    }
    break;
  case 9:
    {
    double x[]={-0.15,0.1,-0.15,-0.05};
    double y[]={-0.1,0.0,0.1,0.0};
    Object2D_polygon(obj2d,4,x,y,1);
    }
    break;
  case 10:
    {
    Object2D_circle(obj2d,0.1,0);
    }
    break;
  case 11:
    {
    Object2D_circle(obj2d,0.1,1);
    }
    break;
  case 12:
    {
    if(!Object2D_image(obj2d,"fish.bmp",0.02))
      {
      fprintf(stderr,"Can't load image !!!\n");
      }
    }
    break;
  case 13:
    {
    Object2D_noShape(obj2d);
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

if (o1!=NULL) Object2D_delete(o1);
if (o2!=NULL) Object2D_delete(o2);
if (o3!=NULL) Object2D_delete(o3);
if (o4!=NULL) Object2D_delete(o4);

//-------------------------------

o1 = Object2D_new();
o2 = Object2D_new();
o3 = Object2D_new();
o4 = Object2D_new();

Object2D_translate(o1,1,1);
Object2D_translate(o2,2,2);
Object2D_translate(o3,3,3);
Object2D_translate(o4,4,4);

Object2D_attachTo(o1,o2);
Object2D_attachTo(o2,o3);
Object2D_attachTo(o3,o4);
Object2D_attachTo(o4,o1);

Object2D_square(o1,1,1); Object2D_setColor(o1,"red");
Object2D_square(o2,1,1); Object2D_setColor(o2,"green");
Object2D_square(o3,1,1); Object2D_setColor(o3,"cyan");
Object2D_square(o4,1,1); Object2D_setColor(o4,"yellow");

//-------------------------------
}

void testViewObject2D(AppliData * data)
{
 double range = data->viewRadius;

 Object2D** v;
 int i, nbObj2D;

 nbObj2D = Object2D_viewObject2D(data->yellowCircle,&v,2*M_PI,range,0.0);

 for(i=0;i<nbObj2D;i++)
 {
  if (v[i]!=data->frame && v[i]!=data->frame2)
  {
   v[i]->setColor("yellow");
  }
 }

 free(v);  /* Important (autrement, il y a une fuite memoire !) */
}

void testViewFirstObject2D(AppliData * data)
{
 double range = data->viewRadius;

 Object2D* first;

 first = Object2D_viewFirstObject2D(data->redCircle,2*M_PI,range,0.0);

 if (first && first!=data->frame && first!=data->frame2)
 {
  first->setColor("red");
 }
}

void freeAppliData(AppliData * data)
{
 unsigned int i;

 Object2D_delete(data->frame2);
 Object2D_delete(data->frame);
 Object2D_delete(data->back);
 Object2D_delete(data->cursor);
 Object2D_delete(data->message);
 Object2D_delete(data->target);

 Object2D_delete(data->redCircle);
 Object2D_delete(data->yellowCircle);

 for(i=0;i<data->nbObj;i++)
 {
  Object2D_delete(data->obj[i]);
 }

 free(data->obj);
 free(data->colors);

 free(data);
}

void help(void)
{
 printf("******************************************\n");
 printf("help\n");
 printf("----\n");
 printf("Actions clavier SANS objet selectionne:\n");
 printf("- h : help\n");
 printf("- a : autoscale (oui/non)\n");
 printf("-' ': pause     (oui/non)\n");
 printf("- q : quitter\n");
 printf("- t : test de attachTo\n");
 printf("- v : rendre visible des objets invisibles\n");
 printf("Actions clavier AVEC objet selectionne:\n");
 printf("- c : changer la couleur d'un objet\n");
 printf("- s : changer la forme (shape) d'un objet\n");
 printf("- k : kopier un objet\n");
 printf("******************************************\n");
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

data=(AppliData *)malloc(sizeof(AppliData));
data->nbShapes=14;
data->nbColors=12;
data->colors=(const char **)malloc(data->nbColors*sizeof(char *));
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
data->obj=(Object2D **)malloc(data->nbObj*sizeof(Object2D *));
for(i=0;i<data->nbObj;i++)
  {
  data->obj[i]= Object2D_new();
  if(i)
    {
    changeShape(data->obj[i],data,9);
    Object2D_setLayer(data->obj[i],1);
    changeColor(data->obj[i],data,integerRand(data->nbColors));
    }
  else
    {
    changeShape(data->obj[i],data,12);  /* Le 1er, c'est le poisson */
    }
  Object2D_rotate(data->obj[i],0.25*i);
  Object2D_translate(data->obj[i],0.25*i,0.0);
  }

data->viewRadius   = 1.0;
data->yellowCircle = Object2D_new();
  {
  Object2D_circle(data->yellowCircle,data->viewRadius,0);
  Object2D_setColor(data->yellowCircle,"yellow");
  Object2D_setLocation(data->yellowCircle,-6.9,-5.0,0.0);
  }
data->redCircle    = Object2D_new();
  {
  Object2D_circle(data->redCircle,data->viewRadius,0);
  Object2D_setColor(data->redCircle,"red");
  Object2D_setLocation(data->redCircle,-6.9,-3.0,0.0);
  }

data->target = Object2D_new();
  {
  Object2D_setColor(data->target,"red");
  Object2D_setLayer(data->target,2);
  }

data->message = Object2D_new();
  {
  Object2D_setLayer(data->message,-1);
  Object2D_setLocation(data->message,-7.9,6.75,0.0);
  }

data->cursor = Object2D_new();
  {
  double x[]={0.0,0.15,0.0,-0.15};
  double y[]={-0.5,0.0,0.5,0.0};
  Object2D_setLayer(data->cursor,-1);
  Object2D_setColor(data->cursor,"yellow");
  Object2D_polygon(data->cursor,4,x,y,1);
  Object2D_setLocation(data->cursor,0,-6.5,0.0);
  }

data->back = Object2D_new();
  {
  if(!Object2D_image(data->back,"back.bmp",0.1))
    {
    fprintf(stderr,"Can't load image !!!\n");
    }
  Object2D_setLayer(data->back,-1);
  Object2D_setY(data->back,-0.5*(12-7.9));
  }

data->frame = Object2D_new();
  {
  Object2D_rectangle(data->frame,15.8,12,1);
  Object2D_setColor(data->frame,"blue");
  Object2D_setLayer(data->frame,-2);
  }

data->frame2 = Object2D_new();
  {
  Object2D_rectangle(data->frame2,17.8,14,1);
  Object2D_setColor(data->frame2,"black");
  Object2D_setLayer(data->frame2,-3);
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
  Object2D_rotate(data->obj[0],
                  -5e-3*dt*Object2D_getX(data->cursor)/data->maxCursor);
  Object2D_getLocation(data->obj[0],&x,&y,&th);
  if(Object2D_intersectRay(data->frame,x,y,th,&xInter,&yInter))
    {
    Object2D_translate(data->obj[0],data->speed*dt,0.0);
    Object2D_circle(data->target,0.1,1);
    Object2D_setLocation(data->target,xInter,yInter,0.0);
    }
  else /* stop when not facing the aquarium */
    {
    Object2D_point(data->target);
    Object2D_text(data->message,"Boom !!!");
    Object2D_setColor(data->message,"red");
    message=1;
    }
  Object2D_getLocation(data->obj[0],&x,&y,&th);
  if(Object2D_getImagePixelAt(data->back,x,y,&r,&g,&b)&& /* can read pixel */
     ((r!=0)||(g!=0)||(b!=255)))                         /* but not blue */
    {
    char buffer[0x100];
    sprintf(buffer,"Ouch ... my scales !!! (%d/%d/%d)",r,g,b);
    Object2D_text(data->message,buffer);
    Object2D_setColor(data->message,"orange");
    message=1;
    }
  if(!message)
    {
    Object2D_text(data->message,"OK ...");
    Object2D_setColor(data->message,"green");
    }
  for(i=1;i<data->nbObj;i++)
    {
    Object2D_getLocation(data->obj[i-1],&x,&y,&th);
    Object2D_globalToLocalPosition(data->obj[i],&x,&y);
    cartesianToPolar(x,y,&d,&th);
    d-=0.25; /* distance between objects */
    if(d>0.0)
      {
      double step=data->maxSpeed*dt;
      Object2D_rotate(data->obj[i],th); /* face the preceding object */
      if(d<1.0) step*=d*d; /* slow down */
      if(step>d) step=d; /* stay behind the preceding object */
      Object2D_translate(data->obj[i],step,0.0);
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
  freeAppliData(data);
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
    if ((Object2D_getColor(data->obj[i]))==NULL)
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
if(!strcmp(key,"d")||!strcmp(key,"D"))
  {
   Object2D_newCopy(obj2d);  /* Test de la copie... ici, pointeur non stocke */
   return;
  }

Object2D_onKeyPress(obj2d,key);
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

Object2D_onMouseDrag(obj2d,dx,dy);
}

/*--------------------------------------------------------------------------*/
