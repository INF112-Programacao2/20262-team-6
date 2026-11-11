#include "celula.hpp"
#include "posicao.hpp"

Celula::Celula(int x, int y): _posicao(x,y){}
void Celula::set_position(int x,int y)
{
    this->_posicao.set_position(x,y);
}

Posicao Celula::get_position() const
{
    return this->_posicao;
}

Celula::~Celula(){}