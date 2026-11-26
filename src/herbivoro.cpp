#include "herbivoro.hpp"
#include "ser.hpp"
#include "grid.hpp"

Herbivoro::Herbivoro(int x, int y) : Ser(x, y) {
    set_energia(40); 

    _qtd_celulas_comidas = 0;
}

int Herbivoro::get_qtd_celulas_comidas(){
    return _qtd_celulas_comidas;
}

int Herbivoro:: get_tipo() const{
    return 4; //tipo do herbivoro = 4
}


bool Herbivoro::reproduzirHerbivoro(Grid *grid){

 if (get_energia() >= 60) {
        // Procura um espaço vazio na vizinhança para o filho nascer
        bool encontrou_lugar = false;
        for(int i = 0; i <= 2; i++){
            for(int j = 0; j <= 2; j++){
            
                if (grid->get_celula(i, j) == nullptr) {

                    _quer_reproduzir = true;
                    // converte da cópia para o grid real
                    int filho_x = get_position().get_x() + (i - 1);
                    int filho_y = get_position().get_y() + (j - 1);
                    
                    // Perde metade da energia
                    set_energia(get_energia() / 2);
                    set_qtd_filhos(get_qtd_filhos()+1);

                    encontrou_lugar = true;

                    return true;
                }
            }
        }
    }
    return false;
}

bool Herbivoro::alimentar(Grid *grid){

    for(int i = 0; i<= 2 ; i++){
        for(int j = 0; j <= 2; j++){

             Celula* celula_vizinha = grid->get_celula(i, j);
             if (celula_vizinha != nullptr && celula_vizinha->get_tipo() == 1) { // verifica se esta ocupada e se é uma planta
                    // Come a planta (ganha energia)
                    set_energia(get_energia() + 20);
                      _qtd_celulas_comidas++;

                    // converte coordenada do subgrid (0..2) para o grid real
                    int destino_x = get_position().get_x() + (i - 1);
                    int destino_y = get_position().get_y() + (j - 1);

                   // _posi_destino = Posicao(destino_x, destino_y);
                    return true;

             }
        }
    }    
    return false;
}

bool Herbivoro::andar(Grid *grid){
/*  if (!comeu) {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i == 0 && j == 0) continue;

                int vizinho_x = atual_x + i;
                int vizinho_y = atual_y + j;

                if (vizinho_x >= 0 && vizinho_x < grid->get_largura() && 
                    vizinho_y >= 0 && vizinho_y < grid->get_altura()) {
                    
                    // Se a célula estiver vazia
                    if (grid->get_celula(vizinho_x, vizinho_y) == nullptr) {
                        set_position(vizinho_x, vizinho_y);
                        set_energia(get_energia() - 2); // anda e gasta energia
                       
                    }
                }
            }
        }
    }
*/

}



void Herbivoro::atualizar(Grid *grid) {
    
    //Atualiza a idade e a energia
    Ser::atualizar(grid);

    if (get_energia() <= 0) {  ///Se a energia chegar a 0, ele morre
        return; 
    }
    
    bool alimentou = false;   
    bool reproduziu = false;
    bool andou = false;

    // a prioridade  é reproduzir, depois comer, e por ultimo andar 
    //ele executa apenas 1 ação por turno.
    
        
    reproduziu = reproduzirHerbivoro(grid);

    //se não se reproduziu, tenta comer, e se comer ganha 20 de energia
    if(!reproduziu)
    alimentou =  alimentar(grid);

    // se n comeu, tenta se locomover e gasta 2 de energia
    if(!alimentou)
    andou = andar(grid);
} 

Herbivoro::~Herbivoro(){}
