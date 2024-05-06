#include <iostream>
#include <string>
#include "network_class.h"
#include "line_class.h"

//funciones auxuliares

//definir una plantilla para redimensionar elementos en ptr_line que es de tipo string y matrixnetwork que es de line
template<typename T>
void resizeArreglo(T* arreglo, int initial_size, int new_size) {
    // Crear una copia para guardar los elementos
    T* copy = new T[initial_size];
    for (int i = 0; i < initial_size; i++) {
        copy[i] = arreglo[i];
    }
    // Liberar memoria del arreglo original
    delete[] arreglo;
    // Reservar memoria con la nueva dimensión
    arreglo = new T[new_size];
    // Ingresar los nuevos elementos y los que tenía
    for (int i = 0; i < initial_size; i++) {
        arreglo[i] = copy[i];
    }
    // Liberar memoria de la copia temporal
    delete[] copy;
}

line* verifyLine(network* N){

    //verifica que una linea exista y si no existe se le pide al usuario que ingrese un nombre valido

    string name_line;
    line* line;
    bool end=true;
    while (true){

        cout<<"ingrese el nombre de la linea ";cin>>name_line;
        cout<<endl;

        //verificar que la linea exista y encontrar la linea
        for(unsigned int i=0;i<N->get_numLines();i++){

            if(name_line==N->getMatrixnetwork()[i].get_name_line()){
                line=&N->getMatrixnetwork()[i];
                end=true;
                break;
            }

            if(i==N->get_numLines()-1){
                cout<<"la linea no existe intente con otra diferente "<<endl;
                end=false;
            }
        }

        if(end) break;
    }
    return line;
}

void menu(){

    int lines;
    cout<<"Bienvenido a la simulacion de una red metro\n";
    cout<<"ingrese el numero de lineas que tendra la red metro: ";cin>>lines;

    //instanciar la calse network

    network red(lines);
    virtual_network_class *red_aux;

    //inicializar clase
    red.inicialization_red(red_aux);


    while(true){
        char op;

        red.printNetwork();
        cout<<endl<<endl;

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





        if(op=='1'){

        }else if(op=='2'){

        }else if(op=='3'){

            while(true){

                char volver;

                cout<<"si desea seguir agregando lineas ingrese 1 de lo contrario ingrese cualquier caracter para volver al menu principal ";cin>>volver;
                cout<<endl;
                if(volver!='1') break;

            }

        }else if(op=='4'){

            while(true){

                char volver;



                cout<<"si desea seguir eliminando lineas ingrese 1 de lo contrario ingrese cualquier caracter para volver al menu principal ";cin>>volver;
                cout<<endl;
                if(volver!='1') break;

            }


        }else if(op=='5'){

            line* line;
            line=verifyLine(&red);
            line->amountStations();

        }else if(op=='6'){

            line* line;
            //encontrar la linea
            line=verifyLine(&red);
            string name_sta;
            cout<<"ingrese el nombre de la estacion: ";cin>>name_sta;
            if(line->findStation(name_sta)){
                cout<<"la estacion "<<name_sta<< " esta en la linea "<<line->get_name_line()<<endl;
            }else{
                cout<<"la estacion "<<name_sta<< " no esta en la linea "<<line->get_name_line()<<endl;
            }


        }else if(op=='7'){

            while(true){
                char volver;
                line* line;

                line=verifyLine(&red);

                char x;
                bool first=false;

                cout<<"ingrese 1 si la estacion que desea agregar estara en la primera posicion de la linea de lo contario ingrese cualquier caracter: ";cin>>x;
                cout<<endl;

                if(x=='1')first=true;
            
                string name_sta;
                cout<<"ingrese el nombre de la estacion que desea agregar: ";cin>>name_sta;
                cout<<endl;

                //verificar que haya espacio para agregar el elemento
                if((line->get_num_estations()*2)+1>line->get_tam_ptr_line()){
                    // no hay espacio en el arreglo lo redimensionar
                    resizeArreglo<string>(line->get_ptr_line(),line->get_tam_ptr_line(),line->get_tam_ptr_line()+29);//se le suma 29 por la expectativa
                    line->addStation(name_sta,false);
                    cout<<"estacion "<<name_sta<<" agregada"<<endl;

                }else{

                    if(first){
                        //ingresarla en la primera posicion
                        line->addStation(name_sta,true);
                    }else{
                        //posicion cualquiera
                          line->addStation(name_sta,false);
                    }
                }


                cout<<"si desea seguir agregando estaciones ingrese 1 de lo contrario ingrese cualquier caracter para volver al menu principal ";cin>>volver;
                cout<<endl;
                if(volver!='1') break;

            }

        }else if(op=='8'){

            while(true){

                char volver;

                line* line;
                line=verifyLine(&red);

                line->deleteStation();
                cout<<"si desea seguir eliminando estaciones ingrese 1 de lo contrario ingrese cualquier caracter para volver al menu principal ";cin>>volver;
                cout<<endl;
                if(volver!='1') break;

            }

        }else{

            //tiempos

            while(true){

                char volver;

                line* line;
                line=verifyLine(&red);

                line->timeStations();

                cout<<"si desea conocer mas timepos entre estaciones en una lineas especifica ingrese 1 de lo contrario ingrese cualquier caracter para volver al menu principal ";cin>>volver;
                cout<<endl;
                if(volver!='1') break;

            }

        }

        red.printNetwork();

        char terminar;


        cout<<"si desea continuar en la red ingrese 1 de lo contrario ingrese cualquier caracter ";cin>>terminar;
        cout<<endl;
        if(terminar!='1') break;


    }


}








