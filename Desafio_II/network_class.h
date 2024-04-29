#include<string>
using namespace std;


#ifndef NETWORK_CLASS_H
#define NETWORK_CLASS_H

class network {

private:

    string **matrixNetwork;
    int numLines;
    int *elemLine;

public:

    //constructor


    network(int _numLines);

    //metodos
    void addLine();
    void deleteLine();
    void amountline();
    void amountStations();
    void printNetwork();

};



#endif // NETWORK_CLASS_H
