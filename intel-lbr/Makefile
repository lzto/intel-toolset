all: liblbr.a

CFLAGS := $(CFLAGS) -fPIC -g

liblbr.a: lbr.o
	ar cr liblbr.a lbr.o
lbr.o:
	$(CC) $(CFLAGS) -I./ lbr.c -c
clean:
	rm lbr.o liblbr.a
