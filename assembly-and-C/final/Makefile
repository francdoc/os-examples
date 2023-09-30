INCLUDE_DIRS = 
LIB_DIRS = 
CC=gcc
AS=as

CDEFS=
CFLAGS= -O0 $(INCLUDE_DIRS) $(CDEFS)
ASFLAGS= $(INCLUDE_DIRS)
LIBS= 

HFILES= sortw.h
CFILES= sortw.c sortc.c
ASMFILES= sorta.s

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}
AOBJS= ${ASMFILES:.s=.o}

all:	sortw sortc.cod

clean:
	-rm -f *.o *.d *.cod
	-rm -f sortw

distclean:
	-rm -f *.o *.d

sortw: ${OBJS} ${AOBJS}
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ ${AOBJS} ${OBJS} $(LIBS)

sortc.cod: sortc.c
	$(CC) -O0 -S $< -o $@

depend:

.c.o: 
	$(CC) $(CFLAGS) -c $<

.s.o: 
	$(AS) $(ASFLAGS) $< -o $@
