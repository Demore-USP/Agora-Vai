#ifndef LISTA_H
#define LISTA_H

#include "produto.h"

typedef struct no_lista {
    produto *ponteiro_produto;
    struct no_lista *prox;
} No_Lista;

typedef struct {
    No_Lista *inicio;
    No_Lista *fim;
} Lista;

void inicializar_lista(Lista *);
int lista_vazia(Lista *);
void inserir_produto_no_usuario(Lista *, produto *, int *);
int tamanho_lista(Lista *);
char *devolver_produto(Lista *, int, int *);
void excluir_lista(Lista *, int *);

#endif