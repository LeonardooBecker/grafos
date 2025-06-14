#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dfs.h"


void DFS_S(grafo *g, vertice *v, int *tempo)
{
    v->estado = 1;
    (*tempo)++;
    v->pre = *tempo;
    v->low = v->pre;
    v->componente = g->n_componentes + 1;

    int filhos = 0;

    vizinho *u = v->vizinhos;
    while (u != NULL)
    {
        if ((u->v->estado == 1) && (u->v != v->pai))
        {
            if (u->v->pre < v->low)
            {
                v->low = u->v->pre;
            }
            if (u->v->cor == v->cor)
            {
                g->eh_bipartido = 0;
            }
        }
        else if (u->v->estado == 0)
        {
            filhos++;

            u->v->pai = v;
            u->v->nivel = v->nivel + 1;
            u->v->cor = 1 - v->cor;

            DFS_S(g, u->v, tempo);

            if (u->v->low < v->low)
            {
                v->low = u->v->low;
            }

            if (u->v->low > (v->pre))
            {
                u->eh_corte = 1;
                g->total_aresta_corte++;

                vizinho *back = u->v->vizinhos;
                while (back != NULL)
                {
                    if (back->v == v)
                    {
                        back->eh_corte = 1;
                    }
                    back = back->prox;
                }
            }
        }

        u = u->prox;
    }

    // Verifica vértice de corte (não raiz)
    if (v->pai != NULL)
    {
        vizinho *u2 = v->vizinhos;
        while (u2 != NULL)
        {
            if ((u2->v != v->pai) && (u2->v->low >= v->pre))
            {
                v->eh_corte = 1;
                g->total_vertice_corte++;
                break;
            }
            u2 = u2->prox;
        }
    }

    // Verifica vértice de corte (raiz com múltiplos filhos)
    if (v->pai == NULL)
    {
        if (filhos > 1)
        {
            v->eh_corte = 1;
            g->total_vertice_corte++;
        }
    }

    (*tempo)++;
    v->pos = *tempo;
    v->estado = 2;
}


void DFS(grafo *g)
{
    int tempo = 0;
    g->eh_bipartido = 1;
    g->total_aresta_corte = 0;
    g->total_vertice_corte = 0;

    for (unsigned int i = 0; i < g->n_vertices; i++)
    {
        vertice *v = g->vertices[i];
        v->estado = 0;
        v->cor = -1;
        v->pai = NULL;
        v->nivel = 0;
        v->pre = -1;
        v->pos = -1;
        v->low = -1;
        v->eh_corte = 0;

        vizinho *u = v->vizinhos;
        while (u != NULL)
        {
            u->eh_corte = 0;
            u = u->prox;
        }
    }

    g->n_componentes = 0;

    for (unsigned int i = 0; i < g->n_vertices; i++)
    {
        if (g->vertices[i]->estado == 0)
        {
            DFS_S(g, g->vertices[i], &tempo);
            g->n_componentes++;
        }
    }
}
