#ifndef PAREDE_HPP
#define PAREDE_HPP
#include "celula.hpp"
class Parede : public Celula
{
private:


public:
    //lembrar de atualizar o _tipo
    Parede(int x, int y);

    void atualizar(Grid *grid);
    ~Parede();
};
#endif