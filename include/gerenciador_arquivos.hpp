#ifndef GERENCIADOR_ARQUIVO_HPP
#define GERENCIADOR_ARQUIVO_HPP

#include <string>
#include "grid.hpp"

class Gerenciador_arquivo
{
private:
    std::string _In_file_name;
    std::string _out_file_name;
    std::string **_file_buffer;
    //variaveis e metodos auxiliares para o buffer
    int _capacidade;
    int _tamanho;

    void redimencionar_buffer();
    void limpar_buffer();

public:
    Gerenciador_arquivo(std::string &arquivo);

    //funcoes boleanas dão throw, que devem ser capturados e tratados extenamente
    void set_file(const std::string &arquivo);
    std::string get_file() const;

    void set_save(const std::string &save);
    std::string get_save() const;
    
    void load(Grid& grid);
    /* metodo possivelmente obsoleto
    void load_save(Grid& grid);
    */
    void save(const Grid& grid);
    void end_stats(const Grid& grid);
    //atualizar esse metodo em conjunto a simulacao, para que ele possa registrar os dados 
    void stats_update(const Grid& grid);

    ~Gerenciador_arquivo();
};
#endif