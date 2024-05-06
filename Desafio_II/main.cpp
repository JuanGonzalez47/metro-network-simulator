#include <iostream>
#include <string>
#include "network_class.h"

using namespace std;


int main(){

    network red(2);
    virtual_network_class *red_aux;
    string name_line_delete = "B";

    red.inicialization_red(red_aux);
    red.addLine(red_aux);
    red.deleteLine(name_line_delete);
    red.printNetwork();

    return 0;
}
