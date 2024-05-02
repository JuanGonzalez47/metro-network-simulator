#include <iostream>
#include <string>
#include "network_class.h"

using namespace std;


int main(){

    network red(3);
    red.inicialization_red();
    red.printNetwork();

    return 0;
}
