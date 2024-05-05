#include <iostream>
#include <string>
#include "network_class.h"
#include "line_class.h"

void menu(){
    char op;
    int lines;
    cout<<"Bienvenido a la simulacion de una red metro\n";
    cout<<"ingrese el numero de lineas que tendra la red metro: ";cin>>lines;

    //instanciar la calse network
    //network red(lines);

    //inicializar clase

    cout<<"si desea saber cuantas lineas tiene la red metro ingrese 1 "<<endl;
    cout<<"si desea saber cuantas estaciones tiene la red metro ingrese 2 "<<endl;
    cout<<"si desea agregar lineas a la red metro ingrese 3 "<<endl;
    cout<<"si desea eliminar lineas a la red metro ingrese 4 "<<endl<<endl;

    cout<<"si desea saber cuantas estaciones tiene una linea especifica de la red metro ingrese 5 "<<endl;
    cout<<"si desea saber si una estacion cualquiera pertenece a una linea especifica ingrese 6 "<<endl;
    cout<<"si desea agregar estaciones a una linea especifica ingrese 7 "<<endl;
    cout<<"si desea eliminar estaciones a una linea especifica ingrese 8 "<<endl;
    cout<<"si desea conocer el tiempo que tarda un tren en ir de una estacion a otra en una linea especifica ingrese cualquier carcater"<<endl;

    cout<<"ingrese la opcion: ";cin>>op;

    switch (op) {

    case '1':



        //
        break;
    case '2':

        //
        break;
    case '3':



        while(true){

             char volver;



            cout<<"si desea seguir agregando lineas ingrese 1 de lo contrario ingrese cualquier caracter para volver al menu principal ";cin>>volver;
            cout<<endl;
            if(volver!=1) break;

        }
        //
        break;
    case '4':

        while(true){

            char volver;



            cout<<"si desea seguir eliminando lineas ingrese 1 de lo contrario ingrese cualquier caracter para volver al menu principal ";cin>>volver;
            cout<<endl;
            if(volver!=1) break;

        }

        break;
        //
    case '5':

        //
        break;
    case '6':
        //
        break;
    case '7':


        while(true){

            char volver;



            cout<<"si desea seguir agregando estaciones ingrese 1 de lo contrario ingrese cualquier caracter para volver al menu principal ";cin>>volver;
            cout<<endl;
            if(volver!=1) break;

        }
        //
        break;
    case '8':

        while(true){

            char volver;


            cout<<"si desea seguir eliminando estaciones ingrese 1 de lo contrario ingrese cualquier caracter para volver al menu principal ";cin>>volver;
            cout<<endl;
            if(volver!=1) break;

        }
        break;

    default:

         //tiempos

        while(true){

            char volver;



            cout<<"si desea conocer mas timepos entre estaciones en una lineas especifica ingrese 1 de lo contrario ingrese cualquier caracter para volver al menu principal ";cin>>volver;
            cout<<endl;
            if(volver!=1) break;

        }

    }

}

//funciones auxuliares

//definir una plantilla para redimensionar elementos en ptr_line que es de tipo string y matrixnetwork que es de line
template<typename T>
T resizeArreglo(T*arreglo,int initial_size, int new_size){

    //crear una copia para guardar los elementos
    T copy=new T[initial_size];
    for(unsigned int i=0;i<initial_size;i++){
        copy[i]=arreglo[i];
    }
    //liberar memoria
    delete [] arreglo;
    //reservar memoria con la nueva dimension
    T new_arreglo=new T[(new_size)];

    //ingresar el nuevo elemento y los que tenia
    for(unsigned int i=0;i<initial_size;i++){
        new_arreglo[i]==copy[i];
    }
}






