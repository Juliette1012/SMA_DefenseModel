###########################################################################

#----- lib a utiliser
DIRAGENTS=../../../../../GestionAgents
INCAGENTS=${DIRAGENTS}/LibMoRis/include
LIBAGENTS=${DIRAGENTS}/LibMoRis/lib
AGENTSLIBNAME=Agents

#-------------  Appli  --------------

TARGET=ex

all: ${TARGET}

#---- les fichiers sources ----

FILESex=ex.cpp \
	A.cpp  \
	B.cpp  \
	C.cpp  \
	D.cpp  \
	E.cpp  \
	F.cpp  \
	MessageInt.cpp

###########################################################################

#---- les variables ----

CC=g++
INC=-I${INCAGENTS}
CCFLAGS=-W -Wall -Werror -pedantic ${INC}
LIBFLAGS=

LDFLAGS=\
-L${LIBAGENTS} -l${AGENTSLIBNAME} \
${LIBFLAGS}

###########################################################################

#---- les fichiers objets ----

OBJECTSex=${FILESex:.cpp=.o}

#---- librairies utilisees ----

DEPLIBS=${LIBAGENTS}/lib${AGENTSLIBNAME}.a

#--------- realisation de l'executable (edition de liens) ----

ex: ${OBJECTSex} ${DEPLIBS}
	${CC} ${OBJECTSex} ${LDFLAGS} -o ex

#------------------------------------

A.o: A.h A.cpp ${INCAGENTS}/MAS.h
	${CC} ${CCFLAGS} -c A.cpp

B.o: B.h B.cpp ${INCAGENTS}/MAS.h
	${CC} ${CCFLAGS} -c B.cpp

C.o: C.h C.cpp ${INCAGENTS}/MAS.h
	${CC} ${CCFLAGS} -c C.cpp

D.o: D.h D.cpp ${INCAGENTS}/MAS.h
	${CC} ${CCFLAGS} -c D.cpp

E.o: E.h E.cpp ${INCAGENTS}/MAS.h
	${CC} ${CCFLAGS} -c E.cpp

F.o: F.h F.cpp ${INCAGENTS}/MAS.h
	${CC} ${CCFLAGS} -c F.cpp

MessageInt.o: MessageInt.h MessageInt.cpp ${INCAGENTS}/MAS.h
	${CC} ${CCFLAGS} -c MessageInt.cpp

ex.o: ex.cpp ${INCAGENTS}/MAS.h
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

#------------- clean - clear --------

CLEANING=rm -f *.o core a.out *.exe *.exe.stackdump ${TARGET}

clear:
	${CLEANING}
clean:
	${CLEANING}
