#include "gerenciador_io.hpp"
#include <algorithm>

Gerenciador_io::Gerenciador_io(const std::string &arquivo): Gerenciador_de_arquivos(arquivo), _file_buffer(nullptr)
{
    //inicia o vetor com tamanho 10, propenso a aumento posteriormente
    this->_file_buffer= new std::string* [this->_capacidade]();
}

void Gerenciador_io::limpar_buffer()
{
    //deleta os buffers e reseta seus parametros
    for (int i=0;i<this->_tamanho;i++)
        delete this->_file_buffer[i];
    delete[] this->_file_buffer;

    this->_file_buffer=nullptr;
    this->_capacidade=this->_tamanho=0;
}

void Gerenciador_io::redimencionar_buffer()
{   
    //duplica a capacidade do buffer, copiando o anterior para o novo ponteiro e deletando o antigo
    //se o buffer foi apagado, volta para tamanho 10
    this->_capacidade = std::max(10, this->_capacidade * 2);

    std::string **novo_buffer = new std::string* [this->_capacidade]();

    for (int i=0;i<this->_tamanho;i++)
        novo_buffer[i]=this->_file_buffer[i];
    delete[] this->_file_buffer;

    this->_file_buffer=novo_buffer;
}

Gerenciador_io::~Gerenciador_io()
{
    limpar_buffer();
}