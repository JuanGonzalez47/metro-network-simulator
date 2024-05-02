#ifndef NETWORK_CLASS_H
#define NETWORK_CLASS_H

#include<line_class.h>

class network {

private:

    line *matrixNetwork;
    unsigned int numLines;
    int *elemLine;

public:

    //constructor


    //destructor


    //metodos
    network(unsigned int numLines_);
    void inicialization_red();
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
