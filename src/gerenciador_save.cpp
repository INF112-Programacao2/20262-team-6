#include "gerenciador_save.hpp"
#include <stdexcept>
#include <fstream>
#include <algorithm>

Gerenciador_save::Gerenciador_save(const std::string &arquivo): Gerenciador_io(arquivo) {}

void Gerenciador_save::save(Grid& grid, int ciclo_atual)
{
    //verifica se o user ja setou um arquivo de saida
    if(this->_file_name.empty())
        throw std::invalid_argument("ainda nao foi definido um arquivo de saida\n");
    
    //limpa possiveis buffers residuais
    limpar_buffer();

    // garante que ciclos restantes nunca seja gravado como negativo
    int ciclos_restantes = std::max(0, this->_max_ciclos - ciclo_atual);

    for (int i = 0; i < grid.get_altura(); i++)
    {
        //verifica se o buffer n esta cheio
        if (this->_tamanho >= this->_capacidade) {
            this->redimencionar_buffer();
        }
        this->_file_buffer[this->_tamanho]= new std::string();
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
            *this->_file_buffer[this->_tamanho]+=cell_buffer;
        }
        *this->_file_buffer[this->_tamanho]+="\n";
        this->_tamanho++; //vai para uma linha nova
    }
    
    //inicio do procedimeento de save em arquivo
    //cria o stream e verifica se foi aberto
    std::ofstream arquivo_save(this->_file_name);
    if(!arquivo_save.is_open())
    {
        throw std::runtime_error("nao foi possivel abrir o arquivo " + this->_file_name + "\n");
    }

    // grava o cabecalho de ciclos restantes no topo do arquivo
    arquivo_save << "C:" << ciclos_restantes << "\n";

    for (int i = 0; i < this->_tamanho; i++) {
        arquivo_save << *this->_file_buffer[i];
    }
    arquivo_save.close();
    
    //economia de memoria
    limpar_buffer();
}

void Gerenciador_save::save(Grid& grid)
{
    save(grid,grid.get_ciclos());
}

Gerenciador_save::~Gerenciador_save(){/*ja invoca o destruidor abstrato*/}