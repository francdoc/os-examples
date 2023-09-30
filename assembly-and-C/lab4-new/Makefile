INCLUDE_DIRS = 
LIB_DIRS = 
CC=gcc
AS=as

CDEFS=
CFLAGS= -O0 $(INCLUDE_DIRS) $(CDEFS)
ASFLAGS= $(INCLUDE_DIRS)
LIBS= -lrt

HFILES= imu.h
CFILES= accel.c integ.c imu.c state.c
WFILES= accelw.c integw.c
ASMFILES= accela.s intega.s

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}
AOBJS= ${ASMFILES:.s=.o}

all:	imu imuc
cod:	accelw.cod integw.cod

clean:
	-rm -f *.o *.d *.cod
	-rm -f imu imuc

distclean:
	-rm -f *.o *.d

imuc: ${OBJS}
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ ${OBJS} $(LIBS)

imu: imu.o state.o ${AOBJS}
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ ${AOBJS} imu.o state.o $(LIBS)

depend:

integw.cod: integw.c
	$(CC) -c -S $< -o $@

accelw.cod: accelw.c
	$(CC) -c -S $< -o $@

.c.o: 
	$(CC) $(CFLAGS) -c $<

.s.o: 
	$(AS) $(ASFLAGS) $< -o $@
