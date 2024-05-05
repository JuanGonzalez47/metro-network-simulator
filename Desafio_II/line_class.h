#include <string>
#include <iostream>
using namespace std;

#ifndef LINE_CLASS_H
#define LINE_CLASS_H

#include "virtual_network_class.h"

//definir clase line
class line
{
private:
    //Numero de estaciones que tendra la linea
    unsigned int num_estations;
    // matriz unidimensional con la linea
    string *ptr_line;
    string name_line;
    //bool que me devolvera si el objeto es valido o no
    bool object_valid;

public:
    //constructor
    line();
    line(unsigned int num_estations_, string name_line_);

    //destructor
    ~line();

    //metodos
    void inicialization_line(unsigned int num_estations, string name_line, unsigned int m, virtual_network_class *red_aux, unsigned int cont_line);
    void addStation();
    void amountStations();
    int findStation();
    void deleteStation();
    void timeStations();

    //geters
    string get_name_line();
    string* get_ptr_line();
    unsigned int get_num_estations();
    bool get_object_valid();
};













#endif // LINE_CLASS_H

