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
