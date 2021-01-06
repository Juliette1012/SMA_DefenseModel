#ifndef _APPLIDATA_H
#define _APPLIDATA_H

#include "Agent2D.h"
#include "Environnement.h"

typedef struct
{
Scheduler*     sched;
Environnement* env;
int    autoscale;
int    pause;
} AppliData;

#endif // _APPLIDATA_H
