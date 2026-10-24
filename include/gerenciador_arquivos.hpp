#ifndef GERENCIADOR_ARQUIVO_HPP
#define GERENCIADOR_ARQUIVO_HPP

#include <string>
#include "grid.hpp"

class Gerenciador_arquivo
{
private:
    std::string _In_file_name;
    std::string _out_file_name;
public:
    Gerenciador_arquivo(std::string &arquivo);

    bool set_file(std::string &arquivo);
    std::string get_file() const;

    bool set_save(std::string &save);
    std::string get_save() const;
    
    bool load(Grid& grid);
    bool load_save(Grid& grid);

    bool save(const Grid& grid);
    bool end_stats(const Grid& grid);

    ~Gerenciador_arquivo();
};
#endif