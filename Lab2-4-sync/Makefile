#CFLAGS = -DDEBUG
CFLAGS =

beowulfpc: beowulfpc.c
	gcc $(CFLAGS) -o beowulfpc  beowulfpc.c -lrt -pthread

clean:
	rm -f beowulfpc child-log parent-log beowulfpipe
