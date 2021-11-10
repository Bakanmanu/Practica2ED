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
	img[0] = new byte[filas*cols];

}

Imagen::Imagen(const Imagen &I){

  	filas = I.filas;
	cols = I.cols;
	img[0] = new byte[filas*cols];
	img[0] = I.img[0];
	
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


/*******************************************************************************
************************************ ZOOM **************************************
*******************************************************************************/

void Imagen::Zoom(int x1, int y1, int x2, int y2){
	
	if (EsCuadrada(x1, y1, x2, y2)){
		int lado = x2-x1+1;
		int lado_zoom = lado*2;
		int tam_zoom = lado_zoom*lado_zoom;
		byte * porcion = PorcionImagen(img[0], x1, y1, x2, y2);		//array con la porcion a aumentar de la imagen
		byte *zoom = new unsigned char[tam_zoom]; 				//buffer de la imagen con el zoom realizado
		
		//Ajuste del buffer para dejar los huecos para realizar la interpolación a continuación
		for (int i=0, k=0;i<lado; i++, k+=2){										//contea filas, k es el valor de la fila para el buffer de zoom, ya que hay que dejar una fila libre para la interpolacion de filas. 
			for (int j=0;j<lado; j++){												//contea columnas		
				zoom[(k*lado+j)*2] = porcion[i*lado+j];								//Esto asigna los valores con un hueco para la interpolacion de columnas
			}
		}
		
		//Interpolacion columnas
		for (int i=0, k=0;i<lado; i++, k+=2){												//contea filas, k es el valor de la fila para el buffer de zoom, ya que hay que dejar una fila libre para la interpolacion de filas. 
			for (int j=0;j<lado; j++){														//contea columnas		
				zoom[(k*lado+j)*2+1] = MediaZoom(porcion[i*lado+j],porcion[i*lado+j+1]); 	//Aqui se introducen los valores interpolados en los huecos dejados anteriomente
			}
		}
		
		//Interpolacion filas
		for(int i=0; i<lado_zoom-2; i+=2){
			for (int j=0; j<lado_zoom; j++){
				zoom[(i+1)*lado_zoom+j] = MediaZoom(zoom[i*lado_zoom+j], zoom[(i+2)*lado_zoom+j]);
			}
		}

		filas = lado_zoom;
		cols = lado_zoom;
		img[0] = zoom;
	}
}


bool Imagen::EsCuadrada(int x1, int y1, int x2, int y2){
	
	bool esCuadrado = false;
	int lado_x, lado_y;
	if(x1<x2 && y1<y2){
		lado_x = x2-x1;
		lado_y = y2-y1;
		if(lado_x == lado_y)
			esCuadrado = true;
		
	}else{
		cout << "Coordenadas introducidas incorrectamente."<<endl;
	}
	return esCuadrado;
}


byte* Imagen::PorcionImagen(byte * buffer, int x1, int y1, int x2, int y2){
	
	int tam = x2-x1+1;
	byte *buffer_porcion = new byte[tam*tam];

	for(int i=x1, k=0; i<=x2 && k<tam; i++, k++)					//Este for contea las filas
		for(int j=y1, l=0; j<=y2 && l<tam; j++, l++) 			//Este for contea las columnas
			buffer_porcion[k*tam+l]=buffer[i*getNumFilas()+j];
	return buffer_porcion;
}

byte Imagen::MediaZoom(byte valor1, byte valor2){
	int media = 0;
	if(((int) valor1 + (int) valor2)%2 == 0){
		media = (valor1+valor2)/2;
	}else{
		media = (valor1+valor2)/2 + 1;
	}
	return (byte) media;
}
