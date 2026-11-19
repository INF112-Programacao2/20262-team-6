#include "interface.hpp"
#include "celula.hpp"
#include <optional>
#include <string>

Interface::Interface(Grid *grid, int tam_celula)
    : _grid(grid), _tam_celula(tam_celula), _tipo_selecionado(1),
      //a janela tem o tamanho exato do grid e nao pode ser redimensionada
      _janela(sf::VideoMode({static_cast<unsigned int>(grid->get_largura() * tam_celula),
                             static_cast<unsigned int>(grid->get_altura() * tam_celula)}),
              "Ecossistema", sf::Style::Titlebar | sf::Style::Close)
{
    _janela.setFramerateLimit(60);
    atualizar_titulo();
}

void Interface::executar()
{
    while (_janela.isOpen())
    {
        processar_eventos();
        desenhar();
    }
}

void Interface::processar_eventos()
{
    //eventos sao coisas que aconteceram uma vez: fechar a janela, apertar uma tecla
    while (const std::optional evento = _janela.pollEvent())
    {
        if (evento->is<sf::Event::Closed>())
            _janela.close();
        else if (const auto *tecla = evento->getIf<sf::Event::KeyPressed>())
        {
            //os numeros escolhem o tipo que o mouse desenha
            if (tecla->code == sf::Keyboard::Key::Num1)
                _tipo_selecionado = 1;
            else if (tecla->code == sf::Keyboard::Key::Num2)
                _tipo_selecionado = 2;
            else if (tecla->code == sf::Keyboard::Key::Num3)
                _tipo_selecionado = 3;
            else if (tecla->code == sf::Keyboard::Key::Num4)
                _tipo_selecionado = 4;
            atualizar_titulo();
        }
    }

    //o botao do mouse e lido a cada quadro, para desenhar tambem enquanto arrasta
    if (!_janela.hasFocus())
        return;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        pintar(sf::Mouse::getPosition(_janela), _tipo_selecionado);
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
        pintar(sf::Mouse::getPosition(_janela), 0);
}

void Interface::pintar(sf::Vector2i pixel, int tipo)
{
    //o mouse pode estar fora da janela
    if (pixel.x < 0 || pixel.y < 0)
        return;

    //converte de pixel para posicao do grid
    int x = pixel.x / _tam_celula;
    int y = pixel.y / _tam_celula;
    if (!_grid->is_valid(x, y))
        return;

    //se a celula ja é desse tipo, nao cria outra por cima
    Celula *celula = _grid->get_celula(x, y);
    int tipo_atual = 0;
    if (celula != nullptr)
        tipo_atual = celula->get_tipo();
    if (tipo_atual == tipo)
        return;

    _grid->set_celula(tipo, x, y);
}

void Interface::desenhar()
{
    _janela.clear(sf::Color(30, 30, 30));

    //um unico quadrado é reaproveitado para todas as celulas
    float lado = static_cast<float>(_tam_celula);
    //linha da grade
    sf::RectangleShape quadrado({lado - 1.f, lado - 1.f});

    for (int x = 0; x < _grid->get_largura(); x++)
        for (int y = 0; y < _grid->get_altura(); y++)
        {
            Celula *celula = _grid->get_celula(x, y);
            if (celula == nullptr)
                quadrado.setFillColor(sf::Color(50, 50, 50));
            else
                quadrado.setFillColor(cor_do_tipo(celula->get_tipo()));
            quadrado.setPosition({x * lado, y * lado});
            _janela.draw(quadrado);
        }

    _janela.display();
}

void Interface::atualizar_titulo()
{
    std::string nome;
    switch (_tipo_selecionado) {
    case 1:
        nome = "Planta";
        break;
    case 2:
        nome = "Parede";
        break;
    case 3:
        nome = "Carnivoro";
        break;
    case 4:
        nome = "Herbivoro";
        break;
    };
    _janela.setTitle("Ecossistema - desenhando: " + nome);
}

sf::Color Interface::cor_do_tipo(int tipo) const
{
    //mesmos numeros usados em Grid::set_celula
    switch (tipo) {
    case 1:
        return sf::Color(60, 180, 75); //planta
    case 2:
        return sf::Color(130, 130, 130); //parede
    case 3:
        return sf::Color(220, 60, 60); //carnivoro
    case 4:
        return sf::Color(240, 200, 60); //herbivoro
    };
    return sf::Color::Magenta;
}
