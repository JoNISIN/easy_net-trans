CC = gcc
LIB = libfiletool
all:$(LIB).o
$(LIB).o:$(LIB).c $(LIB).h
	$(CC) -c -o ../$@ $< $(SS)
clean:
	del *.o *.d core