##############################################################################

#----- lib a obtenir
DIRAGENTS2D=../../../GestionAgents2D
INCAGENTS2D=${DIRAGENTS2D}/LibAgents2D/include
LIBAGENTS2D=${DIRAGENTS2D}/LibAgents2D/lib
AGENTS2DLIBNAME=Agents2D
#----- lib a utiliser
DIRAGENTS=../../../GestionAgents
INCAGENTS=${DIRAGENTS}/LibMoRis/include
LIBAGENTS=${DIRAGENTS}/LibMoRis/lib
AGENTSLIBNAME=Agents
#----- lib a utiliser
DIROBJECTS2D=../../../GestionObjects2D
INCOBJECTS2D=${DIROBJECTS2D}/LibObjects2D/include
LIBOBJECTS2D=${DIROBJECTS2D}/LibObjects2D/lib
OBJECTS2DLIBNAME=Object2D

#---- la bibliotheque a obtenir

LIB=${LIBAGENTS2D}/lib${AGENTS2DLIBNAME}.a

TARGET=${LIB}

all: ${TARGET}

#---- les fichiers sources ----

FILESlibAgents2D=Agent2D.cpp Decor.cpp

##############################################################################

#---- les variables ----

CC=g++
INC_APPLE=-I/usr/X11/include
INC=-I${INCAGENTS2D} -I${INCAGENTS} -I${INCOBJECTS2D} ${INC_APPLE}
CCFLAGS=-W -Wall -Werror ${INC} -DX_GUI # Avant APPLE, -pedantic en plus..!

##############################################################################

#---- les fichiers objets ----

OBJECTSlibAgents2D=${FILESlibAgents2D:.cpp=.o}

#----- realisation de la bibliotheque

${LIB} : ${OBJECTSlibAgents2D}
	ar -rs $(TARGET) ${OBJECTSlibAgents2D}

#----- regle

Agent2D.o : Agent2D.cpp ${INCAGENTS2D}/Agent2D.h
	${CC} ${CCFLAGS} -c Agent2D.cpp

#------- la regle par defaut (.c/cpp --> .o) ----

.c.o :
	@echo
	${CC} -o $*.o -c ${CCFLAGS} $<
	@echo

.cpp.o :
	@echo
	${CC} -o $*.o -c ${CCFLAGS} $<
	@echo

#------------- clean - clear --------

CLEANING=rm -f *.o ${LIB}

clear :
	${CLEANING}
clean :
	${CLEANING}
