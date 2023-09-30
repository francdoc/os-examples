NCLUDE_DIRS = 
LIB_DIRS = 

CDEFS= 
CFLAGS= -O0 -g $(INCLUDE_DIRS) $(CDEFS)
LIBS= -lpthread -lrt

PRODUCT=posix_clock posix_linux_demo posix_mq pmq_send pmq_receive

HFILES=
CFILES= posix_clock.c posix_linux_demo.c posix_mq.c pmq_send.c pmq_receive.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	${PRODUCT}

clean:
	-rm -f *.o *.NEW *~ *.d
	-rm -f ${PRODUCT} ${GARBAGE}

posix_linux_demo:	posix_linux_demo.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ posix_linux_demo.o $(LIBS)

posix_clock:	posix_clock.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ posix_clock.o $(LIBS)

posix_mq:	posix_mq.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ posix_mq.o $(LIBS)

pmq_send:	pmq_send.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ pmq_send.o $(LIBS)

pmq_receive:	pmq_receive.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ pmq_receive.o $(LIBS)

depend:

.c.o:
	$(CC) -MD $(CFLAGS) -c $<
