INCLUDE_DIRS = 
LIB_DIRS = 
CC = gcc

CDEFS= 
CFLAGS= -O0 -g $(INCLUDE_DIRS) $(CDEFS)
LIBS= -laio -lpthread

PRODUCT=aio-stress

HFILES=
CFILES= aio-stress.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	${PRODUCT}

clean:
	-rm -f *.o *.NEW *~ *.d a335*.ppm a335*.pgm
	-rm -f ${PRODUCT} ${GARBAGE}

aio-stress:	aio-stress.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ aio-stress.o $(LIBS)

depend:

.c.o:
	$(CC) -MD $(CFLAGS) -c $<
