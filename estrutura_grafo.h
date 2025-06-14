#ifndef ESTRUTURA_GRAFO_H
#define ESTRUTURA_GRAFO_H

#define MAX_LINHA 2048

// estrutura para um vértice
typedef struct vertice
{
    char *nome;
    struct vizinho *vizinhos; // lista de adjacência
    int estado;
    unsigned int componente;
    int distancia_raiz;
    unsigned int custo;
    struct vertice *pai;

    int nivel;
    int pre;
    int pos;
    int low;

    int eh_corte;

    int cor;
} vertice;

// estrutura para vizinhos (lista de adjacência)
typedef struct vizinho
{
    vertice *v;
    unsigned int peso;
    struct vizinho *prox;
    int eh_corte;
} vizinho;


// estrutura do grafo
struct grafo
{
    char *nome;
    vertice **vertices;
    unsigned int n_vertices;
    unsigned int n_arestas;
    unsigned int n_componentes;
    unsigned int eh_bipartido;

    unsigned int total_vertice_corte;
    unsigned int total_aresta_corte;
};

#endif