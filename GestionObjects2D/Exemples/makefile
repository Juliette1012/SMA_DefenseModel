##############################################################################

#----- lib a utiliser
DIROBJECTS2D=../../GestionObjects2D
INCOBJECTS2D=${DIROBJECTS2D}/LibObjects2D/include
LIBOBJECTS2D=${DIROBJECTS2D}/LibObjects2D/lib
OBJECTS2DLIBNAME=Object2D

#---- les programmes a obtenir (cibles principales) ----

TARGET=graphTest graphTestC

all : ${TARGET}

#---- les fichiers sources ----

FILESgraphTest=graphTest.cpp
FILESgraphTestC=graphTestC.cpp

##############################################################################

#---- les variables ----

CC=g++

INCFLAGS_STD=-I$(INCOBJECTS2D)
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
-L${LIBOBJECTS2D} -l${OBJECTS2DLIBNAME} \
${LIBFLAGS}

##############################################################################

#---- les fichiers objets ----

OBJECTSgraphTest=${FILESgraphTest:.cpp=.o}
OBJECTSgraphTestC=${FILESgraphTestC:.cpp=.o}

#---- librairies utilisees ----

DEPLIBS=${LIBOBJECTS2D}/lib${OBJECTS2DLIBNAME}.a

#---- realisation des l'executables (edition de liens) ----

graphTest : ${OBJECTSgraphTest} ${DEPLIBS}
	@echo
	${CC} -o graphTest ${OBJECTSgraphTest} ${LDFLAGS}
	@echo

graphTestC : ${OBJECTSgraphTestC} ${DEPLIBS}
	@echo
	$(CC) -o graphTestC ${OBJECTSgraphTestC} ${LDFLAGS}
	@echo

#---- regles -----

graphTest.o : graphTest.cpp ${INCOBJECTS2D}/Object2D.h
	${CC} ${CCFLAGS} -c graphTest.cpp

graphTestC.o : graphTestC.cpp ${INCOBJECTS2D}/CObject2D.h
	${CC} ${INCFLAGS} -DX_GUI -c graphTestC.cpp

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

CLEANING=rm -f ${TARGET} *.o a.out *.exe core *.exe.stackdump

clear :
	${CLEANING}

clean :
	${CLEANING}

##############################################################################
