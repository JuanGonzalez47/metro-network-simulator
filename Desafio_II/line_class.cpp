#include <iostream>
#include <string>
#include "network_class.h"
#include <ctime>//para conocer la hora actual


using namespace std;


//constructores
line::line()
{
//constructor por defecto para la reserva de memoria de matrixNetwork
    object_valid = false;
}

line::line(unsigned int num_estations_, string name_line_)
{
    num_estations = num_estations_;
    name_line = name_line_;

    //creamos el arreglo con la linea se le suma 29  ya que esa es la expectativa de creciemineto contando los tiempos
    //y se le multiplica por dos  al numero estaciones  para añadir los timepos entre cada estacion
    tam_ptr_line=(((num_estations_)*2-1)+29);
    ptr_line = new string [tam_ptr_line];
    object_valid = true;

}

//metodos clase line

void line::inicialization_line(unsigned int num_estations, string name_line, unsigned int m, virtual_network_class *red_aux, unsigned int cont_line)
{
    bool verify = true;
    bool verify1 = true;
    bool valid = false;
    //string para guardar las estaciones donde ya se hicieron transferencia
    string already_transfer = "";
    string name_estation;
    unsigned int num_line_transfer;
    //string que almacenara los nombres de las lineas con los cuales va a hacer transferencia
    string name_line_transfer,time_station;
    //string que se almacenaran las estaciones de la misma linea para ver si repiten
    string name_estation_same_line;
    unsigned int cont=0;
    //es para dar permiso de ingresar la primera estacion de todo el programa
    if (m != 0) valid = true;
    //se le agregan los tiempos entre cada esatcion
    num_estations=(num_estations*2)-1;
    //inicializar la linea
    for (unsigned int i = 0; i < num_estations; i+=2){
        verify = true;
        verify1 = true;
        already_transfer = "";
        cont++;
        cout<<endl;
        cout<<"Nota: recuerde que si desea ingresar una estacion de transferencia, al final debera de escirbir un guion. Ejemplo:(name-)"<<endl<<endl;
        while (verify){
            cout<<"Ingrese la estacion "<<cont<<" : ";cin>>name_estation;
            if (name_estation.find('-') != string::npos){
                //verificar que la estacion no este repetida en la linea o en la red en general
                if (red_aux->normal_estation_on_red(name_estation,red_aux->get_numLines(),valid,name_estation_same_line)) cout<<"Ingrese una estacion que no este repetida"<<endl<<endl;
                else{
                    //verificar que la red tenga mas de una linea para poder que ingrese una estacion de transferencia
                    if(m == 0){
                        cout<<"No puede crear una estacion de transferencia ya que la red no tiene mas de una linea"<<endl<<endl;
                        verify1 = false;
                    }
                    else{
                        while(verify1){
                            cout<<"Ingrese con cuantas lineas va a hacer transferencia: ";cin>>num_line_transfer;cout<<endl;
                            //se verifica que cuando vaya a hacer transfrencia hayan lineas disponibles para hacerlo
                            //se verifica que el numero que ingrese a hacer transferencia sea cero
                            if (num_line_transfer == 0 || num_line_transfer > cont_line) cout<<"Ingrese un numero valido de lineas a hacer transferencia"<<endl<<endl;
                            else{
                                red_aux->set_Amount_stations_auxiliar(num_line_transfer);
                                while(verify1){
                                    for (unsigned int k = 0; k < num_line_transfer; k++){
                                        cout<<"Ingrese el nombre de la linea con la que desea hacer transferencia: ";cin>>name_line_transfer;
                                        //verificar que la linea que escriba este disponible para hacer transferencia y que no sea ella misma
                                        while (true){
                                            if (already_transfer.find(name_line_transfer) != string::npos) {
                                                cout<<"Por favor ingrese una linea diferente a hacer transferencia"<<endl;
                                            }
                                        }
                                        if (!red_aux->line_on_red(name_line_transfer) || name_line_transfer == name_line) cout<<"Ingrese una linea que se encuentre en la red, recuerde que no puede ser la linea actual"<<endl<<endl;
                                        else{
                                            //metodo para buscar la linea con la que desea hacer transferencia y agregar la estacion de transferencia
                                            //llamar metodo que ponga una estacion en una linea en especifico
                                            red_aux->search_transfer_and_put(name_line_transfer,name_estation);
                                            ptr_line[i] = name_estation + "linea_" + name_line;
                                            name_estation_same_line += name_estation;
                                            already_transfer += name_line_transfer;


                                            while(i==(num_estations-1)){

                                                //agregar tiempo entre estaciones

                                                for(unsigned int i=1;i<(num_estations-1);i+=2){

                                                    cout<<"Ingrese el tiempo (en minutos) que tardara el tren en llegar de la estacion "<<ptr_line[i-1]<<" -> "<<ptr_line[i+1]<<" : ";
                                                    cin>>time_station;
                                                    ptr_line[i]=time_station;
                                                }
                                                break;
                                            }
                                            verify = false;
                                            verify1 = false;
                                        }

                                    }
                                }
                            }
                        }
                    }
                }
            }
            else{
                if (red_aux->normal_estation_on_red(name_estation,red_aux->get_numLines(),valid,name_estation_same_line)) cout<<"Ingrese una estacion que no este repetida"<<endl<<endl;
                else{
                    ptr_line[i] = name_estation;


                    name_estation_same_line += name_estation;
                    verify = false;
                    valid = true;
                    if(i==(num_estations-1)){

                        //agregar tiempo entre estaciones

                        for(unsigned int i=1;i<(num_estations-1);i+=2){

                            cout<<"Ingrese el tiempo (en minutos)  que tardara el tren en llegar de la estacion "<<ptr_line[i-1]<<" -> "<<ptr_line[i+1]<<" : ";
                            cin>>time_station;cout<<endl;
                            ptr_line[i]=time_station;
                        }
                    }
                }
            }
        }
    }
}

