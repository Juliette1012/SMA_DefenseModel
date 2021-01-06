#include "Decor.h"

Decor decor;       // Contient uniquement des Object2D pas des Agent2D !

void addDecor(Object2D* obj2d)
{
 decor.insert(obj2d);
}
void removeDecor(Object2D* obj2d)
{
 decor.erase(obj2d);
}
bool isInDecor(Object2D* obj2d)
{
 set<Object2D*>::iterator foundObj = decor.find(obj2d);
 if (foundObj==decor.end()) return false;
 else                       return true;
}
