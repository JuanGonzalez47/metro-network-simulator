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

    if (sta == ptr_line[0]){
        for(unsigned int j=0;j<(num_estations*2)-1;j++){
            //correr el resto de valores dos posiciones a la izquierda
            ptr_line[j]=ptr_line[j+2];
        }
    }
    else if(sta == ptr_line[(num_estations*2)-2]){
        ptr_line[(num_estations*2)-2] = "";
        ptr_line[(num_estations*2)-3] = "";

    }
    else{
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
        //eliminar las ultimas dos posiciones que quedan sobrando (tiempo-estacion)
        ptr_line[(num_estations*2)-2] = "";
        ptr_line[(num_estations*2)-3] = "";
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
        time1=verifyNum();

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
        time1=verifyNum();

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
                time2=verifyNum();
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

void line::addStation(string sta, unsigned int i)
{
    ptr_line[i] = sta;
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

    cout<<"Si usted sale de la estacion "<<sta1<<" a las "<<tiempoLocal->tm_hour << ":" << tiempoLocal->tm_min<< endl;

    tiempoActual+=sum_tiempo;

    tm* tiempoLlegada = localtime(&tiempoActual);

    cout<<"Llegara a la estacion "<<sta2<<" a las "<<tiempoLlegada->tm_hour << ":" << tiempoLlegada->tm_min << endl;

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

void line::set_tam_ptr_line(unsigned int tam_)
{
    tam_ptr_line+=tam_;
}


//destructor


line::~line()
{
    delete[] ptr_line;
}

//funcion

string mayus_to_minus(string word){
    //convertir todos los caracters de un string a minuscula esto se hace para que los nombres de las esatciones sean minusculas
    for (unsigned int i = 0; i < word.length(); i++) {
        word[i] = tolower( word[i]);
    }
    return word;
}

string minus_to_mayus(string word) {
  //convertir todos los caracters de un string a mayuculas esto se hace para que los nombres de las lineas sean mayusculas
    for (unsigned int i = 0; i < word.length(); i++) {
        word[i] = toupper(word[i]);
    }
    return word;
}

string verifyNum(){

    //verifica que la entrada sea un carcater numerico
    bool out;
    string num;
    int ascii;
    bool iter1=false;
    while(true){
        out=true;
        if(iter1){
            cout<<"Intente nuevamente: ";cin>>num;
            cout<<"\n";
        }else{
            cin>>num;
        }

        int len=num.length();

        for(int i=0;i<len;i++){
            ascii=num[i];
            if(ascii<48 || ascii>57){
                cout<<"Solo puede ingresar caracteres numericos\n";
                iter1=true;
                out=false;
                break;
            }
        }
        if(out) break;
    }
    return num;
}

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
