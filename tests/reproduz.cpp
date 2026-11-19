//codigo exemplo para nova rotina de reproducao das celulas
#include "celula.hpp"
#include "posicao.hpp"

class Ser : public Celula
{
protected:
    bool _quer_reproduzir=false;
    Posicao _posi_filho;
public:
    bool reproduzir()
    {
        if(this->_quer_reproduzir){
            //evita reproducao continua
            this->_quer_reproduzir=false;
            //se quiser, podemos mover o consumo de energia para ca
            //retorna que ela quer ter um filho
            return true;
        }
        return false;
    }
    //usar essa no controle de simulacao apenas se o reproduzir()=true
    Posicao get_posi_filho() const
    {
        //declarar essa posicao usando o local que a celula escolheu no subgrid
        /*n esquecer de converter as coordenadas do subgrid para as do grid, 
        como celula ja tem sua posicao relativa no grid completo, vc pode fazer isso no atualizar() mesmo*/
        return this->_posi_filho;
    }
};