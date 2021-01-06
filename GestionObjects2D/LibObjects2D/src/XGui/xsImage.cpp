#ifdef X_GUI

#include "XGui/xsImage.h"
#include "XGui/xgView2d.h"
#include "XGui/xgMgr.h"

//--------------------------------------------------------------------------//
// class XGuiImage                                                          //
//--------------------------------------------------------------------------//

//-------- Allocators ------------------------------------------------------//
XGuiImage::XGuiImage(double x,double y,double theta,const Strings & color,
                     const Strings & fileName,const StringsVect * pathVect,
                     double scale)
 : XGuiShape2D(x,y,theta,color),
   _nbColumns(0), _nbLines(0), _scale(scale),
   _fileName(fileName), _red((unsigned char *)0),
   _green((unsigned char *)0), _blue((unsigned char *)0),
   _colors((unsigned long *)0), _nbColors(0),
   _pixels((unsigned long *)0), _fail(false),
   _l_2(0.0), _w_2(0.0), _dx(0.0), _dy(0.0)
{
Strings name(fileName);
FILE * file=::fopen(name,"rb");
if(!file&&pathVect)                                               // find file
  {
  for(unsigned int i=0;!file&&i<pathVect->size();i++)
    {
    name=(*pathVect)[i]+fileName;
    file=::fopen(name,"rb");
    }
  }
if(!file) _fail=true;
else                                                              // read file
  {
  Strings ext(fileName.extension());
  ext.toLower();
  if(ext==Strings(".bmp"))
    {
    if(!getXGuiManager()->readBMP(file,_red,_green,_blue,_nbColors,
                                       _pixels,_nbColumns,_nbLines))
      _fail=true;
    }
  else if(ext==Strings(".ras"))
    {
    if(!getXGuiManager()->readRAS(file,_red,_green,_blue,_nbColors,
                                       _pixels,_nbColumns,_nbLines))
      _fail=true;
    }
  else _fail=true;
  ::fclose(file);
  if(!_fail)
    {                                                      // allocate colors
    _colors=(unsigned long *)malloc(_nbColors* sizeof(unsigned long));
    for(int i=_nbColors;i--;)
      {
      if(!getXGuiManager()->allocColor(((int)_red[i])<<8,
                                       ((int)_green[i])<<8,
                                       ((int)_blue[i])<<8,
                                       _colors[i]))
        {
        if(!getXGuiManager()->allocNamedColor(_color,_colors[i]))
          {
          getXGuiManager()->allocNamedColor("white",_colors[i]);
          }
        }
      }
    }
  }
if(_scale<=0.0) _fail=true;
_l_2=_nbColumns*_scale/2.0;
_w_2=_nbLines*_scale/2.0;
computePosition();
}

XGuiImage::XGuiImage(const XGuiImage & s)
 : XGuiShape2D(s),
   _nbColumns(s._nbColumns), _nbLines(s._nbLines), _scale(s._scale),
   _fileName(s._fileName), _red((unsigned char *)0),
   _green((unsigned char *)0), _blue((unsigned char *)0),
   _colors((unsigned long *)0), _nbColors(s._nbColors),
   _pixels((unsigned long *)0), _fail(s._fail),
   _l_2(s._l_2), _w_2(s._w_2), _dx(s._dx), _dy(s._dy)
{
if(!_fail)
  {
  unsigned int colorSize=_nbColors*sizeof(unsigned char);
  _red=(unsigned char *)malloc(colorSize);
  _green=(unsigned char *)malloc(colorSize);
  _blue=(unsigned char *)malloc(colorSize);
  _colors=(unsigned long *)malloc(_nbColors* sizeof(unsigned long));
  int i;
  for(i=_nbColors;i--;)
    {
    _red[i]=s._red[i];
    _green[i]=s._green[i];
    _blue[i]=s._blue[i];
    if(!getXGuiManager()->allocColor(((int)_red[i])<<8,
                                     ((int)_green[i])<<8,
                                     ((int)_blue[i])<<8,
                                     _colors[i]))
      {
      if(!getXGuiManager()->allocNamedColor(_color,_colors[i]))
        {
        getXGuiManager()->allocNamedColor("white",_colors[i]);
        }
      }
    }
  _pixels=(unsigned long *)malloc(_nbLines*_nbColumns* sizeof(unsigned long));
  for(i=_nbLines*_nbColumns;i--;)
    {
    _pixels[i]=s._pixels[i];
    }
  for(i=4;i--;)
    {
    _coordX[i]=s._coordX[i];
    _coordY[i]=s._coordY[i];
    _oldCoordX[i]=s._oldCoordX[i];
    _oldCoordY[i]=s._oldCoordY[i];
    }
  }
}

