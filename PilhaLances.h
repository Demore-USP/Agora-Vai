#ifndef PILHALANCES_H
#define PILHALANCES_H

#include "Fila.h"

/* Struct que armazena um valor de um lance e uma fila de ponteiros
para quaisquer usuarios que deram um lance deste mesmo valor */  
typedef struct no_pilha
{
    float valor;
    Fila fila_usuarios; // Fila de ponteiros para usuários
    struct no_pilha *prox;
} No_Pilha;

// Ponteiro topo (sempre aponta pro lance mais alto)
typedef struct Pilha
{
    No_Pilha *topo;
} Pilha;

// Protótipo das funções utilizadas
void inicializar_pilha(Pilha *);
int pilha_vazia(Pilha *);
void empilhar(Pilha *, Fila *, float, int *);
float desempilhar(Pilha *, int *);
float retorna_topo_pilha(Pilha *, int *);
void copiar_pilha(Pilha *, Pilha *, int *);
Fila fila_especifica(Pilha *, float, int *);
void excluir_pilha(Pilha *, int *);

#endif