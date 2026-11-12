#ifndef PLANTA_HPP
#define PLANTA_HPP
#include "celula.hpp"
class Planta : public Ser
{
private:
    int _energia;
public:
    Planta(int x, int y);

    //recebe um grid reduzido, e atualiza a planta de acordo com as regras do jogo
    virtual void atualizar(Grid *grid) override;

    int get_tipo() const;

    ~Planta();
};
#endif