##############################################################################

#----- lib a utiliser
DIRIMAGES=../../GestionImages
INCIMAGES=${DIRIMAGES}/LibImages/include
LIBIMAGES=${DIRIMAGES}/LibImages/lib
IMAGESLIBNAME=Images
#-----

#---- les programmes a obtenir (cibles principales) ----

TARGET=progX1 progX2 prog ex exCurseur

all : ${TARGET}

#---- les fichiers sources ----

FILESprogX1=progX1.cpp \
	traitement.cpp

FILESprogX2=progX2.cpp \
	traitement.cpp

FILESprog=prog.cpp \
	traitement.cpp

FILESex=ex.cpp

FILESexCurseur=exCurseur.cpp

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

OBJECTSprogX1=${FILESprogX1:.cpp=.o}
OBJECTSprogX2=${FILESprogX2:.cpp=.o}
OBJECTSprog=${FILESprog:.cpp=.o}
OBJECTSex=${FILESex:.cpp=.o}
OBJECTSexCurseur=${FILESexCurseur:.cpp=.o}

#---- librairies utilisees ----

DEPLIBS=${LIBIMAGES}/lib${IMAGESLIBNAME}.a

#---- realisation des l'executables (edition de liens) ----

progX1: ${OBJECTSprogX1} ${DEPLIBS} ${INCIMAGES}/LibImages.h
	${CC} ${OBJECTSprogX1} ${LDFLAGS} -o progX1

progX2: $(OBJECTSprogX2) ${DEPLIBS} ${INCIMAGES}/LibImages.h
	${CC} ${OBJECTSprogX2} ${LDFLAGS} -o progX2

prog: ${OBJECTSprog} ${DEPLIBS} ${INCIMAGES}/LibImages.h
	${CC} ${OBJECTSprog} ${LDFLAGS} -o prog

ex: ${OBJECTSex} ${DEPLIBS} ${INCIMAGES}/LibImages.h
	${CC} ${OBJECTSex} ${LDFLAGS} -o ex

exCurseur: ${OBJECTSexCurseur} ${DEPLIBS} ${INCIMAGES}/LibImages.h
	${CC} ${OBJECTSexCurseur} ${LDFLAGS} -o exCurseur

#------ regles -----------------------

traitement.o: traitement.h traitement.cpp ${INCIMAGES}/LibImages.h
	${CC} ${CCFLAGS} -c traitement.cpp

progX1.o: traitement.h progX1.cpp ${INCIMAGES}/LibImages.h
	${CC} ${CCFLAGS} -c progX1.cpp

progX2.o: progX2.cpp ${INCIMAGES}/LibImages.h
	${CC} ${CCFLAGS} -c progX2.cpp

prog.o: prog.cpp ${INCIMAGES}/LibImages.h
	${CC} ${CCFLAGS} -c prog.cpp

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
