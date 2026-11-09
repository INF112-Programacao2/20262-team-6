#ifndef CONTROLADOR_SIMULACAO_HPP
#define CONTROLADOR_SIMULACAO_HPP

class Grid;

class ControladorSimulacao
{
private:
    //nao e dono do grid, entao nao deleta ele no destrutor
    Grid *_grid;
    bool _pausado;
    float _segundos_por_ciclo;
    float _tempo_acumulado;

public:
    ControladorSimulacao(Grid *grid, float segundos_por_ciclo);
    void atualizar(float tempo);

    void avancar_ciclo();
    void avancar_ciclos(int qtd);

    void pausar();
    void retomar();
    void alternar_pausa();
    bool is_pausado() const;

    void set_segundos_por_ciclo(float segundos);
    float get_segundos_por_ciclo() const;

    Grid *get_grid() const;

    ~ControladorSimulacao();
};
#endif
