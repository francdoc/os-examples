INCLUDE_DIRS = 
LIB_DIRS = 
CC=gcc
AS=as

CDEFS=
CFLAGS= -O0 $(INCLUDE_DIRS) $(CDEFS)
ASFLAGS= $(INCLUDE_DIRS)
LIBS= 

HFILES= lcmw.h
CFILES= lcmw.c lcmc.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}
AOBJS= ${ASMFILES:.s=.o}

all:	lcmw lcmc.cod

clean:
	-rm -f *.o *.d
	-rm -f lcmw

distclean:
	-rm -f *.o *.d

lcmw: ${OBJS} ${AOBJS}
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ ${AOBJS} ${OBJS} $(LIBS)

lcmc.cod: lcmc.c
	$(CC) -O0 -S $< -o $@

depend:

.c.o: 
	$(CC) $(CFLAGS) -c $<

.s.o: 
	$(AS) $(ASFLAGS) $< -o $@
