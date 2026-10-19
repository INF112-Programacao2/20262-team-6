#ifndef HERBIVORO_HPP
#define HERBIVORO_HPP
#include "ser.hpp"
class Herbivoro : public Ser
{
private:
    int _qtd_celulas_comidas;
    void set_qtd_celulas_comidas(int qtd);

public:
    //lembrar de atualizar o _tipo
    Herbivoro(int x, int y);

    virtual void atualizar(Grid *grid) override;

    int get_qtd_celulas_comidas();
    
    ~Herbivoro();
};
#endif