       // Source d'inspiration :
       // http://student.kuleuven.be/~m0216922/CG/floodfill.html 

#include <iostream>

using namespace std;

#include "Image.h"

///////////////
// The stack //
///////////////

#define STLSTACK

#ifdef STLSTACK
//------- STL ------------
#include <stack>
static stack<int> theStack;
//------------------------
#else
//-------- C -------------
#define stackSize 16777216
static int theStack[stackSize];
static int stackPointer=0;
//------------------------
#endif

static int h=0; // modifie dans floodFillScanlineStack

#ifdef STLSTACK
//------- STL ------------
static
bool pop(int &x, int &y)
{
 if (theStack.empty()) return false;

 int p = theStack.top(); theStack.pop();
 x = p / h;
 y = p % h;
 return true;
}

static
bool push(int x, int y)
{
 theStack.push(h * x + y);
 return true;
}

static
void emptyStack(void)
{
 int x, y; while (pop(x,y)); // theStack.clear();
}
//------------------------
#else
//-------- C -------------
static
bool pop(int &x, int &y)
{
 if (stackPointer<=0) return false;

 int p = theStack[--stackPointer];
 x = p / h;
 y = p % h;
 return true;
}   
 
static
bool push(int x, int y)
{
 if (stackPointer>=stackSize) return false;

 theStack[stackPointer++] = h * x + y;
 return true;
}    

static
void emptyStack(void)
{
 stackPointer=0; // int x, y; while (pop(x,y));
}
//------------------------
#endif

//////////////////////////////////////////////////////////
// Remplissage de la forme se trouvant dans l'image im. //
// x et y doivent etre a l'interieur de la forme.       //
//////////////////////////////////////////////////////////
void floodFillScanlineStack(Image& im,
                            int row,
                            int col,
                            octet newColor, octet oldColor)
{
  int x = col;
  int y = row;

  if(oldColor == newColor) return;
  emptyStack();

      h = im.getNbRow(); // Modif variable globale static
  int w = im.getNbCol();
    
  int  y1=0; 
  bool spanLeft=false, spanRight=false;

    
  if(!push(x,y)) { cerr << "Stack error "
                        << __FILE__
                        << " line "
                        << __LINE__
                        << endl;
                   exit(1);
  }

  while(pop(x,y))
  {    
    y1 = y;
    while (y1>=0 && im[y1][x]==oldColor) { y1--; }
    y1++;
    spanLeft = spanRight = false;
    while (y1<h && im[y1][x]==oldColor)
    {
     im[y1][x] = newColor;
     if(!spanLeft && x>0 && im[y1][x-1]==oldColor) 
     {
      if(!push(x-1,y1)) { cerr << "Stack error "
                               << __FILE__
                               << " line "
                               << __LINE__
                               << endl;
                          exit(1);
      }
      spanLeft = true;
     }
     else if(spanLeft && x>0 && im[y1][x-1]!=oldColor)
          {
           spanLeft = false;
          }
     if(!spanRight && x<w-1 && im[y1][x+1]==oldColor) 
     {
      if(!push(x+1,y1)) { cerr << "Stack error "
                               << __FILE__
                               << " line "
                               << __LINE__
                               << endl;
                          exit(1);
      }
      spanRight = true;
     }
     else if(spanRight && x<w-1 && im[y1][x + 1]!=oldColor)
          {
           spanRight = false;
          } 
     y1++;
    }
  }
}
