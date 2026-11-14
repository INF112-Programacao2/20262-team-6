/*
Thiago Luis de Arruda Rodrigues
to do: terminar metodos nao implementados
       introduzir _populacao_maxima aos dados
       adicionar atributos estastiscos _maior_familia e _mais_velho
*/
#include <string>
#include <fstream>
#include "gerenciador_arquivos.hpp"
#include "celula.hpp"
#include "grid.hpp"
#include <filesystem>
#include <stdexcept>
#include <algorithm>
#include <iostream>

Gerenciador_arquivo::Gerenciador_arquivo(std::string &arquivo):_In_file_name(arquivo),_out_file_name(""),\
    _max_ciclos(100),_capacidade_file(10),_tamanho_file(0),_capacidade_pop(100),_tamanho_pop(0){

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

void Gerenciador_arquivo::limpar_buffer(std::string **&buffer)
{
    for (int i=0;i<this->_tamanho_file;i++)
        delete buffer[i];
    delete[] buffer;
    buffer=nullptr;
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

int Gerenciador_arquivo::get_max_ciclos() const
{
    return this->_max_ciclos;
}

Grid* Gerenciador_arquivo::load()
{
    //verifica se o user ja setou um arquivo de entrada
    if(this->_In_file_name.empty())
        throw std::invalid_argument("ainda nao foi definido um arquivo de entrada\n");

    //inicio do procedimeento de load em arquivo
    //cria o stream e verifica se foi aberto
    std::ifstream arquivo(this->_In_file_name);
    if(!arquivo.is_open())
    {
        throw std::runtime_error("nao foi possivel abrir o arquivo " + this->_In_file_name + "\n verifique que o arquivo exista\n");
    }

    //limpa possiveis buffers residuais
    limpar_buffer(this->_file_buffer);
    this->_max_ciclos = 100;

    int largura=0;
    bool cabecalho_verificado = false;
    std::string marcador = "C:";

    //le as linhas do arquivo e grava no buffer
    for(std::string linha; std::getline(arquivo,linha);)
    {
        //tratamento para windows
        if (!linha.empty() && linha.back() == '\r') 
        {
            linha.pop_back();
        }
        if (linha.empty()) {
            continue;
        }

        //verifica dados nao posicionais(como quantidade de ciclos desejado)
        if (!cabecalho_verificado) {
            cabecalho_verificado = true;

            if (linha.rfind(marcador, 0) == 0) {
                std::string error("numero de ciclos invalido. assumindo 100.\n");
                try {
                    int valor = std::stoi(linha.substr(marcador.size()));
                    if (valor > 0) {
                        this->_max_ciclos = valor;
                    } else {
                        std::cerr << error;
                    }
                } catch (const std::exception&) {
                    std::cerr << error;
                }
                continue; // descarta a linha de cabecalho para nao entrar no grid
            }
        }

        //verifica se o buffer n esta cheio
        if (this->_tamanho_file >= this->_capacidade_file) {
            this->redimencionar_buffer(this->_file_buffer);
        }
        this->_file_buffer[this->_tamanho_file]= new std::string(linha);
        largura = std::max(largura,(int)linha.size());
        this->_tamanho_file++;
    }

    arquivo.close(); 


    //tratamento de mapas nao retangulares
    if (this->_tamanho_file == 0) {
        throw std::runtime_error("arquivo de entrada vazio ou corrompido\n");
    }
    Grid* novo_grid = new Grid(largura, this->_tamanho_file);
    for (int i = 0; i < this->_tamanho_file; i++)
    {
        //tratamento de linhas mal formatadas
        this->_file_buffer[i]->resize(largura, ' ');
        for (int j = 0; j < largura; j++)
        {
            switch((*this->_file_buffer[i])[j])
            {
                case ' ':
                    break;
                case '*':
                    novo_grid->set_celula(0,j,i);
                    break;
                case 'P':
                    novo_grid->set_celula(1,j,i);
                    break;
                case '#':
                    novo_grid->set_celula(2,j,i);
                    break;
                case 'C':
                    novo_grid->set_celula(3,j,i);
                    break;
                case 'H':
                    novo_grid->set_celula(4,j,i);
                    break;
                default:
                    std::cerr << "caracter de celula '" << (*this->_file_buffer[i])[j] << "' em (" <<
                    j << "," <<i << "), assumindo celula vazia ' '\n";
                    break;
            }
        }
    }

    //economia de memoria
    limpar_buffer(this->_file_buffer);

    return novo_grid;
}

void Gerenciador_arquivo::save(Grid& grid, int ciclo_atual)
{
    //verifica se o user ja setou um arquivo de saida
    if(this->_out_file_name.empty())
        throw std::invalid_argument("ainda nao foi definido um arquivo de saida\n");
    
    //limpa possiveis buffers residuais
    limpar_buffer(this->_file_buffer);

    // garante que ciclos restantes nunca seja gravado como negativo
    int ciclos_restantes = std::max(0, this->_max_ciclos - ciclo_atual);

    for (int i = 0; i < grid.get_altura(); i++)
    {
        //verifica se o buffer n esta cheio
        if (this->_tamanho_file >= this->_capacidade_file) {
            this->redimencionar_buffer(this->_file_buffer);
        }
        this->_file_buffer[this->_tamanho_file]= new std::string();
        for (int j = 0; j < grid.get_largura(); j++)
        {
            std::string cell_buffer = " ";
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
        this->_tamanho_file++; //vai para uma linha nova
    }
    
    //inicio do procedimeento de save em arquivo
    //cria o stream e verifica se foi aberto
    std::ofstream arquivo_save(this->_out_file_name);
    if(!arquivo_save.is_open())
    {
        throw std::runtime_error("nao foi possivel abrir o arquivo " + this->_out_file_name + "\n");
    }

    // grava o cabecalho de ciclos restantes no topo do arquivo
    arquivo_save << "C:" << ciclos_restantes << "\n";

    for (int i = 0; i < this->_tamanho_file; i++) {
        arquivo_save << *this->_file_buffer[i];
    }
    arquivo_save.close();
    
    //economia de memoria
    limpar_buffer(this->_file_buffer);
}

void Gerenciador_arquivo::save(Grid& grid)
{
    save(grid,grid.get_ciclos());
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