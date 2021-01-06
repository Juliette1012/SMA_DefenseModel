#include <iostream>             // Fichier exCurseur.cpp

using namespace std;

#include "LibImages.h"

int main(void)
{
 ImageRVB im("../Images/Lena/lena24FullColor.ras");

 XAffichage *Fim = new XAffichage(im.getNbRow(),im.getNbCol());
 Fim->setLabel("lena24FullColor.ras");

 while (1)
 {                                 /***************************************/
  XAffichageEvent event;           /* Dans un XAffichageEvent, il y a:    */
                                   /*                                     */
  /* typedef                    */ /* 1) Recuperation caractere appuye:   */
  /*    struct {                */ /*                                     */
  /*      char key;             */ /* char key (le caractere appuye ou    */
  /*      int  button;          */ /*           -1 si aucun caractere)    */
  /*      int  row;             */ /* key...aussi le retour de XEvenement */
  /*      int  col;             */ /*                                     */
  /*      bool onButtonPress;   */ /* 2) Gestion souris:                  */
  /*      bool onButtonRelease; */ /*                                     */
  /*      bool onButtonMotion;  */ /* int button (1,2 ou 3 si evt souris  */
  /*    } XAffichageEvent;      */ /*             -1 si aucun evt souris) */
                                   /* Si button!= -1 :                    */
  char cim;                        /* . int row,int col(coord y,x souris) */
                                   /*     (row,col)=(-1,-1) si en dehors  */
  Fim->Afficher(im);               /* . bool onButtonPress  (true,false), */
  cim=Fim->XEvenement(im,&event);  /* . bool onButtonRelease(true,false), */
  cim = tolower(cim);              /* . bool onButtonMotion (true,false). */
  if (event.button>0)              /***************************************/
  {
   if (event.onButtonPress)   { cout << "  Press";   }
   else
   if (event.onButtonRelease) { cout << "Release"; }
   else
   if (event.onButtonMotion)  { cout << " Motion"; }
   else { cout << "???????"; }

   cout << "(" << event.button << "):";
// cout<<"("<<event.button<<"):"<<" row: "<<event.row<<" col: "<< event.col;
   cout << " row: "; cout.width(4); cout << right << event.row;
   cout << " col: "; cout.width(4); cout << right << event.col;
   if (event.row!=-1 && event.col!=-1)
   {
    octet r,v,b;
    im.readPix(event.row,event.col,r,v,b);
    cout << "   (r,v,b): ";
    cout << "(" ;
    cout.width(3); cout << right << (int)r;
    cout << ",";
    cout.width(3); cout << right << (int)v;
    cout << ",";
    cout.width(3); cout << right << (int)b;
    cout << ")" ;
   }
   cout << endl;
  }

  if (cim=='q')  break;
 }

 delete(Fim);

 return 0;
}
