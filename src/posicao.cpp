#include "posicao.hpp"


Posicao::Posicao(int x, int y):
    _x(x),_y(y){};

void Posicao::set_x(int x){
    _x=x;
};

void Posicao::set_y(int y){
    _y=y;
};

void Posicao::set_position(int x, int y){
    _x=x;
    _y=y;
};

int Posicao::get_x(){
    return _x;
};

int Posicao::get_y(){
    return _y;
};

Posicao::~Posicao(){};