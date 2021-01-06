// @(#) ENIB/LI2 (c) - oRis - Version 2.3
//--------------------------------------------------------------------------//
// file        : guiTrans.h                                                 //
// description : header file for platform dependant GUI translations        //
// author(s)   : F. Harrouet                                                //
// copyright   : Laboratoire d'Informatique Industrielle (LI2)              //
//               Ecole Nationale d'Ingenieurs de Brest (ENIB)               //
//               CP 30815 - 29608 Brest Cedex - FRANCE                      //
//               Tel: (33) 02.98.05.66.31 , Fax: (33) 02.98.05.66.29        //
//               e-mail: li2@enib.fr                                        //
//--------------------------------------------------------------------------//
// Copyright (c) 1996-2000                                                  //
// Laboratoire d'Informatique Industrielle (LI2)                            //
// Ecole Nationale d'Ingenieurs de Brest (ENIB)                             //
//                                                                          //
// Permission to use, copy, modify, distribute and sell this software       //
// and its documentation for any purpose is hereby granted without fee,     //
// provided that the above copyright notice appear in all copies and        //
// that both that copyright notice and this permission notice appear        //
// in supporting documentation.                                             //
// ENIB/LI2 makes no representations about the suitability of this          //
// software for any purpose.                                                //
// It is provided "as is" without express or implied warranty.              //
//--------------------------------------------------------------------------//

#ifndef GUI_H
#define GUI_H

#ifdef X_GUI
#  include "XGui/xgArea.h"
#  include "XGui/xgBtnDlg.h"
#  include "XGui/xgButton.h"
#  include "XGui/xgCArea.h"
#  include "XGui/xgColCh.h"
#  include "XGui/xgCursor.h"
#  include "XGui/xgCurve.h"
#  include "XGui/xgEditor.h"
#  include "XGui/xgElem.h"
#  include "XGui/xgFileCh.h"
#  include "XGui/xgFrame.h"
#  include "XGui/xgGraph.h"
#  include "XGui/xgHScAre.h"
#  include "XGui/xgLabel.h"
#  include "XGui/xgList.h"
#  include "XGui/xgMenu.h"
#  include "XGui/xgMgr.h"
#  include "XGui/xgMnuBar.h"
#  include "XGui/xgMnuItm.h"
#  include "XGui/xgMnuSep.h"
#  include "XGui/xgOptMnu.h"
#  include "XGui/xgScArea.h"
#  include "XGui/xgScroll.h"
#  include "XGui/xgShap2d.h"
#  include "XGui/xgTab.h"
#  include "XGui/xgTabGrp.h"
#  include "XGui/xgTglGrp.h"
#  include "XGui/xgToggle.h"
#  include "XGui/xgTxtDlg.h"
#  include "XGui/xgVScAre.h"
#  include "XGui/xgView2d.h"
#  include "XGui/xgWin.h"
#  include "XGui/xsCircle.h"
#  include "XGui/xsImage.h"
#  include "XGui/xsLine.h"
#  include "XGui/xsPoint.h"
#  include "XGui/xsPolygo.h"
#  include "XGui/xsPolyli.h"
#  include "XGui/xsRectan.h"
#  include "XGui/xsSquare.h"
#  include "XGui/xsText.h"
#  ifdef OPEN_GL
#    include "XGui/xgShap3d.h"
#    include "XGui/xgView3d.h"
#  endif // OPEN_GL
#  define GUI_TYPEDEF(guiType) typedef X##guiType guiType;
#  define GUI_GET_MANAGER inline GuiManager * getGuiManager(void) \
                          {return(getXGuiManager());}
