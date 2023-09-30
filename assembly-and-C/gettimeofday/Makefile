INCLUDE_DIRS = 
LIB_DIRS = 
CC=gcc

CDEFS=
CFLAGS= -O3 $(INCLUDE_DIRS) $(CDEFS)
LIBS= 

HFILES= perflib.h
CFILES= perfmon.c perflib.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	perfmon

clean:
	-rm -f *.o *.d
	-rm -f perfmon

distclean:
	-rm -f *.o *.d

perfmon: ${OBJS}
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $@.o perflib.o $(LIBS)

depend:

.c.o:
	$(CC) $(CFLAGS) -c $<