XGuiImage::~XGuiImage(void)
{
if(_red) free(_red);
if(_green) free(_green);
if(_blue) free(_blue);
if(_colors)
  {
  for(int i=_nbColors;i--;) getXGuiManager()->freeColor(_colors[i]);
  free(_colors);
  }
if(_pixels) free(_pixels);
while(_drawMap.size()) removeViewer((*_drawMap.begin()).first);
}

XGuiShape2D * XGuiImage::duplicate(void) const // virtual
{
return(new XGuiImage(*this));
}

//-------- Inspectors ------------------------------------------------------//
// inline void XGuiImage::getLocalBoundingBox(double & xmin,double & ymin,
//                                            double & xmax,double & ymax)
//                                            const // virtual

// inline void XGuiImage::getBoundingBox(double & xmin,double & ymin,
//                                       double & xmax,double & ymax,
//                                       const XGuiViewer2D * viewer) const
//                                                                // virtual

// inline double XGuiImage::distanceTo(double x,double y,
//                                     const XGuiViewer2D * viewer)
//                                                          const // virtual

bool XGuiImage::isInside(double x,double y) const // virtual
{
double cosTh=::cos(_theta0);
double sinTh=::sin(_theta0);
x-=_x0;
y-=_y0;
double xLocal=x*cosTh+y*sinTh;
double yLocal=y*cosTh-x*sinTh;
return((xLocal>-_l_2)&&(xLocal<_l_2)&&(yLocal>-_w_2)&&(yLocal<_w_2));
}

bool XGuiImage::intersectRay(double xRay,double yRay,double xDir,double yDir,
                             double & x,double & y) const // virtual
{
double a1=0.0,b1=0.0,c1=0.0,
       a2,b2,c2,x1,y1,x2,y2,xInter,yInter,dx,dy,d,dmin=0.0;
bool found=false;
XGuiShape2D::_equationLine(xRay,yRay,xRay+xDir,yRay+yDir,a1,b1,c1);
x1=_coordX[0];
y1=_coordY[0];
for(int i=4;i--;)
  {
  x2=x1;
  y2=y1;
  x1=_coordX[i];
  y1=_coordY[i];
  if(!XGuiShape2D::_equationLine(x1,y1,x2,y2,a2,b2,c2)||
     !XGuiShape2D::_intersectLines(a1,b1,c1,a2,b2,c2,xInter,yInter))
    continue; // no intersection
  dx=xInter-xRay;
  dy=yInter-yRay;
  d=dx*dx+dy*dy;
  if((found&&(d>=dmin))||
     (dx*xDir+dy*yDir<=0.0)) continue; // too far or bad direction
  if(x1!=x2)
    {
    dx=(xInter-x1)/(x2-x1);
    if((dx>=0.0)&&(dx<=1.0))
      {
      found=true;
      dmin=d;
      x=xInter;
      y=yInter;
      }
    }
  else
    {
    dy=(yInter-y1)/(y2-y1);
    if((dy>=0.0)&&(dy<=1.0))
      {
      found=true;
      dmin=d;
      x=xInter;
      y=yInter;
      }
    }
  }
return(found);
}

// inline int XGuiImage::getNbColors(void) const

// inline unsigned long XGuiImage::getPixel(int x,int y) const

// inline int XGuiImage::getNbColumns(void) const

// inline int XGuiImage::getNbLines(void) const

// inline const Strings & XGuiImage::getFileName(void) const

// inline double XGuiImage::getScale(void) const

// inline bool XGuiImage::fail(void) const

// inline void XGuiImage::getRGB(unsigned long pixel,unsigned char & r,
//                               unsigned char & g,unsigned char & b) const

//-------- Input/Output ----------------------------------------------------//
Strings XGuiImage::print(void) const // virtual
{
Strings str="image("+_fileName.dump()+","+Strings(_scale)+")";
return(str);
}

//-------- Modifiers -------------------------------------------------------//
void XGuiImage::addViewer(XGuiViewer2D * viewer) // virtual
{
_drawMap.insert(DrawMap::value_type(viewer,(XGuiImageDraw *)0));
}

