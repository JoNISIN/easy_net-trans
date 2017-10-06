CC = gcc
RUN = main
OBJ = libnetinfo

all:$(RUN).exe $(OBJ).o
$(OBJ).o:$(OBJ).c $(OBJ).h
	$(CC) -c $< -lws2_32
$(RUN).exe:$(RUN).c $(OBJ).o
	$(CC) -o $@ $^ -lws2_32
clean:
	del *.o $(RUN).exe