#ifndef GERENCIADOR_ARQUIVO_HPP
#define GERENCIADOR_ARQUIVO_HPP

#include <string>
#include <fstream>
#include "grid.hpp"

class Gerenciador_arquivo
{
private:
    std::string _In_file_name;
    std::string _out_file_name;
    std::string _stats_file_name;
    int _max_ciclos;
    int _max_pop;
    int _maior_familia;
    int _mais_velho;
    
    int *_population_ser_buffer;
    int *_population_plant_buffer;
    int *_population_prey_buffer;
    int *_population_carnivore_buffer;
    std::string **_file_buffer;
    //variaveis auxiliares para o buffer
    int _capacidade_file;
    int _tamanho_file;
    int _capacidade_pop;
    int _tamanho_pop;

    //metodos auxiliares para o buffer, com sobrecargas para diferente manuseio de ponteiros
    void redimencionar_buffer(std::string **&buffer);
    void redimencionar_buffer();
    void limpar_buffer();
    void limpar_buffer(std::string **&buffer);
    void porcentagem_populacional(int populacao, int escala_populacional,char simbolo, std::ofstream& o_file);

public:
    Gerenciador_arquivo(std::string &arquivo);

    //throw um invalid_argument se o arquivo nao existir 
    void set_file(const std::string &arquivo);
    std::string get_file() const;

    void set_save(const std::string &save);
    std::string get_save() const;

    void set_stats(const std::string &stats);
    std::string get_stats() const;
    
    int get_max_ciclos() const;
    int get_max_pop() const;

    //throw um invalid_argument, um runtime_error ou um cerr
    Grid* load();

    //throw um invalid_argument ou um runtime_error
    void save(Grid& grid);
    //sobrecarga em caso de ciclo n salvo no grid
    //throw um invalid_argument, um runtime_error
    void save(Grid& grid, int ciclo_atual);

    //define a escala de atualizacoes dos dados
    //throw um invalid_argument, um runtime_error
    void end_stats(int escala_populacional,int escala_temporal);
    //atualizar esse metodo em conjunto a simulacao, para que ele possa registrar os dados 
    void stats_update(Grid& grid);

    ~Gerenciador_arquivo();
};
#endif