#else
#  ifdef W_GUI
#    include "WGui/wgArea.h"
#    include "WGui/wgBtnDlg.h"
#    include "WGui/wgButton.h"
#    include "WGui/wgCArea.h"
#    include "WGui/wgColCh.h"
#    include "WGui/wgCursor.h"
#    include "WGui/wgCurve.h"
#    include "WGui/wgEditor.h"
#    include "WGui/wgElem.h"
#    include "WGui/wgFileCh.h"
#    include "WGui/wgFrame.h"
#    include "WGui/wgGraph.h"
#    include "WGui/wgHScAre.h"
#    include "WGui/wgLabel.h"
#    include "WGui/wgList.h"
#    include "WGui/wgMenu.h"
#    include "WGui/wgMgr.h"
#    include "WGui/wgMnuBar.h"
#    include "WGui/wgMnuItm.h"
#    include "WGui/wgMnuSep.h"
#    include "WGui/wgOptMnu.h"
#    include "WGui/wgScArea.h"
#    include "WGui/wgScroll.h"
#    include "WGui/wgShap2d.h"
#    include "WGui/wgTab.h"
#    include "WGui/wgTabGrp.h"
#    include "WGui/wgTglGrp.h"
#    include "WGui/wgToggle.h"
#    include "WGui/wgTxtDlg.h"
#    include "WGui/wgVScAre.h"
#    include "WGui/wgView2d.h"
#    include "WGui/wgWin.h"
#    include "WGui/wsCircle.h"
#    include "WGui/wsImage.h"
#    include "WGui/wsLine.h"
#    include "WGui/wsPoint.h"
#    include "WGui/wsPolygo.h"
#    include "WGui/wsPolyli.h"
#    include "WGui/wsRectan.h"
#    include "WGui/wsSquare.h"
#    include "WGui/wsText.h"
#    ifdef OPEN_GL
#      include "WGui/wgShap3d.h"
#      include "WGui/wgView3d.h"
#    endif // OPEN_GL
#    define GUI_TYPEDEF(guiType) typedef W##guiType guiType;
#    define GUI_GET_MANAGER inline GuiManager * getGuiManager(void) \
                            {return(getWGuiManager());}
#  else
#    error NO GUI DEFINED !
#  endif // W_GUI
#endif // X_GUI

GUI_TYPEDEF(GuiArea)
GUI_TYPEDEF(GuiButtonDialog)
GUI_TYPEDEF(GuiButton)
GUI_TYPEDEF(GuiColorArea)
GUI_TYPEDEF(GuiColorChooser)
GUI_TYPEDEF(GuiCursor)
GUI_TYPEDEF(GuiCurve)
GUI_TYPEDEF(GuiEditor)
GUI_TYPEDEF(GuiElement)
GUI_TYPEDEF(GuiFileChooser)
GUI_TYPEDEF(GuiFrame)
GUI_TYPEDEF(GuiGrapher)
GUI_TYPEDEF(GuiHScrolledArea)
GUI_TYPEDEF(GuiLabel)
GUI_TYPEDEF(GuiList)
GUI_TYPEDEF(GuiMenu)
GUI_TYPEDEF(GuiManager)
GUI_TYPEDEF(GuiMenuBar)
GUI_TYPEDEF(GuiMenuItem)
GUI_TYPEDEF(GuiMenuSepar)
GUI_TYPEDEF(GuiOptionMenu)
GUI_TYPEDEF(GuiScrolledArea)
GUI_TYPEDEF(GuiScroller)
GUI_TYPEDEF(GuiShape2D)
GUI_TYPEDEF(GuiTab)
GUI_TYPEDEF(GuiTabGroup)
GUI_TYPEDEF(GuiToggleGroup)
GUI_TYPEDEF(GuiToggle)
GUI_TYPEDEF(GuiTextDialog)
GUI_TYPEDEF(GuiVScrolledArea)
GUI_TYPEDEF(GuiViewer2D)
GUI_TYPEDEF(GuiWindow)
GUI_TYPEDEF(GuiCircle)
GUI_TYPEDEF(GuiImage)
GUI_TYPEDEF(GuiLine)
GUI_TYPEDEF(GuiPoint)
GUI_TYPEDEF(GuiPolygon)
GUI_TYPEDEF(GuiPolyline)
GUI_TYPEDEF(GuiRectangle)
GUI_TYPEDEF(GuiSquare)
GUI_TYPEDEF(GuiText)
#ifdef OPEN_GL
  GUI_TYPEDEF(GuiShape3D)
  GUI_TYPEDEF(Gui3DPoint)
  GUI_TYPEDEF(Gui3DPointVect)
  GUI_TYPEDEF(Gui3DTriangle)
  GUI_TYPEDEF(Gui3DTriangleVect)
  GUI_TYPEDEF(Gui3DColor)
  GUI_TYPEDEF(Gui3DColorVect)
  GUI_TYPEDEF(Gui3DTexture)
  GUI_TYPEDEF(Gui3DTextureVect)
  GUI_TYPEDEF(GuiViewer3D)
#endif // OPEN_GL
GUI_GET_MANAGER

#undef GUI_TYPEDEF
#undef GUI_GET_MANAGER
#endif // GUI_H

