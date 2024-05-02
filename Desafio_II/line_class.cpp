#include <iostream>
#include <string>
#include "line_class.h"

using namespace std;

//metodos clase line

line::line()
{
//constructor por defecto para la reserva de memoria de matrixNetwork
}

line::line(unsigned int num_estations_, string name_line_)
{
    num_estations = num_estations_;
    name_line = name_line_;
    //creamos el arreglo con la linea, se le suma 16, ya que la primera estara ocupada con el nombre de la fila y el resto son la expectativa de estaciones
    ptr_line = new string [((num_estations+15)*2)-1];

}


void line::inicialization_line(unsigned int num_estations)
{
    string name_estation;
    //inicializar la linea
    for (unsigned int i = 0; i < num_estations; i++){
        cout<<"Ingrese la estacion "<<i+1<<" : ";cin>>name_estation;
        ptr_line[i] = name_estation;
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


line::~line()
{
    delete ptr_line;
}
