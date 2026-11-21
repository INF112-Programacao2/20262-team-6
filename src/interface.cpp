#include "interface.hpp"
#include "celula.hpp"
#include <algorithm>
#include <exception>
#include <iomanip>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>

//caminho da pasta de onde o programa e executado
const std::string ARQUIVO_FONTE = "msc/fonte.ttf";
const int TAM_FONTE = 16;
const int ALTURA_PAINEL = 136;
//largura minima para os botoes caberem
const int LARGURA_MINIMA = 800;

const int QTD_BOTOES = 6;
const float LARGURA_BOTOES[QTD_BOTOES] = {130.f, 90.f, 40.f, 40.f, 100.f, 130.f};
const float ALTURA_BOTAO = 30.f;
const float ESPACO_BOTOES = 8.f;

//limites da velocidade, em segundos por ciclo
const float CICLO_MAIS_RAPIDO = 0.05f;
const float CICLO_MAIS_LENTO = 2.f;

Interface::Interface(ControladorSimulacao *controlador, Gerenciador_arquivo *gerenciador, int tam_celula)
    : _controlador(controlador), _gerenciador(gerenciador), _grid(controlador->get_grid()),
      _tam_celula(tam_celula), _tipo_selecionado(1), _tempo_acumulado(0.f), _mensagem(""),
      //a janela tem o tamanho do grid mais o painel e nao pode ser redimensionada
      _janela(sf::VideoMode({static_cast<unsigned int>(std::max(_grid->get_largura() * tam_celula, LARGURA_MINIMA)),
                             static_cast<unsigned int>(_grid->get_altura() * tam_celula + ALTURA_PAINEL)}),
              "Ecossistema", sf::Style::Titlebar | sf::Style::Close)
{
    if (!_fonte.openFromFile(ARQUIVO_FONTE))
        throw std::runtime_error("nao foi possivel abrir a fonte " + ARQUIVO_FONTE + "\n");
    _janela.setFramerateLimit(60);
}

void Interface::executar()
{
    while (_janela.isOpen())
    {
        processar_eventos();
        atualizar();
        desenhar();
    }
}

