#include <iostream>
#include <string>
#include "network_class.h"

using namespace std;


network::network(int _numLines){

    //numero de lineas de la red
    numLines=_numLines;
    //cantidad de lineas con las cuales una estacion hara transferencia
    int amount_transfer_lines;
    //arreglo con los nombres de las lienas con las que la estacion hara transferencia
    string names_transfer_estations =  "";
    //arreglo con los nombres de las estaciones que no son de trasnsferencia en la red
    string names_estations_in_red = "";
    //se define como "global" para que despues del primer for, el arreglo no desaparezca
    int *elemLine;


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
        //en caso de que quiera crear una linea con cero estaciones
        if (auxelemLine == 0) throw error3;
        else{
            auxelemLine+=(auxelemLine-1);

            //guardar num estaciones
            elemLine[i]=auxelemLine;

            //resevar matriz estaciones
            matrixNetwork[i]=new string[auxelemLine];
        }

    }

    string nameStation,timeStation;
    for(int i=0;i<numLines;i++){

        amount_transfer_lines = 0;
        cout<<endl;
        cout<<"ingrese las estaciones para la linea "<<i+1<<endl<<endl;
        int cont=1;

        for(int j=0;j<elemLine[i];j+=2){

            cout<<"Nota: si la estacion sera de transferencia ingrese en el apartado (Nombre) el nombre seguido de un - (estacion-t) de lo contrario ingrese el correspondiente nombre "<<endl<<endl;

            cout<<"Nombre de la estacion "<<cont++<<" : ";cin>>nameStation;
            cout<<endl;


            //en caso que desee agregar una estacion de transferencia
            if (nameStation.find("-") != string::npos){
                // preguntar si ya hay una linea en la red para verificar que los nombres de las estaciones de transfeerncia no se repitan y en caso de que se pueda permitir el ingreso de esta estacion
                if (i != 0){
                    // los dos for anidados tienen como objetivo recorrer la matriz en busca de el namestation
                    for(int m = i-1; m>=0; m--){
                        for (int l = 0; l<elemLine[i];l+=2){
                            // si encuentra que namestation es una estacion de transferencia y ademas la linea tiene permitido hacer transferncia con esta se agregara la estacion
                            if (names_transfer_estations.find(nameStation) != string::npos && ptr_estations_transfer->find(to_string(i+1)) != string::npos){

                                //eliminamos de la lista la linea en la cual ya se establecio la transferencia
                                ptr_estations_transfer->erase(ptr_estations_transfer->find(to_string(i+1)),1);

                                matrixNetwork[i][j]=nameStation+"linea "+(to_string(i+1));

                                if(j==(elemLine[i]-1)){

                                    //agregar tiempo entre estaciones

                                    for(int j=1;j<(elemLine[i]-1);j+=2){

                                        cout<<"ingrese el tiempo que tardara el tren en llegar de la estacion "<<matrixNetwork[i][j-1]<<" -> "<<matrixNetwork[i][j+1]<<"-"<<i+1<<" : ";
                                        cin>>timeStation;cout<<endl;
                                        matrixNetwork[i][j]=timeStation;

                                    }
                                }
                                break;
                            }
                            //caso en el que la fila no tenga permitido agregar la estacion de transferencia
                            else if (names_transfer_estations.find(nameStation) != string::npos && ptr_estations_transfer->find(to_string(i+1)) == string::npos) throw error2;
                            //caso en el que si tenga permitido agregar una nueva estacion de transferencia
                            else{
                                names_transfer_estations += nameStation;
                                cout <<"Ingrese con cuantas lineas la estacion tendra transferencia: ";cin>>amount_transfer_lines;
                                //en caso de que desee hacer transferncia con lineas que no estan creadas o realziar transferencia con ella misma
                                if (amount_transfer_lines >= _numLines || amount_transfer_lines == 0) throw error1;
                                else{
                                    // crear string que contiene cuales son las lineas con las cuales nameStation tendra transferencia para una futura verificacion
                                    ptr_estations_transfer = new string[amount_transfer_lines];
                                    for (int k = 0; k<amount_transfer_lines; k++){

                                        cout<<"Ingrese la linea "<<k+1<<" con la cual tendra transferencia: ";cin>>ptr_estations_transfer[k];cout<<endl;

                                        //caso en el que quiera hacer trasnferencia con ella misma o con una linea no existente
                                        if (stoi(ptr_estations_transfer[k]) > numLines || stoi(ptr_estations_transfer[k]) == i+1 || stoi(ptr_estations_transfer[k]) == 0) throw error1;

                                        matrixNetwork[i][j]=nameStation+"linea "+to_string(i+1);

                                        if(j==(elemLine[i]-1)){

                                            //agregar tiempo entre estaciones

                                            for(int j=1;j<(elemLine[i]-1);j+=2){

                                                cout<<"ingrese el tiempo que tardara el tren en llegar de la estacion "<<matrixNetwork[i][j-1]<<" -> "<<matrixNetwork[i][j+1]<<"-"<<i+1<<" : ";
                                                cin>>timeStation;cout<<endl;
                                                matrixNetwork[i][j]=timeStation;

                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                //realizar correctamente la primera iteracion y el ingreso de la estacion de transferencia que desee en la linea 1
                else{
                    //en caso de que vaya a ingresar una estacion de transferencia que ya se encuentra creada saltara un error
                    if (nameStation.find("-") != string::npos && names_transfer_estations.find(nameStation) != string::npos) throw error2;
                    names_transfer_estations += nameStation;
                    cout <<"Ingrese con cuantas lineas la estacion tendra transferencia: ";cin>>amount_transfer_lines;
                    //en caso de que desee hacer transferncia con lineas que no estan creadas o realziar transferencia con ella misma
                    if (amount_transfer_lines >= _numLines || amount_transfer_lines == 0) throw error1;
                    else{
                        // crear string que contiene cuales son las lineas con las cuales nameStation tendra transferencia para una futura verificacion
                        ptr_estations_transfer = new string[amount_transfer_lines];
                        for (int k = 0; k<amount_transfer_lines; k++){

                            cout<<"Ingrese la linea "<<k+1<<" con la cual tendra transferencia: ";cin>>ptr_estations_transfer[k];

                            //caso en el que quiera hacer trasnferencia con ella misma o con una linea no existente
                            if (stoi(ptr_estations_transfer[k]) > numLines || stoi(ptr_estations_transfer[k]) == i+1 || stoi(ptr_estations_transfer[k]) == 0) throw error1;
                            matrixNetwork[i][j]=nameStation+"linea "+(to_string(i+1));

                            if(j==(elemLine[i]-1)){

                                //agregar tiempo entre estaciones

                                for(int j=1;j<(elemLine[i]-1);j+=2){

                                    cout<<"ingrese el tiempo que tardara el tren en llegar de la estacion "<<matrixNetwork[i][j-1]<<" -> "<<matrixNetwork[i][j+1]<<"-"<<i+1<<" : ";
                                    cin>>timeStation;cout<<endl;
                                    matrixNetwork[i][j]=timeStation;

                                }
                            }
                        }
                    }
                }
            }
            else{
                //en caso de que desee agregar una estacion que es igual a otra
                if (names_estations_in_red.find(nameStation) != string::npos) throw error2;
                else{
                    names_estations_in_red += nameStation;
                    matrixNetwork[i][j]=nameStation;

                    if(j==(elemLine[i]-1)){

                        //agregar tiempo entre estaciones

                        for(int j=1;j<(elemLine[i]-1);j+=2){

                            cout<<"ingrese el tiempo que tardara el tren en llegar de la estacion "<<matrixNetwork[i][j-1]<<" -> "<<matrixNetwork[i][j+1]<<" : ";
                            cin>>timeStation;cout<<endl;
                            matrixNetwork[i][j]=timeStation;

                        }
                    }
                }
            }
        }
    }
    //eliminar toda la memoria reservada
}


void network::printNetwork(){
    cout << "RED METRO\n\n";

    for(int i=0;i<numLines;i++) {

        cout<<"Linea "<<i+1<<" | ";
        for (int j=0;j<elemLine[i];j+=2) {
            cout << matrixNetwork[i][j] << " | ";
        }
        cout<<endl;
    }
}

void network::amountline(){

    cout<<"la red metro tiene "<<numLines<<"lineas \n";

}
