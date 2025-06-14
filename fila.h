#ifndef FILA_H
#define FILA_H
#include "estrutura_grafo.h"


typedef struct nodo_fila
{
    vertice *vertice;
    struct nodo_fila *proximo;
    unsigned int peso;
} nodo_fila;

typedef struct fila
{
    struct nodo_fila *inicio;
    unsigned int fim;
    unsigned int capacidade;
} fila;

//----------------------------------------------------------------------------
// Cria e inicializa uma nova fila com a capacidade especificada.
fila *cria_fila(unsigned int capacidade);

//----------------------------------------------------------------------------
// Libera toda a memória alocada para a fila, incluindo seus nós internos.
void destroi_fila(fila *f);

//----------------------------------------------------------------------------
// Insere um vértice no final da fila (sem considerar prioridade).
void enfileira(fila *f, vertice *v);

//----------------------------------------------------------------------------
// Insere um vértice na fila de forma ordenada pelo peso (menor peso primeiro).
void enfileira_ordenado(fila *f, vertice *v, unsigned int peso);

//----------------------------------------------------------------------------
// Remove e retorna o vértice que está no início da fila.
vertice *desenfileira(fila *f);

//----------------------------------------------------------------------------
// Atualiza a posição de um vértice na fila após mudança de peso,
// garantindo que a fila permaneça ordenada.
void corrige_fila(fila *f, vertice *v, unsigned int novo_peso);

//----------------------------------------------------------------------------
// Retorna 1 se a fila estiver vazia, ou 0 caso contrário.
int fila_vazia(fila *f);

//----------------------------------------------------------------------------
// Imprime o conteúdo da fila na saída padrão (usado para debug).
void imprime_fila(fila *f);

#endif // FILA_H