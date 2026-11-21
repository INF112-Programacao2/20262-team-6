//abre a interface com um grid vazio, para testar o desenho com o mouse e os botoes
//executar a partir da raiz do projeto, para a fonte em msc/ ser encontrada
#include "grid.hpp"
#include "controlador_simulacao.hpp"
#include "gerenciador_arquivos.hpp"
#include "interface.hpp"
#include <string>

int main()
{
    Grid grid(40, 30);

    //comeca pausado, para dar tempo de desenhar antes de simular
    ControladorSimulacao controlador(&grid, 0.2f);
    controlador.pausar();

    //salvar e carregar usam o mesmo arquivo
    std::string arquivo = "build/ecossistema.txt";
    Gerenciador_arquivo gerenciador(arquivo);
    gerenciador.set_save(arquivo);

    Interface tela(&controlador, &gerenciador, 20);
    tela.executar();
    return 0;
}
