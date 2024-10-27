#ifndef LISTA_H
#define LISTA_H

#include "produto.h"

// Cada nó armazena um ponteiro para um produto
typedef struct no_lista
{
    produto *ponteiro_produto; // Ponteiro para a struct produto (que contém o nome)
    struct no_lista *prox;
} No_Lista;

// Ponteiros de início e fim da lista
typedef struct
{
    No_Lista *inicio;
    No_Lista *fim;
} Lista;

// Protótipos das funções utilizadas
void inicializar_lista(Lista *);
int lista_vazia(Lista *);
void inserir_produto_no_usuario(Lista *, char *, int *);
int tamanho_lista(Lista *);
char *devolver_produto(Lista *, int, int *);
void excluir_lista(Lista *, int *);

#endif