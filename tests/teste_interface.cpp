//abre a interface com um grid vazio, para testar o desenho com o mouse
#include "grid.hpp"
#include "interface.hpp"

int main()
{
    Grid grid(40, 30);
    Interface tela(&grid, 20);
    tela.executar();
    return 0;
}
