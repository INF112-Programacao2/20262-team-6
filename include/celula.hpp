#ifndef CELULA_HPP
#define CELULA_HPP
#include "posicao.hpp"
#include "grid.hpp"
#include <string>
class Celula
{
private:
    Posicao _posicao;
    const int _tipo;
    std::string _regras;
public:
    Celula(Posicao &Posicao);
    void set_position(Posicao &Posicao);
    Posicao get_position();
    int get_tipo() const;
    virtual void atualizar(Grid &grid);
    ~Celula();
};
#endif