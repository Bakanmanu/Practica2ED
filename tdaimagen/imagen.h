/****************************************************************************/
// Fichero: imagen.h
// Fichero de cabecera asociado a la biblioteca libimg.a.
// Implementacion del TDA imagen (imagen digital en niveles de gris).
/****************************************************************************/

#ifndef _IMAGEN_H
#define _IMAGEN_H
#include "imagenES.h"
typedef unsigned char byte;

/**
  *  @brief T.D.A. Imagen
  *
  * Una instancia @e I del tipo de datos abstracto @c Imagen es un objeto
  * representado por dos números enteros que representan el número de filas y
  * de columnas respectivamente, así como un array bidimensional de char para
  * representar la imagen en forma de matriz
  *
  * @author Claudia Salado Méndez
  * @author Manuel Zafra Mota
  * @date Noviembre 2021
  */
class Imagen{
  private:
    int filas;    // Número de filas de la imagen
    int cols;     // Número de columnas de la imagen
    byte **img;   // La imagen en si: una matriz dinamica 2D de bytes
    void Swap(Imagen &I);



  public:

/*******************************************************************************
**************************** FUNCIONES BÁSICAS *********************************
*******************************************************************************/

      /**
        * @brief Constructor por defecto de la clase
        */

      	Imagen();

        /**
          * @brief Inicializador de la clase con paramentros
          * @param fils, número de filas del objeto imagen
          * @param columnas, número de columnas del objeto imagen
          * @param buffer, donde guardaremos nuestra imagen
          * @pre filas > 0 & Not NULL
          * @pre cols > 0 & Not NULL
          * @return Crea el objeto imagen
          */

        void Inicialize(int fils, int columnas, byte* buffer);

      /**
        * @brief Constructor de la clase con paramentros
        * @param filas, número de filas del objeto imagen
        * @param cols, número de columnas del objeto imagen
        * @pre filas > 0 & Not NULL
        * @pre cols > 0 & Not NULL
        * @return Crea el objeto imagen
        */

        Imagen(int filas, int cols);

      /**
        * @brief Constructor de copia de imagen
        * @param I, es al objeto imagen que vamos a copiar
        */

      	Imagen(const Imagen &I);

      /**
        * @brief Destructor de la clase
        * @post se libera la memoria reservada
        */

      	void Destruye();

/*******************************************************************************
**************************** GETTERS Y SETTERS *********************************
*******************************************************************************/

      /**
        * @brief Get del número de filas
        * @return Devuelve el número de filas de la matriz de imagen
        */

      	int getNumFilas() const;

      /**
        * @brief Get del número de columnas
        * @return Devuelve el número de columnas de la matriz de imagen
        */

	      int getNumColumnas() const;

      /**
        * @brief Asignación de un valor de gris a un pixel
        * @param fil, número de fila del pixel que vamos a añadir
        * @param col, número de columna del pixel que vamos a añadir
        * @param valor, numero entre 0 y 255 que corresponde a un color en la escala de grises
        * @return Asigna al pixel(i,j) el color correspondiente al valor introduciodo.
        * @pre fil >= 0 & NOT NULL
        * @pre col >= 0 & NOT NULL
        * @pre valor >= 0 & NOT NULL
        */

      	void setPixel(int fil, int col, byte valor);

      /**
        * @brief Obtiene el valor del pixel de la fila y columna introducidas
        * @param fil, número de la fila del pixel
        * @param col, número de la columna del pixel
        * @return el valor entre 0 y 255 (el color) del pixel
        * @pre fil >= 0 & NOT NULL
        * @pre col >= 0 & NOT NULL
        */

      	byte getPixel(int fil, int col) const;

/*******************************************************************************
********************************** OPERADORES **********************************
*******************************************************************************/

      /**
        * @brief Operador de Asignación
        * @return devuelve el control del objeto
        */

      	Imagen & operator=(const Imagen &I);

      /**
        * @brief Sobrecarga del operador()
        * @param fil número de la fila del pixel
        * @param col número de la columna del pixel
        * @return valor del pixel comprendido entre 0 y 255
        * @pre fil >= 0 & NOT NULL
        * @pre col >= 0 & NOT NULL
        */

        byte & operator() (int fil, int col);

      /**
        * @brief Sobrecarga del operador() const
        * @param fil número de la fila del pixel
        * @param col número de la columna del pixel
        * @return valor del pixel comprendido entre 0 y 255
        * @pre fil >= 0 & NOT NULL
        * @pre col >= 0 & NOT NULL
        */

        const byte &operator() (int fil, int col) const;

/*******************************************************************************
******************************* ENTRADA Y SALIDA *******************************
*******************************************************************************/

      /**
        * @brief Carga un archivo que sea una imagen como  objeto de la clase
        * @param nombre, nombre del archivo que contiene la imagen
        * @return retorna true si se carga la imagen con éxito.
        * @pre el nombre debe tener extensión .pgm
        */

      	bool LoadImagen(const char * nombre);

