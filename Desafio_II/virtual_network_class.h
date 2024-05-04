#ifndef VIRTUAL_NETWORK_CLASS_H
#define VIRTUAL_NETWORK_CLASS_H
#include <string>
using namespace std;

class virtual_network_class{
public:
    virtual bool normal_estation_on_red(string name_estation, unsigned int num_estations, unsigned int numLines, bool valid, string name_estation_same_line) = 0;
    virtual unsigned int get_numLines() = 0;
    virtual string get_name_lines() = 0;
    virtual void search_transfer_line_and_put_estation(string name_estation, string name_line_transfer, unsigned int num_estations_line, unsigned int numLines) = 0;
};

#endif // VIRTUAL_NETWORK_CLASS_H
