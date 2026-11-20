#include "gerenciador_load.hpp"

#include <filesystem>
#include <stdexcept>
#include <fstream>
#include <iostream>

Gerenciador_load::Gerenciador_load(const std::string &arquivo): Gerenciador_io(arquivo){}

void Gerenciador_load::set_file(const std::string &arquivo)
{
    if (!std::filesystem::exists(arquivo)) {
        // faz o throw se o arquivo de input n existe
        std::string error = "Arquivo " + arquivo + " nao encontrado ou nao existe\n";
        throw std::invalid_argument(error);
    }
    Gerenciador_de_arquivos::set_file(arquivo);
}

Grid* Gerenciador_load::load()
{
    //verifica se o user ja setou um arquivo de entrada
    if(this->_file_name.empty())
        throw std::invalid_argument("ainda nao foi definido um arquivo de entrada\n");

    //inicio do procedimeento de load em arquivo
    //cria o stream e verifica se foi aberto
    std::ifstream arquivo(this->_file_name);
    if(!arquivo.is_open())
    {
        throw std::runtime_error("nao foi possivel abrir o arquivo " + this->_file_name + "\n verifique que o arquivo exista\n");
    }

    //limpa possiveis buffers residuais
    limpar_buffer();
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
        if (this->_tamanho >= this->_capacidade) {
            this->redimencionar_buffer();
        }
        this->_file_buffer[this->_tamanho]= new std::string(linha);
        largura = std::max(largura,(int)linha.size());
        this->_tamanho++;
    }

    arquivo.close(); 


    //tratamento de mapas nao retangulares
    if (this->_tamanho == 0) {
        throw std::runtime_error("arquivo de entrada vazio ou corrompido\n");
    }
    Grid* novo_grid = new Grid(largura, this->_tamanho);
    for (int i = 0; i < this->_tamanho; i++)
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
    limpar_buffer();

    return novo_grid;
}

Gerenciador_load::~Gerenciador_load(){/*ja chama o destrutor generico*/}