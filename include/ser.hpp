#ifndef SER_HPP
#define SER_HPP
#include "celula.hpp"
class Ser : public Celula
{
protected:
    int _energia, _idade, _qtd_filhos;
    //nao to entendendo o que esse regras vai fazer
    const std::string _regras;
    void set_qtd_filhos(int qtd);
    void set_idade(int qtd);
    void set_energia(int qtd);

public:
    Ser(int x, int y);

    int get_qtd_filhos();
    int get_idade();
    int get_energia();
    std::string get_regras();
    virtual void atualizar(Grid *grid);

    ~Ser();
};
#endif