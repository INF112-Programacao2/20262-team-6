/*#ifndef GRID_HPP
#define GRID_HPP
#include "celula.hpp"
class Grid
{
private:
    Celula *_grid[][];
    int **matriz
    int _largura,_altura;
public:
    Grid(int largura,int altura);
    void set_celula(int tipo, Posicao &posicao);
    Celula* get_celula(Posicao &posicao);
    bool is_valid();
    Celula **get_grid();
    ~Grid();
};
#endif*/