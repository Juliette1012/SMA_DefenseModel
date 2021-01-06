#ifndef _APPLIDATA_H
#define _APPLIDATA_H

#include "Object2D.h"
#include "Agent2D.h"

typedef struct
{
Scheduler* sched;
unsigned int nbShapes;
unsigned int nbColors;
const char ** colors;
unsigned int nbObj;
Agent2D ** obj;
double     viewRadius;
Agent2D  * yellowCircle;
Agent2D  * redCircle;
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
} AppliData;

#endif
