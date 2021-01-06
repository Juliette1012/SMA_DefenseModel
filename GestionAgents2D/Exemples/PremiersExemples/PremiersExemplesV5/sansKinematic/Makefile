##############################################################################

#----- lib a utiliser
DIRAGENTS2D=../../../../../GestionAgents2D
INCAGENTS2D=${DIRAGENTS2D}/LibAgents2D/include
LIBAGENTS2D=${DIRAGENTS2D}/LibAgents2D/lib
AGENTS2DLIBNAME=Agents2D
#----- lib a utiliser
DIRAGENTS=../../../../../GestionAgents
INCAGENTS=${DIRAGENTS}/LibMoRis/include
LIBAGENTS=${DIRAGENTS}/LibMoRis/lib
AGENTSLIBNAME=Agents
#----- lib a utiliser
DIROBJECTS2D=../../../../../GestionObjects2D
INCOBJECTS2D=${DIROBJECTS2D}/LibObjects2D/include
LIBOBJECTS2D=${DIROBJECTS2D}/LibObjects2D/lib
OBJECTS2DLIBNAME=Object2D

#---- le programme a obtenir (cible principale) ----

TARGET=ex

all : ${TARGET}

#---- les fichiers sources ----

FILESex=ex.cpp Environnement.cpp Rond.cpp Label.cpp MessageColor.cpp

##############################################################################

#---- les variables ----

CC=g++

INCFLAGS_STD=-I${INCAGENTS2D} -I${INCAGENTS} -I${INCOBJECTS2D}
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
-L${LIBAGENTS}    -l${AGENTSLIBNAME}    \
-L${LIBOBJECTS2D} -l${OBJECTS2DLIBNAME} \
-L${LIBAGENTS2D}  -l${AGENTS2DLIBNAME}  \
${LIBFLAGS}

##############################################################################

#---- les fichiers objets ----

OBJECTSex=${FILESex:.cpp=.o}

#---- librairies utilisees ----

DEPLIBS=${LIBAGENTS2D}/lib${AGENTS2DLIBNAME}.a \
${LIBAGENTS}/lib${AGENTSLIBNAME}.a             \
${LIBOBJECTS2D}/lib${OBJECTS2DLIBNAME}.a

#---- realisation de l'executable (edition de liens) ----

ex : ${OBJECTSex} ${DEPLIBS}
	@echo
	${CC} -o ex ${OBJECTSex} ${LDFLAGS}
	@echo

#---- regle ----

ex.o : ex.cpp ${INCAGENTS2D}/Agent2D.h
	${CC} ${CCFLAGS} -c ex.cpp

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

clean :
	${CLEANING}

clear :
	${CLEANING}

##############################################################################
