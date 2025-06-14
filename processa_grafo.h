#ifndef PROCESSA_GRAFO_H
#define PROCESSA_GRAFO_H
#include "estrutura_grafo.h"
#include "grafo.h"

//------------------------------------------------------------------------------
// Busca um vértice no grafo pelo nome.
// Retorna o ponteiro para o vértice se encontrado, ou NULL caso contrário.
vertice *busca_vertice(grafo *g, char *nome);

//------------------------------------------------------------------------------
// Cria um novo vértice no grafo, caso ainda não exista.
// Insere o vértice na lista de vértices mantendo a ordem alfabética.
// Retorna o ponteiro para o vértice criado ou existente.
vertice *cria_vertice(grafo *g, char *nome);

//------------------------------------------------------------------------------
// Adiciona uma aresta não-direcionada (grafo não orientado) entre dois vértices,
// criando os vértices se necessário.
// Também incrementa o contador total de arestas do grafo.
void adiciona_aresta(grafo *g, char *nome1, char *nome2, unsigned int peso);

//------------------------------------------------------------------------------
// Lê e processa um grafo a partir de um arquivo de entrada no formato texto.
// A primeira linha é o nome do grafo. As linhas seguintes são vértices isolados
// ou arestas (com ou sem pesos). Ignora linhas de comentário iniciadas com "//".
// Retorna um ponteiro para a estrutura grafo preenchida.
grafo *processa_entrada(FILE *f);

//------------------------------------------------------------------------------
// Imprime na saída padrão todas as informações dos vértices do grafo,
// incluindo nome, estado de visita, número da componente conexa, vizinhos,
// pai na árvore de busca e distância até a raiz.
// Útil para fins de depuração.
void imprime_lista_vertice(grafo *g);

#endif // PROCESSA_GRAFO_H
