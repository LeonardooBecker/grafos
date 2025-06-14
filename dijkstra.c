#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "dijkstra.h"

#define INFINITO UINT_MAX

void dijkstra(grafo *g, vertice *raiz)
{
    for (unsigned int i = 0; i < g->n_vertices; i++)
    {
        g->vertices[i]->estado = 0;
        g->vertices[i]->custo = INFINITO;
        g->vertices[i]->pai = NULL;
    }

    raiz->custo = 0;
    fila *f = cria_fila(g->n_vertices);
    enfileira_ordenado(f, raiz, raiz->custo);
    raiz->estado = 1;

    while (!fila_vazia(f))
    {
        vertice *v = desenfileira(f);
        v->estado = 2;

        vizinho *u = v->vizinhos;
        while (u != NULL)
        {
            vertice *w = u->v;
            unsigned int peso_aresta = u->peso;

            if (w->estado == 0)
            {
                w->custo = v->custo + peso_aresta;
                w->pai = v;
                enfileira_ordenado(f, w, w->custo);
                w->estado = 1;
            }
            else if (w->estado == 1 && v->custo + peso_aresta < w->custo)
            {
                w->custo = v->custo + peso_aresta;
                w->pai = v;
                corrige_fila(f, w, w->custo);
            }

            u = u->prox;
        }
    }

    destroi_fila(f);
}

char *diametros_dijkstra(grafo *g)
{
    unsigned int *diametros = malloc(sizeof(unsigned int) * g->n_vertices);

    // Calcula diâmetro de cada componente
    for (unsigned int comp = 1; comp <= g->n_componentes; comp++)
    {
        unsigned int diametro = 0;

        for (unsigned int i = 0; i < g->n_vertices; i++)
        {
            if (g->vertices[i]->componente == comp)
            {
                dijkstra(g, g->vertices[i]);

                for (unsigned int j = 0; j < g->n_vertices; j++)
                {
                    if (g->vertices[j]->componente == comp && g->vertices[j]->custo != INFINITO)
                    {
                        if (g->vertices[j]->custo > diametro)
                        {
                            diametro = g->vertices[j]->custo;
                        }
                    }
                }
            }
        }

        diametros[comp - 1] = diametro;
    }

    // Ordena os diâmetros em ordem crescente
    for (unsigned int i = 0; i < g->n_componentes - 1; i++)
    {
        for (unsigned int j = i + 1; j < g->n_componentes; j++)
        {
            if (diametros[i] > diametros[j])
            {
                unsigned int temp = diametros[i];
                diametros[i] = diametros[j];
                diametros[j] = temp;
            }
        }
    }

    // Concatena os diâmetros em uma única string
    unsigned int tamanho_maximo = MAX_LINHA * g->n_componentes + 1;
    char *resultado = malloc(tamanho_maximo); // Aloca espaço suficiente para a string
    if(!resultado)
    {
        fprintf(stderr, "Erro ao alocar memória para a string de diâmetros.\n");
        free(diametros);
        return NULL;
    }

    resultado[0] = '\0'; // Inicializa a string vazia

    for (unsigned int i = 0; i < g->n_componentes; i++)
    {
        char buffer[MAX_LINHA];
        snprintf(buffer, sizeof(buffer), "%u", diametros[i]);
        strcat(resultado, buffer);
        if (i < g->n_componentes - 1)
        {
            strcat(resultado, " ");
        }
    }

    free(diametros);

    // Retorna a string contendo os diâmetros
    return resultado;
}
