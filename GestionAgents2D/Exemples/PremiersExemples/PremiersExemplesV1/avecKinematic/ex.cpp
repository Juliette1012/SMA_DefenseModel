/*----------------------------------------------------------------------------
  graphTest.cpp
----------------------------------------------------------------------------*/

#include "Agent2D.h"
#include "Rond.h"

#include <string.h>

/*-------- Application -----------------------------------------------------*/

/*---- application specific data ----*/

#include "AppliData.h"

/*
#ifndef _APPLIDATA_H
#define _APPLIDATA_H

#include "Agent2D.h"

typedef struct
{
Scheduler* sched;
double     squareSize;
Agent2D*   square;
int    autoscale;
int    pause;
} AppliData;

#endif // _APPLIDATA_H
*/

void deleteAppliData(AppliData * data)
{
 delete(data->square);
 delete(data->sched);

 delete(data);
}

void help(void)
{
 cout << "****************************************"<< endl;
 cout << "help"                                    << endl;
 cout << "----"                                    << endl;
 cout << "Actions clavier SANS objet selectionne:" << endl;
 cout << "- h : help"                              << endl;
 cout << "- a : autoscale (oui/non)"               << endl;
 cout << "-' ': pause     (oui/non)"               << endl;
 cout << "- q : quitter"                           << endl;
 cout << "- r : creation d'un rond"                << endl;
 cout << "Actions clavier AVEC objet selectionne:" << endl;
 cout << "- d : destruction d'un objet"            << endl;      
 cout << "****************************************"<< endl;
}

int
main(void)
{
AppliData * data;

/*---- initialize random generator ----*/

initRandom();

/*---- initialize graphic window ----*/

graphic_init("My Window","-*-helvetica-*-r-normal--14-*");
graphic_setWidth(640);
graphic_setHeight(480);
graphic_setBackground("cyan4");

/*---- initialize application specific data ----*/

data=(AppliData *)malloc(sizeof(AppliData));
data->sched=new Scheduler;
data->sched->setRandomMode(true);
data->sched->setRealTimeMode(true);

/*---- initialize Agent2D  ----*/

data->squareSize=100.0;
data->square = new Agent2D();
  {
  data->square->square(data->squareSize,0);
  data->square->setColor("white");
  data->square->setLayer(2);
  }

new Rond(5,data);

/*----- initialize specific data -----*/

data->autoscale=0;
data->pause=0;

/*---- run the graphic application ----*/

help();

graphic_run(data);
return(0);
}

void
graphic_mainLoop(void * userData)
{
AppliData * data=(AppliData *)userData;
if(!data->pause)
  {

  data->sched->cycle();

  }
if(data->autoscale)
  {
  graphic_autoscale();
  }
}

void
graphic_selectCallback(Agent2D * agt2d,
                       void * userData)
{
AppliData * data=(AppliData *)userData;
(void)agt2d;(void)data;

 if (agt2d==NULL) return; // No sens !

 agt2d->onSelection();
}

void
graphic_keyPressCallback(Agent2D * agt2d,
                         const char * key,
                         void * userData)
{
AppliData * data=(AppliData *)userData;

if (agt2d==NULL)         /* Interaction clavier SANS objet selectionne */
{
 if(!strcmp(key,"h")||!strcmp(key,"H"))
  {
  help();
  }
 else
 if(!strcmp(key,"a")||!strcmp(key,"A"))
  {
  data->autoscale=1-data->autoscale;
  }
 else
 if(!strcmp(key," "))
  {
  data->pause=1-data->pause;
  }
 else
 if(!strcmp(key,"q")||!strcmp(key,"Q")||!strcmp(key,"\x1b")) /* Esc */
  {
  deleteAppliData(data);
  exit(0);
  }
 else
 if(!strcmp(key,"r")||!strcmp(key,"R"))
  {
   new Rond(5,data);
   //new Rond(1,data);
  }
 else { fprintf(stderr,"Viewer key <%s>\n",key); }
 return;
}

        /*  ET donc ici, interaction clavier AVEC un objet selectionne */

agt2d->onKeyPress(key);
}

void
graphic_mouseDragCallback(Agent2D * agt2d,
                          double dx,
                          double dy,
                          void * userData)
{
AppliData * data=(AppliData *)userData;

if(agt2d==data->square)
  {
  return; /* avoid interaction with these objects */
  }

agt2d->onMouseDrag(dx,dy);
}

/*--------------------------------------------------------------------------*/
