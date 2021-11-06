#include "imagen.h"
#include "imagenES/imagenES.h"
#include <cassert>
#include <iostream>
#include "string.h"

using namespace std;


/*******************************************************************************
*************************** FUNCIONES NECESARIAS *******************************
*******************************************************************************/

void Imagen::Swap(Imagen &I){

	int filas_aux = filas;
	filas = I.filas;
	I.filas = filas_aux;

	int cols_aux = cols;
	cols = I.cols;
	I.cols = cols_aux;

	byte ** datos_aux = img;
	img = I.img;
	I.img = datos_aux;

}

/*******************************************************************************
**************************** FUNCIONES BÁSICAS *********************************
*******************************************************************************/

Imagen::Imagen(){

	filas = 0;
	cols = 0;
	img = NULL;

}

Imagen::Imagen(int filas, int cols){

	filas = filas;
	cols = cols;
	img = new byte*[filas];
	for (int i = 0; i < filas; i++)
		img[i] = new byte[cols];

}

Imagen::Imagen(const Imagen &I){

  filas = I.filas;
	cols = I.cols;
	img = new byte*[filas];
	for (int i = 0; i < filas; i++)
		img[i] = new byte[cols];

	for (int i = 0; i < filas; i++)
		for (int j = 0; j < cols; j++)
			img[i][j] = I.img[i][j];

}

Imagen::~Imagen(){

  for (int i = 0; i < filas; i++)
		delete[] img[i];

	delete[] img;

}

/*******************************************************************************
**************************** GETTERS Y SETTERS *********************************
*******************************************************************************/

int Imagen::getNumFilas() const{

	return filas;

}

int Imagen::getNumColumnas() const{

	return cols;

}

void Imagen::setPixel(int fil, int col, byte valor){

	assert(fil < filas && col < cols);
	img[fil][col] = valor;

}

byte Imagen::getPixel(int fil, int col) const{

	assert(fil < filas && col < cols);
	byte pixel = img[fil][col];

	return pixel;

}

/*******************************************************************************
********************************** OPERADORES **********************************
*******************************************************************************/

Imagen& Imagen::operator=(const Imagen &I){

	Imagen aux (I);

	aux.Swap(*this);

	return *this;
}

	byte& Imagen::operator() (int fil, int col){

  	assert(fil < filas && col < cols);
  	return img[fil][col];

}

const byte& Imagen::operator() (int fil, int col) const{

  	assert(fil < filas && col < cols);
  	return img[fil][col];

}

/*******************************************************************************
******************************* ENTRADA Y SALIDA *******************************
*******************************************************************************/

bool Imagen::LoadImagen(const char * nombre){
	if(LeerTipoImagen(nombre) != IMG_PGM)
		return false;

	unsigned char *buffer = LeerImagenPGM(nombre, filas, cols);

	if(buffer == 0)
		return false;

	img = new byte*[filas];
	for (int i = 0; i < filas; i++)
		img[i] = new byte[cols];
	memcpy(img, buffer, sizeof(byte)*filas*cols);

	delete[] buffer;

	return true;
}
/*******************Version 1 load (Genera un core, accede fuera de memoria)
bool Imagen::LoadImagen(const char * nombre){
	const char *extension = ".pgm";
	string str(nombre);

	if (strstr(nombre, extension) == NULL)
		str += ".pgm";

	char * fichero = strdup(str.c_str());

	TipoImagen t = LeerTipoImagen(fichero);
	if (t==IMG_PGM){
		int f, c;
		unsigned char *buf = LeerImagenPGM (fichero, f, c);
		if (buf!=0){
			Imagen aux(f, c);
			for (int i = 0; i < f; i++)
				for (int j = 0; j < c; j++)
					aux(i, j) = buf[i*c + j];

			delete[] buf;
			*this = aux;
			return true;
		}
		else{
			cout << "No se ha podido cargar la imagen" << endl;
			return false;
		}
	}
	else{
		cout << "Formato de imagen incorrecto" << endl;
		return false;
	}
}
*/

bool Imagen::SaveImagen(const char * nombre){
	
	if(LeerTipoImagen(nombre) != IMG_PGM)
		return false;

	const char *extension = ".pgm";
	string str(nombre);

	if (strstr(nombre, extension)==NULL)
		str += ".pgm";

	char *fichero = strdup(str.c_str());

	return EscribirImagenPGM(fichero, img[0], filas, cols);

/* 
	const char *extension = ".pgm";
	string str(nombre);

	if (strstr(nombre, extension) == NULL)
		str += ".pgm";

	char * fichero = strdup(str.c_str());

	unsigned char *buf = new unsigned char [filas*cols];
	for (int i = 0; i < filas; i++)
		for (int j = 0; j < cols; j++)
			buf[i*cols + j] = img [i][j];

	if (EscribirImagenPGM(fichero, buf, filas, cols)){
		delete[] buf;
		return true;
	}
	else{
		delete[] buf;
		return false;
	} 
*/

}

/*******************************************************************************
********************************* UMBRAL ***************************************
*******************************************************************************/

void Imagen::Umbral(const char * origen, const char * destino, int inf, int sup){

	Imagen umbral;

	umbral.LoadImagen(origen);


	for (int i = 0; i < umbral.getNumFilas(); i++)
		for (int j = 0; j < umbral.getNumColumnas(); j++)
			if (umbral(i,j) <= inf || umbral(i,j) >= sup)
				umbral(i,j) = 255;

	if (umbral.SaveImagen(destino))
		cout << "Se ha aplicado el umbral con exito" << endl;
	else
		cout << "ERROR: No se ha aplicado el umbral" << endl;

}
