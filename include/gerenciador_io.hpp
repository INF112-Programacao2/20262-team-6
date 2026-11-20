#ifndef GERENCIADOR_IO_HPP
#define GERENCIADOR_IO_HPP

#include "gerenciador_de_arquivos.hpp"

class Gerenciador_io: public Gerenciador_de_arquivos
{
protected:
    std::string **_file_buffer;
    
    //metodos auxiliares para os buffers
    virtual void redimencionar_buffer() override;
    virtual void limpar_buffer() override;

    //nao existe motivo para instanciar essa classe
    Gerenciador_io(const std::string &arquivo);

public:

    virtual ~Gerenciador_io();
};


#endif