void Interface::processar_eventos()
{
    //eventos: fechar a janela, apertar uma tecla, clicar
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
            else if (tecla->code == sf::Keyboard::Key::Space)
                _controlador->alternar_pausa();
            else if (tecla->code == sf::Keyboard::Key::Right)
                avancar_um_ciclo();
        }
        else if (const auto *clique = evento->getIf<sf::Event::MouseButtonPressed>())
        {
            //um clique no painel aciona o botao que estiver embaixo do mouse
            if (clique->button == sf::Mouse::Button::Left)
                for (int i = 0; i < QTD_BOTOES; i++)
                    if (area_botao(i).contains(sf::Vector2f(clique->position)))
                        clicar_botao(i);
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

void Interface::atualizar()
{
    float tempo = _relogio.restart().asSeconds();
    if (_controlador->is_pausado())
    {
        _tempo_acumulado = 0.f;
        return;
    }

    //se um quadro demorar muito, nao tenta recuperar todos os ciclos de uma vez
    if (tempo > 0.25f)
        tempo = 0.25f;

    //o controlador so avanca ciclos inteiros, entao o tempo e guardado ate completar um
    _tempo_acumulado += tempo;
    float segundos_por_ciclo = _controlador->get_segundos_por_ciclo();
    while (_tempo_acumulado >= segundos_por_ciclo)
    {
        _controlador->avancar_ciclo();
        _tempo_acumulado -= segundos_por_ciclo;
    }
}

void Interface::pintar(sf::Vector2i pixel, int tipo)
{
    //o mouse pode estar fora da janela
    if (pixel.x < 0 || pixel.y < 0)
        return;

    //converte de pixel para posicao do grid (no painel, cai fora do grid e nao faz nada)
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
    desenhar_grid();
    desenhar_painel();
    _janela.display();
}

void Interface::desenhar_grid()
{
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
}

void Interface::desenhar_painel()
{
    float topo = static_cast<float>(_grid->get_altura() * _tam_celula);
    sf::Color branco(235, 235, 235);
    sf::Color cinza(160, 160, 160);

    //linha 1: instrucoes, com o tipo selecionado em destaque
    float x = 10.f;
    sf::RectangleShape amostra({14.f, 14.f});
    for (int tipo = 1; tipo <= 4; tipo++)
    {
        amostra.setPosition({x, topo + 11.f});
        amostra.setFillColor(cor_do_tipo(tipo));
        amostra.setOutlineThickness(tipo == _tipo_selecionado ? 2.f : 0.f);
        amostra.setOutlineColor(branco);
        _janela.draw(amostra);
        escrever(std::to_string(tipo) + " " + nome_do_tipo(tipo), x + 22.f, topo + 8.f,
                 tipo == _tipo_selecionado ? branco : cinza);
        x += 170.f;
    }

    //linha 2: botoes
    sf::Vector2f mouse(sf::Mouse::getPosition(_janela));
    for (int i = 0; i < QTD_BOTOES; i++)
    {
        sf::FloatRect area = area_botao(i);
        sf::RectangleShape botao(area.size);
        botao.setPosition(area.position);
        //o botao fica mais claro com o mouse em cima
        botao.setFillColor(area.contains(mouse) ? sf::Color(95, 95, 95) : sf::Color(70, 70, 70));
        botao.setOutlineThickness(1.f);
        botao.setOutlineColor(cinza);
        _janela.draw(botao);
        escrever(texto_botao(i), area.position.x + 10.f, area.position.y + 4.f, branco);
    }

    //linha 3: estado da simulacao
    std::ostringstream estado;
    estado << "Ciclo " << _grid->get_ciclos()
           << "   Vivos " << _grid->get_seres_vivos()
           << "   " << std::fixed << std::setprecision(1) << 1.f / _controlador->get_segundos_por_ciclo() << " ciclos/s";
    escrever(estado.str(), 10.f, topo + 78.f, branco);

    //linha 4: resultado do ultimo salvar/carregar ou, se nao houver, os comandos
    if (!_mensagem.empty())
        escrever(_mensagem, 10.f, topo + 106.f, branco);
    else
        escrever("Esq desenha   Dir apaga   Espaco pausa   Seta passo", 10.f, topo + 106.f, cinza);
}

void Interface::escrever(const std::string &texto, float x, float y, sf::Color cor)
{
    sf::Text escrita(_fonte, texto, TAM_FONTE);
    escrita.setFillColor(cor);
    escrita.setPosition({x, y});
    _janela.draw(escrita);
}

sf::FloatRect Interface::area_botao(int indice) const
{
    //cada botao começa onde o anterior termina
    float x = 10.f;
    for (int i = 0; i < indice; i++)
        x += LARGURA_BOTOES[i] + ESPACO_BOTOES;
    float y = static_cast<float>(_grid->get_altura() * _tam_celula) + 38.f;
    return sf::FloatRect({x, y}, {LARGURA_BOTOES[indice], ALTURA_BOTAO});
}

std::string Interface::texto_botao(int indice) const
{
    switch (indice) {
    case 0:
        return _controlador->is_pausado() ? "Retomar" : "Pausar";
    case 1:
        return "Passo";
    case 2:
        return "-";
    case 3:
        return "+";
    case 4:
        return "Salvar";
    case 5:
        return "Carregar";
    };
    return "";
}

void Interface::clicar_botao(int indice)
{
    switch (indice) {
    case 0:
        _controlador->alternar_pausa();
        break;
    case 1:
        avancar_um_ciclo();
        break;
    case 2:
        mudar_velocidade(2.f); //o dobro do tempo por ciclo
        break;
    case 3:
        mudar_velocidade(0.5f); //metade do tempo --
        break;
    case 4:
        salvar();
        break;
    case 5:
        carregar();
        break;
    };
}

void Interface::avancar_um_ciclo()
{
    //o controlador nao avanca enquanto esta pausado, entao a pausa e solta so durante esse ciclo
    bool estava_pausado = _controlador->is_pausado();
    _controlador->retomar();
    _controlador->avancar_ciclo();
    if (estava_pausado)
        _controlador->pausar();
}

void Interface::mudar_velocidade(float fator)
{
    float segundos = _controlador->get_segundos_por_ciclo() * fator;
    if (segundos < CICLO_MAIS_RAPIDO)
        segundos = CICLO_MAIS_RAPIDO;
    if (segundos > CICLO_MAIS_LENTO)
        segundos = CICLO_MAIS_LENTO;
    _controlador->set_segundos_por_ciclo(segundos);
}

void Interface::salvar()
{
    try {
        _gerenciador->save(*_grid);
        _mensagem = "Salvo em " + _gerenciador->get_save();
    } catch (const std::exception &erro) {
        //so a primeira linha do erro cabe no painel
        _mensagem = std::string(erro.what());
        _mensagem = "Erro: " + _mensagem.substr(0, _mensagem.find('\n'));
    }
}

void Interface::carregar()
{
    try {
        //o gerenciador devolve um grid novo; as celulas dele sao copiadas para o grid da simulacao
        Grid *carregado = _gerenciador->load();
        for (int x = 0; x < _grid->get_largura(); x++)
            for (int y = 0; y < _grid->get_altura(); y++)
            {
                int tipo = 0;
                if (carregado->is_valid(x, y) && carregado->get_celula(x, y) != nullptr)
                    tipo = carregado->get_celula(x, y)->get_tipo();
                _grid->set_celula(tipo, x, y);
            }
        delete carregado;
        _mensagem = "Carregado de " + _gerenciador->get_file();
    } catch (const std::exception &erro) {
        _mensagem = std::string(erro.what());
        _mensagem = "Erro: " + _mensagem.substr(0, _mensagem.find('\n'));
    }
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

std::string Interface::nome_do_tipo(int tipo) const
{
    switch (tipo) {
    case 1:
        return "Planta";
    case 2:
        return "Parede";
    case 3:
        return "Carnivoro";
    case 4:
        return "Herbivoro";
    };
    return "";
}
