#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include "estrutura_grafo.h"
#include "fila.h"
#include "grafo.h"

//----------------------------------------------------------------------------
// Executa o algoritmo de Dijkstra a partir de um vértice raiz,
// calculando o custo mínimo (menor distância ponderada) até todos os outros vértices do grafo.
void dijkstra(grafo *g, vertice *raiz);

//----------------------------------------------------------------------------
// Calcula o diâmetro de cada componente conexo do grafo usando Dijkstra,
// ordena os diâmetros em ordem crescente e retorna uma string com os valores separados por espaço.
char *diametros_dijkstra(grafo *g);

#endif // DIJKSTRA_H
