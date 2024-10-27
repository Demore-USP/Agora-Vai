#ifndef FILA_H
#define FILA_H

#include "usuario.h"

// Struct onde cada nó armazena um ponteiro para um usuário 
typedef struct no_fila
{
    usuario *ponteiro_usuario; // Ponteiro para a struct usuário (que contém o nome)
    struct no_fila *prox;
} No_fila;

// Ponteiros de início e fim da fila
typedef struct Fila
{
    No_fila *inicio;
    No_fila *fim;
} Fila;

// Protótipos das funções utilizadas
void inicializar_fila(Fila *);
int fila_vazia(Fila *);
void inserir_na_fila(Fila *, char *, int *);
int esta_na_fila(Fila *, char *, int *);
char *remover_da_fila(Fila *, int *);
char *retorna_inicio_fila(Fila, int *);
int tamanho_fila(Fila *);
void copiar_fila(Fila *, Fila *, int *);
void excluir_fila(Fila *, int *);

#endif