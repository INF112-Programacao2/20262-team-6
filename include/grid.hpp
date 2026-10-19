#ifndef GRID_HPP
#define GRID_HPP
#include "celula.hpp"

class Celula;

class Grid
{
private:
    Celula ***_grid;
    int _largura,_altura,_ciclos,_seres_vivos;
    
    void set_seres_vivos();
    void set_largura();
    void set_altura();
    void set_ciclos();
public:
    Grid(int largura,int altura);

    void set_celula(int tipo, Posicao &posicao);
    Celula* get_celula(Posicao &posicao);
    bool is_valid();
    //recebe posicao da celula e o raio de visao dela
    Grid *get_grid(Posicao &posicao, int visao);

    int get_seres_vivos();
    int get_largura();
    int get_altura();
    int get_ciclos();

    void atualizar_posicao(Posicao &posicao);

    ~Grid();
};
#endif