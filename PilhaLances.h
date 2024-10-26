#ifndef PILHALANCES_H
#define PILHALANCES_H

#include "Fila.h"

// Struct que armazena o valor do lance e a fila de usuarios que deram aquele lance
typedef struct no_pilha {
    float valor;
    Fila fila_usuarios;
    struct no_pilha *prox;
} No_Pilha;

// Ponteiro topo da Pilha (sempre aponta pro lance mais alto)
typedef struct Pilha {
    No_Pilha *topo;
} Pilha;

void inicializar_pilha(Pilha *);
int pilha_vazia(Pilha *);
void empilhar(Pilha *, float, int *);
float desempilhar(Pilha *, int *); 
void copiar_pilha(Pilha *, Pilha *, int *);
Fila fila_especifica(Pilha *, float, int *);
void excluir_pilha(Pilha *, int *);

#endif