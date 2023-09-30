INCLUDE_DIRS = 
LIB_DIRS = 
CC=gcc
AS=as

CDEFS=
CFLAGS= -O0 $(INCLUDE_DIRS) $(CDEFS)
ASFLAGS= $(INCLUDE_DIRS)
LIBS= 

HFILES= hww.h
CFILES= hww.c hwc.c
ASMFILES= hwa.s

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}
AOBJS= ${ASMFILES:.s=.o}

all:	hww hwc.cod

clean:
	-rm -f *.o *.d *.cod
	-rm -f hww

distclean:
	-rm -f *.o *.d

hww: ${OBJS} ${AOBJS}
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ ${AOBJS} ${OBJS} $(LIBS)

hwc.cod: ${CFILES}
	$(CC) -S $< -o $@

depend:

.c.o: 
	$(CC) $(CFLAGS) -c $<

.s.o: 
	$(AS) $(ASFLAGS) $< -o $@
