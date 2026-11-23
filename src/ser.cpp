#include "ser.hpp"
#include "celula.hpp"


Ser::Ser(int x, int y)
    : Celula(x, y), _energia(100), _idade(0),
      _qtd_filhos(0), _regras(""),
      _quer_reproduzir(false), _posi_filho(x, y)
{
}

Ser::~Ser(){
}

void  Ser::set_qtd_filhos(int qtd){
    this->_qtd_filhos = qtd;
}
void Ser::set_idade(int qtd){
    this->_idade = qtd;
}

void Ser::set_energia(int qtd){
    this->_energia = qtd;
}

int  Ser::get_qtd_filhos(){
    return this->_qtd_filhos;
}
int Ser::get_idade(){
    return this->_idade;
}
int Ser::get_energia(){
    return this->_energia;
}
std::string Ser::get_regras(){
    return this->_regras;
}

int Ser::get_tipo() const
{
    return 0; //ser generico
}

void Ser::atualizar(Grid *grid)
{
    this->set_idade(get_idade() + 1);
    this->set_energia(get_energia() - 1);
}

bool Ser::reproduzir()
{
    if(this->_quer_reproduzir){
        //evita reproducao continua
        this->_quer_reproduzir = false;
        return true;
    }
    return false;
}

Posicao Ser::get_posi_filho() const
{
    return this->_posi_filho;
}