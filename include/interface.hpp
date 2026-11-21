#ifndef INTERFACE_HPP
#define INTERFACE_HPP
#include <SFML/Graphics.hpp>
#include <string>
#include "grid.hpp"
#include "controlador_simulacao.hpp"
#include "gerenciador_arquivos.hpp"

class Interface{
private:
    //a interface nao e dona do controlador nem do gerenciador, entao nao deleta essas classes
    ControladorSimulacao *_controlador;
    Gerenciador_arquivo *_gerenciador;
    Grid *_grid;
    int _tam_celula;
    //tipo que o botao esquerdo do mouse desenha
    int _tipo_selecionado;
    //tempo guardado ate completar um ciclo
    float _tempo_acumulado;
    //resultado do ultimo salvar/carregar, mostrado no painel
    std::string _mensagem;
    sf::RenderWindow _janela;
    sf::Font _fonte;
    sf::Clock _relogio;

    void processar_eventos();
    //avanca a simulacao pelo controlador, no ritmo da velocidade escolhida
    void atualizar();
    void desenhar();
    void desenhar_grid();
    //parte de baixo da janela: legenda, botoes, estado da simulacao e comandos
    void desenhar_painel();
    void escrever(const std::string &texto, float x, float y, sf::Color cor);

    //coloca uma celula do tipo dado na posicao do grid que esta embaixo do pixel (tipo 0 apaga)
    void pintar(sf::Vector2i pixel, int tipo);
    sf::Color cor_do_tipo(int tipo) const;
    std::string nome_do_tipo(int tipo) const;

    //botoes do painel, numerados de 0 a 5 da esquerda para a direita
    sf::FloatRect area_botao(int indice) const;
    std::string texto_botao(int indice) const;
    void clicar_botao(int indice);

    void avancar_um_ciclo();
    void mudar_velocidade(float fator);
    void salvar();
    void carregar();

public:
    //throw um runtime_error se a fonte nao for encontrada
    Interface(ControladorSimulacao *controlador, Gerenciador_arquivo *gerenciador, int tam_celula);
    //abre a janela e so retorna quando ela for fechada
    void executar();
};

#endif
