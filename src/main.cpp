#include "controlador_simulacao.hpp"
#include "gerenciador_arquivos.hpp"
#include "interface.hpp"
#include <cstring>
#include <stdexcept>

//possivelmente passar pelos argumentos da main
const int TAM_CELULA=50;

int main(int argc, char* argv[])
{
    bool headless =false;
    bool gui=false;
    try{
        if(std::strcmp(argv[1],"gui"))
            gui=true;
        else if(std::strcmp(argv[1],"headless"))
            headless=true;
        else 
            throw std::invalid_argument("uso: ./<bin> <modo> ex: headless e gui\n");
    }
    catch(const std::invalid_argument &e)
    {

    }
    return 0;
}