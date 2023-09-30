INCLUDE_DIRS = 
LIB_DIRS = 
CC=gcc
AS=as

CDEFS=
CFLAGS= -O0 $(INCLUDE_DIRS) $(CDEFS)
ASFLAGS= $(INCLUDE_DIRS)
LIBS= 

HFILES= fibw.h
CFILES= fibw.c fibc.c
ASMFILES= fiba.s

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}
AOBJS= ${ASMFILES:.s=.o}

all:	fibw fibc.cod

clean:
	-rm -f *.o *.d
	-rm -f fibw

distclean:
	-rm -f *.o *.d

fibw: ${OBJS} ${AOBJS}
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ ${AOBJS} ${OBJS} $(LIBS)

fibc.cod: ${CFILES}
	$(CC) -S $< -o $@

depend:

.c.o: 
	$(CC) $(CFLAGS) -c $<

.s.o: 
	$(AS) $(ASFLAGS) $< -o $@
