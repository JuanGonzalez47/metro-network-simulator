#ifndef VIRTUAL_NETWORK_CLASS_H
#define VIRTUAL_NETWORK_CLASS_H
#include <string>
using namespace std;

class virtual_network_class{
public:
    virtual bool normal_estation_on_red(string name_estation, unsigned int numLines, bool valid, string name_estation_same_line) = 0;
    virtual unsigned int get_numLines() = 0;
    virtual void search_transfer_and_put(string name_line_transfer, string name_estation) = 0;
    virtual bool line_on_red(string name_line) = 0;
    virtual void set_Amount_stations_auxiliar(unsigned int new_value) = 0;
};

#endif // VIRTUAL_NETWORK_CLASS_H
