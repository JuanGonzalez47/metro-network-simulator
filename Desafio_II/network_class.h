#ifndef NETWORK_CLASS_H
#define NETWORK_CLASS_H

#include "line_class.h"

class network : public virtual_network_class{

private:

    line *matrixNetwork;
    unsigned int numLines;
    int *elemLine;
    string name_lines;

public:

    //constructor
    network(unsigned int numLines_);
    network();

    //destructor


    //metodos
    void inicialization_red(virtual_network_class *red_aux);
    void addLine();
    void deleteLine();
    void amountline();
    void amountStations();
    void printNetwork();
    bool line_on_red(string name_line);
    bool normal_estation_on_red(string name_estation, unsigned int num_estations, unsigned int numLines, bool valid, string name_estation_same_line) override;
  
    //geters
    unsigned int get_numLines () override;
    string get_name_lines() override;


};



#endif // NETWORK_CLASS_H
