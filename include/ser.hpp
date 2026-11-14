#ifndef SER_HPP
#define SER_HPP
#include "celula.hpp"
class Ser : public Celula{
protected:
    int _energia, _idade, _qtd_filhos;
    const std::string _regras;
    //as derivadas marcam true no atualizar() quando querem se reproduzir
    bool _quer_reproduzir;
    //onde o filho deve nascer
    Posicao _posi_filho;
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

    //retorna true uma unica vez quando o ser quer ter um filho
    bool reproduzir();
    Posicao get_posi_filho() const; // caso se reproduza

    ~Ser();
};
#endif