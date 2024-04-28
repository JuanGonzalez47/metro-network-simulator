#include <iostream>
#include <string>
#include "network_class.h"

using namespace std;


network::network(int _numLines){

    numLines=_numLines;

    elemLine=new int[numLines];
    int nameLine=0;

    //arreglo numero de elemento en cada linea
    int auxelemLine;

    // Reserva de memoria para la primera dimensión que seran las filas
    matrixNetwork = new string*[numLines];
    for (int i = 0; i < numLines; ++i) {
        nameLine+=1;
        cout<<"ingrese el numero de estaciones que tendra la linea "<<nameLine<<": ";cin>>auxelemLine;
        cout<<"\n";

        auxelemLine+=(auxelemLine-1);

        //guardar num estaciones
        elemLine[i]=auxelemLine;

        //resevar matriz estaciones
        matrixNetwork[i]=new string[auxelemLine];
    }

    string nameStation,timeStation;
    for(int i=0;i<numLines;i++){

        cout<<"ingrese las estaciones para la linea "<<i+1<<endl;
        int cont=1;

        for(int j=0;j<elemLine[i];j+=2){

            string op;

            // cout<<"Nota: si la estacion sera de transferencia ingrese en el apartado (Nombre) el siguiente caracter  \T  de lo contrario ingrese el correspondiente nombre "<<endl;

            cout<<"estacion "<<cont++<<" Nombre : ";cin>>nameStation;
            cout<<endl;


            //agregar nombre estaciones

            matrixNetwork[i][j]=nameStation;

            if(j==(elemLine[i]-1)){

                //agregar tiempo entre estaciones

                for(int j=1;j<(elemLine[i]-1);j+=2){

                    cout<<"ingrese el tiempo que tardara el tren en llegar de la estacion |"<<matrixNetwork[i][j-1]<<"| a |"<<matrixNetwork[i][j+1]<<"| :";
                    cin>>timeStation;cout<<endl;
                    matrixNetwork[i][j]=timeStation;

                }
            }
        }
    }
}

void network::printNetwork(){
    cout << "RED METRO\n\n";

    cout<< "           Estaciones        "<<endl;

    for(int i=0;i<numLines;i++) {

        cout<<"Linea "<<i+1<<" | ";
        for (int j=0;j<elemLine[i];j+=2) {
            cout << matrixNetwork[i][j] << " | ";
        }
        cout << endl;
    }
}

void network::amountline(){

    cout<<"la red metro tiene "<<numLines<<"lineas \n";

}
