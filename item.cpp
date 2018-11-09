#include "Item.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

Item::Item(){

}

Item::Item(string ti,int gol,int x,int y){

    tipo=ti;
    c_golpes=gol;
    proxima_cx=x;
    proxima_cy=y;

}

string Item::getTipo(){

    return tipo;

}

void Item::setTipo(string t){

    tipo=t;

}

int Item::getGolpes(){

    return c_golpes;

}


void Item::setGolpes(int g){

    c_golpes=g;

}

int Item::getPX(){

    return proxima_cx;

}


void Item::setPX(int x){

    proxima_cx=x;

}


int Item::getPY(){

    return proxima_cy;

}


void Item::setPY(int y){

    proxima_cy=y;

}

