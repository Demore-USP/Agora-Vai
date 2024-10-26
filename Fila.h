#ifndef FILA_H
#define FILA_H

#include "usuario.h"

// Struct que armazena um ponteiro pra ponteiro com o nome dos usuarios encadeados
typedef struct no_fila {
    usuario *ponteiro_usuario;
    struct no_fila *prox;
} No_fila;

typedef struct Fila {
    No_fila *inicio;
    No_fila *fim;
} Fila;

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