bool line::findStation(string sta){

    for(unsigned int i=0;i<(num_estations*2)-1;i+=2){
        if(ptr_line[i]==sta){
            return true;
        }
    }
    return false;
}

void line::deleteStation(string sta){

    unsigned int x=0;

    for(unsigned int i=0;i<(num_estations*2)-1;i+=2){
        x++;
        if(ptr_line[i]==sta){
            //sumar tiempo que tenia la estacion a la lado y lado
            float sumt=stof(ptr_line[i-1])+stof(ptr_line[i+1]);

            ptr_line[i-1]=to_string(sumt);
            //siguiente estacion
            ptr_line[i]=ptr_line[i+2];
            break;
        }
    }

    for(unsigned int j=x;j<(num_estations*2)-1;j++){

        //correr el resto de valores dos posiciones a la izquierda
        ptr_line[j]=ptr_line[j+2];

    }
    cout<<"La estacion "<<sta<<" fue eliminada "<<endl;
    num_estations--;

}

void line::amountStations(){

    cout<<"la linea tiene "<<num_estations<<" estaciones"<<endl;

}

void line::addStation(string sta,bool first_pos){

    string time1;
    //si la esatcion sera ingresada en la primera posicion
    if(first_pos){
        cout<<"Ingrese el tiempo que tardara el tren en llegar de la estacion "<<sta<<" a la estacion "<<ptr_line[0]<<" : ";
        cin>>time1;cout<<endl;

        //mover lo elementos dos posiciones hacia la derecha
        for (int i =(num_estations*2);i>=2;i--) {
            ptr_line[i] = ptr_line[i - 2];
        }
        //agrgar estacion y timepo en las primeras posiciones
        ptr_line[0]=sta;
        ptr_line[1]=time1;
        num_estations++;


    }else{

        string elem;
        //verificar que la estacion exista
        elem=verifyStation(this,"despues de cual estacion quiere agregar la nueva (nombre)");

        string time2;
        cout<<"Ingrese el tiempo que tardara el tren en llegar de la estacion "<<elem<<" a la estacion "<<sta<<" : ";
        cin>>time1;cout<<endl;

        for(unsigned int i=(num_estations*2)-1;true;i--){

            //verificar si el ultimo elemento sera ingresado en la ultima posicion
            if(ptr_line[i-1]==elem){
                ptr_line[i]=time1;
                ptr_line[i+1]=sta;
                break;

            }
            //desplazar lo elementos hacia la derecha hasta que encuentre elem
            ptr_line[i+1]=ptr_line[i-1];
            //encontro el elmento
            if(ptr_line[i-3]==elem){
                //asignar los nuevos valores
                cout<<"Ingrese el tiempo que tardara el tren en llegar de la estacion "<<sta<<" a la estacion "<<ptr_line[i+1]<<" : ";
                cin>>time2;cout<<endl;
                ptr_line[i]=time2;
                ptr_line[i-1]=sta;
                ptr_line[i-2]=time1;
                break;
            }
            ptr_line[i]=ptr_line[i-2];

        }
        cout<<"La estacion "<<sta<<" fue agregada "<<endl;
        num_estations++;

    }



}

