#ifndef CELULA_HPP
#define CELULA_HPP
#include "posicao.hpp"
#include <string>

class Grid;

class Celula
{
protected:
    Posicao _posicao; 
public:
    //cria Posicao internamente
    Celula(int x, int y);

    Posicao get_position() const;
    void set_position(int x, int y);

    virtual int get_tipo() const = 0 ;

    virtual void atualizar(Grid *grid) = 0;

    virtual ~Celula();
};
#endif