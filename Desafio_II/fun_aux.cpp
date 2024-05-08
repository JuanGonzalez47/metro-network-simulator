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

        cout<<endl;
        cout<<"Ingrese el nombre de la linea: ";cin>>name_line;
        name_line=mayus_to_minus(name_line);
        cout<<endl;

        //verificar que la linea exista y encontrar la linea
        for(unsigned int i=0;i<N->get_numLines();i++){

            if(name_line==N->getMatrixnetwork()[i].get_name_line()){
                line=&N->getMatrixnetwork()[i];
                end=true;
                break;
            }

            if(i==N->get_numLines()-1){
                cout<<"La linea no existe intente con otra diferente "<<endl;
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
    cout<<"Ingrese el numero de lineas que tendra la red metro: ";cin>>lines;///////////////////////////////

    //instanciar la calse network

    network red(lines);

    //inicializar clase
    red.inicialization_red();


    while(true){
        char op;

        red.printNetwork();
        cout<<endl;

        cout<<"Si desea saber cuantas lineas tiene la red metro ingrese 1 "<<endl;
        cout<<"Si desea saber cuantas estaciones tiene la red metro ingrese 2 "<<endl;
        cout<<"Si desea agregar lineas a la red metro ingrese 3 "<<endl;
        cout<<"Si desea eliminar lineas a la red metro ingrese 4 "<<endl;
        cout<<"Si desea saber cuantas estaciones tiene una linea especifica de la red metro ingrese 5 "<<endl;
        cout<<"Si desea saber si una estacion cualquiera pertenece a una linea especifica ingrese 6 "<<endl;
        cout<<"Si desea agregar estaciones a una linea especifica ingrese 7 "<<endl;
        cout<<"Si desea eliminar estaciones a una linea especifica ingrese 8 "<<endl;
        cout<<"Si desea conocer el tiempo que tarda un tren en ir de una estacion a otra en una linea especifica ingrese cualquier caracter"<<endl<<endl;

        cout<<"Ingrese la opcion: ";cin>>op;


        if(op=='1'){
            red.amountline();
        }

        else if(op=='2'){
            red.amountStations();
        }

        else if(op=='3'){

            while(true){

                char volver;
                red.addLine();
                cout<<"la red ha quedado de la siguiente manera: "<<endl<<endl;
                red.printNetwork();
                cout<<"Si desea seguir agregando lineas ingrese 1 de lo contrario ingrese cualquier caracter: ";cin>>volver;
                cout<<endl;
                if(volver!='1') break;

            }

        }else if(op=='4'){


            bool band1 = true;
            bool band2 = true;
            while(band1){
                char volver;
                string name_line;
                cout<<"La red metro es la siguiente: "<<endl<<endl;
                red.printNetwork();
                while (band2){
                    cout<<"Ingrese el nombre de la linea que desea eliminar: ";cin>>name_line;
                    name_line=mayus_to_minus(name_line);
                    if (red.line_on_red(name_line)){
                        red.deleteLine(name_line);
                        cout<<"Si desea seguir eliminando lineas ingrese 1 de lo contrario ingrese cualquier caracter: ";cin>>volver;
                        cout<<endl<<endl;
                        if(volver!='1'){
                            band1 = false;
                            band2 = false;
                        }
                    }
                    else if (red.get_numLines() == 0){
                        cout<<"No se puede eliminar mas lineas ya que la red esta vacia"<<endl<<endl;
                        band1 = false;
                        band2 = false;
                    }
                    else cout<<"Ingrese una linea que se encuentre en la red"<<endl;
                }
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
            cout<<"Ingrese el nombre de la estacion: ";cin>>name_sta;
            name_sta=mayus_to_minus(name_sta);
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

                cout<<"Ingrese 1 si la estacion que desea agregar estara en la primera posicion de la linea de lo contario ingrese cualquier caracter: ";cin>>x;
                cout<<endl;

                if(x=='1')first=true;
            
                string name_sta;
                while(true){
                    cout<<"Ingrese el nombre de la estacion que desea agregar: ";cin>>name_sta;
                    if (red.normal_estation_on_red(name_sta)) cout<<"Ingrese una estacion que no este en la red"<<endl;
                    else break;
                }
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
                while (name_sta.find('-') != string::npos){
                    unsigned int amount_line_transfer;
                    string name_line_transfer;
                    cout<<"Ingrese con cuantas lineas desea hacer transferencia: ";cin>>amount_line_transfer;///////////////////////////////7
                    if (amount_line_transfer == 0 || amount_line_transfer >= red.get_numLines()) cout<<"Ingrese un numero valido de lineas a hacer transferencia";
                    else{
                        red.set_Amount_stations_auxiliar(amount_line_transfer);

                        for (unsigned int i = 0; i < amount_line_transfer; i++){
                            while (true){
                                cout<<"Ingrese la linea "<<i+1<<" con la que va a hacer transferencia: ";cin>>name_line_transfer;
                                 name_line_transfer=mayus_to_minus(name_line_transfer);

                                cout<<"Ingrese 1 si la estacion que desea agregar estara en la primera posicion de la linea de lo contario ingrese cualquier caracter: ";cin>>x;
                                cout<<endl;

                                while(x=='1'){
                                    first=true;
                                    break;
                                }
                                if (red.getMatrixnetwork()[i].get_name_line() == name_line_transfer){
                                    if (red.line_on_red(name_line_transfer)){
                                        if(first){
                                            //ingresarla en la primera posicion
                                            red.getMatrixnetwork()[i].addStation(name_sta + "linea_" + red.getMatrixnetwork()[i].get_name_line(),true);
                                        }else{
                                            //posicion cualquiera
                                            red.getMatrixnetwork()[i].addStation(name_sta + "linea_" + red.getMatrixnetwork()[i].get_name_line(),false);
                                        }
                                        break;
                                    }
                                    else if (name_line_transfer == line->get_name_line()) cout<<"Ingrese una linea que este en la red, recuerde que no puede ser usted misma"<<endl;
                                    else cout<<"Ingrese una linea que este en la red, recuerde que no puede ser usted misma"<<endl;
                                }
                            }
                        }
                        break;
                    }

                }
                cout<<"Si desea seguir agregando estaciones ingrese 1 de lo contrario ingrese cualquier caracter: ";cin>>volver;
                cout<<endl;
                if(volver!='1') break;

            }

        }else if(op=='8'){

            bool band3 = true;

            while(band3){

                char volver;
                bool band = true;
                string name_line_transfer_delete;
                string sta;
                line* line;
                line=verifyLine(&red);

                if (line->get_num_estations() == 1) cout<<"No se puede eliminar una estacion de la linea ya que la linea solo tiene una estacion"<<endl<<endl;
                else{
                    while(band){
                        cout<<"Ingrese la estacion que va a eliminar: ";cin>>sta;
                        sta=mayus_to_minus(sta);
                        if (!red.getMatrixnetwork()->findStation(sta)) cout<<"Ingrese una estacion que se encuentre en la red"<<endl;
                        else{
                            if (sta.find('-') != string::npos){
                                cout<<"No se puede eliminar una estacion de transferencia"<<endl;
                            }
                            else{
                                line->deleteStation(sta);
                                band = false;
                            }
                        }
                    }
                }

                cout<<"Si desea seguir eliminando estaciones ingrese 1 de lo contrario ingrese cualquier caracter: ";cin>>volver;
                cout<<endl;
                if(volver!='1') band3 = false;

            }

        }else{

            //tiempos

            while(true){

                char volver;

                line* line;
                line=verifyLine(&red);

                line->timeStations();

                cout<<"Si desea conocer mas tiempos entre estaciones en una linea especifica ingrese 1 de lo contrario ingrese cualquier caracter: ";cin>>volver;
                cout<<endl;
                if(volver!='1') break;

            }

        }

        red.printNetwork();

        char terminar;


        cout<<"Si desea volver al menu principal ingrese 1 de lo contrario ingrese cualquier caracter: ";cin>>terminar;
        cout<<endl;
        if(terminar!='1') break;


    }

}