void line::timeStations(){


    string sta1,sta2;
    float sum_tiempo=0;
    //para verificar si sta1 se encuetra primero que sta2 en la linea
    bool order=NULL,start_sum=false;
    cout<<"Ingrese las estaciones entre las cuales quiere conocer el tiempo que tarda el tren en llegar "<<endl;


    //verificar que las estaciones existan
    sta1=verifyStation(this,"el nombre de la primera estacion");
    sta2=verifyStation(this,"el nombre de la segunda estacion");


    for(unsigned int i=0;i<(num_estations*2)-1;i+=2){

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

        for(unsigned int i=0;i<(num_estations*2)-1;i+=2){
            //cuando ecuentre la estacion hacer empezar a sumar
            if(sta1==ptr_line[i]){
                start_sum=true;
            }

            if(start_sum){

                //hasta que encuentre la otra estacion dejar de sumar
                if(sta2==ptr_line[i]){

                    break;
                }
                //i+1 siguiente posicion donde se encuentra el tiempo pasarlo a float
                sum_tiempo+=stof(ptr_line[i+1]);
            }

        }

    }else{
        //como sta2 esta primero en el ptr hacer lo mismo de arriba pero alreves
        for(unsigned int i=(num_estations*2)-2;i>0;i-=2){
            //cuando ecuentre la estacion hacer empezar a sumar
            if(sta1==ptr_line[i]){
                start_sum=true;
            }

            if(start_sum){

                //hasta que encuentre la otra estacion dejar de sumar
                if(sta2==ptr_line[i]){
                    break;
                }
                //i-1 siguiente posicion donde se encuentra el tiempo pasarlo a float
                sum_tiempo+=stof(ptr_line[i-1]);
            }

        }

    }

    //pasar los minutos a segundos
    sum_tiempo*=60;

    // Obtiene el tiempo en segundos
    time_t tiempoActual = time(nullptr);

    //se le restan 180000 para obtener la actual
    //tiempoActual-=18000;

    // Convierte el tiempo a una forma legible
    tm* tiempoLocal = localtime(&tiempoActual);

    cout<<"Si usted sale de la estacion "<<sta1<<" a las "<<tiempoLocal->tm_hour << ":" << tiempoLocal->tm_min << ":" << tiempoLocal->tm_sec << endl;

    tiempoActual+=sum_tiempo;

    tm* tiempoLlegada = localtime(&tiempoActual);

    cout<<"Llegara a la estacion "<<sta2<<" a las "<<tiempoLlegada->tm_hour << ":" << tiempoLlegada->tm_min << ":" << tiempoLlegada->tm_sec << endl;

}

//getters

string line::get_name_line()
{
    return name_line;
}

string *line::get_ptr_line()
{
    return ptr_line;
}

unsigned int line::get_tam_ptr_line()
{
    return tam_ptr_line;
}

unsigned int line::get_num_estations()
{
    return num_estations;
}

bool line::get_object_valid()
{
    return object_valid;
}


//destructor


line::~line()
{
    delete ptr_line;
}

//funcion

string verifyStation(line *L, string phrase) {
    string temp;
    string sta;
    while(true){
        cout<<"Ingrese "+phrase<<": ";cin>>sta;
        cout<<endl;
        if(!L->findStation(sta)){
            cout<<"La estacion no existe\ningrese otra estacion"<<endl;
        }else{
            break;
        }
    }

    return sta;
}
