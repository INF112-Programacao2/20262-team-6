#ifndef INTERFACEIF_HPP
#define INTERFACEIF_HPP

/*sobe metodos comuns dos dois meios de funcionamento do sistema*/
class InterfaceIF
{
public:
    virtual void executar() = 0;

    virtual ~InterfaceIF() = default;
};

#endif