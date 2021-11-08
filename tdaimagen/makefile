INCLUDE = ./imagenES
LIB     = .
OBJ     = .
SRC	= .
CC = g++

all: ejecutable1

ejercicio1 : ejercicio1.cpp imagen
	$(CC) -c ejercicio1.cpp -I$(INCLUDE)

imagenS: $(INCLUDE)/imagenES.h $(INCLUDE)/imagenES.cpp
	$(CC) -c $(INCLUDE)/imagenES.cpp -I./imagenES

imagen : imagenS imagen.h imagen.cpp imagenES.o
	$(CC) -c imagen.cpp -I$(INCLUDE)

ejecutable1: ejercicio1 ejercicio1.o
	$(CC) -o ejercicio1 ejercicio1.o imagen.o imagenES.o -I$(INCLUDE)


clean:
	rm *.o
	rm ./imagenES/*.o

documentacion:
	doxygen
