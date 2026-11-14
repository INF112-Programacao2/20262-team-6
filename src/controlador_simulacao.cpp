#include "controlador_simulacao.hpp"
#include "grid.hpp"
#include "posicao.hpp"

ControladorSimulacao::ControladorSimulacao(Grid *grid, float segundos_por_ciclo):
_grid(grid),_pausado(false),_segundos_por_ciclo(segundos_por_ciclo),_tempo_acumulado(0){};

void ControladorSimulacao::atualizar(float tempo){
    int num_de_ciclos = tempo / get_segundos_por_ciclo(); //qtd de ciclos 
    for(int x = 0; x<num_de_ciclos; x++){ //roda x ciclos
        _grid->passar_ciclo();
        _grid->set_seres_vivos(_grid->get_seres_vivos());
        for(int i = 0; i < _grid->get_largura(); i++)
            for(int j = 0; j < _grid->get_altura(); j++)
                if(_grid->get_celula(i, j) != nullptr){ //se a posicao nao estiver vazia (ou seja, esta com uma celula)  
                    Posicao posicaoAtual(i,j);
                    _grid->atualizar_posicao(posicaoAtual);//atualiza ela

                    if(_grid->get_celula(i,j)->reroduzir())//se a celula for reproduzir
                        _grid->set_celula(_grid->get_celula()->get_tipo(),i ,j);//cria uma nova celula no local designado
                    };
                }
    }
};

void ControladorSimulacao::avancar_ciclo(){
    atualizar(get_segundos_por_ciclo());//passa apenas 1 ciclo
};

void ControladorSimulacao::avancar_ciclos(int qtd){
    for(int i = 0; i < qtd; i++)//atualiza x ciclos
        atualizar(get_segundos_por_ciclo());
};


void ControladorSimulacao::pausar(){
    _pausado = true;
};

void ControladorSimulacao::retomar(){
    _pausado = false;
};

void ControladorSimulacao::alternar_pausa(){
    _pausado = !_pausado;
};

bool ControladorSimulacao::is_pausado() const{
    return _pausado;
};


void ControladorSimulacao::set_segundos_por_ciclo(float segundos){
    _segundos_por_ciclo = segundos;
};

float ControladorSimulacao::get_segundos_por_ciclo() const{
    return _segundos_por_ciclo;
};


Grid *ControladorSimulacao::get_grid() const{
    return _grid;
}; 


//nao e dono do grid, entao nao deleta o grid no destrutor
ControladorSimulacao::~ControladorSimulacao(){
    
};
