#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"
#include "processa_grafo.h"
#include "fila.h"
#include "dijkstra.h"
#include "dfs.h"
#include "estrutura_grafo.h"

//----------------------------------------------------------------------------
grafo *le_grafo(FILE *file)
{
    grafo *g = processa_entrada(file);
    g->eh_bipartido = 1;

    DFS(g);

    // for (unsigned int i = 0; i < g->n_vertices; i++)
    // {
    //     vertice *v = g->vertices[i];
    //     printf("Vértice %s: nivel=%d, pre=%d, pos=%d, low=%d\n",
    //            v->nome, v->nivel, v->pre, v->pos, v->low);
    // }

    return g;
}

//----------------------------------------------------------------------------
unsigned int destroi_grafo(grafo *g)
{
    if (!g)
        return 0;
    for (unsigned int i = 0; i < g->n_vertices; i++)
    {
        free(g->vertices[i]->nome);
        vizinho *v = g->vertices[i]->vizinhos;
        while (v)
        {
            vizinho *tmp = v;
            v = v->prox;
            free(tmp);
        }
        free(g->vertices[i]);
    }
    free(g->vertices);
    free(g->nome);
    free(g);
    return 1;
}

//----------------------------------------------------------------------------
char *nome(grafo *g)
{
    if (g != NULL)
        return g->nome;
    else
        return NULL;
}

//----------------------------------------------------------------------------
unsigned int n_vertices(grafo *g)
{
    if (g != NULL)
        return g->n_vertices;
    else
        return 0;
}

//----------------------------------------------------------------------------
unsigned int n_arestas(grafo *g)
{
    if (g != NULL)
        return g->n_arestas;
    else
        return 0;
}

//----------------------------------------------------------------------------
unsigned int n_componentes(grafo *g)
{
    if (g != NULL)
        return g->n_componentes;
    else
        return 0;
}

unsigned int bipartido(grafo *g)
{
    if (g != NULL)
        return g->eh_bipartido;
    else
        return 0;
}

char *diametros(grafo *g){
    if(g != NULL)
        return diametros_dijkstra(g);
    else
        return NULL;
}

char *vertices_corte(grafo *g)
{
    size_t tamanho_maximo = (MAX_LINHA * g->total_vertice_corte) + 1;
    char *vertices_corte = malloc(tamanho_maximo);
    if (vertices_corte == NULL)
    {
        fprintf(stderr, "Erro ao alocar memoria\n");
        exit(1);
    }
    vertices_corte[0] = '\0'; // Inicia com string vazia

    for (unsigned int i = 0; i < g->n_vertices; i++)
    {
        if (g->vertices[i]->eh_corte)
        {
            strncat(vertices_corte, g->vertices[i]->nome, tamanho_maximo - strlen(vertices_corte) - 1);
            strncat(vertices_corte, " ", tamanho_maximo - strlen(vertices_corte) - 1);
        }
    }

    // Remove o espaço extra no final da string vertices_corte, se existir
    size_t len = strlen(vertices_corte);
    if (len > 0 && vertices_corte[len - 1] == ' ')
    {
        vertices_corte[len - 1] = '\0';
    }

    return vertices_corte;
}

char *arestas_corte(grafo *g)
{
    size_t tamanho_maximo = (MAX_LINHA * g->total_aresta_corte) + 1;
    char *arestas_corte = malloc(tamanho_maximo);
    if (arestas_corte == NULL)
    {
        fprintf(stderr, "Erro ao alocar memoria\n");
        exit(1);
    }
    arestas_corte[0] = '\0'; // Inicia com string vazia

    for (unsigned int i = 0; i < g->n_vertices; i++)
    {
        vizinho *v = g->vertices[i]->vizinhos;
        while (v)
        {
            if (v->eh_corte)
            {
                if (strcmp(g->vertices[i]->nome, v->v->nome) < 0)
                {
                    char buffer[MAX_LINHA];
                    snprintf(buffer, sizeof(buffer), "%s %s ", g->vertices[i]->nome, v->v->nome);
                    strncat(arestas_corte, buffer, tamanho_maximo - strlen(arestas_corte) - 1);
                }
            }
            v = v->prox;
        }
    }

    // Remove o espaço extra no final da string arestas_corte, se existir
    size_t len = strlen(arestas_corte);
    if (len > 0 && arestas_corte[len - 1] == ' ')
    {
        arestas_corte[len - 1] = '\0';
    }

    return arestas_corte;
}
