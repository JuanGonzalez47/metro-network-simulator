#include "network_class.h"


network::network(unsigned int numLines_)
{
    numLines = numLines_;
    //memoria reservada para la red que contendra los objetas "line"
    matrixNetwork = new line[numLines + 10];
}

network::network()
{
//constructor para poder llevar a cabo el polimorfismo
}

void network::inicialization_red(virtual_network_class *red_aux)
{
    //booleano que me dira si la linea esta o no repetida
    bool verify_line;
    string name_line;
    unsigned int num_estations;
    //entero para llevar a cabo una verificacion de transferencia
    unsigned int cont_line = 0;

    for (unsigned int i = 0; i < numLines; i++){
        verify_line = true;
        while (verify_line){
            cout<<"Ingrese el nombre de la linea "<<i+1<<" : ";cin>>name_line;
            if (this->line_on_red(name_line)) cout<<"Ingrese una linea que no este en la red"<<endl<<endl;
            else{
                //agregar al string que contiene los nombres de las lineas, la linea que se agrego
                name_lines += name_line;
                cout<<"Ingrese el numero de estaciones de la linea "<<name_line<<" : ";cin>>num_estations;
                //crear un puntero a cada uno de los objetos
                //esto se hace porque si pasamos el objeto directamente, cuando sale del for llama automaticamente
                //el destrcutor y matrixNetwork estaria accediendo a una memoria invalida (ya liberada)
                //le pasamos al constructor sobrecargado de la clase line ese puntero a la clase network
                //para que el puntero de la clase abstracta quede incializado con un puntero a la clase red y posteriormente
                //usar metodos de la clase network en line (esto se da por el polimorfismo y la sobreescritura que estamos haciendo del metodo)
                red_aux = this;
                line* name_object = new line(num_estations, name_line);
                name_object->inicialization_line(num_estations,name_line,i,red_aux,cont_line);
                matrixNetwork[i] = *name_object;
                cont_line++;
                verify_line = false;
            }
        }
    }
}

void network::addLine(virtual_network_class *red_aux)
{
    //booleano que me dira si la linea esta o no repetida
    bool verify_line = true;
    string name_line;
    unsigned int num_estations;
    //entero para llevar a cabo una verificacion de transferencia
    unsigned int cont_line = 0;
    while (verify_line){
        cout<<"Ingrese el nombre de la linea "<<numLines + 1<<" a agregar : ";cin>>name_line;
        if (this->line_on_red(name_line)) cout<<"Ingrese una linea que no este en la red"<<endl<<endl;
        else{
            //agregar al string que contiene los nombres de las lineas, la linea que se agrego
            name_lines += name_line;
            cout<<"Ingrese el numero de estaciones de la linea "<<name_line<<" : ";cin>>num_estations;
            //crear un puntero a cada uno de los objetos
            //esto se hace porque si pasamos el objeto directamente, cuando sale del for llama automaticamente
            //el destrcutor y matrixNetwork estaria accediendo a una memoria invalida (ya liberada)
            //le pasamos al constructor sobrecargado de la clase line ese puntero a la clase network
            //para que el puntero de la clase abstracta quede incializado con un puntero a la clase red y posteriormente
            //usar metodos de la clase network en line (esto se da por el polimorfismo y la sobreescritura que estamos haciendo del metodo)
            red_aux = this;
            line* name_object = new line(num_estations, name_line);
            name_object->inicialization_line(num_estations,name_line,1,red_aux,cont_line);
            matrixNetwork[numLines] = *name_object;
            cont_line++;
            verify_line = false;
            //actualizar el atributo de numero de lineas
            numLines++;
        }
    }
}


void network::printNetwork(){
    cout << "RED METRO\n\n";
    for(unsigned int i = 0; i < numLines;i++){
        cout<<"linea "<<matrixNetwork[i].get_name_line();
        for(unsigned j = 0; j < (matrixNetwork[i].get_num_estations()*2)-1;j+=2){
            cout<<" " <<"|"<<(matrixNetwork[i].get_ptr_line())[j]<<"|";
        }
        cout<<endl;
    }
    cout<<endl;
}

bool network::line_on_red(string name_line)
{
    for (unsigned int i = 0; i < numLines; i++){
        if (name_line == matrixNetwork[i].get_name_line())return true;
    }
    return false;
}

bool network::normal_estation_on_red(string name_estation, unsigned int num_estations, unsigned int numLines, bool valid, string name_estation_same_line)
{
    for (unsigned int i = 0; i < numLines; i++){
        if (name_estation_same_line.find(name_estation) != string::npos) return true;
        else if (matrixNetwork[i].get_object_valid()){
            for (unsigned j = 0; j < num_estations; j++){
                if (valid == true) if (name_estation == matrixNetwork[i].get_ptr_line()[j]) return true;
            }
        }
        else return false;
    }
    return false;
}

void network::find_name_line(string name_line_transfer)
{
    for (unsigned int w = 0; w < numLines; w++){
        if (matrixNetwork[w].get_name_line() == name_line_transfer) matrixNetwork[w].addStation();
    }
}


unsigned int network::get_numLines()
{
    return numLines;
}


string network::get_name_lines()
{
    return name_lines;
}

void network::amountline(){

    cout<<"la red metro tiene "<<numLines<<" lineas \n";

}


void network::amountStations()
{
    unsigned int sum_estations = 0;
    for(unsigned int i = 0; i < numLines; i++){
        sum_estations += matrixNetwork[i].get_num_estations();
    }
    cout<<"La red metro tiene "<<sum_estations<<" estaciones \n";
}


void network::deleteLine(string name_line)
{
    for(unsigned int i = 0; i < numLines; i++){
        if (matrixNetwork[i].get_name_line() == name_line){
            //pasarle un nuevo objeto line invalido
            line* name_object = new line();
            if (i == numLines - 1) {
                matrixNetwork[i] = *name_object;
                //actualizar atributo
                numLines--;
                break;
            }
            else{
                //poner en esa posicion otro objeto vacio e invalido
                matrixNetwork[i] = *name_object;
                //tomar la posicion en la cual la encontro
                for(unsigned int j = i; j < numLines; j++){
                    //mover los elementos
                    matrixNetwork[j] = matrixNetwork[j+1];
                }
                //actualizar atributo
                numLines--;
                break;
            }
        }
    }

}

