#ifndef ITEM_H
#define ITEM_H

#include <string>

using std::string;

class Item{

    private:
        string tipo;
        int c_golpes;
        int proxima_cx;
        int proxima_cy;
    public:
    //constructor y destructor
        Item();
        Item(string,int,int,int);
        ~Item();
    //Mutadores
        string getTipo();
        void setTipo(string);
        
        int getGolpes();
        void setGolpes(int);
    
        int getPX();
        void setPX(int);

        int getPY();
        void setPY(int);
};

#endif
