#include "Image.h"
#include "traitement.h"

#define  C  0
#define NC 255

void seuillage(const Image& in, Image& out, octet seuil)
{
 int nbRow = in.getNbRow(), nbCol = in.getNbCol();

 out.setImageSize(nbRow,nbCol);  // Au cas ou

#if 0

 for(int l=0;l<nbRow;l++)
 {
  for(int c=0;c<nbCol;c++)
  {
   out[l][c] = (in[l][c] > seuil) ? C : NC;
  }
 }

#else    // Pour aller plus vite

 octet* ptrOut = out.begin();

 for(const octet* ptrIn = in.begin() ; ptrIn < in.end() ; ptrIn++)
 {
  *ptrOut++ = (*ptrIn > seuil) ? C : NC;
 }

#endif

}

void seuillageRVB(const ImageRVB& in, ImageRVB& out, octet seuil)
{
 int nbRow = in.getNbRow(), nbCol = in.getNbCol();

 out.setImageSize(nbRow,nbCol);  // Au cas ou

 seuillage(in.getR(),out.getR(),seuil);
 seuillage(in.getV(),out.getV(),seuil);
 seuillage(in.getB(),out.getB(),seuil);
}
