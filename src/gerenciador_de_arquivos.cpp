#include "gerenciador_de_arquivos.hpp"

Gerenciador_de_arquivos::Gerenciador_de_arquivos(const std::string &arquivo): _file_name(arquivo), _capacidade(0), _tamanho(0) {}

void Gerenciador_de_arquivos::set_file(const std::string &arquivo)
{
    this->_file_name = arquivo;
}

std::string Gerenciador_de_arquivos::get_file() const
{
    return this->_file_name;
}

Gerenciador_de_arquivos::~Gerenciador_de_arquivos(){}