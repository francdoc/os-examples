INCLUDE_DIRS = 
LIB_DIRS = 
CC=gcc
AS=as

CDEFS=
CFLAGS= -O0 $(INCLUDE_DIRS) $(CDEFS)
ASFLAGS= $(INCLUDE_DIRS)
LIBS= 

HFILES= gcdw.h
CFILES= gcdw.c gcdc.c
ASMFILES= gcda.s

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}
AOBJS= ${ASMFILES:.s=.o}

all:	gcdw gcdc.cod

clean:
	-rm -f *.o *.d *.cod
	-rm -f gcdw

distclean:
	-rm -f *.o *.d

gcdw: ${OBJS} ${AOBJS}
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ ${AOBJS} ${OBJS} $(LIBS)

gcdc.cod: gcdc.c
	$(CC) -O0 -S $< -o $@

depend:

.c.o: 
	$(CC) $(CFLAGS) -c $<

.s.o: 
	$(AS) $(ASFLAGS) $< -o $@
