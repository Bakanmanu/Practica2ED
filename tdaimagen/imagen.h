/****************************************************************************/
// Fichero: imagen.h
// Fichero de cabecera asociado a la biblioteca libimg.a.
// Implementacion del TDA imagen (imagen digital en niveles de gris).
/****************************************************************************/

#ifndef IMAGEN_H
#define IMAGEN_H
#include "imagenesES.h"
typedef unsigned char byte;

/**
  *  @brief T.D.A. Racional
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



  public:

/*******************************************************************************
**************************** FUNCIONES BÁSICAS *********************************
*******************************************************************************/

      /**
        * @brief Constructor por defecto de la clase
        */

      	Imagen();

      /**
        * @brief Constructor de la clase con paramentros
        * @param filas, número de filas del objeto imagen
        * @param cols, número de columnas del objeto imagen
        * @pre filas > 0 & Not NULL
        * @pre cols > 0 & Not NULL
        * @return Crea el objeto imagen
        */

        Imagen(int filas, int cols)

      /**
        * @brief Constructor de copia de imagen
        * @param I, es al objeto imagen que vamos a copiar
        */

      	Imagen(const Imagen &I);

      /**
        * @brief Destructor de la clase
        * @post se libera la memoria reservada
        */

      	~Imagen();

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
        * @param img, nombre del archivo que contiene la imagen
        * @return retorna true si se carga la imagen con éxito.
        * @pre el nombre debe tener extensión .pgm
        */

      	bool LoadImagen(const char * img);

      /**
        * @brief Guarda una imagen formato .pgm a partir de un objeto de la clase
        * @param nombre, nombre con el que se guarda la imagen
        * @return true en el caso de que se guarde la imagen con éxito.
        * @post la imagen se almacenará con la extensión .pgm
        */

      	bool SaveImagen(const char * nombre);

/*******************************************************************************
********************************* UMBRAL ***************************************
*******************************************************************************/

      /**
        * @brief Cambia los tonos de la imagen si no estan entre el umbral
        * @param origen, nombre del archivo qe queremos abrir
        * @param destino, nombre con el que queremos guardar el archivo
        * @param inf, limite inferior del umbral
        * @param suup, limite superior del umbral
        * @post la imagen se almacenará con la extensión .pgm
        */
        void Umbral(const char * origen, const char * destino, int inf, int sup){
}
#endif
