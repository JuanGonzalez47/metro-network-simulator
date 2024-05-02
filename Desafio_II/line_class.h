#include <string>
#include <iostream>
using namespace std;

#ifndef LINE_CLASS_H
#define LINE_CLASS_H

//definir clase line

class line
{
private:
    //Numero de estaciones que tendra la linea
    unsigned int num_estations;
    // matriz unidimensional con la linea
    string *ptr_line;
    string name_line;
public:
    //constructor
    line();
    line(unsigned int num_estations_, string name_line_);
    //destructor
    ~line();
    //metodos
    void inicialization_line(unsigned int num_estations);
    string get_name_line();
    string* get_ptr_line();
    unsigned int get_num_estations();
};

#endif // LINE_CLASS_H
