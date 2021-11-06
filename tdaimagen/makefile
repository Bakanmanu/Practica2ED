INCLUDE =./imagenES
LIB     =.
OBJ     =obj
SRC		=.
CC 		=g++

all: ejecutable1

ejecutable1: /$(OBJ)/ejercicio1.o /$(OBJ)/imagenES.o /$(OBJ)/imagen.o
	$(CC) -g -o ejercicio1 $(OBJ)/ejercicio1.o $(OBJ)/imagen.o $(OBJ)/imagenES.o -I$(INCLUDE)

/$(OBJ)/ejercicio1.o: ejercicio1.cpp imagen.h
	$(CC) -g -c -o $(OBJ)/ejercicio1.o ejercicio1.cpp -I$(INCLUDE)

/$(OBJ)/imagenES.o: $(INCLUDE)/imagenES.h $(INCLUDE)/imagenES.cpp
	$(CC) -g -c -o $(OBJ)/imagenES.o $(INCLUDE)/imagenES.cpp -I./imagenES.h

/$(OBJ)/imagen.o: imagen.h imagen.cpp $(INCLUDE)/imagenES.h
	$(CC) -g -c -o $(OBJ)/imagen.o imagen.cpp -I.


clean:
	rm *.o
	rm ./imagenES/*.o

documentacion:
	doxygen
