#include "controlador_simulacao.hpp"
#include "grid.hpp"
#include "posicao.hpp"

ControladorSimulacao::ControladorSimulacao(Grid *grid, float segundos_por_ciclo):
_grid(grid),_pausado(false),_segundos_por_ciclo(segundos_por_ciclo),_tempo_acumulado(0){};

void ControladorSimulacao::atualizar(float tempo){
    //percorre o grid
    for(int i = 0; i < _grid->get_largura(); i++)
        for(int j = 0; j < _grid->get_altura(); j++)
            if(_grid->get_celula(i, j) != nullptr){ //se a posicao nao estiver vazia (ou seja, esta com uma celula)  
                Posicao posicaoAtual(i,j);
                Grid *visao = _grid->get_grid(posicaoAtual, 1); //criando um sub-grid com raio 1
                _grid->get_celula(i, j)->atualizar(visao);//atualizando a celula
                delete visao;//deletando o subgrid criado
            }
};

void ControladorSimulacao::avancar_ciclo(){
    atualizar(1);
};

void ControladorSimulacao::avancar_ciclos(int qtd){
    for(int i = 0; i < qtd; i++)
        atualizar(1);
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