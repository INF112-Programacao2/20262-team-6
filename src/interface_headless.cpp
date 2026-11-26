#include "interface_headless.hpp"
#include "celula.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>

Interface_headless::Interface_headless(bool tui, ControladorSimulacao *controlador,
                                       Gerenciador_save *save, Gerenciador_load *load,
                                       Gerenciador_stats *stats)
    : _TUI(tui), _controlador(controlador), _gerenciador_save(save),
      _gerenciador_load(load), _gerenciador_stats(stats),
      _grid(controlador->get_grid())
{
    //sincroniza dados entre os gerenciadores
    if (_gerenciador_load != nullptr) {
        int max_ciclos = _gerenciador_load->get_max_ciclos();
        if (_gerenciador_stats != nullptr)
            _gerenciador_stats->set_max_ciclos(max_ciclos);
        if (_gerenciador_save != nullptr)
            _gerenciador_save->set_max_ciclos(max_ciclos);
    }
}

void Interface_headless::desenhar_painel()
{
    //codigo ASCII para limpar a tela
    std::cout << "\033[2J\033[H";
    for(int i = 0; i < this->_grid->get_altura();i++)
    {
        for (int j = 0; j < this->_grid->get_largura(); j++)
        {
            char cell_buffer = ' ';
            Celula *cell = this->_grid->get_celula(j,i);
            if(cell == nullptr)
                cell_buffer=' ';
            else if(cell->get_tipo()==0)
                cell_buffer='*';
            else if(cell->get_tipo()==1)
                cell_buffer='P';
            else if(cell->get_tipo()==2)
                cell_buffer='#';
            else if(cell->get_tipo()==3)
                cell_buffer='C';
            else if(cell->get_tipo()==4)
                cell_buffer='H';
            std::cout << cell_buffer;
        }
        std::cout << std::endl;
    }
    
}

void Interface_headless::executar()
{
    int max_ciclos = _gerenciador_load->get_max_ciclos();

    _gerenciador_stats->stats_update(*_grid);
    if (_TUI) 
        desenhar_painel();

    while (_grid->get_ciclos() < max_ciclos)
    {
        _controlador->avancar_ciclo();
        _gerenciador_stats->stats_update(*_grid);

        if (_TUI) {
            desenhar_painel();
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
        }
    }

    _gerenciador_save->save(*_grid);
    _gerenciador_stats->end_stats(50, std::max(1, max_ciclos / 20));
}

Interface_headless::~Interface_headless(){}