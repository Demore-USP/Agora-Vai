#include <stdio.h>
#include <stdlib.h>
#include "PilhaLances.h"

void inicializar_pilha(Pilha *P) {
    P->topo = NULL;
}

int pilha_vazia(Pilha *P) {
    if(P->topo == NULL)
        return 1;
    return 0;
}

void empilhar(Pilha *P, float valor, int *erro) {
    No_Pilha *novo = (No_Pilha *)malloc(sizeof(No_Pilha)); // Aloca memória para um novo Nó
    if (novo == NULL) {
        *erro = 1;
        return; // Caso a alocação falhe, retorna e o erro é atualizado
    }

    // O novo lance aponta para o antigo topo, e o ponteiro 'topo'
    // passa a apontar para o novo lance
    novo->valor = valor;
    novo->prox = P->topo;
    P->topo = novo;

    inicializar_fila(&novo->fila_usuarios);

    *erro = 0;
}

float desempilhar(Pilha *P, int *erro) {
    if (pilha_vazia(P)) {
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

void copiar_pilha(Pilha *PO, Pilha *PC, int *erro){
    if (pilha_vazia(PO)) {
        *erro = 1;
        return; // Caso a pilha original esteja vazia, retorna e o erro é atualizado
    }

    // Inicializa a pilha copiada
    inicializar_pilha(PC);

    // Variável auxiliar para percorrer a pilha original
    No_Pilha *aux = PO->topo;

    // Variável para armazenar o valor do lance
    float valor;

    // Copia os valores da pilha original para a pilha copiada
    while (aux != NULL) {
        valor = aux->valor;
        empilhar(PC, valor, erro);
        aux = aux->prox;
    }

    *erro = 0;
}

void excluir_pilha(Pilha *P, int *erro);