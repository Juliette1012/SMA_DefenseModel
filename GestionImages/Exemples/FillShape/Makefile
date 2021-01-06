##############################################################################

#----- lib a utiliser
DIRIMAGES=../../../GestionImages
INCIMAGES=${DIRIMAGES}/LibImages/include
LIBIMAGES=${DIRIMAGES}/LibImages/lib
IMAGESLIBNAME=Images
#-----

#---- les programmes a obtenir (cibles principales) ----

TARGET=progFill

all : ${TARGET}

#---- les fichiers sources ----

FILESprogFill=progFill.cpp \
	fill.cpp

##############################################################################

#---- les variables ----

CC=g++

INCFLAGS_STD=-I${INCIMAGES}
INCFLAGS_APPLE=-I/usr/X11/include
INCFLAGS=$(INCFLAGS_STD) $(INCFLAGS_APPLE)

LIBX11_STD=-L/usr/X11R6/lib
LIBX11_APPLE=-L/usr/X11/lib

LIBX11=$(LIBX11_STD)
LIBX11=$(LIBX11_APPLE)
LIBFLAGS=-lm $(LIBX11) -lX11 -lXt

WOFF=-W -Wall -Werror # Avant APPLE, -pedantic en plus.!
CCOPTS=-DX_GUI
OPTIMIZER=-O3 -fno-exceptions

CCFLAGS=$(INCFLAGS) $(WOFF) $(OPTIMIZER) $(CCOPTS)

LDFLAGS=\
-L${LIBIMAGES} -l${IMAGESLIBNAME} \
${LIBFLAGS}

##############################################################################

#---- les fichiers objets ----

OBJECTSprogFill=${FILESprogFill:.cpp=.o}

#---- librairies utilisees ----

DEPLIBS=${LIBIMAGES}/lib${IMAGESLIBNAME}.a

#---- realisation des l'executables (edition de liens) ----

progFill: ${OBJECTSprogFill} ${DEPLIBS} ${INCIMAGES}/LibImages.h
	${CC} ${OBJECTSprogFill} ${LDFLAGS} -o progFill

#------ regles -----------------------

fill.o: fill.h fill.cpp ${INCIMAGES}/LibImages.h
	${CC} ${CCFLAGS} -c fill.cpp

#---- la regle par defaut (.c/cpp --> .o) ----

.c.o :
	@echo
	${CC} -o $*.o -c ${CCFLAGS} $<
	@echo

.cpp.o :
	@echo
	${CC} -o $*.o -c ${CCFLAGS} $<
	@echo

#---- nettoyage ----

CLEANING=rm -f *.o a.out *.exe core *.exe.stackdump ${TARGET}

clean :
	${CLEANING}

clear :
	${CLEANING}

##############################################################################