void XGuiImage::removeViewer(XGuiViewer2D * viewer) // virtual
{
DrawMap::iterator it=_drawMap.find(viewer);
if(it!=_drawMap.end())
  {
  if((*it).second)
    {
    XFreePixmap(getXGuiManager()->getDisplay(),(*it).second->pixmap);
    XDestroyRegion((*it).second->region);
    delete (*it).second;
    }
  _drawMap.erase(it);
  }
}

void XGuiImage::changedViewerBackground(XGuiViewer2D * viewer) // virtual
{
DrawMap::iterator it=_drawMap.find(viewer);
if((it!=_drawMap.end())&&(*it).second)
  {
  XFreePixmap(getXGuiManager()->getDisplay(),(*it).second->pixmap);
  XDestroyRegion((*it).second->region);
  delete (*it).second;
  (*it).second=(XGuiImageDraw *)0;
  }
}

void XGuiImage::drawInViewer(XGuiViewer2D * viewer) // virtual
{
if(!_fail)
  {
  DrawMap::iterator it=_drawMap.find(viewer);
  if(it==_drawMap.end()) // not found
    {
    addViewer(viewer);
    it=_drawMap.find(viewer);
    }
  bool rebuild=!(*it).second; // not drawn
  int i;
  for(i=4;!rebuild&&i--;) // image has moved
    {
    rebuild|=(viewer->getColumn(_oldCoordX[i])!=viewer->getColumn(_coordX[i]));
    rebuild|=(viewer->getLine(_oldCoordY[i])!=viewer->getLine(_coordY[i]));
    }
  if(!rebuild) // viewer has changed
    {
    rebuild|=((*it).second->xmin!=viewer->getXmin());
    rebuild|=((*it).second->ymin!=viewer->getYmin());
    rebuild|=((*it).second->scale!=viewer->getScale());
    }
  if(rebuild)
    {
    if((*it).second)
      {
      XFreePixmap(getXGuiManager()->getDisplay(),(*it).second->pixmap);
      XDestroyRegion((*it).second->region);
      delete (*it).second;
      (*it).second=(XGuiImageDraw *)0;
      }
    double xmin,ymin,xmax,ymax;
    getBoundingBox(xmin,ymin,xmax,ymax,viewer);
    if(xmin<viewer->getXmin()) xmin=viewer->getXmin();
    if(ymin<viewer->getYmin()) ymin=viewer->getYmin();
    if(xmax>viewer->getXmax()) xmax=viewer->getXmax();
    if(ymax>viewer->getYmax()) ymax=viewer->getYmax();
    int pixWidth=(int)((xmax-xmin)*viewer->getScale());
    int pixHeight=(int)((ymax-ymin)*viewer->getScale());
    if((pixWidth>0)&&(pixHeight>0))
      {
      (*it).second=new XGuiImageDraw;
      (*it).second->pixmap=getXGuiManager()->getNewPixmap(viewer->getWindow(),
                                                          pixWidth,pixHeight);
      getXGuiManager()->chooseColor(viewer->getBackgroundPixel());
      XFillRectangle(getXGuiManager()->getDisplay(),
                     (*it).second->pixmap,getXGuiManager()->getGC(),
                     0,0,1+pixWidth,1+pixHeight);
      XPoint points[4];
      for(i=4;i--;)
        {
        points[i].x=viewer->getColumn(_coordX[i]);
        points[i].y=viewer->getLine(_coordY[i]);
        }
      (*it).second->region=XPolygonRegion(points,4,WindingRule);
      double xx,yy;
      double xxOffset=_coordX[1]-(xmin-viewer->getXmin());
      double yyOffset=_coordY[1]-(ymax-viewer->getYmax());
      for(int y=_nbLines;y--;)
        {
        for(int x=_nbColumns;x--;)
          {
          xx=xxOffset+x*_dx+y*_dy;
          yy=yyOffset+x*_dy-y*_dx;
          points[0].x=viewer->getColumn(xx);
          points[0].y=viewer->getLine(yy);
          points[1].x=viewer->getColumn(xx+_dx);
          points[1].y=viewer->getLine(yy+_dy);
          points[2].x=viewer->getColumn(xx+_dx+_dy);
          points[2].y=viewer->getLine(yy+_dy-_dx);
          points[3].x=viewer->getColumn(xx+_dy);
          points[3].y=viewer->getLine(yy-_dx);
          getXGuiManager()->chooseColor(_colors[_pixels[_nbColumns*y+x]]);
          XFillPolygon(getXGuiManager()->getDisplay(),
                       (*it).second->pixmap,getXGuiManager()->getGC(),
                       points,4,Convex,CoordModeOrigin);
          }
        }
      (*it).second->pixX=viewer->getColumn(xmin);
      (*it).second->pixY=viewer->getLine(ymax);
      (*it).second->pixWidth=pixWidth;
      (*it).second->pixHeight=pixHeight;
      (*it).second->xmin=viewer->getXmin();
      (*it).second->ymin=viewer->getYmin();
      (*it).second->scale=viewer->getScale();
      (*it).second->xOffset=xxOffset;
      (*it).second->yOffset=yyOffset;
      }
    }
  if((*it).second)
    {
    XSetRegion(getXGuiManager()->getDisplay(),
               getXGuiManager()->getGC(),
               (*it).second->region);
    XCopyArea(getXGuiManager()->getDisplay(),(*it).second->pixmap,
              viewer->getPixmap(),getXGuiManager()->getGC(),0,0,
              (*it).second->pixWidth,(*it).second->pixHeight,
              (*it).second->pixX,(*it).second->pixY);
    XSetClipMask(getXGuiManager()->getDisplay(),
                 getXGuiManager()->getGC(),
                 None);
    }
  }
}

