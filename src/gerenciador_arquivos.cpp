#include <string>
#include <fstream>
#include "gerenciador_arquivos.hpp"
#include <filesystem>
#include <stdexcept>

Gerenciador_arquivo::Gerenciador_arquivo(std::string &arquivo):_In_file_name(arquivo),_out_file_name(""),\
    _capacidade(10),_tamanho(0){
    //inicia o vetor com tamanho 10, propenso a aumento posteriormente
    this->_file_buffer= new std::string* [_capacidade]();
}

void Gerenciador_arquivo::redimencionar_buffer()
{   
    //duplica a capacidade do buffer, copiando o anterior para o novo ponteiro e deletando o antigo
    this->_capacidade*=2;
    std::string **novo_buffer = new std::string* [this->_capacidade]();
    for (int i=0;i<this->_tamanho;i++)
        novo_buffer[i]=this->_file_buffer[i];
    delete[] this->_file_buffer;
    this->_file_buffer=novo_buffer;
}

void Gerenciador_arquivo::set_file(const std::string &arquivo)
{
    if (!std::filesystem::exists(arquivo)) {
        // faz o throw se o arquivo de input n existe
        throw std::invalid_argument("Arquivo nao encontrado");
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

void Gerenciador_arquivo::load(Grid& grid)
{
    
}