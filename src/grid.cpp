#include "grid.hpp"
#include "celula.hpp"
#include "parede.hpp"
#include "planta.hpp"
#include "carnivoro.hpp"
#include "herbivoro.hpp"

Grid::Grid(int largura,int altura)
{
    _largura = largura;
    _altura = altura;
    _ciclos = 0;
    _seres_vivos = 0;
    //criando a matriz de ponteiros para Celula
    _grid = new Celula**[_largura];

    //para cada linha, cria as colunas e define como nullptr
    for (int i = 0; i < _largura; i++) {
        _grid[i] = new Celula*[_altura];
        for (int j = 0; j < _altura; j++)
            _grid[i][j] = nullptr;
    }
}

void Grid::set_celula(int tipo, int x, int y)
{
    //criando uma nova celula e adicionando na matriz
    Celula *new_celula = nullptr;
    switch (tipo) {
    // case 0:
    //     new_celula = new Ser(x, y);
    //     break;
    case 1:
        new_celula = new Planta(x, y);
        break;
    // case 2:
    //     new_celula = new Parede(x, y);
    //     break;
    // case 3:
    //     new_celula = new Carnivoro(x, y);
    //     break;
    // case 4:
    //     new_celula = new Herbivoro(x, y);
    //     break;
    };

    _grid[x][y] = new_celula;
}

Celula* Grid::get_celula(int x, int y)
{
    //retorna a celula na posicao (x,y)
    return _grid[x][y];
}

bool Grid::is_valid(int x, int y)
{
    //retorna true se a posicao (x,y) está dentro do grid, false caso contrario
    if(x >= 0 && x < _largura && y >= 0 && y < _altura)
    {
        return true;
    }
    return false;
}

//recebe posicao da celula e o raio de visao dela
Grid *Grid::get_grid(Posicao &posicao, int visao)
{
    //cria um novo grid com tamanho (visao*2+1) x (visao*2+1) ainda vazio centrado na posicao dada
    int x = posicao.get_x();
    int y = posicao.get_y();
    Grid *new_grid = new Grid(visao*2+1, visao*2+1);

    //percorre o grid original e adiciona as celulas dentro do raio de visao no novo grid
    for(int i = -visao; i <= visao; i++)
    {
        for(int j = -visao; j <= visao; j++)
        {
            if(is_valid(x+i, y+j)) 
                //adiciona a celula na posicao (x+i,y+j) do grid original na posicao (i+visao,j+visao) do novo grid
                if(_grid[x+i][y+j]!=nullptr)  
                new_grid->set_celula(_grid[x+i][y+j]->get_tipo(), i+visao, j+visao);
            else
                //se a posicao estiver fora do grid...
                new_grid->set_celula(2, i+visao, j+visao);//cria uma parede no local, para nao ser considerado vazio
        }
    }
    return new_grid; //retorna o ponteiro pro sub-grid
    //LEMBRAR DE DESALOCAR APOS O USO!! (atualizar_posicao ja realiza a desalocacao)
}

int Grid::get_seres_vivos()
{
    //percorre o grid e conta o numero de celulas vivas
    int count = 0;
    for(int i = 0; i < _largura; i++)
    {
        for(int j = 0; j < _altura; j++)
        {
            //verifica se a celula existe e se não é uma parede
            //neste caso, plantas estao sendo consideradas como seres vivos
            if(_grid[i][j] != nullptr && _grid[i][j]->get_tipo() != 0 && _grid[i][j]->get_tipo() != 2)
            {
                count++;
            }
        }
    }
    return count;
}

void Grid::passar_ciclo(){
    _ciclos++;
};

void Grid::set_seres_vivos(int qtd){
    _seres_vivos=qtd;
};

void Grid::atualizar_posicao(Posicao &posicao){
    Grid *visao = get_grid(posicao, 1); //criando um sub-grid com raio 1
    _grid[posicao.get_x()][posicao.get_y()]->atualizar(visao);//atualizando a celula 
    delete visao;//deletando o subgrid criado
};

Grid::~Grid() {
    for(int i = 0; i < _largura; i++)
    {
        for(int j = 0; j < _altura; j++)
        {
            //deleta a celula na posicao (i,j) se ela existir
            if(_grid[i][j] != nullptr)
            {
                delete _grid[i][j];
            }
        }
        delete[] _grid[i];
    }
    delete[] _grid;
};