      /**
        * @brief Guarda una imagen formato .pgm a partir de un objeto de la clase
        * @param nombre, nombre con el que se guarda la imagen
        * @return true en el caso de que se guarde la imagen con éxito.
        * @post la imagen se almacenará con la extensión .pgm
        */

      	void SaveImagen(const char * nombre);

/*******************************************************************************
********************************* UMBRAL ***************************************
*******************************************************************************/

      /**
        * @brief Busca el tono intermedio de grises de la imagen
        * @param pos_i, posicion de las filas desde la que inicializamos
        * @param pos_j, posicion de las columnas desde la que inicializamos
        * @param height, numero de filas
        * @param width, numero de columnas
        * @post un double de la media.
        */

        double Media(int pos_i,int pos_j, int height, int width);

      /**
        * @brief Calcula de forma automatica el valor del umbral
        * @post Devuelve el valor del umbral.
        */

        byte Umbral();

      /**
        * @brief Aplica el umbral a una imagen
        * @param t, es el valor del umbral
        */

        void AplicarUmbral(byte t);

/*******************************************************************************
********************************* CONTRASTE ************************************
*******************************************************************************/

      /**
        * @brief Calcula el byte maximo de una imagen
        * @post Devuelve el byte maximo
        */

        byte Max(void);

      /**
        * @brief Calcula el byte minimo de una imagen
        * @post Devuelve el byte minimo
        */

        byte Min(void);


      /**
        * @brief Efectua el contraste a una imagen a partir del min y max que le pasemos.
        * @param minimo, valor minimo que queremos que tenga el byte de la imagen
        * @param maximo, valor maximo que queremos que tenga el byte de la imagen
        * @post la imagen contrastada.
        */

        void AjustaContraste(byte minimo, byte maximo);


/*******************************************************************************
************************************* ZOOM *************************************
*******************************************************************************/

      /**
       * @brief Realiza un zoom en una porción de la imagen mediante interpolación.
       * @param entrada, Nombre del archivo de la imagen a la que hacer zoom.
       * @param salida, Nombre del archivo que tendrá la imagen con el zoom realizado.
       * @param x1, coordenada del eje x de la esquina superior izquierda de la porción de la imagen a la que hacer zoom.
       * @param y1, coordenada del eje y de la esquina superior izquierda de la porción de la imagen a la que hacer zoom.
       * @param x2, coordenada del eje x de la esquina inferior derecha de la porcion de la imagen a la que hacer zoom.
       * @param y2, coordenada del eje x de la esquina inferior derecha de la porción de la imagen a la que hacer zoom.
       * @pre x1 > 0 & NOT NULL
       * @pre y1 > 0 & NOT NULL
       * @pre x2 > 0 & NOT NULL
       * @pre y2 > 0 & NOT NULL
       * @pre La porción generada por las coordenadas debe ser cuadrada.
       * @pre entrada y salida deben ser archivos con la extensión .pgm.
       * @pre x1 < x2
       * @pre y1 < y2       
       */

      void Zoom(int x1, int y1, int x2, int y2);

      /**
       * @brief Calcula si la porción dada es cuadrada o no
       * @param x1, Valor de la coordenada x de la esquina superior izquierda.
       * @param y1, Valor de la coordenada y de la esquina superior izquierda.
       * @param x2, Valor de la coordenada x de la esquina inferior derecha.
       * @param y2, Valor de la coordenada y de la esquina inferior derecha.
       * @return Devuelve si la porción generada es cuadrada o no.
       * @pre x1 > 0 & NOT NULL
       * @pre y1 > 0 & NOT NULL
       * @pre x2 > 0 & NOT NULL
       * @pre y2 > 0 & NOT NULL
       * @pre x1 < x2
       * @pre y1 < y2
       */ 

      bool EsCuadrada(int x1, int y1, int x2, int y2);


      /**
       * @brief Recorta la porcion de la imagen a la que queremos hacer zoom.
       * @param buffer, Array que contiene la imagen de donde queremos recortar la porcion a la que hacer el zoom
       * @param x1, Valor de la coordenada x de la esquina superior izquierda.
       * @param y1, Valor de la coordenada y de la esquina superior izquierda.
       * @param x2, Valor de la coordenada x de la esquina inferior derecha.
       * @param y2, Valor de la coordenada y de la esquina inferior derecha.
       * @return, Devuelve un buffer con la porcion recortada de la imagen.
       * @pre x1 > 0 & NOT NULL
       * @pre y1 > 0 & NOT NULL
       * @pre x2 > 0 & NOT NULL
       * @pre y2 > 0 & NOT NULL
       * @pre x1 < x2
       * @pre y1 < y2
       */

      byte* PorcionImagen(unsigned char * buffer, int x1, int y1, int x2, int y2);  

      /**
       * @brief, Calcula la media por exceso de los valores para realizar la interpolacion.
       * @param valor1, Primer valor con el que hacer la media.
       * @param valor2, Segundo valor con el que hacer la media.
       * @return, Devuelve la media por exceso de ambos valores dados.
       * @pre valor1 <= 0 & NOT NULL
       * @pre valor2 <= 0 & NOT NULL
       */
      byte MediaZoom(byte valor1, byte valor2);    

};
#endif
