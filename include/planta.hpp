#ifndef PLANTA_HPP
#define PLANTA_HPP
#include "ser.hpp"
class Planta : public Ser {
private:  
public:
    Planta(int x, int y);

    //recebe um subgrid, e atualiza a planta de acordo com as regras do jogo
    virtual void atualizar(Grid *grid) override;

    int get_tipo() const;

    ~Planta();
};
#endif