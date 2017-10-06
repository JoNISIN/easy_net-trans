CC = gcc
LIB = libnet.o
SS =  -lws2_32
all:libnet.o
libnet.o:libnet.c libnet.h
	$(CC) -c -o ../$@ $< $(SS)
clean:
	del *.o *.d core