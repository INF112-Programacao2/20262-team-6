#include "gerenciador_stats.hpp"
#include "ser.hpp"

#include <algorithm>
#include <cmath>
#include <fstream>

Gerenciador_stats::Gerenciador_stats(const std::string &arquivo): Gerenciador_de_arquivos(arquivo),_max_pop(0),_maior_familia(0),_mais_velho(0)
{
    //sobrescreve o default para a quantidade de ciclos
    this->_capacidade = this->_max_ciclos;

    //inicia o vetor de dados populacionais para a quantidade inicial de ciclos
    this->_population_plant_buffer=new int[this->_capacidade]();
    this->_population_prey_buffer=new int[this->_capacidade]();
    this->_population_carnivore_buffer=new int[this->_capacidade]();
    this->_population_ser_buffer=new int[this->_capacidade]();
}

void Gerenciador_stats::limpar_buffer()
{
    //deleta os buffers e reseta seus parametros
    delete[] this->_population_plant_buffer;
    delete[] this->_population_prey_buffer;
    delete[] this->_population_carnivore_buffer;
    delete[] this->_population_ser_buffer;

    this->_population_plant_buffer=this->_population_prey_buffer=this->_population_carnivore_buffer=this->_population_ser_buffer=nullptr;
    this->_capacidade=this->_tamanho=0;
}

void Gerenciador_stats::redimencionar_buffer()
{   
    //duplica a capacidade do buffer, copiando o anterior para o novo ponteiro e deletando o antigo
    this->_capacidade= std::max(100, this->_capacidade * 2);

    int*novo_buffer_plant = new int [this->_capacidade]();
    int*novo_buffer_prey = new int [this->_capacidade]();
    int*novo_buffer_carnivore = new int [this->_capacidade]();
    int*novo_buffer_ser = new int [this->_capacidade]();

    for (int i=0;i<this->_tamanho;i++){
        novo_buffer_plant[i] = this->_population_plant_buffer[i];
        novo_buffer_prey[i] = this->_population_prey_buffer[i];
        novo_buffer_carnivore[i] = this->_population_carnivore_buffer[i];
        novo_buffer_ser[i] = this->_population_ser_buffer[i];
    }

    delete[] this->_population_plant_buffer;
    delete[] this->_population_prey_buffer;
    delete[] this->_population_carnivore_buffer;
    delete[] this->_population_ser_buffer;

    this->_population_plant_buffer=novo_buffer_plant;
    this->_population_prey_buffer=novo_buffer_prey;
    this->_population_carnivore_buffer=novo_buffer_carnivore;
    this->_population_ser_buffer=novo_buffer_ser;
}

void Gerenciador_stats::porcentagem_populacional(int populacao, int escala_populacional,char simbolo, std::ofstream& o_file)
{
    if (this->_max_pop == 0) 
        return;

    double proporcao = ((double)(populacao) * escala_populacional) / this->_max_pop;
    int qtd_chars = std::min(escala_populacional, (int)(std::ceil(proporcao)));

    o_file << std::string(qtd_chars, simbolo);
}

void Gerenciador_stats::end_stats(int escala_populacional,int escala_temporal)
{
    //verifica se o user ja setou um arquivo de saida
    if(this->_file_name.empty())
        throw std::invalid_argument("ainda nao foi definido um arquivo de saida\n");
    
    if(escala_populacional<=0)
        throw std::invalid_argument("escala populacional deve ser maior que 0\n");
    if(escala_temporal<=0||escala_temporal>this->_max_ciclos)
    {
        std::string error = "escala temporal deve estar no intervalo: 0<x<=" + std::to_string(this->_max_ciclos); 
        throw std::invalid_argument(error + "\n");
    }
    
    std::ofstream stats_log(this->_file_name);
    if(!stats_log.is_open())
    {
        throw std::runtime_error("nao foi possivel abrir o arquivo " + this->_file_name + "\n");
    }
    
    stats_log << "GRAFICO POPULACAO x TEMPO\n";
    stats_log << "legenda:\n";
    stats_log << "* : ser\n";
    stats_log << "P : planta\n";
    stats_log << "H : herbivoro\n";
    stats_log << "C : carnivoro\n";

    //variaveis auxiliares para nao efetuar operacoes repetidas no loop
    char c_aux[5]="*PHC";
    int *Pop_aux[4] = {
        this->_population_ser_buffer,
        this->_population_plant_buffer,
        this->_population_prey_buffer,
        this->_population_carnivore_buffer
    };

    for (int i = 0; i < _tamanho; i+=escala_temporal)
    {
        stats_log<< "C: "<< i << " |";
        for (int j = 0; j < 4; j++)
        {
            porcentagem_populacional(Pop_aux[j][i],escala_populacional,c_aux[j],stats_log);
        }
        stats_log << "\n";
    }
    stats_log << "Recordes: \n";
    stats_log << "-Populacao maxima simultanea: " << this->_max_pop << " celulas\n";
    stats_log << "-Maior familia: " << this->_maior_familia << " celulas filhas\n";
    stats_log << "-Celula mais velha: Sobreviveu " << this->_mais_velho<< " ciclos\n";
    stats_log.close();
}

void Gerenciador_stats::stats_update(Grid& grid)
{
    int seres=0,plantas=0,carnivoros=0,herbivoros=0;
    if (this->_tamanho >= this->_capacidade) {
        this->redimencionar_buffer();
    }
    for (int i = 0; i < grid.get_altura(); i++)
    {
        for (int j = 0; j < grid.get_largura(); j++)
        {
            Celula *cell = grid.get_celula(j,i);
            //evitar invocar metodos em um objeto inexistente
            if(cell != nullptr)
            {   

                if(cell->get_tipo()==0){
                    seres++;
                }
                else if(cell->get_tipo()==1){
                    plantas++;
                }
                else if(cell->get_tipo()==2)
                    continue; //tipo parede, nao ha nada a ser feito
                else if(cell->get_tipo()==3){
                    carnivoros++;
                }
                else if(cell->get_tipo()==4){
                    herbivoros++;
                }
                else 
                {
                    continue;
                }

                //usado para atributos de seres vivos
                Ser* ser = static_cast<Ser*>(cell);

                this->_maior_familia=std::max(ser->get_qtd_filhos(),
                this->_maior_familia);

                this->_mais_velho=std::max(ser->get_idade(),
                this->_mais_velho);
            }
        }
        
    }
    
    int pop= seres + plantas + herbivoros + carnivoros;
    this->_max_pop=std::max(pop,this->_max_pop);

    this->_population_plant_buffer[this->_tamanho]=plantas;
    this->_population_prey_buffer[this->_tamanho]=herbivoros;
    this->_population_carnivore_buffer[this->_tamanho]=carnivoros;
    this->_population_ser_buffer[this->_tamanho]=seres;
    this->_tamanho++;
}

Gerenciador_stats::~Gerenciador_stats()
{
    limpar_buffer();
}