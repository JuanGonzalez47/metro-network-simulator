#ifndef NETWORK_CLASS_H
#define NETWORK_CLASS_H

#include "line_class.h"

class network
{

private:

    unsigned int tam_matrix_network;
    line *matrixNetwork;
    unsigned int numLines;
    //Atributo que tomar en cuenta las veces que se repite una estacion de transferencia, esto a tener en cuenta en el metodo amountStations
    unsigned int Amount_stations_auxiliar = 0;

public:

    //constructor
    network(unsigned int numLines_);

    //destructor
    ~network();

    //metodos
    void inicialization_red();
    void inicialization_line(unsigned int num_estations, string name_line, unsigned int m, unsigned int cont_line, line *line);
    void addLine();
    void deleteLine(string name_line);
    void amountline();
    void amountStations();
    void printNetwork();
    bool line_on_red(string name_line);
    bool normal_estation_on_red(string name_estation, unsigned int numLines, bool valid, string name_estation_same_line);
    void search_transfer_and_put(string name_line_transfer, string name_estation);
    bool normal_estation_on_red(string name_estation);

    //getters
    unsigned int get_numLines();
    line* getMatrixnetwork();
    unsigned int getTamMatrixNetwork();

    //setter
    void set_Amount_stations_auxiliar(unsigned int new_value);
    void setTamMatrixNetwork(unsigned int tam_);
};



#endif // NETWORK_CLASS_H
