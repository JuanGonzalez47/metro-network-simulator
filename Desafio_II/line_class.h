#include <string>
#include <iostream>
#include <sstream>
using namespace std;

#ifndef LINE_CLASS_H
#define LINE_CLASS_H


//definir clase line
class line
{
private:

    //tamaño del arreglo ptrline
    unsigned int tam_ptr_line;
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
    void addStation(string sta,bool first_pos);
    void addStation(string sta, unsigned int i);
    void amountStations();
    bool findStation(string sta);
    void deleteStation(string sta);
    void timeStations();

    //getters
    string get_name_line();
    string* get_ptr_line();
    unsigned int get_tam_ptr_line();
    unsigned int get_num_estations();
    bool get_object_valid();

    //setters
    void set_tam_ptr_line(unsigned int tam_);
};

  //funciones para algunas verificaciones

string verifyStation(line* L,string phrase);
string mayus_to_minus(string word);
string minus_to_mayus(string word);
string verifyNum();



#endif // LINE_CLASS_H

