#ifndef INTERFACE_HPP
#define INTERFACE_HPP
#include <SFML/Graphics.hpp>
#include "grid.hpp"

class Interface
{
private:
    Grid *_grid;
    int _tam_celula;
    sf::RenderWindow _janela;
    sf::Clock _relogio;
    float _acumulado, _segundos_por_ciclo;
    bool _pausado, _avancar_um;

    void processar_eventos();
    void atualizar();
    void desenhar();
    sf::Color cor_do_tipo(int tipo) const;

public:
    Interface(Grid *grid, int tam_celula);
    void executar();
};

#endif