# Sistema de Simulação de Ecossistema

Sistema de simulação de um ecossistema baseado em **Autômato Celular**, desenvolvido em C++ para a disciplina de **Programação Orientada a Objetos (POO)**.

O código foi inspirado no Jogo da Vida de John Conway (*John Conway's Game of Life*), e permite criar, carregar, editar e simular um ambiente composto por diferentes tipos de células, observando suas interações e evolução ao longo de uma quantidade X de ciclos.

![Exemplo de Simulação do Jogo da Vida de Conway](msc/readmeexample.gif)

## Sobre o Sistema

O ambiente é representado por um *grid*, onde cada posição pode conter uma célula do ecossistema.

Os principais tipos de células são:

- **Planta** — cresce, envelhece e pode ser consumida por herbívoros.
- **Herbívoro** — procura plantas para se alimentar, possui condições de fome e pode se reproduzir.
- **Predador** — procura herbívoros para se alimentar, possui condições de fome e pode se reproduzir.
- **Parede** — funciona como um obstáculo estático e impede a ocupação daquela posição.

A simulação acontece em **ciclos**, nos quais as células atualizam seus estados de acordo com as regras definidas para o ecossistema.

## Funcionalidades

- Carregamento de um ecossistema a partir de arquivo de texto.
- Validação dos caracteres utilizados no arquivo.
- Criação e edição manual do ambiente.
- Inserção de plantas, herbívoros, predadores e paredes.
- Execução da simulação por ciclos.
- Avanço de um ou vários ciclos.
- Pausar e retomar a simulação.
- Visualização do estado atual do ecossistema.
- Exibição de legenda dos elementos.
- Salvamento e carregamento do estado da simulação.
- Execução de vários ciclos sem atualização da interface.

## Objetivo

O projeto tem como objetivo aplicar, em um sistema de simulação, conceitos de:

- Classes e objetos
- Encapsulamento
- Herança
- Polimorfismo
- Relacionamento entre classes
- Gerenciamento de memória
- Manipulação de arquivos
- Organização e modularização de código

## Arquitetura

                         Celula
                            │
          ┌───────────┬─────┴───────┬───────────────┐
          │           │             │               │
       Planta       Parede      Herbivoro       Carnivoro


      Grid              ControladorSimulacao
       ├── Celula       GerenciadorArquivo
       └── Posicao      Gui
       

## Estrutura da simulação

A cada ciclo, o estado do ecossistema é atualizado de acordo com as regras definidas para cada tipo de célula.


## Arquivos de entrada

O ambiente pode ser definido através de um arquivo de texto contendo a representação do grid.

Exemplo:

..........<br>
..H.......<br>
....P.....<br>
......#...<br>
..P....C..<br>
..........


## Tecnologias

- **C++**
- Programação Orientada a Objetos
- Autômato Celular
- Interface gráfica
- Manipulação de arquivos