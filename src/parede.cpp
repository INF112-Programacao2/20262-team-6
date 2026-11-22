#include"parede.hpp"
#include"celula.cpp"

Parede::Parede(int x, int y) : Celula(x, y){
}

int Parede::get_tipo() const{
    return 2;
}

void Parede::atualizar(Grid *grid){
    (void)grid; // Parede é estática, não executa ações ao atualizar
}

Parede::~Parede(){}