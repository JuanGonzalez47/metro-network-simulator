#include <iostream>
#include <string>
#include "network_class.h"

using namespace std;


int main(){

    network red(3);
    virtual_network_class *red_aux;

    red.inicialization_red(red_aux);
    red.printNetwork();

    return 0;
}
