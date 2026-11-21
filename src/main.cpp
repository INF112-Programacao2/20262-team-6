#include "controlador_simulacao.hpp"
#include "gerenciador_arquivos.hpp"
#include "interface.hpp"
#include <cstring>
#include <stdexcept>
#include <iostream>
#include <memory>

//possivelmente passar pelos argumentos da main
const int TAM_CELULA=50;
const int TAM_MAPA=20;
const float SEG_CIC=20;
const int NUM_CIC=20;

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
    return 0;
}