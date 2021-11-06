INCLUDE = ./imagenES
LIB     = .
OBJ     = ./obj
SRC		= .
CC 		= g++ -g

all: ejecutable1

ejecutable1: $(OBJ)/ejercicio1.o
	$(CC) -o ejercicio1 $(OBJ)/ejercicio1.o $(OBJ)/imagen.o $(OBJ)/imagenES.o -I$(INCLUDE)

$(OBJ)/ejercicio1.o : ejercicio1.cpp imagen
	$(CC) -c -o $(OBJ)/ejercicio1.o ejercicio1.cpp -I$(INCLUDE)

$(OBJ)/imagenES.o: $(INCLUDE)/imagenES.h $(INCLUDE)/imagenES.cpp
	$(CC) -c -o $(OBJ)/imagenES.o $(INCLUDE)/imagenES.cpp -I./imagenES.h

$(OBJ)/imagen.o : imagen.h imagen.cpp 
	$(CC) -c -o $(OBJ)/imagen.o imagen.cpp -I$(INCLUDE)


clean:
	rm *.o
	rm ./imagenES/*.o

documentacion:
	doxygen
