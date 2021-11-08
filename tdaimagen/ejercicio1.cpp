#include <iostream>
#include "imagen.h"

using namespace std;


void Menu(){

    int opcion=0;
    cout << "Elija opcion(1-3): " ;

    while (opcion < 1 || opcion > 4)
    {
        cin >> opcion ;
    }

    Imagen prueba;
    Imagen umbral;

    char *entrada = new char[100];
    char *salida = new char[100];
    byte u;
    int inf, sup ;

    switch (opcion)
    {

      case 1:

        cout << "***** SUBIR IMAGEN *****" << endl;

        //Cargamos la imagen
        cout << "Escriba el nombre de la imagen que quiera subir: " << endl;
        cin >> entrada;
        prueba.LoadImagen(entrada);

        //Guardar la imagen
        cout << "Escriba el nombre con el que quiera guardar la imagen: " << endl;
        cin >> salida;
        prueba.SaveImagen(salida);


      break;

      case 2:

        cout << "***** UMBRAL *****" << endl;

        //Subimos la foto
        cout << "Escriba el nombre de la imagen que quiera subir: " << endl;
        cin >> entrada;
        umbral.LoadImagen(entrada);
        cout << "Dimensiones de la imagen seleccionada: " << umbral.getNumFilas() << 'x' << umbral.getNumColumnas()<< endl;

        //Introduciomos los valores de los umbrales
        cout << "Le efectuamos el umbral" << endl;
        u = umbral.Umbral();
        umbral.AplicarUmbral(u);

        //Fichero de salida
        cout << "Escriba el nombre con el que quiera guardar la imagen: " << endl;
        cin >> salida;
        umbral.SaveImagen(salida);



        //prueba.SaveImagen(salida.c_str());

      break;

      case 3:

        cout << "***** ZOOM *****" << endl;

        cout << "Todavia no implementado" << endl;

      break;

      default:

      break;
}

};

int main(){
    Menu();
    return 0;
    }
