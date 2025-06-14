#ifndef DFS_H
#define DFS_H
#include "estrutura_grafo.h"
#include "grafo.h"

//----------------------------------------------------------------------------
// Realiza a busca em profundidade recursiva a partir de um vértice,
// calculando tempos de descoberta/finalização, low points, vértices e arestas de corte,
// e verificando bipartição.
void DFS_S(grafo *g, vertice *v, int *tempo);


//----------------------------------------------------------------------------
// Executa a busca em profundidade (DFS) em todo o grafo,
// identificando componentes conexas, cortando arestas/vértices e verificando se o grafo é bipartido.
void DFS(grafo *g);

#endif // DFS_H
