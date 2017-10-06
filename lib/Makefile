CC = gcc
LIB = libnet.o libnetinfo.o libfiletool.o
M = main
SS =  -lws2_32
EXE = EzTrans.exe

all:$(EXE)
$(M).o:$(M).c $(M).h $(LIB)
	$(CC) -c $(M).c $(SS)
$(EXE):$(M).o $(LIB)
	$(CC) $(^) $(SS) -o ../bin/$@