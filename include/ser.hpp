#ifndef SER_HPP
#define SER_HPP
#include "celula.hpp"
class Ser : public Celula
{
protected:
    int _energia, _idade, _qtd_filhos;
    const std::string _regras;
    void set_qtd_filhos(int qtd);
    void set_idades(int qtd)
    void set_regras(std::string regras);

public:
    Ser(int x, int y);

    int get_qtd_filhos();
    int get_idade();
    int get_energia();
    virtual void atualizar(Grid *grid);

    ~Ser();
};
#endif