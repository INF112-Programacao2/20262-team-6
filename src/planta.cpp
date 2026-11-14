#include "planta.hpp"
#include "posicao.hpp"
#include "ser.hpp"
#include "grid.hpp"
#include <iostream>

Planta::Planta(int x, int y):
    Ser(x, y){};

void Planta::atualizar(Grid *grid){ 
    set_energia(get_energia()+1); //aumenta a energia da planta a cada ciclo
    set_idade(get_idade()+1);

    if(_energia<5)
        return;

    if(_energia >= 5) //se a energia da planta for maior ou igual a 5, ela se reproduzir
        //procura uma celula vazia ao redor da planta para colocar a nova planta  
        for(int i = 0; i <= 2; i++)
            for(int j = 0; j <= 2; j++) 
                //se a celula estiver vazia
                if(grid->get_celula(i, j) == nullptr){ 
                    Posicao posicao_filho(get_position().get_x()-i,get_position().get_y()-j);//criando a posicao relativa ao grid original
                    _quer_reproduzir = true;//indica que quer reproduzir (sera usado pelo controlador_simulacao)
                    _posi_filho = posicao_filho;//local onde o filho nascera (sera usado pelo controlador_simulacao)
                    set_energia(get_energia()-5); //reduz 5 da energia da planta
                    set_qtd_filhos(get_qtd_filhos()+1);
                    return;
                };
    
    //se, ao olhar todo o grid, nao tiver celulas disponiveis, reseta a energia pra 5;
    set_energia(5);
};

int Planta::get_tipo() const{
    return 1; //retorna o tipo da celula
};

Planta::~Planta(){};