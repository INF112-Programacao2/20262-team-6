#ifndef GERENCIADOR_STATS_HPP
#define GERENCIADOR_STATS_HPP

#include "gerenciador_de_arquivos.hpp"
#include "grid.hpp"

class Gerenciador_stats: public Gerenciador_de_arquivos
{
private:
    int _max_pop;
    int _maior_familia;
    int _mais_velho;
    
    int *_population_ser_buffer;
    int *_population_plant_buffer;
    int *_population_prey_buffer;
    int *_population_carnivore_buffer;

    void porcentagem_populacional(int populacao, int escala_populacional,char simbolo, std::ofstream& o_file);  

    virtual void redimencionar_buffer() override;
    virtual void limpar_buffer() override;

public:
    Gerenciador_stats(const std::string &arquivo);

    //define a escala de atualizacoes dos dados
    //throw um invalid_argument, um runtime_error
    void end_stats(int escala_populacional,int escala_temporal);
    //atualizar esse metodo em conjunto a simulacao, para que ele possa registrar os dados 
    void stats_update(Grid& grid);

    ~Gerenciador_stats();
};

#endif