#include "network_class.h"


network::network(unsigned int numLines_)
{
    numLines = numLines_;
    //memoria reservada para la red que contendra los objetas "line"
    matrixNetwork = new line[numLines + 10];
}

void network::inicialization_red()
{
    string name_line;
    unsigned int num_estations;
    for (unsigned int i = 0; i < numLines; i++){
        cout<<"Ingrese el nombre de la linea "<<i+1<<" : ";cin>>name_line;
        cout<<"Ingrese el numero de estaciones de la linea "<<i+1<<" : ";cin>>num_estations;
        //crear un puntero a cada uno de los objetos
        //esto se hace porque si pasamos el objeto directamente, cuando sale del for llama automaticamente
        //el destrcutor y matrixNetwork estaria accediendo a una memoria invalida (ya liberada)
        line* name_object = new line(num_estations, name_line);
        name_object->inicialization_line(num_estations);
        matrixNetwork[i] = *name_object;
    }
}


void network::printNetwork(){
    cout << "RED METRO\n\n";
    for(unsigned int i = 0; i < numLines;i++){
        cout<<"linea "<<matrixNetwork[i].get_name_line();
        for(unsigned j = 0; j < matrixNetwork[i].get_num_estations();j++){
            cout<<" " <<(matrixNetwork[i].get_ptr_line())[j];
        }
        cout<<endl;
    }
}

void network::amountline(){

    cout<<"la red metro tiene "<<numLines<<"lineas \n";

}


