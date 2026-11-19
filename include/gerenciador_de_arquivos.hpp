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
public:
    Gerenciador_de_arquivos(const std::string &arquivo);

    virtual void set_file(const std::string &arquivo);
    virtual std::string get_file() const;

    virtual ~Gerenciador_de_arquivos();
};
#endif