#ifndef _TRAITEMENT_H_
#define _TRAITEMENT_H_

extern void seuillage(const Image& in, Image& out, octet seuil);
extern void seuillageRVB(const ImageRVB& in, ImageRVB& out, octet seuil);

#endif // _TRAITEMENT_H_
