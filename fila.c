// Fila em C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"
#include "grafo.h"

//------------------------------------------------------------------------------
fila *cria_fila(unsigned int capacidade)
{
    fila *f = malloc(sizeof(fila));
    f->fim = 0;
    f->capacidade = capacidade;
    f->inicio = NULL;
    return f;
}

void destroi_fila(fila *f)
{
    if (f == NULL)
        return;

    nodo_fila *atual = f->inicio;
    while (atual != NULL)
    {
        nodo_fila *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    free(f);
}

void enfileira(fila *f, vertice *v)
{
    if (f == NULL || f->fim >= f->capacidade)
        return;

    nodo_fila *novo = malloc(sizeof(nodo_fila));
    novo->proximo = NULL;
    novo->vertice = v;

    if (f->inicio == NULL)
    {
        f->inicio = novo;
    }
    else
    {
        nodo_fila *atual = f->inicio;
        while (atual->proximo != NULL)
        {
            atual = atual->proximo;
        }
        atual->proximo = novo;
    }
    f->fim++;
}

void enfileira_ordenado(fila *f, vertice *v, unsigned int peso)
{
    if (f->fim >= f->capacidade)
    {
        return;
    }

    nodo_fila *novo = malloc(sizeof(nodo_fila));
    if (!novo)
        return;

    novo->vertice = v;
    novo->peso = peso;
    novo->proximo = NULL;

    // Caso 1: Fila vazia ou novo peso menor que o primeiro
    if (f->inicio == NULL || peso < f->inicio->peso)
    {
        novo->proximo = f->inicio;
        f->inicio = novo;
        f->fim++;
        return;
    }

    // Caso 2: Inserir no meio ou final
    nodo_fila *atual = f->inicio;
    while (atual->proximo != NULL && atual->proximo->peso <= peso)
    {
        atual = atual->proximo;
    }

    novo->proximo = atual->proximo;
    atual->proximo = novo;
    f->fim++;
}

vertice *desenfileira(fila *f)
{
    if (f == NULL || f->inicio == NULL)
        return NULL; // Fila vazia

    nodo_fila *temp = f->inicio;
    vertice *v = temp->vertice;
    f->inicio = temp->proximo;
    free(temp);
    f->fim--;

    return v;
}

void corrige_fila(fila *f, vertice *v, unsigned int novo_peso)
{
    if (f == NULL || f->inicio == NULL)
        return;

    nodo_fila *atual = f->inicio;
    nodo_fila *anterior = NULL;

    while (atual != NULL)
    {
        if (atual->vertice == v)
        {
            if (anterior != NULL)
            {
                anterior->proximo = atual->proximo;
            }
            else
            {
                f->inicio = atual->proximo;
            }
            free(atual);
            f->fim--;

            enfileira_ordenado(f, v, novo_peso);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    return;
}

int fila_vazia(fila *f)
{
    return f == NULL || f->inicio == NULL;
}

void imprime_fila(fila *f)
{
    if (fila_vazia(f))
    {
        return;
    }

    nodo_fila *atual = f->inicio;
    printf("Fila: ");
    while (atual != NULL)
    {
        printf("%s (%d),", atual->vertice->nome, atual->peso);
        atual = atual->proximo;
    }
    printf("\n");
}