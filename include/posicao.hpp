#ifndef POSICAO_HPP
#define POSICAO_HPP
class Posicao
{
private:
    int _x,_y;
public:
    Posicao(int x, int y);
    void set_x(int x);
    void set_y(int y);
    void set_position(int x, int y);
    int get_x();
    int get_y();
    ~Posicao();
};
#endif