#include "controlador_simulacao.hpp"
#include "grid.hpp"
#include "interface.hpp"
#include "interface_headless.hpp"
#include "gerenciador_load.hpp"
#include "gerenciador_save.hpp"
#include "gerenciador_stats.hpp"

#include <cstring>
#include <stdexcept>
#include <iostream>
#include <memory>
#include <iostream>
#include <memory>

//possivelmente passar pelos argumentos da main
const int TAM_CELULA=50;
const int TAM_MAPA=20;
const float SEG_CIC=20;
const int NUM_CIC=20;
const float SEC_PER_CICLO = 0.5;

// funcao recursiva de tratamento de excecao
std::unique_ptr<Gerenciador_load> recLoadInvalido()
{
    std::string arq_load;
    std::cout << "digite o arquivo de entrada/load: ";
    if (!(std::cin >> arq_load)) // evita recursao infinita em caso de EOF (ctrl d)
        throw std::runtime_error("entrada encerrada sem arquivo valido\n");
    try
    {
        return std::make_unique<Gerenciador_load>(arq_load);
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << e.what() << '\n';
        return recLoadInvalido();
    }
}

std::unique_ptr<Grid> recGridInvalido(std::unique_ptr<Gerenciador_load> &load)
{

    std::string arq_load;
    std::cout << "digite o arquivo de entrada/load: ";
    if (!(std::cin >> arq_load))
        throw std::runtime_error("entrada encerrada sem arquivo valido\n");
    try {
        load->set_file(arq_load);
        //casting explicito de ponteiros
        return std::unique_ptr<Grid>(load->load());
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << '\n';
        return recGridInvalido(load);
    }
}

int main(int argc, char* argv[])
{
    try //trata para ver se os argumentos foram corretamente usados
    {
        if(argc<2)
            throw std::invalid_argument("uso: ./<bin> <modo> ex: headless e gui\n");
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    bool headless =false;
    bool gui=false;
    bool tui=false; //terceiro modo

    try
    { //ve se os argumentos estao corretos
        if(std::strcmp(argv[1],"gui")==0)
            gui=true;
        else if(std::strcmp(argv[1],"headless")==0)
            headless=true;
        else if(std::strcmp(argv[1],"tui")==0)
            headless=tui=true;
        else 
            throw std::invalid_argument("uso: ./<bin> <modo> ex: headless, gui, tui\n");
    }
    catch(const std::invalid_argument &e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    std::unique_ptr<Grid>mapa=(new Grid(TAM_MAPA);
    ControladorSimulacao simulacao(mapa, SEG_CIC);
    if(gui){//versao grafica
        Interface interface(mapa, TAM_CELULA)
        for(int i = 0; i < NUM_CIC; i++){
            simulacao.avancar_ciclo();
            intergace.executar();
        }
    }else if(headless){//versao headless
        for(int i = 0; i < NUM_CIC; i++)
            simulacao.avancar_ciclo();
    }
        std::cerr << e.what() << '\n';
        return 1;
    }

    //instanciacao de acordo com o modo
    std::unique_ptr<Interface> interface; // trocar pra InterfaceIF se tiver polimorfismo
    std::unique_ptr<Interface_headless> interface_headless;
    std::unique_ptr<Gerenciador_load> load;
    std::unique_ptr<Gerenciador_stats>stats;
    std::unique_ptr<Gerenciador_save> save;

    std::string arq_save, arq_load, arq_stats;
    //save e load sempre sao instanciados
    //tenta ler arquivos usando os argumnentos da main
    if(argc>=4)
    {
        arq_save=argv[2];
        arq_load=argv[3];
    }
    else //se n existir pede ao user
    {   
        std::cout << "digite o arquivo de entrada/load: ";
        std::cin >> arq_load;

        std::cout << "digite o arquivo de saida/save: ";
        std::cin >> arq_save;
    }

    try
    {
        load = std::make_unique<Gerenciador_load>(arq_load);
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << e.what() << '\n';
        //arquivo ivalido
        try
        {
            load = recLoadInvalido();
        }
        catch(const std::runtime_error& e)
        {
            std::cerr << e.what() << '\n';
            return 1; //falha de load, impossivel continuar sem um arquivo
        }
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what();
        //arquivo ivalido
        try
        {
            load = recLoadInvalido();
        }
        catch(const std::runtime_error& e)
        {
            std::cerr << e.what() << '\n';
            return 1; //falha de load, impossivel continuar sem um arquivo
        }
    }

    //instancia depois para evitar um new desnecesario
    save = std::make_unique<Gerenciador_save>(arq_save);
    std::unique_ptr<Grid> grid;
    try
    {
        grid = std::unique_ptr<Grid>(load->load());
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what();
        //arquivo vazio, excreva dnv
        try
        {
            grid = recGridInvalido(load);
        }
        catch(const std::runtime_error& e)
        {
            std::cerr << e.what() << '\n';
            return 1; //falha de load, impossivel continuar sem um arquivo
        }
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << e.what();
        return 1; //falha de load, impossivel continuar sem um arquivo
    }
    
    std::unique_ptr<ControladorSimulacao> controlador = std::make_unique<ControladorSimulacao>(grid.get(),SEC_PER_CICLO);

    if(gui)
    {
        save->set_max_ciclos(load->get_max_ciclos()); //interface n faz esse tratamento
        interface = std::make_unique<Interface>(controlador.get(), save.get(), load.get(), TAM_CELULA);
    }
    else if(headless)
    {
        if(argc==5)
        {
            arq_stats=argv[4];
        }
        else
        {
            std::cout << "digite o arquivo de stats/save: ";
            std::cin >> arq_stats;
        }

        stats =std::make_unique<Gerenciador_stats>(arq_stats);
        interface_headless = std::make_unique<Interface_headless>(tui,controlador.get(),save.get(),load.get(),stats.get());
    }

    //tui e apenas um estado de interface_headless
    if(gui)
        interface->executar();
    else
        interface_headless->executar();
    
    return 0;
}