#include "herbivoro.hpp"
#include "ser.hpp"
#include "grid.cpp"

Herbivoro::Herbivoro(int x, int y) : Ser(x, y) {
    set_energia(40); 
}

int Herbivoro::get_qtd_celulas_comidas(){
    return _qtd_celulas_comidas;
}

int Herbivoro:: get_tipo() const{
    return 4; //tipo do herbivoro = 4
}


void Herbivoro::atualizar(Grid *grid) {
    
    //Atualiza a idade e a energia
    Ser::atualizar(grid);

    if (get_energia() <= 0) {  ///Se a energia chegar a 0, ele morre
        return; 
    }


    //tentar comer:
    //olha todas as casas vizinhas e verifica se tem alguma planta
    //se sim ele se move para a celula da planta e aumenta a energia
    

    int atual_x = get_position().get_x();
    int atual_y = get_position().get_y();
    bool comeu = false;

   
    for (int i = -1; i <= 1 && !comeu; i++) {   //um loop pra olhar as casas vizinhas 
        for (int j = -1; j <= 1 && !comeu; j++) {
            if (i == 0 && j == 0) continue; // ignora a própria posição

            int vizinho_x = atual_x + i;
            int vizinho_y = atual_y + j;

            // verificar se está dentro dos limites do mapa:
            if (vizinho_x >= 0 && vizinho_x < grid->get_largura() && 
                vizinho_y >= 0 && vizinho_y < grid->get_altura()) {
                
                Celula* celula_vizinha = grid->get_celula(vizinho_x, vizinho_y);
                
                // Se a célula não está vazia e é uma Planta, verifica se esta vazio pq o c++ n consegue verificar se nullpt é igual a 1, da erro
                if (celula_vizinha != nullptr && celula_vizinha->get_tipo() == 1) {
                    // Come a planta (ganha energia)
                    set_energia(get_energia() + 20);
                    
                    // Apaga a planta do grid e move o herbívoro para essa posição
                    grid->set_celula(0, vizinho_x, vizinho_y); // "liberta" a célula
                    set_position(vizinho_x, vizinho_y);
                    comeu = true;
                }
            }
        }
    }

    // se n comeu, tenta se locomover e gasta 2 de energia
    if (!comeu) {
        for (int i = -1; i <= 1 && !comeu; i++) {
            for (int j = -1; j <= 1 && !comeu; j++) {
                if (i == 0 && j == 0) continue;

                int vizinho_x = atual_x + i;
                int vizinho_y = atual_y + j;

                if (vizinho_x >= 0 && vizinho_x < grid->get_largura() && 
                    vizinho_y >= 0 && vizinho_y < grid->get_altura()) {
                    
                    // Se a célula estiver vazia
                    if (grid->get_celula(vizinho_x, vizinho_y) == nullptr) {
                        set_position(vizinho_x, vizinho_y);
                        set_energia(get_energia() - 2); // anda e gasta energia
                        comeu = true;
                    }
                }
            }
        }
    }

    // reproduzir: 
    if (get_energia() >= 60) {
        // Procura um espaço vazio na vizinhança para o filho nascer
        bool encontrou_lugar = false;
        for (int i = -1; i <= 1 && !encontrou_lugar; i++) {
            for (int j = -1; j <= 1 && !encontrou_lugar; j++) {
                if (i == 0 && j == 0) continue;

                int vizinho_x = get_position().get_x() + i; // Usa a posição atual (pra caso tenha andado)
                int vizinho_y = get_position().get_y() + j;

                if (vizinho_x >= 0 && vizinho_x < grid->get_largura() && 
                    vizinho_y >= 0 && vizinho_y < grid->get_altura()) {
                    
                    if (grid->get_celula(vizinho_x, vizinho_y) == nullptr) {

                        _quer_reproduzir = true;
                        _posi_filho = Posicao(vizinho_x, vizinho_y);
                        
                        // Perde metade da energia
                        set_energia(get_energia() / 2);
                        
                        encontrou_lugar = true;
                    }
                }
            }
        }
    }
} 

Herbivoro::~Herbivoro(){}
