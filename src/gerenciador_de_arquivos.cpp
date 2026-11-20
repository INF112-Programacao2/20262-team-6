#include "gerenciador_de_arquivos.hpp"

Gerenciador_de_arquivos::Gerenciador_de_arquivos(const std::string &arquivo): _file_name(arquivo), _capacidade(10), _tamanho(0), _max_ciclos(100) {}

void Gerenciador_de_arquivos::set_file(const std::string &arquivo)
{
    this->_file_name = arquivo;
}

std::string Gerenciador_de_arquivos::get_file() const
{
    return this->_file_name;
}

int Gerenciador_de_arquivos::get_max_ciclos() const
{
    return this->_max_ciclos;
}

void Gerenciador_de_arquivos::set_max_ciclos(int max_ciclos)
{
    this->_max_ciclos = max_ciclos;
}

Gerenciador_de_arquivos::~Gerenciador_de_arquivos(){}