#include "network_class.h"



network::network(unsigned int numLines_)
{
    numLines = numLines_;
    //memoria reservada para la red que contendra los objetas "line"
    tam_matrix_network=numLines+10;
    matrixNetwork = new line[tam_matrix_network];
}

void network::inicialization_line(unsigned int num_estations, string name_line, unsigned int m, unsigned int cont_line, line *line)
{
    bool verify = true;
    bool verify1 = true;
    bool valid = false;
    //string para guardar las estaciones donde ya se hicieron transferencia
    string already_transfer = "";
    string name_estation;
    unsigned int num_line_transfer;
    string str_num_line_transfer;
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
            //pasarlo a minusculas
            name_estation=mayus_to_minus(name_estation);
            if (name_estation.find('-') != string::npos){
                //verificar que la estacion no este repetida en la linea o en la red en general
                if (this->normal_estation_on_red(name_estation,this->get_numLines(),valid,name_estation_same_line)) cout<<"Ingrese una estacion que no este repetida"<<endl<<endl;
                else{
                    //verificar que la red tenga mas de una linea para poder que ingrese una estacion de transferencia
                    if(m == 0){
                        cout<<"No puede crear una estacion de transferencia ya que la red no tiene mas de una linea"<<endl<<endl;
                        verify1 = false;
                    }
                    else{
                        while(verify1){
                            cout<<"Ingrese con cuantas lineas va a hacer transferencia: ";
                            str_num_line_transfer=verifyNum();
                            num_line_transfer=stoi(str_num_line_transfer);
                            //se verifica que cuando vaya a hacer transfrencia hayan lineas disponibles para hacerlo
                            //se verifica que el numero que ingrese a hacer transferencia sea cero
                            if (num_line_transfer == 0 || num_line_transfer > cont_line) cout<<"Ingrese un numero valido de lineas a hacer transferencia"<<endl<<endl;
                            else{
                                this->set_Amount_stations_auxiliar(num_line_transfer);
                                while(verify1){
                                    for (unsigned int k = 0; k < num_line_transfer; k++){
                                        //verificar que la linea que escriba este disponible para hacer transferencia y que no sea ella misma
                                        while (true){
                                            cout<<"Ingrese el nombre de la linea con la que desea hacer transferencia: ";cin>>name_line_transfer;
                                            name_line_transfer=minus_to_mayus(name_line_transfer);
                                            if (already_transfer.find(name_line_transfer) != string::npos) {
                                                cout<<"Por favor ingrese una linea diferente a hacer transferencia"<<endl;
                                            }
                                            else break;
                                        }
                                        if (!this->line_on_red(name_line_transfer) || name_line_transfer == name_line) cout<<"Ingrese una linea que se encuentre en la red, recuerde que no puede ser la linea actual"<<endl<<endl;
                                        else{
                                            //metodo para buscar la linea con la que desea hacer transferencia y agregar la estacion de transferencia
                                            //llamar metodo que ponga una estacion en una linea en especifico
                                            this->search_transfer_and_put(name_line_transfer,name_estation);
                                            line->addStation(name_estation + "linea_" + name_line,i);
                                            name_estation_same_line += name_estation;
                                            already_transfer += name_line_transfer;


                                            while(i==(num_estations-1)){

                                                //agregar tiempo entre estaciones

                                                for(unsigned int i=1;i<(num_estations-1);i+=2){

                                                    cout<<"Ingrese el tiempo (en minutos) que tardara el tren en llegar de la estacion "<<line->get_ptr_line()[i-1]<<" -> "<<line->get_ptr_line()[i+1]<<" : ";
                                                    time_station=verifyNum();
                                                    line->addStation(time_station,i);
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
                if (this->normal_estation_on_red(name_estation,this->get_numLines(),valid,name_estation_same_line)) cout<<"Ingrese una estacion que no este repetida"<<endl<<endl;
                else{
                    line->addStation(name_estation,i);


                    name_estation_same_line += name_estation;
                    verify = false;
                    valid = true;
                    if(i==(num_estations-1)){

                        //agregar tiempo entre estaciones

                        for(unsigned int i=1;i<(num_estations-1);i+=2){

                            cout<<"Ingrese el tiempo (en minutos)  que tardara el tren en llegar de la estacion "<<line->get_ptr_line()[i-1]<<" -> "<<line->get_ptr_line()[i+1]<<" : ";
                            time_station=verifyNum();
                            line->addStation(time_station,i);
                        }
                    }
                }
            }
        }
    }
}


void network::inicialization_red()
{
    //booleano que me dira si la linea esta o no repetida
    bool verify_line;
    string name_line;
    unsigned int num_estations;
    string str_num_estations;
    //entero para llevar a cabo una verificacion de transferencia
    unsigned int cont_line = 0;

    for (unsigned int i = 0; i < numLines; i++){
        verify_line = true;
        while (verify_line){
            cout<<endl;
            cout<<"Ingrese el nombre de la linea "<<i+1<<" : ";cin>>name_line;
            name_line=minus_to_mayus(name_line);
            if (this->line_on_red(name_line)) cout<<"Ingrese una linea que no este en la red"<<endl<<endl;
            else{
                //agregar al string que contiene los nombres de las lineas, la linea que se agrego
                cout<<"Ingrese el numero de estaciones que tendra la linea: ";

                str_num_estations=verifyNum();
                num_estations=stoi(str_num_estations);

                //crear un puntero a cada uno de los objetos
                //esto se hace porque si pasamos el objeto directamente, cuando sale del for llama automaticamente
                //el destrcutor y matrixNetwork estaria accediendo a una memoria invalida (ya liberada)
                line* name_object = new line(num_estations, name_line);
                this->inicialization_line(num_estations,name_line,i,cont_line,name_object);
                matrixNetwork[i] = *name_object;
                cont_line++;
                verify_line = false;
            }
        }
    }
}

void network::addLine()
{
    //booleano que me dira si la linea esta o no repetida
    bool verify_line = true;
    string name_line;
    unsigned int num_estations;
    string str_num_estations;
    //entero para llevar a cabo una verificacion de transferencia
    unsigned int cont_line = 0;
    while (verify_line){
        cout<<"Ingrese el nombre de la linea "<<numLines + 1<<" a agregar : ";cin>>name_line;
         name_line=minus_to_mayus(name_line);
        if (this->line_on_red(name_line)) cout<<"Ingrese una linea que no este en la red"<<endl<<endl;
        else{
            //agregar al string que contiene los nombres de las lineas, la linea que se agrego
            cout<<"Ingrese el numero de estaciones que tendra la linea: ";
            str_num_estations=verifyNum();
            num_estations=stoi(str_num_estations);

            //crear un puntero a cada uno de los objetos
            //esto se hace porque si pasamos el objeto directamente, cuando sale del for llama automaticamente
            //el destrcutor y matrixNetwork estaria accediendo a una memoria invalida (ya liberada)
            cont_line = numLines;
            line* name_object = new line(num_estations, name_line);
            this->inicialization_line(num_estations,name_line,1,cont_line,name_object);
            matrixNetwork[numLines] = *name_object;
            cont_line++;
            verify_line = false;
            //actualizar el atributo de numero de lineas
            numLines++;
        }
    }
    cout<<"La linea "<<name_line<<" ha sido agregada"<<endl;
}


void network::printNetwork(){
    cout << "RED METRO\n\n";
    for(unsigned int i = 0; i < numLines;i++){
        cout<<"linea "<<matrixNetwork[i].get_name_line();
        for(unsigned j = 0; j < (matrixNetwork[i].get_num_estations()*2)-1;j++){
            cout<<" " <<"|"<<(matrixNetwork[i].get_ptr_line())[j]<<"|";
        }
        cout<<endl;
    }
    cout<<endl;
}

bool network::line_on_red(string name_line)
{
    for (unsigned int i = 0; i < numLines; i++){
        if (name_line == matrixNetwork[i].get_name_line())return true;
    }
    return false;
}

bool network::normal_estation_on_red(string name_estation, unsigned int numLines, bool valid, string name_estation_same_line)
{
    for (unsigned int i = 0; i < numLines; i++){
        istringstream iss(name_estation_same_line);
        string word;
        while (iss >> word) {
            if (word == name_estation) {
                return true;
            }
        }
        if (matrixNetwork[i].get_object_valid()){
            for (unsigned j = 0; j < (matrixNetwork[i].get_num_estations()*2)-1; j+=2){
                if (valid == true){
                    if (name_estation == matrixNetwork[i].get_ptr_line()[j]) return true;
                    string name_estation_aux;
                    name_estation_aux = matrixNetwork[i].get_ptr_line()[j];
                    size_t pos = name_estation_aux.find('-');
                    //tomando una estacion de transferencia solo con el nombre no con los indices
                    name_estation_aux = name_estation_aux.substr(0,pos);
                    if(name_estation == name_estation_aux) return true;
                    else if (name_estation == name_estation_aux + '-') return true;
                    else if (name_estation == matrixNetwork[i].get_ptr_line()[j] + '-') return true;
                }
            }
        }
        else return false;
    }
    return false;
}


void network::search_transfer_and_put(string name_line_transfer, string name_estation)
{
    bool first = false;
    char x;

    cout<<"Ingrese 1 si la estacion que desea agregar estara en la primera posicion de la linea de lo contario ingrese cualquier caracter: ";cin>>x;
    cout<<endl;

    while(x=='1'){
        first=true;
        break;
    }

    if(first){
        //ingresarla en la primera posicion
        for (unsigned int i = 0; i < numLines; i++){
            if (matrixNetwork[i].get_name_line() == name_line_transfer) matrixNetwork[i].addStation(name_estation + "linea_" + matrixNetwork[i].get_name_line(),true);                }
    }
    else{
        //posicion cualquiera
        for (unsigned int i = 0; i < numLines; i++){
            if (matrixNetwork[i].get_name_line() == name_line_transfer) matrixNetwork[i].addStation(name_estation + "linea_" + matrixNetwork[i].get_name_line(),false);
        }
    }
}

bool network::normal_estation_on_red(string name_estation)
{
    for (unsigned int i = 0; i < numLines; i++){
        if (matrixNetwork[i].get_object_valid()){
            for (unsigned j = 0; j < (matrixNetwork[i].get_num_estations()*2)-1; j+=2){
                if (name_estation == matrixNetwork[i].get_ptr_line()[j]) return true;
                string name_estation_aux;
                name_estation_aux = matrixNetwork[i].get_ptr_line()[j];
                size_t pos = name_estation_aux.find('-');
                //tomando una estacion de transferencia solo con el nombre no con los indices
                name_estation_aux = name_estation_aux.substr(0,pos);
                if(name_estation == name_estation_aux) return true;
                else if (name_estation == name_estation_aux + '-') return true;
                else if (name_estation == matrixNetwork[i].get_ptr_line()[j] + '-') return true;
            }
        }
        else return false;
    }
    return false;
}


unsigned int network::get_numLines()
{
    return numLines;
}


line *network::getMatrixnetwork(){

    return matrixNetwork;

}

unsigned int network::getTamMatrixNetwork()
{
    return tam_matrix_network;

}

void network::set_Amount_stations_auxiliar(unsigned int new_value)
{
    Amount_stations_auxiliar += new_value;
}

void network::setTamMatrixNetwork(unsigned int tam_)
{
    tam_matrix_network+=tam_;
}

void network::amountline(){

    cout<<"la red metro tiene "<<numLines<<" lineas \n";

}


void network::amountStations()
{
    unsigned int sum_estations = 0;
    for(unsigned int i = 0; i < numLines; i++){
        sum_estations += matrixNetwork[i].get_num_estations();
    }
    sum_estations -= Amount_stations_auxiliar;
    cout<<"La red metro tiene "<<sum_estations<<" estaciones \n";
}


void network::deleteLine(string name_line)
{
    for(unsigned int i = 0; i < numLines; i++){
        if (matrixNetwork[i].get_name_line() == name_line){
            //pasarle un nuevo objeto line invalido
            line* name_object = new line();
            if (i == numLines - 1) {
                matrixNetwork[i] = *name_object;
                //actualizar atributo
                numLines--;
                break;
            }
            else{
                //poner en esa posicion otro objeto vacio e invalido
                matrixNetwork[i] = *name_object;
                //tomar la posicion en la cual la encontro
                for(unsigned int j = i; j < numLines; j++){
                    //mover los elementos
                    matrixNetwork[j] = matrixNetwork[j+1];
                }
                //actualizar atributo
                numLines--;
                break;
            }
        }
    }
    cout<<"La linea "<<name_line<<" ha sido eliminada"<<endl;

}



