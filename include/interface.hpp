#ifndef INTERFACE_HPP
#define INTERFACE_HPP
#include <SFML/Graphics.hpp>
#include "grid.hpp"

class Interface{
private:
    Grid *_grid;
    int _tam_celula;
    //tipo que o botao esquerdo do mouse desenha 
    int _tipo_selecionado;
    sf::RenderWindow _janela;
    void processar_eventos();
    //coloca uma celula do tipo dado na posicao do grid que esta embaixo do pixel (tipo 0 apaga)
    void pintar(sf::Vector2i pixel, int tipo);
    void desenhar();
    void atualizar_titulo();
    sf::Color cor_do_tipo(int tipo) const;

public:
    Interface(Grid *grid, int tam_celula);
    //abre a janela e so retorna quando ela for fechada
    void executar();
};

#endif
