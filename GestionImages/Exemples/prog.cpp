#include <iostream>

using namespace std;

#include "LibImages.h"

#include "traitement.h"

int main(void)
{
  ImageRVB im1("../Images/Lena/lena24FullColor.ras");
  Image    im2("../Images/Lena/lena24FullColor.ras");

  ImageRVB im1r; 
  Image    im2r; 

  int  seuil = 127;

  seuillageRVB(im1,im1r,seuil);
  seuillage(im2,im2r,seuil);

  im1r.saveImage("../Resultats/im1Seuillee.ras");
  im2r.saveImage("../Resultats/im2Seuillee.ras");

  displayImage("../Resultats/im1Seuillee.ras"); // Avec xv ou autre
  displayImage("../Resultats/im2Seuillee.ras"); // Avec xv ou autre

 return(0);
}
