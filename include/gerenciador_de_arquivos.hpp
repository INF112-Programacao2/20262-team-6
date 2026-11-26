#ifndef GERENCIADOR_DE_ARQUIVO_HPP
#define GERENCIADOR_DE_ARQUIVO_HPP

#include <string>

class Gerenciador_de_arquivos
{
protected:
    std::string _file_name;

    //variaveis auxiliares para o buffer
    int _capacidade;
    int _tamanho;
    
    //metodos auxiliares para os buffers
    virtual void redimencionar_buffer() = 0;
    virtual void limpar_buffer() = 0;

    int _max_ciclos;
public:
    Gerenciador_de_arquivos(const std::string &arquivo);

    virtual void set_file(const std::string &arquivo);
    std::string get_file() const;

    int get_max_ciclos() const;
    void set_max_ciclos(int ciclos);

    virtual ~Gerenciador_de_arquivos();
};
#endif