
#-------- Localisation des fichiers sources ---------------------------

#-------- Repertoires principaux --------
WRKDIR=..
INCDIR=$(WRKDIR)/include
SRCDIR=$(WRKDIR)/src
LIBDIR=$(WRKDIR)/lib

UTILSRC=$(SRCDIR)/Utility
UTILINC=$(INCDIR)/Utility
GUISRC=$(SRCDIR)/XGui
GUIINC=$(INCDIR)/XGui
SRCDIRS=$(SRCDIR) $(UTILSRC) $(GUISRC)
INCDIRS=$(INCDIR) $(UTILINC) $(GUIINC)

all : target

OBJECTS2DLIBNAME=Object2D

#-------- Options de compilation --------------------------------------

INCFLAGS_STD=-I$(INCDIR)
INCFLAGS_APPLE=-I/usr/X11/include
INCFLAGS=$(INCFLAGS_STD) $(INCFLAGS_APPLE)

LIBX11_STD=-L/usr/X11R6/lib
LIBX11_APPLE=-L/usr/X11/lib

LIBX11=$(LIBX11_STD)
LIBX11=$(LIBX11_APPLE)
LIBFLAGS=-lm $(LIBX11) -lX11 -lXt

#---- Linux ----
WOFF=-W -Wall # -Werror # Avant APPLE, -pedantic en plus..!
#OPTIMIZER=-O3 -fomit-frame-pointer -fno-exceptions -fno-rtti -pipe -s \
#          -ffast-math
OPTIMIZER=-O3 -fno-exceptions
#CCOPTS=-rdynamic -fPIC -DX_GUI -DPTHREADS -D_REENTRANT
CCOPTS=-DX_GUI
LDOPTS=-lpthread -ldl
DEPOPT=-MM
CC=g++
-include .depend

#----- SGI ----
# WOFF=
# OPTIMIZER=-Olimit 2048 -Wo,-w -O2
# CCOPTS=-ptv -ptused -DX_GUI -D_SGI_MP_SOURCE
# LDOPTS=-Wl,-woff,15,-woff,84,-woff,85
# DEPOPT=-M -c
# CC=CC
# sinclude .depend

CCFLAGS=$(INCFLAGS) $(WOFF) $(OPTIMIZER) $(CCOPTS)
LDFLAGS=$(LDOPTS) $(LIBFLAGS) 

#-------- Regles ------------------------------------------------------

.SUFFIXES:.cpp

UTILFILES= $(UTILSRC)/strings.cpp

GUIFILES=$(GUISRC)/xgArea.cpp \
         $(GUISRC)/xgCurve.cpp \
         $(GUISRC)/xgElem.cpp \
         $(GUISRC)/xgGraph.cpp \
         $(GUISRC)/xgMenu.cpp \
         $(GUISRC)/xgMgr.cpp \
         $(GUISRC)/xgMnuItm.cpp \
         $(GUISRC)/xgOptMnu.cpp \
         $(GUISRC)/xgShap2d.cpp \
         $(GUISRC)/xgView2d.cpp \
         $(GUISRC)/xgWin.cpp \
         $(GUISRC)/xsCircle.cpp \
         $(GUISRC)/xsImage.cpp \
         $(GUISRC)/xsLine.cpp \
         $(GUISRC)/xsPoint.cpp \
         $(GUISRC)/xsPolygo.cpp \
         $(GUISRC)/xsPolyli.cpp \
         $(GUISRC)/xsRectan.cpp \
         $(GUISRC)/xsSquare.cpp \
         $(GUISRC)/xsText.cpp

#         $(GUISRC)/xgBtnDlg.cpp \
#         $(GUISRC)/xgButton.cpp \
#         $(GUISRC)/xgCArea.cpp \
#         $(GUISRC)/xgColCh.cpp \
#         $(GUISRC)/xgCursor.cpp \
#         $(GUISRC)/xgEditor.cpp \
#         $(GUISRC)/xgFileCh.cpp \
#         $(GUISRC)/xgFrame.cpp \
#         $(GUISRC)/xgHScAre.cpp \
#         $(GUISRC)/xgLabel.cpp \
#         $(GUISRC)/xgList.cpp \
#         $(GUISRC)/xgMnuBar.cpp \
#         $(GUISRC)/xgMnuSep.cpp \
#         $(GUISRC)/xgScArea.cpp \
#         $(GUISRC)/xgScroll.cpp \
#         $(GUISRC)/xgShap3d.cpp \
#         $(GUISRC)/xgTab.cpp \
#         $(GUISRC)/xgTabGrp.cpp \
#         $(GUISRC)/xgTglGrp.cpp \
#         $(GUISRC)/xgToggle.cpp \
#         $(GUISRC)/xgTxtDlg.cpp \
#         $(GUISRC)/xgVScAre.cpp \
#         $(GUISRC)/xgView3d.cpp \

FILES=$(UTILFILES) \
      $(GUIFILES) \
      $(SRCDIR)/Object2D.cpp \
      $(SRCDIR)/CObject2D.cpp\
      $(SRCDIR)/UtilObject2D.cpp

LIBTARGET=$(LIBDIR)/lib$(OBJECTS2DLIBNAME).a
OBJECTS=$(FILES:.cpp=.o)

target : $(LIBTARGET)

$(LIBTARGET) : $(OBJECTS)
	@echo
	@echo ======== $(LIBTARGET) ========
	ar -rs $(LIBTARGET) $(OBJECTS)
	@rm -f so_locations
	@echo

#-------- Regles par defaut --------
.cpp.o :
	@echo
	@echo ======== $< ========
	$(CC) $(CCFLAGS) -c $< -o $*.o
	@echo

#-------- Nettoyage --------
clean : 
	rm -f $(LIBTARGET) so_locations .depend
	for i in $(LIBDIR) $(SRCDIRS) ; do \
          rm -rf $$i/ii_files ; \
          rm -f $$i/a.out $$i/*.o $$i/core ; \
          touch $$i/* ; \
        done

clear : 
	rm -f $(LIBTARGET) so_locations .depend
	for i in $(LIBDIR) $(SRCDIRS) ; do \
          rm -rf $$i/ii_files ; \
          rm -f $$i/a.out $$i/*.o $$i/core ; \
          touch $$i/* ; \
        done

#-------- Dependances --------

dep : $(FILES)
	@echo "======== Mise a jour des dependances ========"
	@rm -f .depend
	@for i in $(FILES) ; do \
          echo $$i ; \
          $(CC) $(DEPOPT) $(CCFLAGS) $$i > .tmpdepend ; \
          OBJNAME=`echo $$i | sed -e s%\\\.cpp%.o% ` ; \
          cat .tmpdepend | \
          sed -e s%`basename $$i .cpp`\\\.o%$$OBJNAME% >> .depend ; \
          echo  >> .depend ; \
        done
	@rm -f .tmpdepend

