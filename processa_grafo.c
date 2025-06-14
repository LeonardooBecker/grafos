#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processa_grafo.h"

vertice *busca_vertice(grafo *g, char *nome)
{
    for (unsigned int i = 0; i < g->n_vertices; i++)
    {
        if (strcmp(g->vertices[i]->nome, nome) == 0)
        {
            return g->vertices[i];
        }
    }
    return NULL;
}

vertice *cria_vertice(grafo *g, char *nome)
{
    vertice *v = busca_vertice(g, nome);
    if (v)
        return v;

    g->n_vertices = g->n_vertices + 1;

    v = malloc(sizeof(vertice));

    v->nome = malloc(strlen(nome) + 1);
    if (!v || !v->nome)
    {
        fprintf(stderr, "Erro ao alocar memória para o vértice %s.\n", nome);
        destroi_grafo(g);
        return NULL;
    }
    strcpy(v->nome, nome);

    v->vizinhos = NULL;
    v->estado = 0;
    v->componente = 0;

    vertice **lista_vertice = malloc(g->n_vertices * sizeof(vertice *));
    vertice **lista_atual = g->vertices;

    for (unsigned int i = 0; i < g->n_vertices - 1; i++)
    {
        lista_vertice[i] = lista_atual[i];
    }

    lista_vertice[g->n_vertices - 1] = v;
    free(lista_atual);

    // Ordena a lista de vértices em ordem alfabética
    for (unsigned int i = 0; i < g->n_vertices - 1; i++)
    {
        for (unsigned int j = i + 1; j < g->n_vertices; j++)
        {
            if (strcmp(lista_vertice[i]->nome, lista_vertice[j]->nome) > 0)
            {
                vertice *temp = lista_vertice[i];
                lista_vertice[i] = lista_vertice[j];
                lista_vertice[j] = temp;
            }
        }
    }

    g->vertices = lista_vertice;

    return v;
}

void adiciona_aresta(grafo *g, char *nome1, char *nome2, unsigned int peso)
{
    vertice *v1 = cria_vertice(g, nome1);
    vertice *v2 = cria_vertice(g, nome2);

    vizinho *novo1 = malloc(sizeof(vizinho));
    novo1->v = v2;
    novo1->peso = peso;
    novo1->prox = v1->vizinhos;
    v1->vizinhos = novo1;

    vizinho *novo2 = malloc(sizeof(vizinho));
    novo2->v = v1;
    novo2->peso = peso;
    novo2->prox = v2->vizinhos;
    v2->vizinhos = novo2;

    g->n_arestas++;
}


grafo *processa_entrada(FILE *f)
{
    grafo *g = malloc(sizeof(grafo));
    g->nome = NULL;
    g->vertices = NULL;
    g->n_vertices = 0;
    g->n_arestas = 0;
    g->n_componentes = 0;

    char linha[MAX_LINHA];

    while (!feof(f))
    {
        if (fgets(linha, MAX_LINHA, f) == NULL)
            break;
        if (linha[0] == '/' && linha[1] == '/')
            continue;

        linha[strcspn(linha, "\n")] = 0;
        if (strlen(linha) == 0)
            continue;

        // printf("%s\n", linha);

        if (!g->nome)
        {
            g->nome = malloc(strlen(linha) + 1);
            if (!g->nome)
            {
                fprintf(stderr, "Erro ao alocar memória para o nome do grafo.\n");
                destroi_grafo(g);
                return NULL;
            }
            strcpy(g->nome, linha);
            continue;
        }

        char v1[256], v2[256];
        unsigned int peso = 1;
        if (sscanf(linha, "%255s -- %255s %d", v1, v2, &peso) < 2)
        {
            if (sscanf(linha, "%255s -- %255s", v1, v2) == 2)
            {
                peso = 1;
                adiciona_aresta(g, v1, v2, peso);
            }
            if (sscanf(linha, "%255s", v1) == 1)
            {
                cria_vertice(g, v1);
            }
        }
        else
        {
            adiciona_aresta(g, v1, v2, peso);
        }
    }

    return g;
}

void imprime_lista_vertice(grafo *g)
{
    for (unsigned int i = 0; i < g->n_vertices; i++)
    {
        vertice *v = g->vertices[i];
        printf("Vértice: %s\n", v->nome);
        printf("estado: %d\n", v->estado);
        printf("Componente: %d\n", v->componente);
        printf("Vizinhos: ");
        vizinho *vaux = v->vizinhos;
        while (vaux)
        {
            printf("%s (%d) ", vaux->v->nome, vaux->peso);
            vaux = vaux->prox;
        }
        printf("\n");
        if (v->pai == NULL)
            printf("Pai: Raiz\n");
        else
            printf("Pai: %s\n", v->pai->nome);
        printf("Distância da raiz: %d\n", v->distancia_raiz);
        printf("\n");
    }
}
