//abre a interface com um grid vazio, para testar o desenho com o mouse e os botoes
//executar a partir da raiz do projeto, para a fonte em msc/ ser encontrada
#include "grid.hpp"
#include "controlador_simulacao.hpp"
#include "gerenciador_save.hpp"
#include "gerenciador_load.hpp"
#include "interface.hpp"
#include <filesystem>
#include <string>

int main()
{
    Grid grid(40, 30);

    //comeca pausado, para dar tempo de desenhar antes de simular
    ControladorSimulacao controlador(&grid, 0.2f);
    controlador.pausar();

    //salvar e carregar usam o mesmo arquivo
    std::string arquivo = "build/ecossistema.txt";
    std::filesystem::create_directories("build");
    Gerenciador_save gerenciador_save(arquivo);

    //o Gerenciador_load da throw se o arquivo nao existir,
    //entao na primeira vez o grid vazio e salvo para criar o arquivo
    if (!std::filesystem::exists(arquivo))
        gerenciador_save.save(grid);
    Gerenciador_load gerenciador_load(arquivo);

    Interface tela(&controlador, &gerenciador_save, &gerenciador_load, 20);
    tela.executar();
    return 0;
}
