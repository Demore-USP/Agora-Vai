#include <stdio.h>
#include <stdlib.h>
#include "PilhaLances.h"

void inicializar_pilha(Pilha *P)
{
    P->topo = NULL;
}

int pilha_vazia(Pilha *P)
{
    if (P->topo == NULL)
        return 1;
    return 0;
}

void empilhar(Pilha *P, Fila *F, float valor, int *erro)
{
    No_Pilha *novo = (No_Pilha *)malloc(sizeof(No_Pilha)); // Aloca memória para um novo Nó
    if (novo == NULL)
    {
        *erro = 1;
        return; // Caso a alocação falhe, retorna e o erro é atualizado
    }

    // O novo lance aponta para o antigo topo, e o ponteiro 'topo'
    // passa a apontar para o novo lance
    novo->valor = valor;
    novo->prox = P->topo;
    inicializar_fila(&novo->fila_usuarios);

    if (!(F == NULL))
    {
        copiar_fila(F, &novo->fila_usuarios, erro);
        if (*erro != 0)
        {
            free(novo);
            return; // Retorna se houver erro ao copiar a fila
        }
    }
    P->topo = novo;

    *erro = 0;
}

float desempilhar(Pilha *P, int *erro)
{
    if (pilha_vazia(P))
    {
        *erro = 1;
        return 0; // Caso a pilha esteja vazia, retorna e o erro é atualizado
    }

    // Buffer que retornará o valor
    float valor = P->topo->valor;

    // Variável auxiliar para apagar o nó
    No_Pilha *aux = P->topo;

    excluir_fila(&P->topo->fila_usuarios, erro);
    P->topo = P->topo->prox; // Ajustando o ponteiro

    free(aux); // Desalocando o nó
    *erro = 0; // Setando o erro
    return valor;
}

float retorna_topo_pilha(Pilha *P, int *erro)
{
    if (pilha_vazia(P))
    {
        *erro = 1;
        return 0; // Caso a pilha esteja vazia, retorna e o erro é atualizado
    }
    *erro = 0;
    return P->topo->valor;
}

void copiar_pilha(Pilha *PO, Pilha *PC, int *erro)
{
    if (pilha_vazia(PO))
    {
        *erro = 1;
        return; // Caso a pilha original esteja vazia, retorna e o erro é atualizado
    }

    // Variável auxiliar para percorrer a pilha original
    No_Pilha *aux = PO->topo;

    // Variável para armazenar o valor do lance
    float valor;

    // Copia os valores da pilha original para a pilha copiada
    while (aux != NULL)
    {
        valor = aux->valor;
        empilhar(PC, &aux->fila_usuarios, valor, erro);
        aux = aux->prox;
    }

    *erro = 0;
}

Fila fila_especifica(Pilha *P, float valor, int *erro) {
    Pilha aux;
    Fila temp;
    inicializar_fila(&temp); // Inicializa 'temp' corretamente

    inicializar_pilha(&aux);
    copiar_pilha(P, &aux, erro);
    if (*erro != 0) {
        excluir_pilha(&aux, erro);
        return temp;
    }

    while (!pilha_vazia(&aux)) {
        if (valor == retorna_topo_pilha(&aux, erro)) {
            copiar_fila(&aux.topo->fila_usuarios, &temp, erro); // Copia a fila de usuários
            if (*erro != 0) {
                excluir_pilha(&aux, erro); // Certifica-se de liberar a pilha auxiliar em caso de erro
                return temp;
            }
            excluir_pilha(&aux, erro);
            return temp;
        }
        desempilhar(&aux, erro);
        if (*erro != 0) {
            excluir_pilha(&aux, erro);
            return temp;
        }
    }

    excluir_pilha(&aux, erro);
    *erro = 1;
    return temp;
}

void excluir_pilha(Pilha *P, int *erro)
{
    if (pilha_vazia(P))
    {
        *erro = 1;
        return; // Caso a pilha esteja vazia, retorna e o erro é atualizado
    }

    // Ponteiros auxiliares
    No_Pilha *atual = P->topo;
    No_Pilha *temp = NULL;

    // Percorre a pilha e libera cada nó
    while (atual != NULL)
    {
        excluir_fila(&P->topo->fila_usuarios, erro);
        temp = atual;        // Guarda o nó atual para liberar
        atual = atual->prox; // Avança para o próximo nó
        free(temp);          // Libera o nó
    }

    P->topo = NULL; // Ajustando o ponteiro
    *erro = 0;      // Setando o erro
}