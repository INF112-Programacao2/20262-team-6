#include "controlador_simulacao.hpp"
#include "grid.hpp"
#include "interface.hpp"
#include "interface_headless.hpp"
#include "gerenciador_load.hpp"
#include "gerenciador_save.hpp"
#include "gerenciador_stats.hpp"
#include "interface.hpp"

#include <cstring>
#include <stdexcept>
#include <iostream>

//possivelmente passar pelos argumentos da main
const int TAM_CELULA=50;
const float SEC_PER_CICLO = 0.5;

// funcao recursiva de tratamento de excecao
Gerenciador_load* recLoadInvalido(Gerenciador_load* fail)
{
    delete fail;
    fail = nullptr; // garante que nao havera double free se o new falhar na proxima tentativa

    std::string arq_load;
    std::cout << "digite o arquivo de entrada/load: ";
    if (!(std::cin >> arq_load)) // evita recursao infinita em caso de EOF (ctrl d)
        throw std::runtime_error("entrada encerrada sem arquivo valido\n");
    try
    {
        fail = new Gerenciador_load(arq_load);
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << e.what() << '\n';
        fail = recLoadInvalido(fail);
    }
    return fail;
}

Grid* recGridInvalido(Grid* fail, Gerenciador_load* load)
{
    delete fail;
    fail = nullptr; // garante que nao havera double free se o new falhar na proxima tentativa

    std::string arq_load;
    std::cout << "digite o arquivo de entrada/load: ";
    if (!(std::cin >> arq_load)) // evita recursao infinita em caso de EOF (ctrl d)
        throw std::runtime_error("entrada encerrada sem arquivo valido\n");
    try
    {
        fail = load->load();
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << e.what() << '\n';
        fail = load->load();
    }
    return fail;
}

int main(int argc, char* argv[])
{
    try //trata para ver se os argumentos foram corretamente usados
    {
        if(argc!=2)
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
        if(std::strcmp(argv[1],"gui"))
            gui=true;
        else if(std::strcmp(argv[1],"headless"))
            headless=true;
        else 
            throw std::invalid_argument("uso: ./<bin> <modo> ex: headless e gui\n");
    }
    catch(const std::invalid_argument &e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    //instanciacao de acordo com o modo
    Interface *interface = nullptr; // trocar pra InterfaceIF se tiver polimorfismo
    Interface_headless *interface_headless = nullptr;
    Gerenciador_load *load = nullptr;
    Gerenciador_stats *stats = nullptr;
    Gerenciador_save *save = nullptr;

    std::string arq_save, arq_load, arq_stats;
    //save e load sempre sao instanciados
    //tenta ler arquivos usando os argumnentos da main
    if(argc==4)
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
        load = recLoadInvalido(load);
    }
    catch(const std::runtime_error& e)
    {
    
        std::cerr << e.what() << '\n';
        return 1; //o sistema n funciona sem um arquivo
    
    }
    //instancia depois para evitar um new desnecesario
    save = new Gerenciador_save(arq_save);
    Grid *grid = nullptr;
    try
    {
        grid = load->load();
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what();
        //arquivo vazio, excreva dnv
        try
        {
            grid = recGridInvalido(grid,load);
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
    
    ControladorSimulacao *controlador = new ControladorSimulacao(grid,SEC_PER_CICLO);

    if(gui)
    {
        interface = new Interface(controlador, save, load, TAM_CELULA);
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

        stats = new Gerenciador_stats(arq_stats);
        interface_headless = new Interface_headless(tui,controlador,save,load,stats);
    }

    if(gui)
        interface->executar();
    else
        interface_headless->executar();
    
    delete interface;
    delete interface_headless;
    delete stats;
    delete save;
    delete load;
    delete controlador;
    delete grid;
    
    return 0;
}