// inline void XGuiImage::computePosition(void) // virtual

// inline void XGuiImage::savePosition(void) // virtual

void XGuiImage::setPixel(int x,int y,unsigned long pixel)
{
y=_nbLines-y-1;
unsigned long * pos=_pixels+x+_nbColumns*y;
if(*pos!=pixel)
  {
  *pos=pixel;
  XPoint points[4];
  DrawMap::iterator it=_drawMap.begin();
  for(;it!=_drawMap.end();it++)
    {
    if((*it).second)
      {
      double xx=(*it).second->xOffset+x*_dx+y*_dy;
      double yy=(*it).second->yOffset+x*_dy-y*_dx;
      points[0].x=(*it).first->getColumn(xx);
      points[0].y=(*it).first->getLine(yy);
      points[1].x=(*it).first->getColumn(xx+_dx);
      points[1].y=(*it).first->getLine(yy+_dy);
      points[2].x=(*it).first->getColumn(xx+_dx+_dy);
      points[2].y=(*it).first->getLine(yy+_dy-_dx);
      points[3].x=(*it).first->getColumn(xx+_dy);
      points[3].y=(*it).first->getLine(yy-_dx);
      getXGuiManager()->chooseColor(_colors[pixel]);
      XFillPolygon(getXGuiManager()->getDisplay(),
                   (*it).second->pixmap,getXGuiManager()->getGC(),
                   points,4,Convex,CoordModeOrigin);
      }
    }
  XGuiViewer2D::forceRedraw();
  }
}

void XGuiImage::sortColors(void)
{
unsigned long i,j,min,sum,minSum;
unsigned long * change1=(unsigned long *)malloc(_nbColors*
                                                     sizeof(unsigned long));
for(i=0;i<(unsigned long)_nbColors;i++) change1[i]=i;
for(i=0;i<(unsigned long)_nbColors-1;i++)
  {
  min=i;
  minSum=(int)_red[i]+(int)_green[i]+(int)_blue[i];
  for(j=i+1;j<(unsigned long)_nbColors;j++)
    {
    sum=(int)_red[j]+(int)_green[j]+(int)_blue[j];
    if(sum<minSum)
      {
      minSum=sum;
      min=j;
      }
    }
  if(i!=min)
    {
    j=_red[i]; _red[i]=_red[min]; _red[min]=j;
    j=_green[i]; _green[i]=_green[min]; _green[min]=j;
    j=_blue[i]; _blue[i]=_blue[min]; _blue[min]=j;
    j=_colors[i]; _colors[i]=_colors[min]; _colors[min]=j;
    j=change1[i]; change1[i]=change1[min]; change1[min]=j;
    }
  }
unsigned long * change2=(unsigned long *)malloc(_nbColors*
                                                     sizeof(unsigned long));
for(i=0;i<(unsigned long)_nbColors;i++) change2[change1[i]]=i;
free(change1);
for(i=_nbLines*_nbColumns;i--;)
  _pixels[i]=change2[_pixels[i]];
free(change2);
}

#endif // X_GUI

