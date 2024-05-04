#include <iostream>
#include <string>
#include "network_class.h"


using namespace std;

//metodos clase line

line::line()
{
//constructor por defecto para la reserva de memoria de matrixNetwork
    object_valid = false;
}

line::line(unsigned int num_estations_, string name_line_)
{
    num_estations = num_estations_;
    name_line = name_line_;
    //creamos el arreglo con la linea, se le suma 16, ya que la primera estara ocupada con el nombre de la fila y el resto son la expectativa de estaciones
    ptr_line = new string [((num_estations+15)*2)-1];
    object_valid = true;

}

void line::inicialization_line(unsigned int num_estations, string name_line, unsigned int m, virtual_network_class *red_aux, unsigned int cont_line)
{
    //booleano que me retornara si se encontro una estacion normal o no dentro de la red
    bool verify = true;
    bool verify1 = true;
    bool valid = false;
    string name_estation;
    unsigned int num_line_transfer;
    //string que almacenara los nombres de las lineas con los cuales va a hacer transferencia
    string name_line_transfer;
    //string que se almacenaran las estaciones de la misma linea para ver si repiten
    string name_estation_same_line;

    //es para dar permiso de ingresar la primera estacion de todo el programa
    if (m != 0) valid = true;

    //inicializar la linea
    for (unsigned int i = 0; i < num_estations; i++){
        verify = true;
        cout<<endl;
        cout<<"Nota: recuerde que si desea ingresar una estacion de transferencia, al final debera de escirbir un guion. Ejemplo:(name-)"<<endl<<endl;
        while (verify){
            cout<<"Ingrese la estacion "<<i+1<<" : ";cin>>name_estation;
            if (name_estation.find('-') != string::npos){
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
                        if (num_line_transfer == 0 || num_line_transfer > red_aux->get_numLines() - cont_line) cout<<"Ingrese un numero valido de lineas a hacer transferencia"<<endl<<endl;
                        else{
                            while(verify1){
                                for (unsigned int k = 0; k < num_line_transfer; k++){
                                    cout<<"Ingrese el nombre de la linea "<<k+1<<" con la que desea hacer transferencia: ";cin>>name_line_transfer;
                                    //verificar que la linea que escriba este disponible para hacer transferencia y que no sea ella misma
                                    if (red_aux->get_name_lines().find(name_line_transfer) == string::npos || name_line_transfer == name_line) cout<<"Ingrese una linea que se encuentre en la red, recuerde que no puede ser la linea actual"<<endl<<endl;
                                    else{
                                        //buscar la linea con la que desea hacer transferencia y agregar al final la estacion de transferencia (recordar actualizar los tiempos de la linea en la cual deseo hacer transferencia)
                                        //llamar metodo que ponga una estacion en una linea en especifico
                                        ptr_line[i] = name_estation + name_line;
                                        verify = false;
                                        verify1 = false;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else{
                if (red_aux->normal_estation_on_red(name_estation,num_estations,red_aux->get_numLines(),valid,name_estation_same_line)) cout<<"Ingrese una estacion que no este repetida"<<endl<<endl;
                else{
                    ptr_line[i] = name_estation;
                    name_estation_same_line += name_estation;
                    verify = false;
                    valid = true;
                }
            }
        }
    }
    cout<<endl;
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

bool line::get_object_valid()
{
    return object_valid;
}

//metodo add line que puede ser de ayuda (adelanto, falta terminar)
/*void line::add_estation(string name_estation, string name_line, unsigned int num_estations_line, unsigned int numLines)
{
    for (unsigned int i = 0; i < numLines; i++){
        if (matrixNetwork[i].get_object_valid()){
                if (valid == true) if (name_line_transfer == matrixNetwork[i].get_name_line()){
                    matrixNetwork[i].get_ptr_line()[num_estations_line+1] = name_estation;
                }
        }
    }
}*/



line::~line()
{
    delete ptr_line;
}
