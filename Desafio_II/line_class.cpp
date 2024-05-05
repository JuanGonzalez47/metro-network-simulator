#include <iostream>
#include <string>
#include <ctime>//para conocer la hora actual
#include "line_class.h"

using namespace std;

//metodos clase line

line::line()
{
//constructor por defecto para la reserva de memoria de matrixNetwork
}

line::line(unsigned int num_estations_, string name_line_)
{
    //num estacions tendra el numero de estaciones mas los tiempos entre cada una
    num_estations = num_estations_;
    name_line = name_line_;
    //creamos el arreglo con la linea, se le suma 16, ya que la primera estara ocupada con el nombre de la fila y el resto son la expectativa de estaciones
    ptr_line = new string [((num_estations+15)*2)-1];

}


void line::inicialization_line(unsigned int num_estations)
{
    string name_estation,time_station;
    //inicializar la linea
    for (unsigned int i = 0; i < num_estations; i+=2 ){
        cout<<"Ingrese la estacion "<<i+1<<" : ";cin>>name_estation;
        //agregar nombre estacion
        ptr_line[i] = name_estation;
        if(i==(num_estations-1)){

            //agregar tiempo entre estaciones

            cout<<"ingrese el timepo entre estaciones, este se tomara en unidades de minutos "<<endl;

            for(unsigned int i=1;i<(num_estations-1);i+=2){

                cout<<"ingrese el tiempo que tardara el tren en llegar de la estacion "<<ptr_line[i-1]<<" -> "<<ptr_line[i+1]<<" : ";
                cin>>time_station;cout<<endl;
                ptr_line[i]=time_station;
            }
        }

    }

}


string line::get_name_line()
{
    return name_line;
}

string *line::get_ptr_line()
{
    return ptr_line;
}

unsigned int line::get_num_estations()
{
    return num_estations;
}

void line::timeStations(){

    //imprimir la red metro

    string sta1,sta2;
    float sum_tiempo=0;
    //para verificar si sta1 se encuetra primero que sta2 en la linea
    bool order=NULL,start_sum=false;
    cout<<"ingrese las estaciones entre las cuales quiere comonocer el timepo que tarda el tren en llegar "<<endl;
    cout<<"ingrese el nombre de la primera estacion: ";cin>>sta1;
    cout<<endl<<"ingrese el nombre de la segunda estacion: ";cin>>sta2;

    for(unsigned int i=0;i<this->get_num_estations();i+=2){

        //verificar el orden
        if(sta1==ptr_line[i]){
            order=true;
            break;
        }
        if(sta2==ptr_line[i]){
            order=false;
            break;
        }

    }

    if(order){

        for(unsigned int i=0;i<this->get_num_estations();i+=2){
            //cuando ecuentre la estacion hacer empezar a sumar
            if(sta1==ptr_line[i]){
                start_sum=true;
            }

            if(start_sum){
                //i+1 siguiente posicion donde se encuentra el tiempo pasarlo a float
                sum_tiempo+=stof(ptr_line[i+1]);
                //hasta que enceuntre la otra esatcion dejar de sumar
                if(sta2==ptr_line[i]){
                    break;
                }
            }

        }

    }else{
        //como sta2 esta primero en el ptr hacer lo mismo de arriba pero alreves
        for(unsigned int i=0;i<this->get_num_estations();i+=2){
            //cuando ecuentre la estacion hacer empezar a sumar
            if(sta2==ptr_line[i]){
                start_sum=true;
            }

            if(start_sum){
                //i+1 siguiente posicion donde se encuentra el tiempo pasarlo a float
                sum_tiempo+=stof(ptr_line[i+1]);
                //hasta que enceuntre la otra esatcion dejar de sumar
                if(sta1==ptr_line[i]){
                    break;
                }
            }

        }

    }

    //pasar los minutos a segundos
    sum_tiempo*=60;

    // Obtiene el tiempo actual en segundos desde el 1 de enero de 1970
    time_t tiempoActual = time(nullptr);
    tiempoActual-=18000;

    // Convierte el tiempo a una forma legible
    tm* tiempoLocal = localtime(&tiempoActual);

    cout<<"si usted sale de la estacion "<<sta1<<" a las "<<tiempoLocal->tm_hour << ":" << tiempoLocal->tm_min << ":" << tiempoLocal->tm_sec << endl;

    tiempoActual+=sum_tiempo;

    tm* tiempoLlegada = localtime(&tiempoActual);

    cout<<" llegara a la esatcion "<<sta2<<" a las "<<tiempoLlegada->tm_hour << ":" << tiempoLlegada->tm_min << ":" << tiempoLlegada->tm_sec << endl;

}


line::~line()
{
    delete ptr_line;
}
