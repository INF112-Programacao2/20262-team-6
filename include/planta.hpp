#ifndef PLANTA_HPP
#define PLANTA_HPP
#include "celula.hpp"
class Planta : public Ser
{
private:

public:
    //lembrar de atualizar o _tipo
    Planta(int x, int y);

    virtual void atualizar(Grid *grid) override;

    int get_tipo() const;

    ~Planta();
};
#endif