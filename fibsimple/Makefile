INCLUDE_DIRS = 
LIB_DIRS = 
CC = g++

CDEFS=
CFLAGS= -O3 -msse3 $(INCLUDE_DIRS) $(CDEFS)
#CFLAGS= -O3 -msse3 -malign-double $(INCLUDE_DIRS) $(CDEFS)
LIBS= 

PRODUCT=fib

HFILES= 
CPPFILES= fib.cpp

SRCS= ${HFILES} ${CPPFILES}
OBJS= ${CPPFILES:.cpp=.o}

all:	${PRODUCT}

clean:
	-rm -f *.o *.NEW *~
	-rm -f ${PRODUCT} ${DERIVED} ${GARBAGE}

${PRODUCT}:	${OBJS}
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

depend:

.cpp.o:
	$(CC) $(CFLAGS) -c $<
