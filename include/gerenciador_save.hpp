#ifndef GERENCIADOR_SAVE_HPP
#define GERENCIADOR_SAVE_HPP

#include "gerenciador_io.hpp"
#include "grid.hpp"

class Gerenciador_save: public Gerenciador_io
{
private:
    
public:
    Gerenciador_save(const std::string &arquivo);

    //throw um invalid_argument ou um runtime_error
    void save(Grid& grid);
    //sobrecarga em caso de ciclo n salvo no grid
    //throw um invalid_argument, um runtime_error
    void save(Grid& grid, int ciclo_atual);

    ~Gerenciador_save();
};



#endif