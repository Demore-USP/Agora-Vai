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

// Struct que armazena o nome do produto,
// com os lances dados nele
typedef struct no
{
    // Declaração da struct produto em si (contém o nome de fato e não um ponteiro)
    produto nome_produto;
    char *descricao;
    // Declaração da struct pilha (cada nó guarda um valor e uma fila de ponteiros para usuários)
    Pilha lances;
    struct no *prox;
} No_ListaProduto;

// Ponteiros de início e fim da lista de produtos
typedef struct Lista_produto
{
    No_ListaProduto *ini;
    No_ListaProduto *fim;
} Lista_produto;

// Protótipos das funções utilizadas
void inicializar_lista_produto(Lista_produto *);
int lista_produtos_vazia(Lista_produto *);
void inserir_lista_produto(Lista_produto *, char *, char *, int *);
void inserir_lance_produto(Lista_produto *, Lista_usuario *, char *, float *, char *, int *);
char *devolver_nome_produto(Lista_produto *, int, int *);
char *devolver_descricao_produto(Lista_produto *, int, int *);
Pilha *pilha_especifica(Lista_produto *, char *, int *);
int vencedor_produto(Lista_produto *, char *, char *);
void excluir_lista_produto(Lista_produto *, int *);

#endif