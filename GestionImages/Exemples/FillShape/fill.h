#ifndef   _FILL_H_
#define   _FILL_H_

#include "Image.h"

// Remplissage de la forme se trouvant dans l'image im.
// x et y doivent etre a l'interieur de la forme.
void floodFillScanlineStack(Image& im,
                            int row, int col,
                            octet newColor, octet oldColor);
#endif  //_FILL_H_
