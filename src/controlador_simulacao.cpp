#include "controlador_simulacao.hpp"
#include "grid.hpp"
#include "ser.hpp"
#include "posicao.hpp"

ControladorSimulacao::ControladorSimulacao(Grid *grid, float segundos_por_ciclo):
_grid(grid),_pausado(false),_segundos_por_ciclo(segundos_por_ciclo),_tempo_acumulado(0){};

//obs: precisamos criar um grid de bool, pra dizer quais celulas ja foram atualizadas(para que uma celula que se moveu nao seja atualizada mais de uma vez)
void ControladorSimulacao::atualizar(float tempo){
    //criando o grid de suporte (todas as celulas podem ser atualizadas)
    bool gridBool[_grid->get_largura()][_grid->get_altura()] = {true}; 
    if(!_pausado){//so ira atualizar se nao estiver pausado
        int num_de_ciclos = tempo / get_segundos_por_ciclo(); //qtd de ciclos 
        for(int x = 0; x<num_de_ciclos; x++){ //roda x ciclos
            _grid->passar_ciclo();
            for(int i = 0; i < _grid->get_largura(); i++)
                for(int j = 0; j < _grid->get_altura(); j++){
                    if(_grid->get_celula(i, j) != nullptr && gridBool[i][j] && _grid->get_celula(i,j)->get_tipo()!=2){ //se a posicao nao estiver vazia (ou seja, esta com uma celula) ou nao for parede  
                        Posicao posicaoAtual(i,j);
                        _grid->atualizar_posicao(posicaoAtual);//atualiza ela
            
                        //movendo a celula
                        Posicao posicaoNova = _grid->get_celula(i, j)->get_position();//pega o novo local da celula
                        int novo_x = posicaoNova.get_x();
                        int novo_y = posicaoNova.get_y();

                        if ((novo_x != i || novo_y != j) && _grid->is_valid(novo_x, novo_y)){ //se for diferente do atual
                            _grid->mover_celula(i, j, novo_x, novo_y);//move ela pra la
                            gridBool[novo_x][novo_y] = false;//impedindo que a celula seja atualizada dnv
                        };

                        //downcasting para Ser
                        Celula* celula = _grid->get_celula(novo_x, novo_y);
                        Ser* ser = dynamic_cast<Ser*>(celula);

                        if (ser != nullptr && ser->reproduzir()) {//se for Ser e for reproduzir
                            Posicao filho = ser->get_posi_filho();
                            _grid->set_celula(ser->get_tipo(), filho.get_x(), filho.get_y());//cria o filho na posicao
                        }
                    }

                    gridBool[i][j] = false;//impede que a celula atual seja atualizado dnv
                }
                _grid->set_seres_vivos(_grid->get_seres_vivos());
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

ControladorSimulacao::~ControladorSimulacao(){
    
};
