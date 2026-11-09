#include "planta.hpp"
#include "Ser.hpp"
#include "grid.hpp"

Planta::Planta(int x, int y):
    Ser(x, y){};

void Planta::atualizar(Grid *grid){ 
    _energia++; //aumenta a energia da planta a cada ciclo

    if(_energia<5)
        return;

    if(_energia >= 5) //se a energia da planta for maior ou igual a 5, ela se reproduz
        //procura uma celula vazia ao redor da planta para colocar a nova planta
        for(int i = -1; i <= 1; i++)
            for(int j = -1; j <= 1; j++)
                //se a celula selecionada estiver dentro do grid...
                if(grid->is_valid(_posicao.get_x()+i, _posicao.get_y()+j))
                    //e a celula estiver vazia
                    if(grid->get_celula(_posicao.get_x()+i, _posicao.get_y()+j) == nullptr){
                        grid->set_celula(1, _posicao.get_x()+i, _posicao.get_y()+j); //cria uma nova planta na celula vazia
                        _energia -= 5; //reduz 5 da energia da planta
                        return;
                    };
    
    //se, ao olhar todo o grid, nao tiver celulas disponiveis, reseta a energia pra 0;
    _energia = 0;
};

int Planta::get_tipo() const{
    return 1; //retorna o tipo da celula
};

Planta::~Planta(){};