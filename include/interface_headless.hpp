
#ifndef INTERFACE_HEADLESS_HPP
#define INTERFACE_HEADLESS_HPP

#include "interfaceIF.hpp"
#include "controlador_simulacao.hpp"
#include "gerenciador_load.hpp"
#include "gerenciador_save.hpp"
#include "gerenciador_stats.hpp"

class Interface_headless: public InterfaceIF
{
private:
    bool _TUI;

    ControladorSimulacao *_controlador;
    Gerenciador_save *_gerenciador_save;
    Gerenciador_load *_gerenciador_load;
    Gerenciador_stats *_gerenciador_stats;
    Grid *_grid;

    void desenhar_painel();
public:
    Interface_headless(bool tui,ControladorSimulacao *controlador, 
            Gerenciador_save *save,Gerenciador_load *load,
            Gerenciador_stats *stats);

    virtual void executar() override;

    virtual ~Interface_headless() override;
};

#endif