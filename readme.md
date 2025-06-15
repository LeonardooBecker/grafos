# Analisador de Grafos em C

## 1. Visão Geral

Este projeto consiste em uma biblioteca de software, desenvolvida em linguagem C, para a modelagem e análise estrutural de grafos não-direcionados. O programa é capaz de processar uma representação de um grafo, extrair um conjunto de propriedades fundamentais e apresentar os resultados de forma textual.

## 2. Funcionalidades

A análise executada sobre o grafo de entrada permite a extração das seguintes métricas e propriedades:
* Quantidade total de vértices e arestas.
* Número de componentes conexas.
* Verificação de bipartição do grafo.
* Identificação de todos os vértices de corte (pontos de articulação).
* Identificação de todas as arestas de corte (pontes).
* Cálculo do diâmetro de cada componente conexa.

## 3. Arquitetura e Módulos

O sistema é organizado em módulos com responsabilidades bem definidas, a fim de promover a manutenibilidade e a clareza do código-fonte:

* **`estrutura_grafo.h`**: Arquivo de cabeçalho que define as estruturas de dados primárias do projeto: `struct grafo`, `struct vertice` e `struct vizinho`.
* **`grafo.c`**: Coordena o fluxo de execução, desde a leitura do grafo até a apresentação dos resultados e a liberação de memória.
* **`dfs.c`**: Contém a implementação da Busca em Profundidade (Depth-First Search) e os algoritmos derivados para análise estrutural.
* **`dijkstra.c`**: Implementa o algoritmo de Dijkstra para o cálculo de caminhos mínimos e a função para determinação de diâmetros.
* **`fila.c`**: Provê uma estrutura de dados de fila com funcionalidade de prioridade, essencial para a execução de algoritmos de otimização como o de Dijkstra.

## 4. Algoritmos Implementados e Suas Finalidades

A extração das propriedades do grafo é realizada através de algoritmos específicos, encapsulados em funções auxiliares.

### 4.1. Busca em Profundidade (DFS)

Uma implementação aprimorada da Busca em Profundidade é utilizada para realizar uma análise estática inicial do grafo. A execução ocorre imediatamente após a leitura dos dados de entrada.

* **Propósito:** Identificar propriedades de conectividade e robustez.
* **Metodologia:** A travessia DFS foi estendida para incorporar os princípios do algoritmo de Tarjan, que se baseia nos tempos de descoberta (`pre`) e nos valores de *low-link* de cada vértice.
    * **Componentes Conexas:** São determinadas pela quantidade de vezes que uma nova busca DFS é iniciada a partir de um vértice ainda não visitado.
    * **Vértices e Arestas de Corte:** São identificados pela análise das relações entre os valores `pre` e `low` na árvore de busca gerada pela DFS.
    * **Bipartição:** É verificada por meio de um algoritmo de 2-coloração executado concorrentemente à travessia. A impossibilidade de atribuir cores distintas a vértices adjacentes invalida a propriedade de bipartição.

### 4.2. Algoritmo de Dijkstra

Este algoritmo é empregado para resolver o problema do caminho mínimo, que é um pré-requisito para análises de distância.

* **Propósito:** Calcular o diâmetro de cada componente conexa do grafo.
* **Metodologia:** O diâmetro de uma componente é definido como a maior excentricidade entre todos os seus vértices. Para computar tal valor, o algoritmo de Dijkstra é executado iterativamente, partindo de cada vértice pertencente à componente. O maior de todos os caminhos mínimos encontrados corresponde ao diâmetro.

### 4.3. Fila de Prioridade

Uma estrutura de dados de fila de prioridade, implementada como uma lista ligada ordenada, serve de suporte para algoritmos de otimização.

* **Propósito:** Gerenciar eficientemente o conjunto de vértices a serem explorados no algoritmo de Dijkstra.
* **Metodologia:** A estrutura mantém os vértices ordenados de acordo com seu custo (distância da origem). A função `enfileira_ordenado` garante a inserção na posição correta, enquanto `corrige_fila` executa a operação de "decrease-key", que é necessária para atualizar a prioridade de um vértice quando um caminho mais curto para ele é descoberto.

## 5. Compilação e Execução

### 5.1. Compilação

O projeto pode ser compilado utilizando um compilador C padrão, como o GCC. Todos os arquivos-fonte `.c` devem ser incluídos no comando.

```bash
gcc -o analisador main.c dfs.c dijkstra.c fila.c [demais_arquivos.c] -Wall -O2
```bash
    make
```

### 5.2. Execução:

```bash
    ./teste < entrada.txt
```

Onde entrada.txt contém a definição do grafo.