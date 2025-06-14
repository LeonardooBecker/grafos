# Análise de Grafos - Trabalho Prático

## Objetivo

O programa lê a descrição de um grafo a partir da entrada padrão e realiza uma série de análises, respondendo:

- **Número de componentes conexos** no grafo.
- Se o grafo é **bipartido** ou não.
- Os **diâmetros** de cada componente conexo (maior distância entre dois vértices da mesma componente).
- Quais são os **vértices de corte** (articulação).
- Quais são as **arestas de corte** (pontes).

## Implementação

- Foi implementada uma **DFS (Busca em Profundidade)** para:

  - Identificar o número de componentes.
  - Verificar se o grafo é bipartido.
  - Encontrar os vértices e arestas de corte.

- Foi implementado o **algoritmo de Dijkstra** para:

  - Calcular os **diâmetros** das componentes, considerando grafos ponderados.

## Como compilar e executar

### Compilação:

```bash
    make
```

### Execução:

```bash
    ./teste < entrada.txt
```

Onde entrada.txt contém a definição do grafo.