#include <string>
#include <fstream>
#include "gerenciador_arquivos.hpp"
#include "celula.hpp"
#include "grid.hpp"
#include <filesystem>
#include <stdexcept>
#include <algorithm>

Gerenciador_arquivo::Gerenciador_arquivo(std::string &arquivo):_In_file_name(arquivo),_out_file_name(""),\
    _capacidade_file(10),_tamanho_file(0),_capacidade_pop(100),_tamanho_pop(0){

    //inicia o vetor com tamanho 10, propenso a aumento posteriormente
    this->_file_buffer= new std::string* [_capacidade_file]();

    //inicia o vetor de dados populacionais para 100 ciclos
    this->_population_plant_buffer=new int[this->_capacidade_pop]();
    this->_population_prey_buffer=new int[this->_capacidade_pop]();
    this->_population_carnivore_buffer=new int[this->_capacidade_pop]();
    this->_population_ser_buffer=new int[this->_capacidade_pop]();
}

void Gerenciador_arquivo::limpar_buffer()
{
    //deleta os buffers e reseta seus parametros
    delete[] this->_population_plant_buffer;
    delete[] this->_population_prey_buffer;
    delete[] this->_population_carnivore_buffer;
    delete[] this->_population_ser_buffer;

    this->_population_plant_buffer=this->_population_prey_buffer=this->_population_carnivore_buffer=this->_population_ser_buffer=nullptr;
    _capacidade_pop=_tamanho_pop=0;

    for (int i=0;i<this->_tamanho_file;i++)
        delete this->_file_buffer[i];
    delete[] this->_file_buffer;
    this->_file_buffer=nullptr;
    _capacidade_file=_tamanho_file=0;
}

void Gerenciador_arquivo::redimencionar_buffer(std::string **&buffer)
{   
    //duplica a capacidade do buffer, copiando o anterior para o novo ponteiro e deletando o antigo
    //se o buffer foi apagado, volta para tamanho 10
    this->_capacidade_file = std::max(10, this->_capacidade_file * 2);

    std::string **novo_buffer = new std::string* [this->_capacidade_file]();

    for (int i=0;i<this->_tamanho_file;i++)
        novo_buffer[i]=buffer[i];
    delete[] buffer;

    buffer=novo_buffer;
}

void Gerenciador_arquivo::redimencionar_buffer()
{   
    //duplica a capacidade do buffer, copiando o anterior para o novo ponteiro e deletando o antigo
    this->_capacidade_pop = std::max(100, this->_capacidade_pop * 2);

    int*novo_buffer_plant = new int [this->_capacidade_pop]();
    int*novo_buffer_prey = new int [this->_capacidade_pop]();
    int*novo_buffer_carnivore = new int [this->_capacidade_pop]();
    int*novo_buffer_ser = new int [this->_capacidade_pop]();

    for (int i=0;i<this->_tamanho_pop;i++){
        novo_buffer_plant[i] = this->_population_plant_buffer[i];
        novo_buffer_prey[i] = this->_population_prey_buffer[i];
        novo_buffer_carnivore[i] = this->_population_carnivore_buffer[i];
        novo_buffer_ser[i] = this->_population_ser_buffer[i];
    }

    delete[] this->_population_plant_buffer;
    delete[] this->_population_prey_buffer;
    delete[] this->_population_carnivore_buffer;
    delete[] this->_population_ser_buffer;

    this->_population_plant_buffer=novo_buffer_plant;
    this->_population_prey_buffer=novo_buffer_prey;
    this->_population_carnivore_buffer=novo_buffer_carnivore;
    this->_population_ser_buffer=novo_buffer_ser;
}

void Gerenciador_arquivo::set_file(const std::string &arquivo)
{
    if (!std::filesystem::exists(arquivo)) {
        // faz o throw se o arquivo de input n existe
        std::string error = "Arquivo " + arquivo + " nao encontrado ou nao existe\n";
        throw std::invalid_argument(error);
    }
    this->_In_file_name = arquivo;
}

std::string Gerenciador_arquivo::get_file() const
{
    return this->_In_file_name;
}

void Gerenciador_arquivo::set_save(const std::string &arquivo)
{
    this->_out_file_name=arquivo;
}

std::string Gerenciador_arquivo::get_save() const
{
    return this->_out_file_name;
}

Grid* Gerenciador_arquivo::load()
{
    
}

void Gerenciador_arquivo::save(Grid& grid)
{
    if (this->_tamanho_file >= this->_capacidade_file) {
        this->redimencionar_buffer(this->_file_buffer);
    }
    std::string cell_buffer;
    for (int i = 0; i < grid.get_altura(); i++)
    {
        for (int j = 0; j < grid.get_largura(); j++)
        {
            Celula *cell = grid.get_celula(j,i);
            if(cell == nullptr)
                cell_buffer=" ";
            else if(cell->get_tipo()==0)
                cell_buffer="*";
            else if(cell->get_tipo()==1)
                cell_buffer="P";
            else if(cell->get_tipo()==2)
                cell_buffer="#";
            else if(cell->get_tipo()==3)
                cell_buffer="C";
            else if(cell->get_tipo()==4)
                cell_buffer="H";
            *this->_file_buffer[this->_tamanho_file]+=cell_buffer;
        }
        *this->_file_buffer[this->_tamanho_file]+="\n";
        this->_tamanho_file++;
    }
    
}

void Gerenciador_arquivo::stats_update(Grid& grid)
{
    int seres=0,plantas=0,carnivoros=0,herbivoros=0;
    if (this->_tamanho_pop >= this->_capacidade_pop) {
        this->redimencionar_buffer();
    }
    for (int i = 0; i < grid.get_altura(); i++)
    {
        for (int j = 0; j < grid.get_largura(); j++)
        {
            Celula *cell = grid.get_celula(j,i);
            //evitar invocar metodos em um objeto inexistente
            if(cell != nullptr)
            {
                if(cell->get_tipo()==0)
                    seres++;
                else if(cell->get_tipo()==1)
                    plantas++;
                else if(cell->get_tipo()==2)
                    continue; //tipo parede, nao ha nada a ser feito
                else if(cell->get_tipo()==3)
                    carnivoros++;
                else if(cell->get_tipo()==4)
                    herbivoros++;
            }
        }
        
    }
    this->_population_plant_buffer[this->_tamanho_pop]=plantas;
    this->_population_prey_buffer[this->_tamanho_pop]=herbivoros;
    this->_population_carnivore_buffer[this->_tamanho_pop]=carnivoros;
    this->_population_ser_buffer[this->_tamanho_pop]=seres;
    this->_tamanho_pop++;
}

Gerenciador_arquivo::~Gerenciador_arquivo()
{
    limpar_buffer();
}