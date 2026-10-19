#ifndef CARNIVORO_HPP
#define CARNIVORO_HPP
#include "ser.hpp"
class Carnivoro : public Ser
{
private:
    int _qtd_celulas_comidas;
    void set_qtd_celulas_comidas(int qtd);
public:
    //lembrar de atualizar o _tipo
    Carnivoro(int x, int y);

    virtual void atualizar(Grid *grid) override;

    int get_qtd_celulas_comidas();

    ~Carnivoro();
};
#endif