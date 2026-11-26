#ifndef GERENCIADOR_LOAD_HPP
#define GERENCIADOR_LOAD_HPP

#include "gerenciador_io.hpp"
#include "grid.hpp"

class Gerenciador_load: public Gerenciador_io
{
private:
    
public:

    Gerenciador_load(const std::string &arquivo);

    //throw um invalid_argument se o arquivo nao existir 
    virtual void set_file(const std::string &arquivo) override;
    
    //throw um invalid_argument, um runtime_error ou um cerr
    Grid* load();

    ~Gerenciador_load();
};

#endif