#ifndef LISTAPRODUTO_H
#define LISTAPRODUTO_H

#include "PilhaLances.h"
#include "Fila.h"
#include "produto.h"
#include "ListaUsuario.h"

// Erros:
// 1- Erro ao alocar memória
// 2- Produto não encontrado
// 3- Produto já existente
// 4- Lance não válido

// Struct que armazena o produto, com seus respectivos lances
typedef struct no
{
    produto nome_produto;
    Pilha lances;
    struct no *prox;
} No_ListaProduto;

// Ponteiros de início e fim da lista de produtos
typedef struct Lista_produto
{
    No_ListaProduto *ini;
    No_ListaProduto *fim;
} Lista_produto;

void inicializar_lista_produto(Lista_produto *);
void inserir_lista_produto(Lista_produto *, char *, int *);
void inserir_lance_produto(Lista_produto *, Lista_usuario *, char *, float *, char *, int *);
char *devolver_nome_produto(Lista_produto *, int, int *);
Pilha *pilha_especifica(Lista_produto *, char *, int *);
int vencedor_produto(Lista_produto *, char *, char *);
void excluir_lista_produto(Lista_produto *, int *);

#endif