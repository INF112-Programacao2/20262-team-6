#ifndef GERENCIADOR_ARQUIVO_HPP
#define GERENCIADOR_ARQUIVO_HPP

#include <string>
#include "grid.hpp"

class Gerenciador_arquivo
{
private:
    std::string _In_file_name;
    std::string _out_file_name;
    
    int *_population_ser_buffer;
    int *_population_plant_buffer;
    int *_population_prey_buffer;
    int *_population_carnivore_buffer;
    std::string **_file_buffer;
    //variaveis e metodos auxiliares para o buffer
    int _capacidade_file;
    int _tamanho_file;
    int _capacidade_pop;
    int _tamanho_pop;

    void redimencionar_buffer(std::string **&buffer);
    void redimencionar_buffer();
    void limpar_buffer();

public:
    Gerenciador_arquivo(std::string &arquivo);
    //throw um invalid_argument se o arquivo nao existir 
    void set_file(const std::string &arquivo);
    std::string get_file() const;

    void set_save(const std::string &save);
    std::string get_save() const;
    
    Grid* load();
    /* metodo possivelmente obsoleto
    void load_save(Grid& grid);
    */
    void save(Grid& grid);
    //define a escala de atualizacoes dos dados
    void end_stats(Grid& grid,int escala_populacional,int escala_temporal);
    //atualizar esse metodo em conjunto a simulacao, para que ele possa registrar os dados 
    void stats_update(Grid& grid);

    ~Gerenciador_arquivo();
};
#endif