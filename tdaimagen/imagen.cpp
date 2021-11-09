#include "imagen.h"
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

void	Imagen::Inicialize(int fils, int columnas, byte * buffer){
		if((fils <=0) && (columnas <=0)){
		filas =0;
		cols =0;
		img =0;
		if(buffer!=0){
			delete [] buffer;
			cerr << "Error no se puede almacenar";
			exit(1);
		}

	}else{
		filas=fils;
		cols = columnas;
		img = new byte * [filas];
		if (buffer!=0)
			img[0] = buffer;
		else
			img[0] = new byte [filas * cols];
	}

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

void Imagen::Destruye(){

  if (img!=0)
		delete [] img[0];
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

bool Imagen::LoadImagen(const char * fichero){

	if (LeerTipoImagen(fichero) != IMG_PGM){
		return false;
		cout << "Formato Incorrecto"<<endl;
	}
	byte * buffer = LeerImagenPGM (fichero, filas, cols);
	if (!buffer)
		return false;

	Destruye();
	Inicialize(filas,cols,buffer);
	return true;
}

void Imagen::SaveImagen(const char * fichero){
		EscribirImagenPGM(fichero, img[0], filas, cols);


}

/*******************************************************************************
********************************* UMBRAL ***************************************
*******************************************************************************/
double Imagen::Media(int pos_i,int pos_j, int height, int width){

		assert((pos_i>=0)&&(pos_j>=0)&&(height>0)&&(width>0));
		long suma=0;
		double resultado=0;
		int i=0,j=0;
		int lim_i = height+pos_i;
		int lim_j = width+pos_j;


		for(i=pos_i;i<lim_i;i++){
			for(j=pos_j;j<lim_j;j++) {
				suma+=img[0][i*lim_i+j];

			}
		}

		resultado = suma/(height*width);
		return resultado;
}

byte Imagen::Umbral(){

	const double epsilon=0'01;
	int t=0, t_old=0;
	double media_objeto=0,media_fondo=0;
	int nelem_objeto=0, nelem_fondo=0,  tam=filas*cols;

	t=Media(0,0,filas,cols);
	while(abs(t-t_old)>=epsilon){
		nelem_objeto=nelem_fondo=media_objeto=media_fondo=0;

	for (int i=0; i<tam;i++)
		if(img[0][i]>=t){
			nelem_objeto++;
			media_objeto+=img[0][i];
		}
		else{
			nelem_fondo++;
			media_fondo+=img[0][i];
		}
		media_objeto = media_objeto/nelem_objeto;
		media_fondo = media_fondo/nelem_fondo;
		t_old=t;
		t=(media_objeto+media_fondo)/2;
}
	return ((byte)t);

}

void Imagen::AplicarUmbral(byte t){
	int tam=filas*cols;
	for (int i=0; i<tam;i++){
		if(img[0][i]>=t){
			img[0][i]= 255;
		}
		else{
			img[0][i]=0;
		}
	}
}

/*******************************************************************************
********************************* CONTRASTE ************************************
*******************************************************************************/

byte Imagen::Max(void){
	assert((filas>0)&&(cols>0));
	int tam = filas*cols;
  int maximo = img[0][0];

  for(int i=0;i<tam;i++){
    if(maximo < img[0][i]){
			maximo=img[0][i];
		}
  }
	return ((byte)maximo);
}

byte Imagen::Min(void){
	assert((filas>0)&&(cols>0));
	int tam = filas*cols;
  int minimo = img[0][0];

  for (int i=0;i<tam;i++){
    if (minimo > img[0][i])
			minimo=img[0][i];
  }
	return ((byte)minimo);
}

void Imagen::AjustaContraste(byte minimo, byte maximo){
  double escala;
  int tam = filas*cols;
  byte minimo_actual = Min();
  byte maximo_actual = Max();
  double cociente = (double) (maximo-minimo) / (double) (maximo_actual-minimo_actual);

  for (int i=0; i< tam; i++){
    img[0][i] = minimo + cociente * (img[0][i] - minimo_actual);
  }
}
