#include "carnivoro.hpp"
#include "grid.hpp"

// Construtor: posicao e energia incial
Carnivoro::Carnivoro(int x, int y) : Ser(x, y) {
    set_energia(40); // Começa com energia abaixo de 60 para não reproduzir logo no inicio
}


int Carnivoro::get_tipo() const {
    return 3; 
} // Define o tipo do Carnívoro (Carnivoro=3)

void Carnivoro::atualizar(Grid *grid) {
    Ser::atualizar(grid); // Atualização (idade +=1 e energia-=1)
   
    if (get_energia() <= 0) {
        return; // Se a energia chegou a 0, ele morre
    }

    int atual_x = get_position().get_x();
    int atual_y = get_position().get_y();
    bool comeu = false;

    // Tenta comer um herbivoro
    for (int i = -1; i <= 1 && !comeu; i++) {
        for (int j = -1; j <= 1 && !comeu; j++) {
            if (i == 0 && j == 0) continue; // Ignora a própria posição

            int vizinho_x = atual_x + i;
            int vizinho_y = atual_y + j;

            // Verifica as posições válidas
            if (vizinho_x >= 0 && vizinho_x < grid->get_largura() && 
                vizinho_y >= 0 && vizinho_y < grid->get_altura()) {
                
                Celula* celula_vizinha = grid->get_celula(vizinho_x, vizinho_y);
                
                // Se não está vazio e eh um herbivoro (tipo 4)
                if (celula_vizinha != nullptr && celula_vizinha->get_tipo() == 4) {
                    set_energia(get_energia() + 20);  // Come o herbívoro ganha 20 de energia
                    
                    grid->set_celula(0, vizinho_x, vizinho_y); 
                    set_position(vizinho_x, vizinho_y);
                    comeu = true; // Come o herbívoro libertando a célula e move o carnívoro para lá
                }
            }
        }
    }

    // Se nao comeu tenta andar
    if (!comeu) {
        for (int i = -1; i <= 1 && !comeu; i++) {
            for (int j = -1; j <= 1 && !comeu; j++) {
                if (i == 0 && j == 0) continue;

                int vizinho_x = atual_x + i;
                int vizinho_y = atual_y + j;

                if (vizinho_x >= 0 && vizinho_x < grid->get_largura() && 
                    vizinho_y >= 0 && vizinho_y < grid->get_altura()) {
                    
                   
                    if (grid->get_celula(vizinho_x, vizinho_y) == nullptr) {
                        set_position(vizinho_x, vizinho_y);
                        set_energia(get_energia() - 1); // Andar gasta energia
                        comeu = true;
                    }
                }
            }
        }
    }

    // Reproducao
    if (get_energia() >= 60) {
        bool encontrou_lugar = false;
        for (int i = -1; i <= 1 && !encontrou_lugar; i++) {
            for (int j = -1; j <= 1 && !encontrou_lugar; j++) {
                if (i == 0 && j == 0) continue;

                // Usa a nova posição (se ele tenha andado ou comido)
                int vizinho_x = get_position().get_x() + i; 
                int vizinho_y = get_position().get_y() + j;

                if (vizinho_x >= 0 && vizinho_x < grid->get_largura() && 
                    vizinho_y >= 0 && vizinho_y < grid->get_altura()) {
                    
                    // Se achar um espaço vazio para o filho nascer
                    if (grid->get_celula(vizinho_x, vizinho_y) == nullptr) {
                        _quer_reproduzir = true;
                        _posi_filho = Posicao(vizinho_x, vizinho_y);
                        
                        // Perde metade da energia
                        set_energia(get_energia()/2);
                        
                        encontrou_lugar = true;
                    }
                }
            }
        }
    }
}
Carnivoro::~Carnivoro() {} //Destrutor