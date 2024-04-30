#include<string>
using namespace std;


#ifndef NETWORK_CLASS_H
#define NETWORK_CLASS_H

class network {

private:

    string **matrixNetwork;
    int numLines;
    int *elemLine;
    string *ptr_estations_transfer = new string;

public:

    //constructor


    network(int _numLines);

    //metodos
    void addLine();
    void deleteLine();
    void amountline();
    void amountStations();
    void printNetwork();

    //errores
    struct does_not_possible_create_tranfer_estation{};
    struct is_impossible_repeat_estation{};
    struct is_impossible_to_create_line{};
    is_impossible_to_create_line error3;
    is_impossible_repeat_estation error2;
    does_not_possible_create_tranfer_estation error1;
};



#endif // NETWORK_CLASS_H
