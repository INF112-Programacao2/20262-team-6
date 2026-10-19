#ifndef CELULA_HPP
#define CELULA_HPP
#include "posicao.hpp"
#include "grid.hpp"
#include <string>

class Grid;

class Celula
{
protected:
    Posicao _posicao;
    const int _tipo;
public:
    //cria Posicao internamente
    Celula(int x, int y);

    Posicao get_position();
    void set_position(int x, int y);


    int get_tipo() const;

    virtual void atualizar(Grid *grid) = 0;

    ~Celula();
};
#endif