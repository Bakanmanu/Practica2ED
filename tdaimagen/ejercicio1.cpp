#include <iostream>
#include "imagen.h"

using namespace std;


void Menu(){

    int opcion=0;
    cout <<
    "Elija opcion:\n"
    <<  "1.Subir y guardar una imagen de prueba.\n"
    <<  "2.Aplicar un umbral a una imagen.\n"
    <<  "3.Hacer zoom a una imagen.\n"
    <<  "4.Contrastar una imagen.\n"
    <<endl;

    while (opcion < 1 || opcion > 4)
    {
        cin >> opcion ;
    }

    Imagen prueba;
    Imagen umbral;
    Imagen contraste;

    char *entrada = new char[100];
    char *salida = new char[100];
    byte u;
    int inf, sup, minimo, maximo ;

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

      case 4:

        cout << "***** CONTRASTE *****" << endl;

        cout << "Escriba el nombre de la imagen que quiera subir: " << endl;
        cin >> entrada;
        contraste.LoadImagen(entrada);
        cout << "Dimensiones de la imagen seleccionada: " << contraste.getNumFilas() << 'x' << contraste.getNumColumnas()<< endl;


        cout << "Cual quieres que sea el nuevo minimo de la imagen: "<<endl;
        cin >> minimo;

        cout << "Cual quieres que sea el nuevo maximo de la imagen: "<<endl;
        cin >> maximo;

        cout << "Efectuamos el contraste" << endl;
        contraste.AjustaContraste(minimo, maximo);

        cout << "Escriba el nombre con el que quiera guardar la imagen: " << endl;
        cin >> salida;
        contraste.SaveImagen(salida);

      break;

      default:

      break;
}

};

int main(){
    Menu();
    return 0;
    }
